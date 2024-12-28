#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <glm/vec3.hpp>

#include "utils/traits.h"

namespace
{
    inline Uint8 r(Uint32 colour)
    {
        return (colour >> 16) & 0xFF;
    }

    inline Uint8 g(Uint32 colour)
    {
        return (colour >> 8) & 0xFF;
    }

    inline Uint8 b(Uint32 colour)
    {
        return colour & 0xFF;
    }
} // namespace

class window : utils::non_copyable
{
public:
    window(int width, int height);
    ~window();

    void draw_point(Uint32 colour, int i, int j)
    {
        SDL_SetRenderDrawColor(renderer_, r(colour), g(colour), b(colour), 255);
        SDL_RenderDrawPoint(renderer_, i, j);
    }

    void present()
    {
        SDL_RenderPresent(renderer_);
    }

    auto format_get()
    {
        return format_;
    };

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_PixelFormat* format_;

    int width_;
    int height_;
};

void init_graphics();
void destroy_graphics();
