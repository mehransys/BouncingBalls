#include "List.h"

List::List()
{
    body.x = 50;
    body.y = 50;
    body.w = 560;
}

void List::addItem(const char *name_text, const char *score_text,const char *name_texture,const char *score_texture,const char *font,SDL_Color text_color){
    scoresTableItem item;
    item.load(name_text,score_text,name_texture,score_texture,font,text_color);
    items.push_back(item);
}

void List::draw(int x, int y){
    int curr_pos = y;
    for (int i = 0 ; i < items.size() ; i++){
        items[i].draw(x,curr_pos);
        curr_pos += items[i].height+10;
    }
}

void List::clean(){
    for (int i = 0 ; i < items.size() ; i++)
        items[i].clean();
    items.clear();
}
