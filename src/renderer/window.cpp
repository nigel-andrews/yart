#include "window.h"

#include <stdexcept>

namespace
{
    bool init = false;
} // namespace

window::window(int width, int height)
    : width_(width)
    , height_(height)
{
    if (!init)
        throw std::runtime_error(
            "Attempting to create window when SDL2 is not initialised");

    if (SDL_CreateWindowAndRenderer(width_, height_, 0, &window_, &renderer_)
        == -1)
        throw std::runtime_error("Failed to create window and renderer");

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
    SDL_RenderClear(renderer_);

    format_ = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
}

window::~window()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_FreeFormat(format_);
}

void init_graphics()
{
    init = !SDL_Init(SDL_INIT_VIDEO);

    if (!init)
        throw std::runtime_error("Failed to initialise SDL2");
}

void destroy_graphics()
{
    SDL_Quit();
}
