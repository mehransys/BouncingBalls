#include "textBox.h"

textBox::textBox(){}

void textBox::load(int x, int y, const char *texture_file,const char *font_name, SDL_Color color){
    font_size = 50;
    texture = IMG_LoadTexture(renderer,texture_file);
    SDL_QueryTexture(texture,NULL,NULL,&frame.w,&frame.h);
    frame.x = x;
    frame.y = y;
    x_pos = x;
    y_pos = y;
    font = TTF_OpenFont(font_name,font_size);
    text_color = color;
}
void textBox::draw(const char *text){
    text_surface = TTF_RenderText_Solid(font,text,text_color);
    text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
    SDL_QueryTexture(text_texture,NULL,NULL,&text_frame.w,&text_frame.h);
    text_frame.x = x_pos + (frame.w - text_frame.w)/2;
    text_frame.y = y_pos + (frame.h - text_frame.h)/2;
    SDL_RenderCopy(renderer,texture,NULL,&frame);
    SDL_RenderCopy(renderer,text_texture,NULL,&text_frame);
}
void textBox::clean(){
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
}

