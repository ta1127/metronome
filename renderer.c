#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<stdio.h>
#include"init.h"

void render(Variables* v)
{

    // 画面クリア
    SDL_SetRenderDrawColor(v -> app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(v -> app.renderer);

    // ボタン描画
    SDL_SetRenderDrawColor(v -> app.renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(v -> app.renderer, &v -> ui.run_metronome_button.button);

    //スライダー描画
    // バー
    SDL_SetRenderDrawColor(v -> app.renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(v -> app.renderer, &v -> ui.slider.slider_bar);

    // つまみ
    SDL_SetRenderDrawColor(v -> app.renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(v -> app.renderer, &v -> ui.slider.slider_knob);

    SDL_Color text_color = {255,255,255,255};

    SDL_Surface* surface = TTF_RenderText_Solid(v -> resources.font, v -> ui.bpm_text, strlen(v -> ui.bpm_text), text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(v -> app.renderer, surface);

    SDL_FRect bpm_display = {100, 50, surface->w, surface->h};
    SDL_RenderTexture(v -> app.renderer, texture, NULL, &bpm_display);

        
    // 表示
    SDL_RenderPresent(v -> app.renderer);

    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);

}