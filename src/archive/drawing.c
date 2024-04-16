#include <stdint.h>
#include <windows.h>

#include "./drawing.h"

void draw_pixel(U32 x, U32 y, U32 color) {
  U32 *pixel = (U32 *)memory;
  pixel += y * client_width + x;
  *pixel = color;
}

void clear_screen(U32 color) {
  U32 *pixel = (U32 *)memory;
  for (U32 i = 0; i < client_width * client_height; ++i) {
    *pixel++ = color;
  }
}

