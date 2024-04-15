#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>

#include "../base/drawing.h"

#pragma comment (lib, "user32.lib")
#pragma comment (lib, "gdi32.lib")

/**
 * win_proc:        Windows procudure, handles messages related to the procedure
 * param w_param:   interpretation information
 * param l_param:   interpretation information
 * param window:    window, some window
 * parma msg:       msg,    some message
*/
LRESULT CALLBACK win_proc(HWND window, UINT msg, 
                          WPARAM w_param, LPARAM l_param) {
    switch(msg) {
        case WM_KEYDOWN: {
            switch(w_param) {
                case 'O': { 
                    DestroyWindow(window);    // closes and destroys a window
                } break;
            }
        } break;
        
        case WM_DESTROY: {
            PostQuitMessage(0);     // posts a quit message to applications message queue
                                    // Indicates application should quit
        } break;
        
        default: {
            return DefWindowProcW(window, msg, w_param, l_param);
        }
    }
    
    return 0;
}

/**
 * WinMain:     Entry point for windows
*/
int WINAPI WinMain(
    HINSTANCE instance,
    HINSTANCE prev_instance,
    LPSTR     cmd,
    int       cmd_show) {  

  OutputDebugString("Hello World!\n");

  /**
   * windows_class:   template for creating windows
  */
  WNDCLASSW wc = {
    .lpszClassName = L"MyWindowClass",  // Class of the window
    .lpfnWndProc = win_proc,
    .hInstance = instance,
    .hCursor = LoadCursor(NULL, IDC_CROSS),
  };

  ATOM atom = RegisterClassW(&wc);
  //Assert(atom && "Failed to register a window");

  /**
   * window HWND:     unique handle window for the application
  */
  HWND window = CreateWindowW(
    wc.lpszClassName,                   // Class of the window
    L"Cannonade",                       // handle window title 
    WS_OVERLAPPEDWINDOW, 
    CW_USEDEFAULT, CW_USEDEFAULT,     // position (x, y)
    CW_USEDEFAULT, CW_USEDEFAULT,     // size (width, height)
    NULL,                             // parent window handle 
    NULL,                             // menu handle
    instance,                         // handle to the application instance
    NULL);                            // additional data to window procedure

  //Assert(window && "Failed to create a window");
  
  ShowWindow(window, cmd_show);

  // Allocate memory for pixels
  RECT rect;
  GetClientRect(window, &rect);
  client_width = rect.right - rect.left;      // Coordinates from the top left
  client_height = rect.bottom - rect.top;     // Coordinates from the top left

  memory = VirtualAlloc(
    0,
    client_width * client_height * 4,
    MEM_RESERVE | MEM_COMMIT,
    PAGE_READWRITE
  );  // Getting memory for the shape (?), basic rectangle

  // Create BITMAPINFO struct for StretchDIBits.

  BITMAPINFO bitmap_info = {
    .bmiHeader.biSize = sizeof(bitmap_info.bmiHeader),
    .bmiHeader.biWidth = client_width,
    .bmiHeader.biHeight = client_height,
    .bmiHeader.biPlanes = 1,
    .bmiHeader.biBitCount = 32,
    .bmiHeader.biCompression = BI_RGB
  };

  HDC hdc = GetDC(window); // No idea what this is for

  /**
   * put stuff in here to have it run while the program runs
  */
  for(;;) {                                         // Continues until explicitly broken out of with break statement
    MSG msg;
    if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if(msg.message == WM_QUIT) break;           // quit message in message queue, quit
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        continue;
    }    

    clear_screen(0x333333);
        
    // Draw white (not white) pixel at 100, 100 (from bottom left).
    
    draw_pixel(100, 100, 0xfffddd);
    
    StretchDIBits(hdc,
                  0,
                  0,
                  client_width,
                  client_height,
                  0,
                  0,
                  client_width,
                  client_height,
                  memory,
                  &bitmap_info,
                  DIB_RGB_COLORS,
                  SRCCOPY
                  );
  }
  return 0;
}
