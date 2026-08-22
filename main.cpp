#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LRESULT CALLBACK WindowProc(
  HWND hwnd,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam
) {
  switch (uMsg) {
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      // All painting occurs here, between BeginPaint and EndPaint.

      FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

      EndPaint(hwnd, &ps);
      return 0;
    }
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
  // Register the window class.
  const wchar_t CLASS_NAME[] = L"acca";
  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  RegisterClass(&wc);

  // Create the window.
  HWND hwnd = CreateWindowEx(
    0,                             // Optional window styles
    CLASS_NAME,                    // Window class
    CLASS_NAME,                    // Window text
    WS_OVERLAPPEDWINDOW,           // Window style
    CW_USEDEFAULT, CW_USEDEFAULT,  // Position (X, Y)
    800, 600,                      // Size (Width, Height)
    nullptr,                       // Parent window
    nullptr,                       // Menu
    hInstance,                     // Instance handle
    nullptr                        // Additional application data
  );

  if (hwnd == nullptr) return 0;

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
