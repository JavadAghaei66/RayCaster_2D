#include "RayCaster.h"

RayCaster::RayCaster()
{
    is_running = true;
    
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

    surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        cout << "Surface creation failed: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void RayCaster::RenderRays()
{
    rayRenderer = SDL_GetRenderer(window);
    SDL_SetRenderDrawColor(rayRenderer, 255, 0, 0, 255); // white

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

            SDL_RenderDrawPoint(rayRenderer, (int)x, (int)y);
        }
    }

    SDL_RenderPresent(rayRenderer);
}

void RayCaster::MoveBlocker()
{
    if (direction) // it goes up
    {
        if (blocker.y <= 0)
            direction = false; // change direction
        else
            blocker.y -= speed;
    }
    else // it goes down
    {
        if ((blocker.y + blocker.h) >= WINDOW_HEIGHT)
            direction = true;
        else
            blocker.y += speed;
    }
}

void RayCaster::RenderBlocker()
{
    blockerRenderer = SDL_GetRenderer(window);
    SDL_SetRenderDrawColor(blockerRenderer, 255, 255, 255, 255); // white

    SDL_RenderFillRect(blockerRenderer, &blocker);
    SDL_RenderPresent(blockerRenderer);
}

void RayCaster::RenderBg()
{
    // black background
    bgRenderer = SDL_GetRenderer(window);
    SDL_Rect black_screen = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_SetRenderDrawColor(bgRenderer, 0, 0, 0, 1); // black
    SDL_RenderFillRect(bgRenderer, &black_screen);
}

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

void RayCaster::Delay()
{
    SDL_Delay(0.001);
}

void RayCaster::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            is_running = false;
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            light_source_X = event.button.x;
            light_source_Y = event.button.y;
            RenderBg();
            RenderBlocker();
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
            RenderRays();
    }
}

void RayCaster::Quit()
{
    if (window)
    {
        SDL_DestroyRenderer(rayRenderer);
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}