# 组件与类目录 (Component Catalog)

HGE 提供了极其丰富的高级 C++ 面向对象组件（Helpers），极大简化了 2D 游戏的开发过程。

## 🧩 精灵系统 (Sprite System)

### `hgeSprite`
- **文件**: `src/helpers/hgesprite.cpp`
- **描述**: 对核心层 `hgeQuad` 图元的 OOP 封装。
- **功能**:
  - `RenderEx(float x, float y, float rot, float hscale, float vscale)`: 这是 HGE 最常用的函数之一。通过传递旋转角度、水平和垂直缩放系数，引擎会自动以**热点 (Hotspot)** 为锚点，计算四边形的 2D 仿射变换并进行渲染。
  - `SetColor(DWORD col, int i = -1)`: 设置顶点颜色，支持顶点级别的渐变（调制模式）。

### `hgeAnim`
- **文件**: `src/helpers/hgeanim.cpp`
- **描述**: `hgeSprite` 的子类，专为序列帧动画设计。
- **功能**:
  - **基于时间的更新**: 通过调用 `Update(float fDeltaTime)` 累加时间，当超过设定的 `fSpeed`（每帧时长）时，自动切换到下一帧的 UV 坐标。
  - **多种播放模式**: 支持正向播放、反弹播放 (Ping-Pong)、循环播放等 (`HGEANIM_FWD`, `HGEANIM_REV`, `HGEANIM_PINGPONG`, `HGEANIM_LOOP`)。

## 🔤 字体渲染 (Bitmap Font)

### `hgeFont`
- **文件**: `src/helpers/hgefont.cpp`
- **描述**: 位图字体渲染系统，通常与配套工具 `fonted` 导出的 `.fnt` 文件结合使用。
- **功能**:
  - 解析字体描述文件，将每个字符的宽、高、偏移量、字距 (Kerning) 映射到一张巨大的纹理 (Texture Atlas) 上。
  - `printf(float x, float y, int align, const char *format, ...)`: 提供类似 C 标准库的格式化输出功能，支持左对齐、居中、右对齐排版。

## ✨ 粒子系统 (Particle Engine)

### `hgeParticleSystem`
- **文件**: `src/helpers/hgeparticle.cpp`
- **描述**: 一个高性能的 2D 粒子发射器，管理成百上千个同质粒子的生命周期。
- **功能**:
  - 读取通过 `particleed` 编辑器生成的预设文件 (`.psi`)。
  - `Update(float fDeltaTime)`: 每一帧更新所有存活粒子的位置（受重力、风力、切向加速度影响）、缩放、颜色（从初态渐变到末态）以及旋转角度。
  - `Render()`: 以极高的效率将所有粒子的四边形推入核心的 Batching 队列中。

### `hgeParticleManager`
- **文件**: `src/helpers/hgepmanager.cpp`
- **描述**: 负责管理多个 `hgeParticleSystem` 实例的容器。
- **功能**:
  - 当一个特效（如爆炸）播放完毕后，自动将其从管理器中剔除并回收内存。
  - `SpawnPS` 和 `KillPS` 提供便捷的发射与销毁接口，是处理游戏中子弹轨迹、烟雾等高频短促特效的最佳选择。

## 🖥️ 用户界面框架 (GUI Framework)

### `hgeGUI`
- **文件**: `src/helpers/hgegui.cpp`
- **描述**: 一个轻量级的 GUI 管理器，基于控件的 Z-Order 进行渲染和事件分发。
- **机制**:
  - **事件路由**: 在 `Update` 中，管理器会遍历所有控件。利用 `hgeRect::TestPoint` 检查鼠标是否在某个控件内部，从而触发相应的虚函数如 `MouseOver`, `MouseLButton`, `FocusLost` 等。
  - **导航**: 支持使用 Tab 键和方向键在控件之间切换输入焦点。

### `hgeGUIObject` 及其派生类
- **文件**: `src/helpers/hgeguictrls.cpp`
- **描述**: 所有 UI 控件的基类，提供统一的接口。HGE 内置了以下基础控件：
  - `hgeGUIButton`: 按钮控件。按下时切换按下态的 Sprite，支持点击音效触发。
  - `hgeGUISlider`: 滑动条控件。支持水平或垂直拖拽，内部将滑块的物理坐标映射为用户指定的浮点数区间 `[min, max]`。
  - `hgeGUIListbox`: 列表框控件。支持多行文本滚动、高亮选中和通过鼠标滚轮上下翻页。
  - `hgeGUIText`: 静态文本标签，封装了对 `hgeFont` 的调用。

## 🔧 配套工具链 (Toolchain)

HGE 的成功不仅在于引擎本身，更在于其完善的生产力工具（均在 `src/` 下开源）：
- **`texasm` (Texture Assembler)**: 纹理打包器。利用“矩形装箱”算法 (`RectPlacement.cpp`)，将零散的小图合并为一张或多张 2^N 的大纹理集 (Atlas)，并输出坐标映射脚本。这极大地优化了显存占用和渲染时的纹理切换开销。
- **`fonted` (Font Editor)**: 允许开发者选择系统字体、字号、特效（描边、发光），并直接栅格化为 HGE 支持的位图格式 (`.fnt` + `.png`)。
- **`particleed` (Particle Editor)**: 一个强大的可视化特效编辑器，可以实时拖拽滑动条修改粒子的速度、生命、颜色渐变，并立即预览效果。导出为 `.psi` 供游戏直接读取。