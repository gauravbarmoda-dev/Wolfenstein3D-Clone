# Wolfenstein3D-Clone

A classic Wolfenstein 3D / Doom style raycasting engine built from scratch using C++ and [Raylib](https://www.raylib.com/).

## Features
- Full 3D raycasting engine with textured walls, floors, and ceilings
- Smooth mouse-look and WSAD movement
- Distance-based fog/shadowing depth effect
- Basic map collision and interaction (break walls)

## Requirements
- C++ Compiler (g++)
- Make
- [Raylib](https://github.com/raysan5/raylib) installed on your system (with its dependencies like OpenGL, X11, etc.)

## Building and Running
1. Clone the repository:
```bash
git clone https://github.com/gauravbarmoda-dev/Wolfenstein3D-Clone.git
cd Wolfenstein3D-Clone
```
2. Build the game using Make:
```bash
make
```
3. Run the executable:
```bash
./bin/doom_game
```

## Controls
- **W, A, S, D**: Move around
- **Mouse**: Look around
- **Left Shift**: Sprint
- **E**: Interact (break brown walls)
