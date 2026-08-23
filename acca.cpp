// acca - Simple source code editor
// Win32 API + Scintilla

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "include/Scintilla.h"

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
      }
      return 0;
    }
  }

  return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}


// エントリーポイント
int WINAPI wWinMain(
  HINSTANCE hInstance,
  HINSTANCE,
  PWSTR,
  int nCmdShow
) {
  const wchar_t CLASS_NAME[] = L"acca";

  // ウィンドウクラスを登録
  WNDCLASSW wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  RegisterClassW(&wc);

  // メインウィンドウを作成
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


  // Scintilla DLLをロード
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

  // Scintilla editorを作成
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

  // DirectWrite
  SendMessageW(
    hwndScintilla,
    SCI_SETTECHNOLOGY,
    SC_TECHNOLOGY_DIRECTWRITERETAIN,
    0
  );

  // 余白を設定
  SendMessageW(hwndScintilla, SCI_SETMARGINWIDTHN, 0, 40);

  // 行番号を表示
  SendMessageW(hwndScintilla, SCI_SETMARGINTYPEN, 0, SC_MARGIN_NUMBER);

  // フォントを設定
  SendMessageW(hwndScintilla, SCI_STYLESETFONT, STYLE_DEFAULT, (LPARAM)"Cascadia Code");

  // フォントサイズを設定
  SendMessageW(hwndScintilla, SCI_STYLESETSIZE, STYLE_DEFAULT, 12);

  // フォントの設定を全文に適用
  SendMessageW(hwndScintilla, SCI_STYLECLEARALL, 0, 0);

  


  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};

  while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  FreeLibrary(hmod);

  return 0;
}
