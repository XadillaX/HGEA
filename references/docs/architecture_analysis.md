# HGE 游戏引擎源码架构深度分析报告（函数级）

HGE (Haaf's Game Engine) 是一款经典的轻量级 2D 硬件加速游戏引擎，其底层基于 Direct3D 8 和 BASS 音频库。引擎源码结构清晰，主要分为 **Core（核心模块）** 与 **Helpers（辅助类）** 两大部分。

以下是对其源码的深度剖析：

## **一、 Core 核心模块**

核心模块的实现集中在单例类 `HGE_Impl` 中，它封装了所有的底层 API 交互。

### **1. System (系统模块)**
负责引擎的初始化、窗口管理以及主循环的驱动。

*   **主循环逻辑 (`System_Start`)**:
    在 [system.cpp](file:///Users/bytedance/Workspace/github/HGEA/references/HGE/src/core/system.cpp) 中，`System_Start` 包含一个 `for(;;)` 无限循环。
    *   **消息处理**: 通过 `PeekMessage` 处理 Windows 系统消息，如果收到 `WM_QUIT` 则退出循环。
    *   **帧率控制**: 计算当前时间与上一帧的时间差 `dt`。如果 `dt` 达到了 `nFixedDelta`（固定帧率的时间间隔），则计算实际的 `fDeltaTime` 并限制最大增量（避免断点导致的大幅跳跃）。
    *   **逻辑回调**: 调用用户注册的 `procFrameFunc()` 进行逻辑更新，如果其返回 `true`，则打破主循环退出游戏。随后调用 `procRenderFunc()` 进行画面渲染。
*   **启动屏逻辑 (`DFrame`)**:
    在 [demo.cpp](file:///Users/bytedance/Workspace/github/HGEA/references/HGE/src/core/demo.cpp#L191-L214) 中，`DFrame` 是 HGE 自带的 Splash Screen 的帧逻辑。
    *   它通过累加 `dtime` 变量来计算阶段：前 0.25 秒淡入，中间保持，1.0 到 1.25 秒淡出。
    *   将计算出的 `alpha` 值位移后赋给 `dquad` 四边形的顶点颜色，调用 `Gfx_RenderQuad` 绘制 Logo。当时间超过 1.25 秒时，返回 `true` 通知引擎结束启动屏循环，进入真正的游戏逻辑。

### **2. Graphics (图形渲染模块)**
对 Direct3D 8 的 2D 渲染封装。

*   **数据结构**: 核心图元数据结构为 `hgeVertex`（包含 x, y, z, diffuse 颜色和 tx, ty 纹理坐标）和 `hgeQuad`。
*   **批处理渲染 (`_render_batch`)**:
    引擎维护了一个固定大小的全局顶点数组 `VertArray`。在调用 `Gfx_RenderQuad` 或 `Gfx_RenderLine` 时，引擎不会立刻绘制，而是比较当前的纹理（`CurTexture`）、混合模式（`CurBlendMode`）和图元类型。如果状态相同，顶点将被累加到数组中。只有当状态改变或缓冲区满时，才会统一调用 D3D 的 `DrawPrimitive` 或 `DrawIndexedPrimitive` 提交渲染，极大减少了 Draw Call。
*   **纹理锁定 (`Texture_Lock`)**:
    *   [graphics.cpp](file:///Users/bytedance/Workspace/github/HGEA/references/HGE/src/core/graphics.cpp#L504-L535) 中的 `Texture_Lock` 函数负责显存级像素操作。
    *   它将 `HTEXTURE` 强制转换为 `LPDIRECT3DTEXTURE8`，通过 `GetLevelDesc` 校验纹理格式是否为 `D3DFMT_A8R8G8B8` 等 32 位格式。
    *   接着封装 `RECT` 结构（如果指定了区域），并调用 D3D 原生的 `pTex->LockRect()`。
    *   返回 `TRect.pBits` 指针，允许开发者直接在 CPU 端修改纹理像素。修改完毕后需调用 `Texture_Unlock` 释放锁定。

### **3. Resource (资源管理模块)**
提供透明的文件/压缩包资源加载能力。

*   **数据结构**: 使用链表 `CResourceList` 存储挂载的资源包（ZIP）路径和对应的解压密码。
*   **与 ZIP 结合的 `Resource_AttachPack`**:
    *   引擎内置了 ZLIB / Minizip 库。
    *   [resource.cpp](file:///Users/bytedance/Workspace/github/HGEA/references/HGE/src/core/resource.cpp#L17-L44) 中的 `Resource_AttachPack` 调用 `unzOpen` 测试 ZIP 文件是否有效。如果有效，创建一个 `CResourceList` 节点插入全局链表表头。
*   **读取策略 (`Resource_Load`)**:
    *   当加载文件时，引擎优先遍历资源包链表。使用 `unzGoToFirstFile` 和 `unzGetCurrentFileInfo` 逐一对比压缩包内的文件名。
    *   命中后，调用 `unzOpenCurrentFilePassword` 处理可能的加密，然后根据压缩前大小 `malloc` 内存，并用 `unzReadCurrentFile` 将数据解压到内存返回。
    *   如果所有包中都找不到文件，则回退到普通的 Windows API (`CreateFile` / `ReadFile`) 直接读取本地文件。

### **4. Audio (音频模块)**
封装了 BASS 动态链接库。

*   通过动态加载 `bass.dll` 并获取函数指针（`GetProcAddress`）进行初始化。
*   区分了短促音效 (`Effect` - `BASS_SampleLoad`)、长背景音乐 (`Music` - `BASS_MusicLoad`，主要针对 MOD/XM 等 Tracker 格式) 和音频流 (`Stream` - `BASS_StreamCreateFile`，针对 MP3/OGG)。

### **5. Input (输入处理模块)**
统一的键盘、鼠标事件管理。

*   在 `WindowProc` 中拦截 `WM_KEYDOWN`、`WM_LBUTTONDOWN`、`WM_MOUSEMOVE` 等系统消息。
*   调用内部方法 `_BuildEvent` 翻译系统按键码，将其转化为 `hgeInputEvent` 结构，并推入由 `CInputEventList` 构成的链表队列中。
*   提供状态数组 `keyz` 用于快速查询 `Input_KeyDown`（按键是否处于按下瞬间）或 `Input_GetKeyState`（当前物理状态）。

---

## **二、 Helpers 辅助类**

Helpers 建立在 Core 接口之上，为游戏开发提供更高阶的抽象。

### **1. Sprite (精灵类)**
*   **数据结构**: 内部持有一个 `hgeQuad` 实例。存储了热点（`hotX`, `hotY`），即旋转和缩放的锚点。
*   **核心算法**: [hgesprite.cpp](file:///Users/bytedance/Workspace/github/HGEA/references/HGE/src/helpers/hgesprite.cpp) 中的 `RenderEx` 函数处理复杂的 2D 变换。计算时首先将四边形的四个角坐标平移到以热点为原点的局部坐标系中，乘以缩放系数 `hscale`/`vscale`，然后通过预先计算的 `sinf(rot)` 和 `cosf(rot)` 应用 2D 旋转矩阵公式，最后平移到屏幕目标位置 `(x, y)` 并交给 `Gfx_RenderQuad` 渲染。

### **2. Anim (动画类)**
*   **数据结构**: 继承自 `hgeSprite`。额外维护了帧数 `nFrames`、帧率速度 `fSpeed`、播放模式（如正向、反弹 PingPong、循环）以及时间累加器 `fSinceLastFrame`。
*   **核心算法**: `Update` 函数根据传入的 `fDeltaTime` 累加时间。当累加器超过单帧时长 `fSpeed` 时，触发帧切换逻辑。通过 `SetFrame` 函数，利用当前帧号和精灵的宽高，动态计算并更新 `hgeQuad` 四个顶点的 UV 坐标 (`tx`, `ty`)，从而在同一张纹理上实现帧动画播放。

### **3. GUI (图形用户界面)**
*   **系统架构**: 基于对象模型的设计。`hgeGUI` 作为管理器，维护一个双向链表管理所有的 `hgeGUIObject`（控件基类）。
*   **事件分发**: 在 `hgeGUI::Update` 中，引擎获取当前鼠标位置，按 Z-Order 从顶到底遍历控件，调用包围盒检测 `rect.TestPoint`。捕获到的鼠标事件（点击、移动、滚轮）将路由调用控件的虚拟方法（如 `MouseLButton`）。同时它也维护了键盘导航（Tab、方向键切换 Focus）的逻辑。
*   **内置控件**: `hgeguictrls.cpp` 实现了诸如 `hgeGUIButton`（内部包含 Up/Down 两个 Sprite 切换渲染状态）、`hgeGUISlider`（基于鼠标拖拽改变浮点数值映射）等标准控件，开发者通过继承 `hgeGUIObject` 可以轻易实现自定义控件。