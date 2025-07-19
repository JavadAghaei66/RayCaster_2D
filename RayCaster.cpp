#include "RayCaster.h"

RayCaster::RayCaster()
{
    is_running = true;
    black_screen = (struct SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    // blockers deafult position
    blockers[0].x = 200;
    blockers[0].y = 0;
    blockers[0].w = 80;
    blockers[0].h = 80;

    blockers[1].x = 520;
    blockers[1].y = 600;
    blockers[1].w = 80;
    blockers[1].h = 80;

    light_source_X = 40;
    light_source_Y = 40;
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

            if (CheckCollision(&blockers[0], x, y) || CheckCollision(&blockers[1], x, y))
                break;

            SDL_RenderDrawPoint(renderer, (int)x, (int)y);
        }
    }
}

// renders moving blocker object
void RayCaster::RenderBlocker()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    for (auto &blocker : blockers)
    {
        SDL_Rect rect_blocker = (struct SDL_Rect){blocker.x, blocker.y, blocker.w, blocker.h};
        SDL_RenderFillRect(renderer, &rect_blocker);
    }
}

// renders black background
void RayCaster::RenderBg()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
    SDL_RenderFillRect(renderer, &black_screen);
}

void RayCaster::MoveBlocker()
{
    for (auto &blocker : blockers)
    {
        if (blocker.direction) // goes up
        {
            if (blocker.y <= 0)
                blocker.direction = false; // change direction
            else
                blocker.y -= speed;
        }
        else // goes down
        {
            if ((blocker.y + blocker.h) >= WINDOW_HEIGHT)
                blocker.direction = true;
            else
                blocker.y += speed;
        }
    }
}

// checks if (x,y) position is inside blocker or not
bool RayCaster::CheckCollision(Blocker *blocker, float x, float y)
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