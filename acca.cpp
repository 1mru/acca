// acca - Simple source code editor
// Win32 API + Scintilla

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "include/Scintilla.h"


// Menu IDs
#define IDM_FILE_NEW          1001
#define IDM_FILE_OPEN         1002
#define IDM_FILE_SAVE         1003
#define IDM_FILE_SAVE_AS      1004
#define IDM_FILE_EXIT         1005

#define IDM_EDIT_UNDO         1101
#define IDM_EDIT_REDO         1102
#define IDM_EDIT_CUT          1103
#define IDM_EDIT_COPY         1104
#define IDM_EDIT_PASTE        1105
#define IDM_EDIT_DELETE       1106
#define IDM_EDIT_SELECT_ALL   1107

#define IDM_VIEW_LINE_NUMBERS 1201
#define IDM_VIEW_STATUS_BAR   1202

#define IDM_HELP_ABOUT        1301


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


  case WM_SIZE: {
    if (hwndScintilla != nullptr) {
      MoveWindow(
        hwndScintilla,
        0,
        0,
        LOWORD(lParam),
        HIWORD(lParam),
        TRUE
      );
    }

    return 0;
  }


  case WM_COMMAND: {
    switch (LOWORD(wParam)) {

    // File
    case IDM_FILE_NEW:
      // TODO: Create a new document.
      break;

    case IDM_FILE_OPEN:
      // TODO: Open a file.
      break;

    case IDM_FILE_SAVE:
      // TODO: Save the current file.
      break;

    case IDM_FILE_SAVE_AS:
      // TODO: Save the current file under a new name.
      break;

    case IDM_FILE_EXIT:
      DestroyWindow(hwnd);
      break;


    // Edit
    case IDM_EDIT_UNDO:
      SendMessageW(
        hwndScintilla,
        SCI_UNDO,
        0,
        0
      );
      break;

    case IDM_EDIT_REDO:
      SendMessageW(
        hwndScintilla,
        SCI_REDO,
        0,
        0
      );
      break;

    case IDM_EDIT_CUT:
      SendMessageW(
        hwndScintilla,
        SCI_CUT,
        0,
        0
      );
      break;

    case IDM_EDIT_COPY:
      SendMessageW(
        hwndScintilla,
        SCI_COPY,
        0,
        0
      );
      break;

    case IDM_EDIT_PASTE:
      SendMessageW(
        hwndScintilla,
        SCI_PASTE,
        0,
        0
      );
      break;

    case IDM_EDIT_DELETE:
      SendMessageW(
        hwndScintilla,
        SCI_CLEAR,
        0,
        0
      );
      break;

    case IDM_EDIT_SELECT_ALL:
      SendMessageW(
        hwndScintilla,
        SCI_SELECTALL,
        0,
        0
      );
      break;


    // View
    case IDM_VIEW_LINE_NUMBERS:
      // TODO: Toggle line numbers.
      break;

    case IDM_VIEW_STATUS_BAR:
      // TODO: Toggle status bar.
      break;


    // Help
    case IDM_HELP_ABOUT:
      MessageBoxW(
        hwnd,
        L"acca\nSimple source code editor",
        L"About acca",
        MB_OK | MB_ICONINFORMATION
      );
      break;
    }

    return 0;
  }
  }

  return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}


