#include "Button.h"

Button::Button(){
    mouse_rect.h = 3;
    mouse_rect.w = 3;
}

void Button::draw(int x , int y, const char *out, const char *hover){
    out_texture = IMG_LoadTexture(renderer,out);
    hover_texture = IMG_LoadTexture(renderer,hover);
    SDL_QueryTexture(out_texture,NULL,NULL,&frame.w,&frame.h);
    frame.x = x;
    frame.y = y;
    SDL_RenderCopy(renderer,out_texture,NULL,&frame);
}

void Button::update(){
    mouse_rect.x = cursur.x;
    mouse_rect.y = cursur.y;

    if (SDL_HasIntersection(&frame,&mouse_rect)){
        button_state = MOUSE_OVER;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT){
            button_state = CLICKED;
        }
    }
    if (!SDL_HasIntersection(&frame,&mouse_rect)){
        button_state = MOUSE_OUT;
    }

    if (button_state == MOUSE_OUT){
            SDL_RenderCopy(renderer,out_texture,NULL,&frame);
    }
    else if (button_state == MOUSE_OVER){
            SDL_RenderCopy(renderer,hover_texture,NULL,&frame);
    }
}

void Button::clean(){
    SDL_DestroyTexture(out_texture);
    SDL_DestroyTexture(hover_texture);
}
