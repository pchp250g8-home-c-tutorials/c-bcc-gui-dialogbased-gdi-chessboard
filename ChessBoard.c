// ChessBoard.c : Defines the entry point for the application.
//

#include "framework.h"
#include "ChessBoard.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


// Forward declarations of functions included in this code module:
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    ChessBoardDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // TODO: Place code here.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESSBOARD));
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHESSBOARD, szWindowClass, MAX_LOADSTRING);
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    return 0;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   INT_PTR nResponse;
   INITCOMMONCONTROLSEX InitCtrls;
   hInst = hInstance; // Store instance handle in our global variable
   InitCtrls.dwSize = sizeof(InitCtrls);
   // Select this option to include all common control classes
   // that you need to use in your application.
   InitCtrls.dwICC = ICC_WIN95_CLASSES;
   InitCommonControlsEx(&InitCtrls);
   // Create and show modal dialog
   nResponse = DialogBox(hInst, MAKEINTRESOURCE(IDD_CHESSBOARD_DIALOG), NULL, ChessBoardDlg);
   if (nResponse == IDOK)
   {
       // TODO: Add code to handle the closing of the dialog box
       //  via the "OK" button
   }
   else if (nResponse == IDCANCEL)
   {
       // TODO: Add code to handle the closing of the dialog box
       //  via the "Cancel" button
   }
   else if (nResponse == -1)
       return FALSE;
   return TRUE;
}

//
//  FUNCTION: ChessBoardDlg(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window (Dialog).
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//  WM_SIZE     - Resize the main window
//
LRESULT CALLBACK ChessBoardDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, About);
                break;
            }
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
        }
        break;
    case WM_SIZE:
        {
            InvalidateRect(hDlg, NULL, TRUE);
        }
        break;
    case WM_ERASEBKGND:
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT rect;
            int width, height;
            // Aqua Brush
            HBRUSH aquaBrush = CreateSolidBrush(RGB(0, 255, 255));
            // Brown Brush
            HBRUSH brownBrush = CreateSolidBrush(RGB(165, 42, 42));
            // Ajust Paint area size
            GetClientRect(hDlg, &rect);
            // Ajust ChessBoard Grid Size
            width = (rect.right - rect.left) / 8;
            height = (rect.bottom - rect.top) / 8;
            BeginPaint(hDlg, &ps);
            // TODO: Add any drawing code here...
            FillRect(ps.hdc, &rect, aquaBrush);
            // Ajust ChessBoard Grid Cell Position. Draw ChessBoard
            // ChessBoard Cell N 1 (odd number - aqua color)
            // ChessBoard Cell N 2 (even number - brown color)
            // Numeration starts from 0
            for (int k = 0; k < 32; k++)
            {
                int i = k / 4;
                int j = (k % 4) * 2 + (i % 2);
                int left = i * width;
                int top = j * height;
                int right = left + width;
                int bottom = top + height;
                RECT chessBoardEelem = { left, top, right, bottom };
                FillRect(ps.hdc, &chessBoardEelem, brownBrush);
            }
            EndPaint(hDlg, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (INT_PTR)FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
