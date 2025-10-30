#include "ToggleButton.h"

ToggleButton::ToggleButton(){
    mouse_rect.h = 3;
    mouse_rect.w = 3;
}

void ToggleButton::draw(int x , int y, const char *text, SDL_Color text_color,const char *font_name, const char *out, const char *hover, const char* toggle){
    out_texture = IMG_LoadTexture(renderer,out);
    hover_texture = IMG_LoadTexture(renderer,hover);
    toggle_texture = IMG_LoadTexture(renderer,toggle);
    font = TTF_OpenFont(font_name,30);
    text_surface = TTF_RenderText_Solid(font,text,text_color);
    text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
    SDL_QueryTexture(out_texture,NULL,NULL,&frame.w,&frame.h);
    SDL_QueryTexture(text_texture,NULL,NULL,&text_frame.w,&text_frame.h);
    frame.x = x;
    frame.y = y;
    text_frame.x = x + (frame.w - text_frame.w)/2;
    text_frame.y = y + (frame.h - text_frame.h)/2;
    SDL_RenderCopy(renderer,out_texture,NULL,&frame);
    SDL_RenderCopy(renderer,text_texture,NULL,&frame);
}

void ToggleButton::update(bool toggled){
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

    if (button_state == MOUSE_OUT && toggled == false){
        SDL_RenderCopy(renderer,out_texture,NULL,&frame);
    }
    if (button_state == MOUSE_OUT && toggled == true){
        SDL_RenderCopy(renderer,toggle_texture,NULL,&frame);
    }
    if (button_state == MOUSE_OVER){
        SDL_RenderCopy(renderer,hover_texture,NULL,&frame);
    }
    SDL_RenderCopy(renderer,text_texture,NULL,&text_frame);
}

void ToggleButton::clean(){
    SDL_DestroyTexture(out_texture);
    SDL_DestroyTexture(hover_texture);
    SDL_DestroyTexture(toggle_texture);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
}
