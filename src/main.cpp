#include "wndproc.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
  const wchar_t CLASS_NAME[] = L"acca";

  WNDCLASSW wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClassW(&wc);

  HWND hwnd = CreateWindowExW(
    0,
    CLASS_NAME,
    CLASS_NAME,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    800, 600,
    nullptr,
    nullptr,
    hInstance,
    nullptr
  );

  if (hwnd == nullptr) return 0;

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};

  while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return 0;
}
