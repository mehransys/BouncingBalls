#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <SDL2/SDL2/SDL.h>
#include <SDL2/SDL2/SDL_mouse.h>
#include <SDL2/SDL2/SDL_image.h>
#include <SDL2/SDL2/SDL_ttf.h>

void init();
void close();
void handlequit();

void show_main_window();
void show_main_settings();
void show_scores_table();
void show_start_menu();
void show_pause_menu();
void show_gameover_menu();

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;
extern SDL_Point cursur;
extern SDL_Texture *background;

extern bool quit;
extern bool main_window;
extern bool main_settings;
extern bool scores_table;
extern bool start_menu;
extern bool pause_menu;
extern bool gameover_menu;
extern int theme;

const int WINDOW_HEIGHT = 650;
const int WINDOW_WIDTH = 700;

#endif // FUNCTIONS_H_INCLUDED