// Entry point
int WINAPI wWinMain(
  HINSTANCE hInstance,
  HINSTANCE,
  PWSTR,
  int nCmdShow
) {
  const wchar_t CLASS_NAME[] = L"acca";


  // Register window class.
  WNDCLASSW wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClassW(&wc);


  // Create main window.
  HWND hwnd = CreateWindowExW(
    0,
    CLASS_NAME,
    CLASS_NAME,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    800,
    600,
    nullptr,
    nullptr,
    hInstance,
    nullptr
  );

  if (hwnd == nullptr) {
    return 0;
  }


  // Create the menu bar.
  HMENU hMenu = CreateMenu();


  // File menu.
  HMENU hFileMenu = CreatePopupMenu();

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_FILE_NEW,
    L"New"
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_FILE_OPEN,
    L"Open..."
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_FILE_SAVE,
    L"Save"
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_FILE_SAVE_AS,
    L"Save As..."
  );

  AppendMenuW(
    hFileMenu,
    MF_SEPARATOR,
    0,
    nullptr
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_FILE_EXIT,
    L"Exit"
  );

  AppendMenuW(
    hMenu,
    MF_POPUP,
    (UINT_PTR)hFileMenu,
    L"File"
  );


  // Edit menu.
  HMENU hEditMenu = CreatePopupMenu();

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_EDIT_UNDO,
    L"Undo"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_EDIT_REDO,
    L"Redo"
  );

  AppendMenuW(
    hEditMenu,
    MF_SEPARATOR,
    0,
    nullptr
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_EDIT_CUT,
    L"Cut"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_EDIT_COPY,
    L"Copy"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_EDIT_PASTE,
    L"Paste"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_EDIT_DELETE,
    L"Delete"
  );

  AppendMenuW(
    hEditMenu,
    MF_SEPARATOR,
    0,
    nullptr
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_EDIT_SELECT_ALL,
    L"Select All"
  );

  AppendMenuW(
    hMenu,
    MF_POPUP,
    (UINT_PTR)hEditMenu,
    L"Edit"
  );


  // View menu.
  HMENU hViewMenu = CreatePopupMenu();

  AppendMenuW(
    hViewMenu,
    MF_STRING,
    IDM_VIEW_LINE_NUMBERS,
    L"Line Numbers"
  );

  AppendMenuW(
    hViewMenu,
    MF_STRING,
    IDM_VIEW_STATUS_BAR,
    L"Status Bar"
  );

  AppendMenuW(
    hMenu,
    MF_POPUP,
    (UINT_PTR)hViewMenu,
    L"View"
  );


  // Help menu.
  HMENU hHelpMenu = CreatePopupMenu();

  AppendMenuW(
    hHelpMenu,
    MF_STRING,
    IDM_HELP_ABOUT,
    L"About acca"
  );

  AppendMenuW(
    hMenu,
    MF_POPUP,
    (UINT_PTR)hHelpMenu,
    L"Help"
  );


  // Set the menu bar.
  SetMenu(hwnd, hMenu);


  // Load Scintilla DLL.
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


  // Create Scintilla editor.
  hwndScintilla = CreateWindowExW(
    0,
    L"Scintilla",
    L"",
    WS_CHILD |
    WS_VISIBLE |
    WS_TABSTOP |
    WS_CLIPCHILDREN,
    0,
    0,
    0,
    0,
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

    FreeLibrary(hmod);
    return 0;
  }


  // Use DirectWrite for text rendering.
  SendMessageW(
    hwndScintilla,
    SCI_SETTECHNOLOGY,
    SC_TECHNOLOGY_DIRECTWRITERETAIN,
    0
  );


  // Show line numbers.
  SendMessageW(
    hwndScintilla,
    SCI_SETMARGINWIDTHN,
    0,
    40
  );

  SendMessageW(
    hwndScintilla,
    SCI_SETMARGINTYPEN,
    0,
    SC_MARGIN_NUMBER
  );


  // Set the editor font.
  SendMessageW(
    hwndScintilla,
    SCI_STYLESETFONT,
    STYLE_DEFAULT,
    (LPARAM)"Cascadia Code"
  );

  SendMessageW(
    hwndScintilla,
    SCI_STYLESETSIZE,
    STYLE_DEFAULT,
    12
  );

  SendMessageW(
    hwndScintilla,
    SCI_STYLECLEARALL,
    0,
    0
  );


  // Use spaces instead of tabs.
  SendMessageW(
    hwndScintilla,
    SCI_SETUSETABS,
    FALSE,
    0
  );

  // Set the tab width to 2 spaces.
  SendMessageW(
    hwndScintilla,
    SCI_SETTABWIDTH,
    2,
    0
  );


  // Show the main window.
  ShowWindow(hwnd, nCmdShow);

  // Give keyboard focus to the editor.
  SetFocus(hwndScintilla);


  // Message loop.
  MSG msg = {};

  while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }


  FreeLibrary(hmod);

  return 0;
}
