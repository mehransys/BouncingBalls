#include "scoresTableItem.h"

void scoresTableItem::load(const char *name_text, const char *score_text,const char *name_texture,const char *score_texture,const char *font,SDL_Color text_color){
    name.load(name_text,font,text_color,name_texture,name_texture);
    score.load(score_text,font,text_color,score_texture,score_texture);
    height = name.frame.h;
}

void scoresTableItem::draw(int x, int y){
    name.draw(x,y);
    score.draw(x+name.frame.w+10,y);
}

void scoresTableItem::clean(){
    name.clean();
    score.clean();
}
