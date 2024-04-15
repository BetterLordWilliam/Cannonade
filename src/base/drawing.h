#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <windows.h>

#ifndef DRAWING_H_
#define DRAWING_H_

#pragma comment (lib, "user32.lib")
#pragma comment (lib, "gdi32.lib")

typedef uint32_t U32;

// Static Types

void *memory;
U32 client_width;
U32 client_height;

// Functions

void draw_pixel(U32 x, U32 y, U32 color);
void clear_screen(U32 color);

#endif