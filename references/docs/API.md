# HGE API Reference

本文档介绍了 HGE 引擎核心头文件 `hge.h` 中的关键 API 接口。

## 🔧 初始化与生命周期 (System)

| 方法 | 说明 |
| :--- | :--- |
| `hgeCreate(int ver)` | 获取 HGE 引擎的单例接口实例。参数必须是 `HGE_VERSION`。 |
| `System_SetState(...)` | 配置引擎初始化参数，包括 `HGE_WINDOWED`, `HGE_FRAMEFUNC` (必须), `HGE_RENDERFUNC` 等。 |
| `System_Initiate()` | 根据之前设置的状态，初始化硬件环境 (创建窗口、D3D 设备、音频引擎等)。 |
| `System_Start()` | 启动引擎主循环。该函数会阻塞，直到 `HGE_FRAMEFUNC` 回调返回 `true`。 |
| `System_Shutdown()` | 释放引擎所有子系统资源，销毁窗口。 |
| `Release()` | 递减引擎的引用计数，并在为 0 时销毁单例实例。 |

## 🎨 图形与渲染 (Graphics)

| 方法 | 说明 |
| :--- | :--- |
| `Gfx_BeginScene(...)` | 开始渲染一帧。可以传入一个渲染目标 `HTARGET`，默认为屏幕。 |
| `Gfx_EndScene()` | 结束渲染并交换缓冲区 (Present)，将画面显示到屏幕上。 |
| `Gfx_Clear(DWORD color)` | 用指定的颜色清空当前渲染目标。 |
| `Gfx_RenderQuad(const hgeQuad *quad)` | 渲染一个带纹理和颜色的四边形。HGE 内部会自动对其进行 Batching。 |
| `Texture_Load(...)` | 从文件或资源包中加载图像并创建 2D 纹理，返回 `HTEXTURE` 句柄。 |
| `Texture_Free(HTEXTURE tex)` | 释放纹理占用的显存。 |

## 🎵 音频处理 (Audio)

| 方法 | 说明 |
| :--- | :--- |
| `Effect_Load(...)` | 加载一个短促的音效文件到内存中，返回 `HEFFECT`。 |
| `Effect_Play(HEFFECT eff)` | 播放指定的音效，返回一个用于控制的声道句柄 `HCHANNEL`。 |
| `Stream_Load(...)` | 以流式解码方式打开一个较长的音频文件 (MP3/OGG)，返回 `HSTREAM`。 |
| `Stream_Play(...)` | 播放音频流，支持循环控制。 |
| `Channel_SetVolume(HCHANNEL chn, int volume)` | 调整指定声道的音量 (0-100)。 |

## ⌨️ 输入设备 (Input)

| 方法 | 说明 |
| :--- | :--- |
| `Input_GetKeyState(int key)` | 返回指定按键当前是否处于按下状态。参数如 `HGEK_SPACE`, `HGEK_ENTER`。 |
| `Input_KeyDown(int key)` | 仅在指定按键被按下的**瞬间**返回 `true`。 |
| `Input_GetMousePos(float *x, float *y)` | 获取鼠标指针在窗口工作区内的坐标。 |
| `Input_GetEvent(hgeInputEvent *event)` | 从事件队列中拉取下一个输入事件，如果队列为空则返回 `false`。 |

## 📦 资源与文件 (Resource)

| 方法 | 说明 |
| :--- | :--- |
| `Resource_AttachPack(...)` | 将一个 ZIP 压缩包挂载到虚拟文件系统中。可以指定解压密码。 |
| `Resource_Load(...)` | 根据文件名加载资源。如果文件在压缩包中则在内存解压；否则直接读取磁盘文件。 |
| `Resource_Free(void *res)` | 释放 `Resource_Load` 分配的内存。 |

## ⏱️ 定时器与数学 (Timer & Math)

| 方法 | 说明 |
| :--- | :--- |
| `Timer_GetDelta()` | 获取上一帧到当前帧的时间间隔 (秒)。通常用于让逻辑与帧率无关。 |
| `Timer_GetFPS()` | 获取当前的帧率 (Frames Per Second)。 |
| `Random_Int(int min, int max)` | 生成指定范围内的伪随机整数。 |
| `Random_Float(float min, float max)` | 生成指定范围内的伪随机浮点数。 |
