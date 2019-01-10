<br>
<p align="center"><img width="350" src="img/logo.svg" alt="LIBDYE" /></p>
<hr>

This is a small cross-platform static C library to bring colors in the console. In posix-compatible systems, it uses ANSI color formatting and Console API in Windows.

### How to use

Provide path to libdye header and library for your project and then you can use it:

```c
#include <stdio.h>
#include <stdlib.h>

#include "dye.h" // libdye header

int main(int argc, char** argv)
{
  // Change foreground and background color
  dye(stdout, DYE_WHITE, DYE_NAVYBLUE);
  printf("White text on blue background\n");
  
  // Change only foreground color
  dyefg(stdout, DYE_YELLOW);
  printf("Yellow text on blue background\n");
  
  // Change only background color
  dyebg(stdout, DYE_GREEN)
  printf("Yellow text on green background\n");
  
  // Reset all colors to default
  dye(stdout, DYE_RESET, DYE_RESET);

  return EXIT_SUCCESS;
}
```

### How to build

Library depends only on [C standart library](https://en.wikipedia.org/wiki/C_standard_library), `unistd.h` header on Unix, `windows.h` and `io.h` on Windows.

On Unix run:
```bash
$ make
```

On Windows run:
```bash
$ nmake -f Makefile.nmake
```

As a result, the `release` and `debug` versions of the library will be created in the `build` directory with the corresponding subdirectories.

### Color pallete

| Color         | Code |
| ------------- | ---- |
| DYE_CURRENT   | -2   |
| DYE_RESET     | -1   |
| DYE_BLACK     | 0    |
| DYE_NAVYBLUE  | 1    |
| DYE_GREEN     | 2    |
| DYE_CYAN      | 3    |
| DYE_MAROON    | 4    |
| DYE_PURPLE    | 5    |
| DYE_OLIVE     | 6    |
| DYE_SILVER    | 7    |
| DYE_GREY      | 8    |
| DYE_GRAY      | 8    |
| DYE_BLUE      | 9    |
| DYE_LIME      | 10   |
| DYE_TEAL      | 11   |
| DYE_RED       | 12   |
| DYE_MAGENTA   | 13   |
| DYE_YELLOW    | 14   |
| DYE_WHITE     | 15   |

### License info

[MIT](https://en.wikipedia.org/wiki/MIT_License) license, copyright (c) Kuznetsov Aleksey
