# HGE (Haaf's Game Engine)

## 📖 项目概述 (Project Overview)
HGE (Haaf's Game Engine) 是一款成熟、易用且强大的 2D 硬件加速游戏引擎。它主要针对 Windows 平台开发，底层基于 **DirectX 8** 实现高性能的图形渲染，使用 **BASS** 库处理音频。HGE 旨在为 2D 游戏开发者提供一个简单、统一的 C++ 接口，隐藏底层复杂的硬件交互细节。

## ✨ 核心特性 (Core Features)
- **硬件加速 2D 渲染**：基于 Direct3D 8，提供极高的 2D 渲染性能。
- **自动渲染批处理 (Batching)**：内部自动合并相同状态的绘制调用，最小化 Draw Call。
- **多媒体音频支持**：集成 BASS 音频库，支持 WAV、MP3、OGG 及多种 Tracker 格式 (MOD, XM, IT)。
- **透明资源管理**：集成 ZLIB，支持直接从本地文件系统或加密的 ZIP 资源包中加载游戏资产。
- **丰富的辅助组件 (Helpers)**：提供面向对象的辅助类，包括精灵 (Sprite)、动画 (Animation)、位图字体 (Font)、粒子系统 (Particle) 和图形用户界面 (GUI)。
- **周边工具链**：包含完善的配套工具，如位图字体编辑器 (`fonted`)、粒子编辑器 (`particleed`)、纹理打包器 (`texasm`) 和 PNG 优化工具 (`pngopt`)。

## 🗂️ 目录结构 (Directory Structure)
```text
HGE/
├── doc/                 # 官方 HTML 格式的 API 帮助文档和教程
├── include/             # 公共头文件目录（包含核心 hge.h 及所有 Helper 类头文件）
├── lib/                 # 预编译静态库输出目录 (bc, gcc, vc)
└── src/                 # 引擎核心与工具源代码目录
    ├── core/            # 引擎核心层实现 (System, Graphics, Audio, Input, Resource)
    ├── helpers/         # 游戏逻辑辅助层实现 (Sprite, Anim, GUI, Particle)
    ├── fontconv/        # 字体转换命令行工具
    ├── fonted/          # 可视化位图字体编辑器
    ├── particleed/      # 可视化粒子特效编辑器
    ├── pngopt/          # PNG 图像体积优化与裁剪工具
    └── texasm/          # 纹理打包器
```

## 📚 文档导读 (Documentation Guide)
为了更深入地了解 HGE 引擎的技术实现，请参阅以下文档：
- [ARCHITECTURE.md](ARCHITECTURE.md): 了解引擎的整体架构设计、核心模块与底层实现机制。
- [COMPONENTS.md](COMPONENTS.md): 详细查看各个核心子系统及辅助类 (Helpers) 的功能和职责。
- [API.md](API.md): 查看核心 API `hge.h` 的接口定义与模块划分。
- [DEVELOPMENT.md](DEVELOPMENT.md): 了解如何在 Windows 环境下编译和构建原版 HGE 引擎。