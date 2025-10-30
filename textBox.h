#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SDL2/SDL2/SDL.h>
#include <SDL2/SDL2/SDL_mouse.h>
#include <SDL2/SDL2/SDL_image.h>
#include <SDL2/SDL2/SDL_ttf.h>

extern SDL_Renderer *renderer;

class textBox
{
    public:
    textBox();

    SDL_Texture *texture = NULL;
    SDL_Texture *text_texture = NULL;
    SDL_Surface *text_surface = NULL;
    TTF_Font *font = NULL;
    SDL_Rect text_frame;
    SDL_Rect frame;
    SDL_Color text_color;
    int x_pos,y_pos;
    int font_size;

    void load(int x, int y, const char *texture_file,const char *font_name, SDL_Color color);
    void draw(const char *text);

    void clean();
};

#endif // TEXTBOX_H
