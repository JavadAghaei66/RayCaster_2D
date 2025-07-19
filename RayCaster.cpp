#include "RayCaster.h"

RayCaster::RayCaster()
{
    is_running = true;

    black_screen = (struct SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    blocker.x = 300;
    blocker.y = 300;
    blocker.w = 80;
    blocker.h = 80;

    light_source_X = 20;
    light_source_Y = 20;
}

bool RayCaster::InitRayCaster()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow(
        "RayCasting",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!window)
    {
        cout << "Window creation failed....\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        cout << "render creation failed: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void RayCaster::Render()
{
    RenderBg();
    RenderRays();
    RenderBlocker();
    SDL_RenderPresent(renderer);
}

void RayCaster::RenderRays()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red

    for (int i = 0; i < RAY_COUNT; i++)
    {
        float angleDeg = (360.0f / RAY_COUNT) * i;
        float angleRad = angleDeg * PI / 180.0f;

        float dx = cos(angleRad);
        float dy = sin(angleRad);

        float x = light_source_X;
        float y = light_source_Y;

        for (int j = 0; j < maxLength; j++)
        {
            x += dx * step;
            y += dy * step;

            if (CheckCollision(&blocker, x, y))
                break;

            SDL_RenderDrawPoint(renderer, (int)x, (int)y);
        }
    }
}

// renders moving blocker object
void RayCaster::RenderBlocker()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderFillRect(renderer, &blocker);
}

// renders black background
void RayCaster::RenderBg()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
    SDL_RenderFillRect(renderer, &black_screen);
}

void RayCaster::MoveBlocker()
{
    if (direction) // goes up
    {
        if (blocker.y <= 0)
            direction = false; // change direction
        else
            blocker.y -= speed;
    }
    else // goes down
    {
        if ((blocker.y + blocker.h) >= WINDOW_HEIGHT)
            direction = true;
        else
            blocker.y += speed;
    }
}

// checks if (x,y) position is inside blocker or not
bool RayCaster::CheckCollision(SDL_Rect *blocker, float x, float y)
{
    float bX = blocker->x;
    float bY = blocker->y;
    float bW = blocker->w;
    float bH = blocker->h;

    return (x >= bX && x <= (bX + bW) && y >= bY && y <= (bY + bH));
}

bool RayCaster::IsRunning() const
{
    return is_running;
}

// 16ms (60fps)
void RayCaster::Delay()
{
    SDL_Delay(16);
}

void RayCaster::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            is_running = false;
        else if (event.type == SDL_MOUSEMOTION)
        {
            light_source_X = event.motion.x;
            light_source_Y = event.motion.y;
        }
    }
}

// cleans up resources and shuts down SDL
void RayCaster::Quit()
{
    if (window)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}