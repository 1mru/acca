#define WIN32_LEAN_AND_MEAN
#include <windows.h>

HWND hwndScintilla = nullptr;

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

      FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_SIZE: {
      if (hwndScintilla != nullptr) {
        MoveWindow(
          hwndScintilla,
          0, 0,
          LOWORD(lParam),
          HIWORD(lParam),
          TRUE
        );
        return 0;
      }
    }
  }

  return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}


int WINAPI wWinMain(
  HINSTANCE hInstance,
  HINSTANCE,
  PWSTR,
  int nCmdShow
) {
  const wchar_t CLASS_NAME[] = L"acca";

  // Set up the window class.
  WNDCLASSW wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  // Register the window class with Windows.
  RegisterClassW(&wc);

  // Main window
  HWND hwnd = CreateWindowExW(
    0,                              // Extended window style
    CLASS_NAME,                     // Window class name
    CLASS_NAME,                     // Window name
    WS_OVERLAPPEDWINDOW,            // Window style
    CW_USEDEFAULT, CW_USEDEFAULT,   // Position
    800, 600,                       // Size
    nullptr,                        // Handle to parent window
    nullptr,                        // Handle to menu
    hInstance,                      // Handle to instance
    nullptr                         // lpParam
  );

  if (hwnd == nullptr) return 0;


  // Scintilla DLL
  HMODULE hmod = LoadLibraryW(L"Scintilla.dll");
  if (hmod == nullptr) {
    MessageBoxW(
      hwnd,
      L"The Scintilla DLL could not be loaded",
      L"Error",
      MB_OK | MB_ICONERROR
    );

    return 0;
  }

  // Scintilla editor
  hwndScintilla = CreateWindowExW(
    0,
    L"Scintilla",
    L"",
    WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN,
    0, 0,
    0, 0,
    hwnd,
    nullptr,
    hInstance,
    nullptr
  );
  if (hwndScintilla == nullptr) {
    MessageBoxW(
      hwnd,
      L"Could not create Scintilla window",
      L"Error",
      MB_OK | MB_ICONERROR
    );

    return 0;
  }


  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};

  while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  FreeLibrary(hmod);

  return 0;
}
