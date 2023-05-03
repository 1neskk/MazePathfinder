# Maze Pathfinder

In this program you can create a maze and set the start point and a goal, the A* algorithm will find the most optimal path between them.

The A* algorithm finds a path from the start node to the end node by checking for open neighbors of the current node, computing a heuristic for each of the neighbors, and adding those neighbors to the list of open nodes to explore next. The next node to explore is the one with the lowest total cost + heuristic (g + h). This process is repeated until the end is found, as long as there are still open nodes to explore.

// TODO: Tomorrow add a picture or gif here.

## Get Started

Officially supports Windows 10/11 with Visual Studio 2022. Linux and MacOS support on the way!

### Windows

1. Clone recursively: `git clone --recursive https://github.com/1neskk/MazePathfinder`
2. Run `scripts/setup.bat`
3. Open the solution file and hit F7 to build
4. Drag the SFML binaries `sfml-window-2.dll, sfml-graphics-2.dll and sfml-system-2.dll` into your output directory
- You will need to use the [SFML 2.5.1](https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip) from their website instead of the current submodule.

---

### Credits

#### Inspired by:
- [xSnapi's pathfinding implementation using SFML](https://github.com/xSnapi/cpp_pathfinding_using_sfml)

### Issues
Feel free to open a Issue if you need some help!
