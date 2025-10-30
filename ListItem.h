#ifndef LISTITEM_H
#define LISTITEM_H

#include "SDL2/SDL2/SDL.h"
#include "SDL2/SDL2/SDL_image.h"
#include "SDL2/SDL2/SDL_ttf.h"

extern SDL_Renderer *renderer;

class listItem{
public:

    SDL_Texture *hover_texture = NULL;
    SDL_Texture *out_texture = NULL;
    SDL_Texture *text_texture = NULL;
    SDL_Surface *text_surface = NULL;
    TTF_Font *font = NULL;
    SDL_Rect text_frame;
    SDL_Rect frame;
    SDL_Color text_color;
    SDL_Rect mouse_rect;

    listItem();

    void load(const char *text,const char *font_name, SDL_Color color,const char *out, const char *hover);
    void draw(int x , int y);
    void clean();

};

#endif // LISTITEM_H
