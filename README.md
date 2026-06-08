
# Ray's C Graphics Engine (RCGE)

A lightweight and portable OpenGL-based graphic engine written in plain C.

[Click Here for RCGE Usage Guide and Detailed Documentation](https://czfray.github.io/rays_c_graphics_engine/)

## Features

- 🪟 Window Management
- ⌨️ Input Handling
- 🎨 Shader Support (Use default shaders or build custom ones.)
- 🖼️ Texture System
- 🔺 Mesh Rendering
- 📷 Camera Control
- 🧱 Elements and Element Mangager System

Features are currently limited, but more will come in the following releases!
## Installation

To use RCGE for your own project, download the newest version [here](https://github.com/czfray/rays_c_graphics_engine/releases), and paste everything in the zip file into your project directory.

`#include <rcge/rcge.h>` at the top of your file. 

If you need to do maths for vectors, matrices and quaternions, please use the cglm library by doing `#include <cglm/cglm.h>`. To learn how cglm works, please [click here](https://cglm.readthedocs.io/en/latest/?badge=latest).

*Please note that only RCGE only supports Windows at the current moment.*

## Source Code

The RCGE source code is located in `libs/rcge`. It is placed within this path intentionally, as this repository is structured to demonstrate how RCGE would be integrated and used in a real application project. 

If you would like to change the source code of RCGE, please clone the entire repository, change the source code in `libs/rcge/src`.

```
git clone https://github.com/czfray/rays_c_graphics_engine
```

Testing of your code should be done in the main.c or other c files in the repository directory. Before you test your code in main.c, be sure to compile RCGE by:

```
cd libs/rcge/cmake
make
```

## Acknowledgements

Internally, RCGE uses the following libraries:

 - [glfw3](https://github.com/glfw/glfw)
 - [glad](https://github.com/dav1dde/glad)
 - [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
 - [cglm](https://github.com/recp/cglm)


## Authors

- [@czfray](https://www.github.com/czfray)

