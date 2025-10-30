#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <SDL2/SDL2/SDL.h>
#include <SDL2/SDL2/SDL_mouse.h>
#include <SDL2/SDL2/SDL_image.h>
#include <SDL2/SDL2/SDL_ttf.h>

extern SDL_Renderer *renderer;
extern SDL_Event event;
extern SDL_Point cursur;

class ToggleButton
{
public:

    enum buttonState
    {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2,
    TOGGLED = 3
    };

    buttonState button_state;

    SDL_Texture *hover_texture = NULL;
    SDL_Texture *out_texture = NULL;
    SDL_Texture *toggle_texture = NULL;
    SDL_Texture *text_texture = NULL;
    SDL_Surface *text_surface = NULL;
    TTF_Font *font = NULL;
    SDL_Color text_color;
    SDL_Rect text_frame;
    SDL_Rect frame;
    SDL_Rect mouse_rect;

    ToggleButton();

    void draw(int x , int y,const char *text,SDL_Color text_color,const char *font_name ,const char *out, const char *hover, const char* toggle);
    void update(bool toggled);
    void clean();
};

#endif // TOGGLEBUTTON_H
