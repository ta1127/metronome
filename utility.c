#include <SDL3/SDL.h>
#include<stdio.h>

bool has_clicked(SDL_FRect button,SDL_Event event)
{
    bool b;
    float clicked_position_x = event.button.x;
    float clicked_position_y = event.button.y;

    b = (clicked_position_x <= button.x  + button.w &&
         clicked_position_x >= button.x &&
         clicked_position_y <= button.y  + button.h &&
         clicked_position_y >= button.y);

    return b;
}

SDL_FRect create_rect(float x, float y, float w, float h)
{
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}