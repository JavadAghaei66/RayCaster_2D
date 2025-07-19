# RayCaster_2D

A simple and educational 2D raycasting visualization written in C++ using SDL2. A central light source emits rays that stop upon hitting animated rectangular blockers.

![Demo](raycasting.gif)

## Prerequisites

- C++ compiler (`g++` for Linux, MSVC/MinGW for Windows)
- [SDL2](https://www.libsdl.org/) development libraries
- [xmake](https://xmake.io/) build system

## Installation

### 🐧 Linux

1. Install dependencies:
   ```bash
   sudo apt update
   sudo apt install -y g++ libsdl2-dev xmake
   ```

2. Clone and build:
   ```bash
   git clone https://github.com/JavadAghaei66/RayCaster_2D.git
   cd RayCaster_2D
   xmake
   ```

3. Run:
   ```bash
   xmake run 
   ```

### 🪟 Windows

1. Install a compiler: Use Visual Studio with C++ or [MinGW](https://www.mingw-w64.org/).
2. Install SDL2: Download [SDL2 devel](https://github.com/libsdl-org/SDL/releases/tag/release-2.32.8), extract to `C:\SDL2`, and add `bin` to PATH.
3. Install [xmake](https://xmake.io/) and add to PATH.
4. Clone and build:
   ```bash
   git clone https://github.com/JavadAghaei66/RayCaster_2D.git
   cd RayCaster_2D
   xmake
   ```
5. Run:
   ```bash
   xmake run
   ```