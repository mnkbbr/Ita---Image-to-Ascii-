# Image to ASCII Converter (Ita)

Converts images and animated GIFs to ASCII art using the <stb_image> library.
It supports any color image and GIFs, but yields better results with black and white inputs

## Fast Start:

_On Windows, you need [MSYS2](https://www.msys2.org/) to build the program, or you can use any alternative method of your choice_

### 1. Compilation

```
mkdir build
cd build
```
```
cmake ..
cmake --build .
```
### 2. Execution 

### Windows
``` cmd
Ita.exe <image_path> <scale_factor>
```

### Linux / macOS
```bash
./Ita <image_path> <scale_factor>
```

**Tip:**  <scale_factor>  Image downscaling factor for correct console output

Recommended scale:
- 6-10 : for small console windows
- 3-5  : for large images / fullscreen
<p align="center">
  <img src="https://github.com/mnkbbr/Ita---Image-to-Ascii-/blob/media/BadApple.png" width="500" alt="ASCII Art">
</p>
