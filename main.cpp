#include <iostream>
#include "RayCaster.h"
using namespace std;

int main()
{
    RayCaster rc;
    if (!rc.InitRayCaster())
    {
        cout << "Unexpected error happend." << endl;
        return 1;
    }

    while (rc.IsRunning())
    {
        rc.Input();
        rc.Render();
        rc.MoveBlocker();
        rc.Delay();
    }

    rc.Quit();
    return 0;
}

#if defined(_WIN32) && defined(_MSC_VER)
#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) { return main(); }

#endif