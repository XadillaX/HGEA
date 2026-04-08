# HGE 引擎开发指南 (Development Guide)

## 🛠️ 编译与构建 (Build Instructions)

原版 HGE 引擎（v1.8）是在 2000 年代中期开发的，因此其原生的构建系统主要针对当时主流的 Windows 编译器：

### 1. 目录结构说明
- `src/core/` 包含一个通用的 `Makefile.win`（适用于 MinGW/GCC）。
- 同时也包含了各个 IDE 的项目文件：
  - `hge.bpf`, `hge.bpr` (Borland C++)
  - `hge.dev` (Dev-C++)
  - `hge.dsp`, `hge.dsw` (Visual Studio 6.0)
  - `hge.sln`, `hge.vcproj` (Visual Studio 2003/2005)

### 2. 第三方依赖说明
要成功编译核心引擎（即生成 `hge.dll` 或静态库），你必须拥有以下 SDK：
- **DirectX 8 SDK**: 引擎强依赖 `d3d8.h` 和 `d3dx8.h`。现代的 Windows SDK 可能已经移除了这些极其老旧的头文件，因此需要单独下载旧版的 DX SDK。
- **BASS SDK**: `bass.dll` 和 `bass.h` 已经包含在源码树中（位于 `src/core/BASS/`），无需额外下载。
- **ZLIB**: 源码已完整包含在 `src/core/ZLIB/` 中，并直接参与核心库的编译。

### 3. 工具链依赖
如果你想编译 `fonted`、`particleed` 或 `texasm` 等编辑器工具，还需要编译 **libPNG**：
- `libPNG` 的源码分散包含在各个工具的目录下（如 `src/fonted/libPNG/`）。
- 这些工具同样使用上述的旧版 IDE 工程文件进行构建。

## 💡 开发提示与最佳实践 (Best Practices)

### 1. 游戏主循环 (Main Loop)
HGE 接管了 `WinMain` 和消息循环，因此你不需要（也不能）自己编写原生的 Windows 消息处理。
- 你必须提供一个 `FrameFunc` 和一个 `RenderFunc`。
- 在 `FrameFunc` 中处理所有的输入 (`Input_GetKeyState`)、物理更新 (`Timer_GetDelta`) 和游戏逻辑。如果游戏需要退出，则返回 `true`。
- 在 `RenderFunc` 中，**必须** 以 `Gfx_BeginScene()` 开始，以 `Gfx_EndScene()` 结束。不要在 `RenderFunc` 中放置耗时的逻辑计算。

### 2. 坐标系 (Coordinate System)
- HGE 使用 **左上角为原点 (0, 0)** 的 2D 屏幕坐标系。
- 向右为 X 轴正方向，向下为 Y 轴正方向。
- `Z-Buffer` 深度值的范围是 `0.0f` 到 `1.0f`，值越大越靠后（被遮挡）。如果初始化时开启了 `HGE_ZBUFFER`，可以利用顶点的 Z 值实现正确的深度排序，而无需手动对精灵数组进行排序。

### 3. 性能优化 (Performance Optimization)
- **尽量使用大纹理**: 频繁的 `Texture_Load` 和 `Texture_Free` 非常耗时。建议使用 `texasm` 将所有小图打包成一张 1024x1024 或 2048x2048 的纹理 (Texture Atlas)。
- **利用 Batching**: HGE 的渲染是基于批处理的。如果你连续渲染使用同一张纹理的 1000 个精灵，底层只会调用一次 `DrawPrimitive`。但如果你交替使用不同的纹理渲染，就会打破 Batching，导致严重的性能下降。
- **谨慎使用 `Texture_Lock`**: 锁定显存并修改像素是一项极其昂贵的操作。不要在每帧的主循环中频繁执行此操作。

### 4. 资源打包 (Resource Packing)
- 在发布游戏时，建议使用普通的 ZIP 软件将所有的 `images`, `sounds`, `scripts` 目录打包成一个 `.zip` 文件，并改后缀名为 `.res`（或其他任意扩展名）。
- 在 `System_Start` 之前，调用 `Resource_AttachPack("data.res", "password123")`。
- 这样，所有的 `Texture_Load` 和 `Effect_Load` 都会透明地从内存中读取解密后的数据，既保护了资产，又避免了大量小文件在磁盘上的碎片化读取。