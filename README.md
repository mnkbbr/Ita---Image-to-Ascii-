# Image to ASCII Converter (Ita)

Converts images to ASCII art using the <stb_image> library.
It supports any color image, but yields better results with black and white inputs

## Fast Start:

### 1. Compilation

```
g++ main.cpp -o Ita
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
