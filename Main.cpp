#include<Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(nCmdShow);

    /*
        To center the focused window on its screen, the following is necessary:
        - Get the hWnd of the current foreground window
        - Get the WindowRect of the window
        - Calculate the top-left coordinates needed to center the window
        - Call SetWindowPos to update the window position
    */
    HWND foregroundWindow = GetForegroundWindow();
    RECT windowRect = { 0 };
    BOOL success = GetWindowRect(foregroundWindow, &windowRect);
    if (!success) return GetLastError();
    
    int wWidth = windowRect.right - windowRect.left;
    int wHeight = windowRect.bottom - windowRect.top;

    HMONITOR monitor = MonitorFromWindow(foregroundWindow, MONITOR_DEFAULTTONULL);
    MONITORINFO mInfo = { 0 };
    mInfo.cbSize = sizeof(MONITORINFO);
    success = GetMonitorInfo(monitor, &mInfo);
    if (!success) return GetLastError();

    int mWidth = mInfo.rcMonitor.right;
    int mHeight = mInfo.rcMonitor.bottom;
   
    int x = (mWidth - wWidth) / 2;
    int y = (mHeight - wHeight) / 2;

    success = MoveWindow(
        foregroundWindow,
        x,
        y,
        wWidth,
        wHeight,
        TRUE
    );
    if (!success) return GetLastError();
}