
#include "RopView.h"
#include "MainUI/mainwindow.h"
using namespace std;
#include <cstdlib>


int main(int argc, char* argv[]) {
    const wchar_t* pipeName = L"\\\\.\\pipe\\UniqueAppPipe";

    HANDLE hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_INBOUND, PIPE_TYPE_BYTE | PIPE_WAIT, 1, 0, 0, 0, NULL);
    if (hPipe == INVALID_HANDLE_VALUE && GetLastError() == ERROR_PIPE_BUSY) {
        std::cerr << "Application is already running.\n";
        return 1; 
    }
    _putenv_s("QSG_RHI_BACKEND", "opengl");

	nmainUI::UIFrame::getInstance().mainloop(argc, argv);
    CloseHandle(hPipe);
}
