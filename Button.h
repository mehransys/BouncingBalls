#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL2/SDL_mouse.h>
#include <SDL2/SDL2/SDL_image.h>

extern SDL_Renderer *renderer;
extern SDL_Event event;
extern SDL_Point cursur;

class Button{
public:
    enum buttonState
    {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
    };

    buttonState button_state;

    SDL_Texture *hover_texture = NULL;
    SDL_Texture *out_texture = NULL;
    SDL_Rect frame;
    SDL_Rect mouse_rect;

    Button();

    void draw(int x , int y, const char *out, const char *hover);
    void update();
    void clean();
};

#endif // BUTTON_H
