#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define CENTER_X (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

#define RAY_COUNT 360
#define BLOCKER_COUNT 2

struct Blocker
{
    int x, y;
    int w, h;
    bool direction = false;
};

class RayCaster
{
private:
    bool is_running;
    const double PI = 3.141592653589793238463;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect black_screen;
    // Rays
    int maxLength = 1000;
    float step = 1.0f;
    // Blocker
    Blocker blockers[2];   // 2 blockers
    bool direction = true; // true means UP false means DOWN
    int speed = 4;
    // Light source
    int light_source_X;
    int light_source_Y;

public:
    RayCaster();
    bool InitRayCaster();
    bool CheckCollision(Blocker *blocker, float x, float y);
    bool IsRunning() const;
    void MoveBlocker();
    void Delay();
    void Input();
    void Quit();
    // Render
    void Render();
    void RenderBg();
    void RenderRays();
    void RenderBlocker();
};