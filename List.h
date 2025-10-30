#ifndef LIST_H
#define LIST_H

#include "scoresTableItem.h"
#include <vector>

class List{
private:
    const int padding = 20;
public:

    std::vector <scoresTableItem> items;
    SDL_Rect body;

    List();
    void addItem(const char *name_text, const char *score_text,const char *name_texture,const char *score_texture,const char *font,SDL_Color text_color);
    void draw(int x, int y);
    void clean();
};


#endif // LIST_H
