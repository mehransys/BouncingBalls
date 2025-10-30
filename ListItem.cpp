#include "ListItem.h"

listItem::listItem()
{
    mouse_rect.h = 3;
    mouse_rect.w = 3;
}

void listItem::load(const char *text,const char *font_name, SDL_Color color,const char *out, const char *hover){
    out_texture = IMG_LoadTexture(renderer,out);
    hover_texture = IMG_LoadTexture(renderer,hover);
    font = TTF_OpenFont(font_name,30);
    text_surface = TTF_RenderText_Solid(font,text,color);
    text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
    SDL_QueryTexture(out_texture,NULL,NULL,&frame.w,&frame.h);
    SDL_QueryTexture(text_texture,NULL,NULL,&text_frame.w,&text_frame.h);
}

void listItem::draw(int x , int y){
    frame.x = x;
    frame.y = y;
    text_frame.x = x + (frame.w - text_frame.w)/2;
    text_frame.y = y + (frame.h - text_frame.h)/2;

    SDL_RenderCopy(renderer,out_texture,NULL,&frame);
    SDL_RenderCopy(renderer,text_texture,NULL,&text_frame);
}

void listItem::clean(){
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(out_texture);
    SDL_DestroyTexture(hover_texture);
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
}
