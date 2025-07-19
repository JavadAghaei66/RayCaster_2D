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
        rc.RenderBg();
        rc.RenderRays();
        rc.RenderBlocker();
        rc.MoveBlocker();
        rc.Delay();
    }

    rc.Quit();
    return 0;
}
