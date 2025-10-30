#ifndef SCORESTABLEITEM_H
#define SCORESTABLEITEM_H

#include "ListItem.h"

extern SDL_Renderer *renderer;
extern SDL_Renderer* renderer;
extern SDL_Event event;
extern SDL_Point cursur;

class scoresTableItem{
public:
    listItem name;
    listItem score;
    int height;

    void load(const char *name_text, const char *score_text,const char *name_texture,const char *score_texture,const char *font,SDL_Color text_color);
    void draw(int x, int y);
    void clean();

};


#endif // SCORESTABLEITEM_H
