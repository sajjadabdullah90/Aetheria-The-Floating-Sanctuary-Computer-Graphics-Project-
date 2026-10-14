# Aetheria: The Floating Sanctuary

A real-time 3D computer-graphics scene built in C++ with OpenGL and GLUT/freeglut. Aetheria presents a fictional floating natural sanctuary with animated environmental details, wildlife, a cabin, mountains, clouds, and a water system.

> **Project type:** Academic computer-graphics project. The repository includes the C++ source and a prebuilt Windows executable; the executable may require compatible graphics libraries and runtime dependencies.

## Scene Features

- **Procedural 3D environment:** Floating terrain, mountains, rocks, trees, flowers, and a cabin.
- **Wildlife models:** Simple geometric representations of a deer, fox, sheep, and birds.
- **Animated atmosphere:** Moving clouds and sky, orbiting scene elements, animated water effects, fireflies, tree motion, smoke, and bird movement.
- **Lighting and depth:** OpenGL lighting, depth testing, fog, blending, and perspective projection.
- **Camera navigation:** Keyboard controls to move the view target and adjust zoom.
- **Continuous rendering:** GLUT timer callbacks update animation and redraw the scene.

The scene is created primarily from OpenGL/GLUT primitives and transformations rather than a separate 3D game engine.

## Technology Stack

| Technology | Purpose |
| --- | --- |
| C++ | Scene logic and animation |
| OpenGL | 3D rendering, lighting, materials, and transformations |
| GLU | Perspective utilities and quadric geometry |
| GLUT/freeglut | Window creation, input handling, timers, and render loop |
| Standard C++ libraries | Math, randomization, strings, and console support |

## Repository Structure

```text
.
├── project.cpp  # Main C++ graphics application
├── main.exe     # Prebuilt executable (Windows)
└── README.md
```

## Build and Run

### Requirements

- A C++ compiler (such as MinGW-w64/GCC or MSVC)
- OpenGL development libraries
- GLUT/freeglut development headers and libraries
- GLU, typically provided by the system's OpenGL utility library

The exact compiler and linker flags depend on the operating system and how GLUT/freeglut is installed.

### Example build command

For a MinGW/GCC environment with compatible freeglut libraries configured:

```bash
g++ project.cpp -o Aetheria.exe -lfreeglut -lopengl32 -lglu32
```

Run the resulting executable from the environment where the required graphics DLLs are available:

```bash
./Aetheria.exe
```

If your toolchain uses a different GLUT library name or library path, adjust the linker options to match your installation. The checked-in `main.exe` may also be launched directly on a compatible Windows machine.

## Controls

| Key | Action |
| --- | --- |
| `+` | Zoom in |
| `-` | Zoom out |
| `W` / `S` | Move the view target forward/backward |
| `A` / `D` | Move the view target left/right |
| `R` / `F` | Move the view target up/down |
| `Esc` | Exit the application |

## Learning Goals

This project demonstrates foundational computer-graphics concepts including 3D transformations, hierarchical object drawing, primitive-based modelling, perspective projection, lighting, blending, fog, keyboard interaction, and timer-driven animation.

## Future Improvements

- Add screenshots or a short demo video of the rendered scene.
- Document the tested compiler and exact dependency versions.
- Separate rendering, scene objects, animation, and input into dedicated source files.
- Add build configuration such as CMake for repeatable builds.

## Author

**Syed Abdullah**  
GitHub: [@sajjadabdullah90](https://github.com/sajjadabdullah90)
