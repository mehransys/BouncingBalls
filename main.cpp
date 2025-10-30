#include "Button.h"
#include "List.h"
#include <time.h>
#include "ListItem.h"
#include "textBox.h"
#include <iostream>
#include "ToggleButton.h"
#include <string>
#include <SDL2/SDL2/SDL_mixer.h>
#include <SDL2/SDL2/SDL2_gfx.h>
#include <fstream>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Point cursur;
Mix_Music *music = NULL;
char *text_font="font1.ttf";

struct balls{
    float x,y,dx,dy,radius;bool condition;char color;bool down_fall;bool checked;bool canon;
};

bool quit;
bool theme_changed = true;
bool main_window = true;
bool main_settings = false;
bool scores_table = false;
bool start_menu = false;
bool pause_menu = false;
bool gameover_menu = false;
bool play_state = false;
bool sound = true;
bool volume_changed = true;
bool track_name_changed = true;
bool score_changed = true;

bool easy_mode = false;
bool difficult_mode = false;
bool standard_mode = true;
bool infinite_mode = true;
bool timer_mode = false;
bool normal_mode = false;

string theme_name;
string volume_name;
string track_name;
string user_name;
int volume = 64;
int track_code = 1;
int theme_code = 1;
int score = 50;
int count_score=0;
int hardness = 1;

int start_time = 0;
int duration = 0;

SDL_Color text_color={0x00,0x00,0xFF};

void init();
void close();
void handle_events();
void show_main_window();
void show_main_settings();
void show_scores_table();
void show_start_menu();
void show_pause_menu();
void show_gameover_menu();
void show_game_playing();
void handle_sound();
void load_themes();
////////////////////////////////////////////
bool intersect(double x1, double y1, double x2, double y2, double r);
vector<char>  print_random_colors_ball(int n , int hardness);
vector<char> canon_colors;
vector<char> canon_color;
vector<struct balls> new_ball(14);
vector<char>  print_random_colors_canon_ball(int n , int hardness,vector<char> &canon_colors);
void check_ball(vector<vector<struct balls>> &ball , float x , float y , char color , int count , vector<struct balls> &ans,vector<struct balls> &ans2 );
vector<vector<struct balls>> ball(4);
vector<struct balls> canon_ball;
int count = 0;
int count_true_while = 1;
int count_white_ball = 0;
int count_2=0;
int count_4=0;
balls new_canon_ball;
void circle (SDL_Renderer *Renderer ,int x, int y , int radius , char  color );
void init_balls();
///////////////////////////////////////////
const int WINDOW_HEIGHT = 650;
const int WINDOW_WIDTH = 700;

//start menu
Button start_menu_play;
Button start_menu_home;
ToggleButton start_menu_easy;
ToggleButton start_menu_difficult;
ToggleButton start_menu_standard;
ToggleButton start_menu_infinity_mode;
ToggleButton start_menu_timer_mode;
ToggleButton start_menu_normal_mode;
listItem mode_padding;
listItem difficulty_padding;

SDL_Texture *background = NULL;

int main (int argc, char** argv){
    init();
    /////////////////////////////////////////////////////
    init_balls();
    /////////////////////////////////////////////////////////
    while(!quit){
        SDL_GetMouseState(&cursur.x,&cursur.y);
        SDL_RenderClear(renderer);
        ////////////////////////////////////////////

        load_themes();
        SDL_RenderCopy(renderer,background,NULL,NULL);
        handle_sound();

        ////////////////////////////////////////////

        if(main_window){
            show_main_window();
        }
        else if(start_menu){
            show_start_menu();
        }
        else if(main_settings){
            show_main_settings();
        }
        else if(scores_table){
            show_scores_table();
        }
        else if(pause_menu){
            show_pause_menu();
        }
        else if(gameover_menu){
            show_gameover_menu();
        }
        else if(play_state){
            show_game_playing();
        }

        ////////////////////////////////////////////
        SDL_Delay(2);
        SDL_RenderPresent(renderer);
        handle_events();
    }
    close();
    return 0;
}
void init(){
SDL_Init(SDL_INIT_EVERYTHING);
window = SDL_CreateWindow("BP", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
TTF_Init();
srand(time(0));
Mix_Init(0);
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,1024);
renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE);
SDL_StartTextInput();
SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
SDL_RenderClear(renderer);
}
void handle_events(){
    if (SDL_PollEvent(&event)){ // mouse and keyboard handling
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            quit = true;
        }
    }
    if(event.type == SDL_TEXTINPUT && start_menu){
        user_name += event.text.text;
    }
    if(event.type == SDL_KEYDOWN && user_name.size() > 0 && start_menu){
        if (event.key.keysym.sym == SDLK_BACKSPACE){
            user_name.pop_back();
        }
    }
    if(event.type==SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && play_state && !pause_menu){
        count_white_ball++;
                int r=0, g=0, b=0, y=0, p=0;
                for(int i=0; i<ball[ball.size()-1].size();i++)
                {
                    if(ball[ball.size()-1][i].color=='r') r++;
                    if(ball[ball.size()-1][i].color=='g') g++;
                    if(ball[ball.size()-1][i].color=='b') b++;
                    if(ball[ball.size()-1][i].color=='y') y++;
                    if(ball[ball.size()-1][i].color=='p') p++;
                }
                canon_colors.clear();
                if(r!=0) canon_colors.push_back('r');
                if(g!=0) canon_colors.push_back('g');
                if(b!=0) canon_colors.push_back('b');
                if(y!=0) canon_colors.push_back('y');
                if(p!=0) canon_colors.push_back('p');
                if(count_white_ball%7==0)
                {
                    canon_color.erase(canon_color.begin());
                    canon_color.push_back('A');
                    new_canon_ball.color= canon_color[0];
                }
                else
                {
                    canon_color.erase(canon_color.begin());
                    canon_color.push_back(print_random_colors_canon_ball(5,hardness,canon_colors)[0]);
                    new_canon_ball.color= canon_color[0];
            }
    }
     if(event.type==SDL_MOUSEBUTTONDOWN && play_state){
        //count_white_ball++;
                count_2++;

                double tan =(cursur.y-new_canon_ball.y)/(cursur.x-new_canon_ball.x);
                if(cursur.x<WINDOW_WIDTH/2)
                {
                    new_canon_ball.dx= -10*cos(atan(tan));
                    new_canon_ball.dy=-10*sin(atan(tan));
                }
                if(cursur.x>WINDOW_WIDTH/2)
                {
                    new_canon_ball.dx=10*cos(atan(tan));
                    new_canon_ball.dy=10*sin(atan(tan));
                }
                canon_ball.push_back(new_canon_ball);
                int r=0, g=0, b=0, y=0, p=0;
                for(int i=0; i<ball[ball.size()-1].size();i++)
                {
                    if(ball[ball.size()-1][i].color=='r') r++;
                    if(ball[ball.size()-1][i].color=='g') g++;
                    if(ball[ball.size()-1][i].color=='b') b++;
                    if(ball[ball.size()-1][i].color=='y') y++;
                    if(ball[ball.size()-1][i].color=='p') p++;
                }
                canon_colors.clear();
                if(r!=0) canon_colors.push_back('r');
                if(g!=0) canon_colors.push_back('g');
                if(b!=0) canon_colors.push_back('b');
                if(y!=0) canon_colors.push_back('y');
                if(p!=0) canon_colors.push_back('p');
                if(count_white_ball%7==0)
                {
                    canon_color.erase(canon_color.begin());
                    canon_color.push_back('A');
                    new_canon_ball.color= canon_color[0];
                }
                else
                {
                    canon_color.erase(canon_color.begin());
                    canon_color.push_back(print_random_colors_canon_ball(5,hardness,canon_colors)[0]);
                    new_canon_ball.color= canon_color[0];
                }
     }
}
void close(){
SDL_DestroyTexture(background);
SDL_DestroyWindow(window);
SDL_DestroyRenderer(renderer);
TTF_Quit();
Mix_Quit();
SDL_Quit();
}
void show_main_window(){
    //main window buttons
    Button main_window_settings_button;
    Button main_window_play_button;
    Button main_window_scores_button;
    SDL_Texture *logo = NULL;
    SDL_Rect logo_rect;
    user_name.clear();
     /////////////////////////// main window
    if (theme_code == 1){
        main_window_settings_button.draw(150,500,"Theme1/1/settings.png","Theme1/2/settings.png");
        main_window_play_button.draw(300,500,"Theme1/1/play.png","Theme1/2/play.png");
        main_window_scores_button.draw(450,505,"Theme1/1/scores.png","Theme1/2/scores.png");
    }
    else if (theme_code == 2){
        main_window_settings_button.draw(150,500,"Theme2/1/settings.png","Theme2/2/settings.png");
        main_window_play_button.draw(300,500,"Theme2/1/play.png","Theme2/2/play.png");
        main_window_scores_button.draw(450,505,"Theme2/1/scores.png","Theme2/2/scores.png");
    }
    else if (theme_code == 3){
        main_window_settings_button.draw(150,500,"Theme3/1/settings.png","Theme3/2/settings.png");
        main_window_play_button.draw(300,500,"Theme3/1/play.png","Theme3/2/play.png");
        main_window_scores_button.draw(450,505,"Theme3/1/scores.png","Theme3/2/scores.png");
    }

    logo = IMG_LoadTexture(renderer,"Theme1/logo.png");

    logo_rect.x = 100;
    logo_rect.y = 50;
    logo_rect.h = 500;
    logo_rect.w = 500;

    SDL_RenderCopy(renderer,logo,NULL,&logo_rect);

    main_window_settings_button.update();
    main_window_play_button.update();
    main_window_scores_button.update();

    if (main_window_scores_button.button_state == 2){
        scores_table = true;
        main_window = false;
    }
    else if (main_window_play_button.button_state == 2){
        start_menu = true;
        main_window = false;
    }
    else if(main_window_settings_button.button_state == 2){
        main_settings = true;
        main_window = false;
    }

    main_window_settings_button.clean();
    main_window_play_button.clean();
    main_window_scores_button.clean();
    SDL_DestroyTexture(logo);
}
void show_scores_table(){

    //score table
    Button scores_table_home;
    static List scores_table_list;

    ////////////////////////// scores_table
    string name_box_path;
    string score_box_path;
    ////////////////////////////
    if(theme_code == 1){
        scores_table_home.draw(300,540,"Theme1/1/home.png","Theme1/2/home.png");
        name_box_path = "Theme1/table_name_box.png";
        score_box_path = "Theme1/raw_square.png";
    }
    else if(theme_code == 2){
        scores_table_home.draw(300,540,"Theme2/1/home.png","Theme2/2/home.png");
        name_box_path = "Theme2/table_name_box.png";
        score_box_path = "Theme2/raw_square.png";
    }
    else {
        scores_table_home.draw(300,540,"Theme3/1/home.png","Theme3/2/home.png");
        name_box_path = "Theme3/table_name_box.png";
         score_box_path = "Theme3/raw_square.png";
    }

    if (score_changed){
        scores_table_list.clean();

        vector <string> lines;
        vector <string> names;
        vector <string> scores;
        string line;

        ifstream scores_file;
        scores_file.open("scores.txt");

        while (getline(scores_file,line)){
            lines.push_back(line);
        }
        scores_file.close();

        for (int i = 0 ; i < lines.size() ; i++){
            string name,score;
            int dashPos = lines[i].find('-');
            name = lines[i].substr(0,dashPos);
            score = lines[i].substr(dashPos+1);
            names.push_back(name);
            scores.push_back(score);
        }

        int n = scores.size();

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (stoi(scores[j]) < stoi(scores[j + 1])) {
                    swap(scores[j], scores[j + 1]);
                    swap(names[j],names[j + 1]);
                }
            }
        }

        for (int i = 0 ; i < n ; i++){
            scores_table_list.addItem(names[i].c_str(),scores[i].c_str(),name_box_path.c_str(),score_box_path.c_str(),text_font,text_color);
        }

        score_changed = false;
    }

    scores_table_list.draw(70,20);
    scores_table_home.update();

    if(scores_table_home.button_state == 2){
        scores_table = false;
        main_window = true;
    }

    scores_table_home.clean();
}
void show_main_settings(){
    //main settings buttons
    Button main_settings_volume_up;
    Button main_settings_volume_down;
    Button main_settings_theme_next;
    Button main_settings_theme_previous;
    Button main_settings_volume_enabled;
    Button main_settings_volume_next;
    Button main_settings_volume_previous;
    Button main_settings_home;
    textBox main_settings_theme_prop;
    textBox main_settings_volume_prop;
    textBox main_settings_sound_prop;
     ////////////////////////// main_settings
    if(theme_code == 1){
        main_settings_theme_next.draw(130,70,"Theme1/1/arrowl.png","Theme1/2/arrowl.png");
        main_settings_theme_previous.draw(470,70,"Theme1/1/arrowr.png","Theme1/2/arrowr.png");
        main_settings_volume_next.draw(130,190,"Theme1/1/arrowl.png","Theme1/2/arrowl.png");
        main_settings_volume_previous.draw(470,190,"Theme1/1/arrowr.png","Theme1/2/arrowr.png");
        main_settings_volume_up.draw(130,310,"Theme1/1/minus.png","Theme1/2/minus.png");
        main_settings_volume_down.draw(470,310,"Theme1/1/plus.png","Theme1/2/plus.png");
        if(sound){
            main_settings_volume_enabled.draw(240,540,"Theme1/1/sound_off.png","Theme1/2/sound_off.png");
        }
        else {
            main_settings_volume_enabled.draw(240,540,"Theme1/1/sound_on.png","Theme1/2/sound_on.png");
        }
        main_settings_home.draw(360,540,"Theme1/1/home.png","Theme1/2/home.png");
        main_settings_theme_prop.load(250,65,"Theme1/status_box.png",text_font,text_color);
        main_settings_sound_prop.load(250,185,"Theme1/status_box.png",text_font,text_color);
        main_settings_volume_prop.load(250,305,"Theme1/status_box.png",text_font,text_color);
    }
    else if(theme_code == 2){
        main_settings_theme_next.draw(130,70,"Theme2/1/arrowl.png","Theme2/2/arrowl.png");
        main_settings_theme_previous.draw(470,70,"Theme2/1/arrowr.png","Theme2/2/arrowr.png");
        main_settings_volume_next.draw(130,190,"Theme2/1/arrowl.png","Theme2/2/arrowl.png");
        main_settings_volume_previous.draw(470,190,"Theme2/1/arrowr.png","Theme2/2/arrowr.png");
        main_settings_volume_up.draw(130,310,"Theme2/1/minus.png","Theme2/2/minus.png");
        main_settings_volume_down.draw(470,310,"Theme2/1/plus.png","Theme2/2/plus.png");
        if(sound){
            main_settings_volume_enabled.draw(240,540,"Theme2/1/sound_off.png","Theme2/2/sound_off.png");
        }
        else {
            main_settings_volume_enabled.draw(240,540,"Theme2/1/sound_on.png","Theme2/2/sound_on.png");
        }
        main_settings_home.draw(360,540,"Theme2/1/home.png","Theme2/2/home.png");
        main_settings_theme_prop.load(250,65,"Theme2/status_box.png",text_font,text_color);
        main_settings_sound_prop.load(250,185,"Theme2/status_box.png",text_font,text_color);
        main_settings_volume_prop.load(250,305,"Theme2/status_box.png",text_font,text_color);
    }
    else {
        main_settings_theme_next.draw(130,70,"Theme3/1/arrowl.png","Theme3/2/arrowl.png");
        main_settings_theme_previous.draw(470,70,"Theme3/1/arrowr.png","Theme3/2/arrowr.png");
        main_settings_volume_next.draw(130,190,"Theme3/1/arrowl.png","Theme3/2/arrowl.png");
        main_settings_volume_previous.draw(470,190,"Theme3/1/arrowr.png","Theme3/2/arrowr.png");
        main_settings_volume_up.draw(130,310,"Theme3/1/minus.png","Theme3/2/minus.png");
        main_settings_volume_down.draw(470,310,"Theme3/1/plus.png","Theme3/2/plus.png");
        if(sound){
            main_settings_volume_enabled.draw(240,540,"Theme3/1/sound_off.png","Theme3/2/sound_off.png");
        }
        else {
            main_settings_volume_enabled.draw(240,540,"Theme3/1/sound_on.png","Theme3/2/sound_on.png");
        }
        main_settings_home.draw(360,540,"Theme3/1/home.png","Theme3/2/home.png");
        main_settings_theme_prop.load(250,65,"Theme3/status_box.png",text_font,text_color);
        main_settings_sound_prop.load(250,185,"Theme3/status_box.png",text_font,text_color);
        main_settings_volume_prop.load(250,305,"Theme3/status_box.png",text_font,text_color);
    }

    main_settings_theme_next.update();
    main_settings_theme_previous.update();
    main_settings_volume_next.update();
    main_settings_volume_previous.update();
    main_settings_volume_up.update();
    main_settings_volume_down.update();
    main_settings_volume_enabled.update();
    main_settings_home.update();
    main_settings_theme_prop.draw(theme_name.c_str());
    main_settings_sound_prop.draw(track_name.c_str());
    main_settings_volume_prop.draw(to_string(volume).c_str());

    if (main_settings_home.button_state == 2){
        main_window = true;
        main_settings = false;
    }
    else if (main_settings_theme_next.button_state == 2){
        theme_code++;
        if (theme_code > 3) theme_code = 1;
        ofstream file;
        file.open("theme.txt");
        file << theme_code;
        file.close();
        theme_changed = true;
        score_changed = true;
    }
    else if (main_settings_theme_previous.button_state == 2){
        theme_code--;
        if (theme_code <= 0) theme_code = 3;
        ofstream file;
        file.open("theme.txt");
        file << theme_code;
        file.close();
        theme_changed = true;
        score_changed = true;
    }
    else if (main_settings_volume_down.button_state == 2){
        volume += 4;
        if (volume >= 128)volume = 4;
        volume_changed = true;
    }
    else if (main_settings_volume_up.button_state == 2){
        volume -= 4;
        if (volume <= 0) volume = 128;
        volume_changed = true;
    }
    else if (main_settings_volume_next.button_state == 2){
        track_code++;
        if (track_code > 3) track_code = 1;
        ofstream file;
        file.open("music.txt");
        file << track_code;
        file.close();
        track_name_changed = true;
    }
    else if (main_settings_volume_previous.button_state == 2){
        track_code--;
        if (track_code <= 0) track_code = 3;
        ofstream file;
        file.open("music.txt");
        file << track_code;
        file.close();
        track_name_changed = true;
    }
    else if (main_settings_volume_enabled.button_state == 2){
        sound = !sound;
    }

    main_settings_theme_next.clean();
    main_settings_theme_previous.clean();
    main_settings_volume_next.clean();
    main_settings_volume_previous.clean();
    main_settings_volume_up.clean();
    main_settings_volume_down.clean();
    main_settings_volume_enabled.clean();
    main_settings_home.clean();
    main_settings_theme_prop.clean();
    main_settings_sound_prop.clean();
    main_settings_volume_prop.clean();
}
void show_gameover_menu(){
    //game over menu
    Button gameover_home;
    textBox gameover_score;
    if (theme_code == 1){
        gameover_home.draw(300,540,"Theme1/1/home.png","Theme1/2/home.png");
        gameover_score.load(50,50,"Theme1/score_back.png",text_font,text_color);
    }
    else if (theme_code == 2){
        gameover_home.draw(300,540,"Theme2/1/home.png","Theme2/2/home.png");
        gameover_score.load(50,50,"Theme2/score_back.png",text_font,text_color);
    }
    else {
        gameover_home.draw(300,540,"Theme3/1/home.png","Theme3/2/home.png");
        gameover_score.load(50,50,"Theme3/score_back.png",text_font,text_color);
    }

    gameover_home.update();
    gameover_score.draw(to_string(score).c_str());

    if (gameover_home.button_state == 2){
        score_changed = true;
        vector <string> lines;
        vector <string> names;
        vector <int> scores;
        string line;
        bool user_exists = false;

        ifstream scores_file;
        scores_file.open("scores.txt");

        while (getline(scores_file,line)){
            lines.push_back(line);
        }
        scores_file.close();

        for (int i = 0 ; i < lines.size() ; i++){
            string name;
            int score;
            int dashPos = lines[i].find('-');
            name = lines[i].substr(0,dashPos);
            score = stoi(lines[i].substr(dashPos+1));
            names.push_back(name);
            scores.push_back(score);
        }

        if(user_exists == false){
            for (int i = 0 ; i < lines.size() ; i++){
                if (names[i] == user_name){
                    scores[i] = score;
                    user_exists = true;
                }
            }
        }
        if (user_exists == false){
            scores.push_back(score);
            names.push_back(user_name);
        }

        ofstream file("scores.txt");
        for (int i = 0; i < scores.size(); i++){
            file << names[i] << '-' << scores[i] << endl;
        }
        file.close();
        gameover_menu = false;
        main_window = true;
    }

    for (int u : user_name) user_name[u] = '\0';

    gameover_home.clean();
    gameover_score.clean();
}
void show_pause_menu(){
    //pause menu
    Button pause_menu_return;
    Button pause_menu_home;
    Button pause_menu_volume_up;
    Button pause_menu_volume_down;
    Button pause_menu_change_volume_state;
    textBox pause_menu_volume;
    //////////////////////////////////////////
    if (theme_code == 1){
        pause_menu_volume_up.draw(470,200,"Theme1/1/plus.png","Theme1/2/plus.png");
        pause_menu_volume_down.draw(130,200,"Theme1/1/minus.png","Theme1/2/minus.png");
        if(sound){
            pause_menu_change_volume_state.draw(170,540,"Theme1/1/sound_off.png","Theme1/2/sound_off.png");
        }
        else {
            pause_menu_change_volume_state.draw(170,540,"Theme1/1/sound_on.png","Theme1/2/sound_on.png");
        }
        pause_menu_home.draw(290,540,"Theme1/1/home.png","Theme1/2/home.png");
        pause_menu_return.draw(410,540,"Theme1/1/play.png","Theme1/2/play.png");
        pause_menu_volume.load(250,190,"Theme1/status_box.png",text_font,text_color);
    }
    else if(theme_code == 2){
        pause_menu_volume_up.draw(470,200,"Theme2/1/plus.png","Theme2/2/plus.png");
        pause_menu_volume_down.draw(130,200,"Theme2/1/minus.png","Theme2/2/minus.png");
        if(sound){
            pause_menu_change_volume_state.draw(170,540,"Theme2/1/sound_off.png","Theme2/2/sound_off.png");
        }
        else {
            pause_menu_change_volume_state.draw(170,540,"Theme2/1/sound_on.png","Theme2/2/sound_on.png");
        }
        pause_menu_home.draw(290,540,"Theme2/1/home.png","Theme2/2/home.png");
        pause_menu_return.draw(410,540,"Theme2/1/play.png","Theme2/2/play.png");
        pause_menu_volume.load(250,200,"Theme2/status_box.png",text_font,text_color);

    }
    else {
        pause_menu_volume_up.draw(470,200,"Theme3/1/plus.png","Theme3/2/plus.png");
        pause_menu_volume_down.draw(130,200,"Theme3/1/minus.png","Theme3/2/minus.png");
        if(sound){
            pause_menu_change_volume_state.draw(170,540,"Theme3/1/sound_off.png","Theme3/2/sound_off.png");
        }
        else {
            pause_menu_change_volume_state.draw(170,540,"Theme3/1/sound_on.png","Theme3/2/sound_on.png");
        }
        pause_menu_home.draw(290,540,"Theme3/1/home.png","Theme3/2/home.png");
        pause_menu_return.draw(410,540,"Theme3/1/play.png","Theme3/2/play.png");
        pause_menu_volume.load(250,200,"Theme3/status_box.png",text_font,text_color);

    }

    pause_menu_change_volume_state.update();
    pause_menu_home.update();
    pause_menu_return.update();
    pause_menu_volume_up.update();
    pause_menu_volume_down.update();
    pause_menu_volume.draw(to_string(volume).c_str());

    if (pause_menu_home.button_state == 2){
        main_window = true;
        pause_menu = false;
    }
    else if (pause_menu_change_volume_state.button_state == 2){
        sound = !sound;
    }
    else if (pause_menu_return.button_state == 2){
        play_state = true;
        pause_menu = false;
    }
    else if (pause_menu_volume_up.button_state == 2){
        volume += 4;
        if (volume >= 128)volume = 4;
        volume_changed = true;
    }
    else if (pause_menu_volume_down.button_state == 2){
        volume -= 4;
        if (volume <= 0) volume = 128;
        volume_changed = true;
    }
    pause_menu_change_volume_state.clean();
    pause_menu_home.clean();
    pause_menu_return.clean();
    pause_menu_volume_up.clean();
    pause_menu_volume_down.clean();
    pause_menu_volume.clean();
}
void show_start_menu(){
    textBox start_menu_input;

    if(theme_code == 1){
        start_menu_input.load(20,20,"Theme1/box.png",text_font,text_color);
    }
    else if(theme_code == 2){
        start_menu_input.load(20,20,"Theme2/box.png",text_font,text_color);
    }
    else {
        start_menu_input.load(20,20,"Theme3/box.png",text_font,text_color);
    }
    //////////////////////////////////////////
    start_menu_input.draw(user_name.c_str());
    start_menu_play.update();
    start_menu_home.update();
    start_menu_easy.update(easy_mode);
    start_menu_difficult.update(difficult_mode);
    start_menu_standard.update(standard_mode);

    start_menu_normal_mode.update(normal_mode);
    start_menu_infinity_mode.update(infinite_mode);
    start_menu_timer_mode.update(timer_mode);
    /////////////////////////////////////////
    if (start_menu_home.button_state == 2){
        user_name.clear();
        start_menu = false;
        main_window = true;
    }
    else if(start_menu_play.button_state == 2){

        start_menu = false;
        play_state = true;
    }
    else if(start_menu_play.button_state == 2 && timer_mode == true){
        start_menu = false;
        play_state = true;
        start_time = SDL_GetTicks();
    }
    else if(start_menu_difficult.button_state == 2){
        difficult_mode = true;
        easy_mode = false;
        standard_mode = false;
    }
    else if(start_menu_easy.button_state == 2){
        difficult_mode = false;
        easy_mode = true;
        standard_mode = false;
    }
    else if(start_menu_standard.button_state == 2){
        difficult_mode = false;
        easy_mode = false;
        standard_mode = true;
    }
    else if(start_menu_normal_mode.button_state == 2){
        normal_mode = true;
        infinite_mode = false;
        timer_mode = false;
    }
    else if(start_menu_infinity_mode.button_state == 2){
        normal_mode = false;
        infinite_mode = true;
        timer_mode = false;
    }
    else if(start_menu_timer_mode.button_state == 2){
        normal_mode = false;
        infinite_mode = false;
        timer_mode = true;
    }
    start_menu_input.clean();
}
void show_game_playing(){
    if(difficult_mode)
        hardness=1;
    if(standard_mode)
        hardness=2;
    if(easy_mode)
        hardness=3;
    if(timer_mode) infinite_mode = true;
    //////////////////////////////////////////
    double tan =(cursur.y-new_canon_ball.y)/(cursur.x-new_canon_ball.x);
        if(cursur.x<WINDOW_WIDTH/2)
        {
            thickLineRGBA(renderer,new_canon_ball.x,new_canon_ball.y,(new_canon_ball.x)-(955*cos(atan(tan))),(new_canon_ball.y)-(955*sin(atan(tan))),4,255,255,255,255);
            if(0>=(new_canon_ball.x)-(955*cos(atan(tan))))
            {
                thickLineRGBA(renderer,0,(WINDOW_HEIGHT-25)-(WINDOW_WIDTH/2*tan),0+(955*cos(atan(tan))),(WINDOW_HEIGHT-25)-(WINDOW_WIDTH/2*tan)-(955*sin(atan(tan))),4,255,255,255,255);
            }
        }
        if(cursur.x>WINDOW_WIDTH/2)
        {
            thickLineRGBA(renderer,new_canon_ball.x,new_canon_ball.y,(new_canon_ball.x)+(955*cos(atan(tan))),(new_canon_ball.y)+(955*sin(atan(tan))),4,255,255,255,255);
            if(WINDOW_WIDTH<=(new_canon_ball.x)+(955*cos(atan(tan))))
            {
                thickLineRGBA(renderer,WINDOW_WIDTH,(WINDOW_HEIGHT-25)+(WINDOW_WIDTH/2*tan),WINDOW_WIDTH-(955*cos(atan(tan))),(WINDOW_HEIGHT-25)+(WINDOW_WIDTH/2*tan)+(955*sin(atan(tan))),4,255,255,255,255);
            }
        }

        for (int i = 0; i < ball.size(); i++)
        {
            for (int j = 0; j < ball[i].size(); j++)
            {
                if(WINDOW_HEIGHT-ball[i][j].y<=75 ) {
                            for (int i = 0; i <ball.size() ; i++)
    {
        for (int j = 0; j <ball[i].size() ; j++)
        {
            if(ball[i][j].condition==0)
            {
                count_score++;
            }
        }
    }
    if(difficult_mode)
        score=count_score*1.5;
    if(standard_mode)
        score=count_score*1;
    if(easy_mode)
        score=count_score*0.5;
                    gameover_menu = true;
                    play_state = false;
                }
            }
        }

        for (int i = 0; i < 7 ; i++)
        {
            circle(renderer,(WINDOW_WIDTH/2)+i*50,WINDOW_HEIGHT-25,25,canon_color[i]);
        }
        //movement of canon balls
        for (int i = 0; i <canon_ball.size() ; i++)
        {
            circle(renderer,canon_ball[i].x,canon_ball[i].y,canon_ball[i].radius,canon_ball[i].color);
        }
        if(count_2>=1)
        {
            for (int i = 0; i <canon_ball.size() ; i++)
            {
                canon_ball[i].x+=canon_ball[i].dx;
                canon_ball[i].y+=canon_ball[i].dy;
            }
        }
        ///////////////////
        if(infinite_mode)
        {
            count_true_while++;
            if(count_true_while%100==0 && ball.size()<=20)
            {
                count_4++;
                // new ball generating
                /////////////////////
                for (int i = 0; i <14 ; i++)
                {
                    new_ball[i].color= print_random_colors_ball(14,3)[i];
                    new_ball[i].condition=1;
                    new_ball[i].checked=0;
                }
                count++;
                if(count%2==0)
                {
                    for (int i = 0; i <14 ; i++)
                    {
                        new_ball[i].y=-count*25* sqrt(3)+25+(10*count_4);
                        new_ball[i].x=i*50+25;
                        new_ball[i].checked=0;
                    }
                }
                else
                {
                    for (int i = 0; i <14 ; i++)
                    {
                        new_ball[i].y=-count*25* sqrt(3)+25+(10*count_4);
                        new_ball[i].x=i*50+50;
                        new_ball[i].checked=0;
                    }

                }
                ball.insert(ball.begin(),new_ball);
            }
              for (int i = 0; i <ball.size() ; i++)
            {
                for (int j = 0; j <ball[i].size() ; j++)
                {
                    ball[i][j].dx=0;
                    ball[i][j].dy=0.1;
                    ball[i][j].x+= ball[i][j].dx;
                    ball[i][j].y+= ball[i][j].dy;
                }
            }
        }
            if(normal_mode)
        {
            count_true_while++;
            if(count_true_while%100==0 && ball.size()<=4)
            {
                count_4++;
                // new ball generating
                /////////////////////
                for (int i = 0; i <14 ; i++)
                {
                    new_ball[i].color= print_random_colors_ball(14,3)[i];
                    new_ball[i].condition=1;
                    new_ball[i].checked=0;
                }
                count++;
                if(count%2==0)
                {
                    for (int i = 0; i <14 ; i++)
                    {
                        new_ball[i].y=-count*25* sqrt(3)+25+(10*count_4);
                        new_ball[i].x=i*50+25;
                        new_ball[i].checked=0;
                    }
                }
                else
                {
                    for (int i = 0; i <14 ; i++)
                    {
                        new_ball[i].y=-count*25* sqrt(3)+25+(10*count_4);
                        new_ball[i].x=i*50+50;
                        new_ball[i].checked=0;
                    }

                }
                ball.insert(ball.begin(),new_ball);
            }
            for (int i = 0; i <ball.size() ; i++)
            {
                for (int j = 0; j <ball[i].size() ; j++)
                {
                    ball[i][j].dx=0;
                    ball[i][j].dy=0.1;
                    ball[i][j].x+= ball[i][j].dx;
                    ball[i][j].y+= ball[i][j].dy;
                }
            }
        }
        bool check_intersect=0;
        float c_x;
        float c_y;
        char c_color;
        for (int i = 0; i < canon_ball.size(); i++)
        {
            for (int j = 0; j < ball.size(); j++)
            {
                for (int k = 0; k < ball[j].size(); k++)
                {
                    if (intersect(canon_ball[i].x, canon_ball[i].y, ball[j][k].x, ball[j][k].y, ball[j][k].radius) && ball[j][k].condition==1)
                    {
                        canon_ball[i].dx = ball[j][k].dx;
                        canon_ball[i].dy = ball[j][k].dy;
                        ball[j].push_back(canon_ball[i]);
                        c_x=canon_ball[i].x;
                        c_y=canon_ball[i].y;
                        if(canon_ball[i].color=='A')
                            c_color=ball[j][k].color;
                        else
                            c_color=canon_ball[i].color;
                        check_intersect=1;
                        canon_ball.erase(canon_ball.begin() + i);
                        i--;
                        break;
                    }
                }
            }
        }
        int count_intersect=0;
        vector<struct balls> ans(0);
        vector<struct balls> ans2(0);
         if(check_intersect)
            check_ball(ball,c_x,c_y,c_color,count_intersect,ans,ans2);
        //movement of main balls
        //////////////////
        /////////////////////
        for (int i = 0; i <canon_ball.size() ; i++)
        {
            if(WINDOW_WIDTH- canon_ball[i].x<=canon_ball[i].radius)
            {
                canon_ball[i].dx*=-1;
            }
            if( canon_ball[i].x<=canon_ball[i].radius)
            {
                canon_ball[i].dx*=-1;
            }
        }
        // rendering
       for (int i = 0; i < ball.size(); i++)
        {
            for (int j = 0; j < ball[i].size(); j++)
            {
                if(ball[i][j].condition==1)
                    circle(renderer, ball[i][j].x, ball[i][j].y, ball[i][j].radius, ball[i][j].color);
//                if(ball[i][j].condition==0)
//                    count_score++;
                if(ball[i][j].down_fall==1)
                {
                    ball[i][j].condition=0;
                    float cc_x,cc_y,cc_dy,cc_dx;
                    cc_x=ball[i][j].x;
                    cc_y=ball[i][j].y;
                    cc_dx=0;
                    cc_dy=5;
                    while (cc_y<= WINDOW_HEIGHT-50)
                    {
                        cc_x+=cc_dx;
                        cc_y+=cc_dy;
                        circle(renderer,cc_x,cc_y,25,ball[i][j].color);
                        SDL_RenderPresent(renderer);
                    }
                }
            }
        }
    if (timer_mode){
        duration = SDL_GetTicks() - start_time;
        if (duration <= 18000){
            filledPieRGBA(renderer,70,580,50,0,360-(duration/100),0x00,0xFF,0x00,0xFF);
        }
        else if (duration > 18000 && duration <= 27000){
            filledPieRGBA(renderer,70,580,50,0,360-(duration/100),0xFF,0xFF,0x00,0xFF);
        }
        else if (duration > 18000 && duration <= 36000){
            filledPieRGBA(renderer,70,580,50,0,360-(duration/100),0xFF,0x00,0x00,0xFF);
        }
        if (duration >= 36000){
            gameover_menu = true;
            play_state = false;
            duration = 0;
        }
    }
    //////////////////////////////////////////
    //game playing
    Button game_playing_pause;
    //////////////////////////////////////////
    if (theme_code == 1){
    game_playing_pause.draw(580,20,"Theme1/1/pause.png","Theme1/2/pause.png");
    }
    else if (theme_code == 2){
        game_playing_pause.draw(580,20,"Theme2/1/pause.png","Theme2/2/pause.png");
    }
    else {
        game_playing_pause.draw(580,20,"Theme3/1/pause.png","Theme3/2/pause.png");
    }
    game_playing_pause.update();

    if(game_playing_pause.button_state == 2){
        play_state = false;
        pause_menu = true;
    }
    game_playing_pause.clean();
}
void handle_sound(){
    if (sound){
            Mix_ResumeMusic();
            if (track_name_changed){
                ifstream music_data;
                music_data.open("music.txt");
                music_data >> track_code;
                music_data.close();

                Mix_VolumeMusic(volume);

                if (track_code == 1){
                    music = Mix_LoadMUS("Music/1.wav");
                    Mix_PlayMusic(music,-1);
                    track_name = "Music 1";
                }
                else if (track_code == 2){
                    music = Mix_LoadMUS("Music/2.wav");
                    Mix_PlayMusic(music,-1);
                    track_name = "Music 2";
                }
                else if (track_code == 3){
                    music = Mix_LoadMUS("Music/3.wav");
                    Mix_PlayMusic(music,-1);
                    track_name = "Music 3";
                }
                Mix_ResumeMusic();
                track_name_changed = false;
                }
            }
            else if (!sound){
                Mix_PauseMusic();
            }

            if(volume_changed){
                Mix_VolumeMusic(volume);
                volume_changed = false;
            }
}
void load_themes(){
if (theme_changed){
    ifstream theme;
    theme.open("theme.txt");
    theme >> theme_code;
    theme.close();
    SDL_DestroyTexture(background);
    start_menu_play.clean();
    start_menu_home.clean();
    start_menu_easy.clean();
    start_menu_standard.clean();
    start_menu_difficult.clean();
    start_menu_infinity_mode.clean();
    start_menu_timer_mode.clean();
    start_menu_normal_mode.clean();

    if (theme_code == 1){
        theme_name = "Jungle";
        text_color = {0x56,0x87,0x35};
        text_font = "font1.ttf";
        background = IMG_LoadTexture(renderer,"Theme1/background.jpg");
        start_menu_play.draw(240,540,"Theme1/1/play.png","Theme1/2/play.png");
        start_menu_home.draw(360,540,"Theme1/1/home.png","Theme1/2/home.png");
        start_menu_easy.draw(30,250,"Easy",text_color,text_font,"Theme1/1/status_box.png","Theme1/2/status_box.png","Theme1/3/status_box.png");
        start_menu_standard.draw(250,250,"Standard",text_color,text_font,"Theme1/1/status_box.png","Theme1/2/status_box.png","Theme1/3/status_box.png");
        start_menu_difficult.draw(470,250,"Difficult",text_color,text_font,"Theme1/1/status_box.png","Theme1/2/status_box.png","Theme1/3/status_box.png");
        start_menu_infinity_mode.draw(30,370,"Infinity",text_color,text_font,"Theme1/1/status_box.png","Theme1/2/status_box.png","Theme1/3/status_box.png");
        start_menu_timer_mode.draw(250,370,"Timer",text_color,text_font,"Theme1/1/status_box.png","Theme1/2/status_box.png","Theme1/3/status_box.png");
        start_menu_normal_mode.draw(470,370,"Normal",text_color,text_font,"Theme1/1/status_box.png","Theme1/2/status_box.png","Theme1/3/status_box.png");
        }
        else if(theme_code == 2){
        theme_name = "Dotted";
        text_color = {0xA9,0x17,0x17};
        text_font = "font2.ttf";
        background = IMG_LoadTexture(renderer,"Theme2/background.jpg");
        start_menu_play.draw(240,540,"Theme2/1/play.png","Theme2/2/play.png");
        start_menu_home.draw(360,540,"Theme2/1/home.png","Theme2/2/home.png");
        start_menu_easy.draw(30,250,"Easy",text_color,text_font,"Theme2/1/status_box.png","Theme2/2/status_box.png","Theme2/3/status_box.png");
        start_menu_standard.draw(250,250,"Standard",text_color,text_font,"Theme2/1/status_box.png","Theme2/2/status_box.png","Theme2/3/status_box.png");
        start_menu_difficult.draw(470,250,"Difficult",text_color,text_font,"Theme2/1/status_box.png","Theme2/2/status_box.png","Theme2/3/status_box.png");
        start_menu_infinity_mode.draw(30,370,"Infinity",text_color,text_font,"Theme2/1/status_box.png","Theme2/2/status_box.png","Theme2/3/status_box.png");
        start_menu_timer_mode.draw(250,370,"Timer",text_color,text_font,"Theme2/1/status_box.png","Theme2/2/status_box.png","Theme2/3/status_box.png");
        start_menu_normal_mode.draw(470,370,"Normal",text_color,text_font,"Theme2/1/status_box.png","Theme2/2/status_box.png","Theme2/3/status_box.png");
        }
        else {
        theme_name = "Purple";
        text_color = {0x9F,0xF6,0xFF};
        text_font = "font3.ttf";
        background = IMG_LoadTexture(renderer,"Theme3/background.jpg");
        start_menu_play.draw(240,540,"Theme3/1/play.png","Theme3/2/play.png");
        start_menu_home.draw(360,540,"Theme3/1/home.png","Theme3/2/home.png");
        start_menu_easy.draw(30,250,"Easy",text_color,text_font,"Theme3/1/status_box.png","Theme3/2/status_box.png","Theme3/3/status_box.png");
        start_menu_standard.draw(250,250,"Standard",text_color,text_font,"Theme3/1/status_box.png","Theme3/2/status_box.png","Theme3/3/status_box.png");
        start_menu_difficult.draw(470,250,"Difficult",text_color,text_font,"Theme3/1/status_box.png","Theme3/2/status_box.png","Theme3/3/status_box.png");
        start_menu_infinity_mode.draw(30,370,"Infinity",text_color,text_font,"Theme3/1/status_box.png","Theme3/2/status_box.png","Theme3/3/status_box.png");
        start_menu_timer_mode.draw(250,370,"Timer",text_color,text_font,"Theme3/1/status_box.png","Theme3/2/status_box.png","Theme3/3/status_box.png");
        start_menu_normal_mode.draw(470,370,"Normal",text_color,text_font,"Theme3/1/status_box.png","Theme3/2/status_box.png","Theme3/3/status_box.png");
        }
        theme_changed = false;
    }
}
bool intersect(double x1, double y1, double x2, double y2, double r){
    double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    if (d <= 2 * r +1  )   return true;
    else  return false;
}
vector<char>  print_random_colors_ball(int n , int hardness){
    vector<char> colors = {'r', 'g', 'b', 'y', 'p'};
    vector<char> result;
    for (int i = 0; i < n; i++)
    {
        result.push_back(colors[rand() % 5]);
    }
    for (char color : colors)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (result[i] == color) count++;
            else  count = 0;
            if (count == hardness)  break;
        }
        while (count < hardness)
        {
            int index = rand() % n;
            if (result[index] != color)
            {
                result[index] = color;
                count++;
            }
        }
    }
    for(int i=1 ;i<hardness;i++)
    {
        result[(rand()%n)]='B';
    }
    return result;
}
vector<char>  print_random_colors_canon_ball(int n , int hardness,vector<char> &canon_colors ){
    vector<char> result;
    for (int i = 0; i < n; i++)
    {
        result.push_back(canon_colors[rand() % canon_colors.size()]);
    }
    for (char color : canon_colors)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (result[i] == color) count++;
            else  count = 0;
            if (count == hardness)  break;
        }
        while (count < hardness)
        {
            int index = rand() % n;
            if (result[index] != color)
            {
                result[index] = color;
                count++;
            }
        }
    }
    return result;
}
void check_ball(vector<vector<struct balls>> &ball , float x , float y , char color , int count , vector<struct balls> &ans,vector<struct balls> &ans2 ) {
    for (int j = 0; j < ball.size(); j++)
    {
        for (int k = 0; k < ball[j].size(); k++)
        {
            if (intersect(x, y, ball[j][k].x, ball[j][k].y, ball[j][k].radius) && ball[j][k].condition == 1 &&
                (ball[j][k].color == color || ball[j][k].color=='A') )
            {
                if (ball[j][k].checked == 0)
                {
                    ball[j][k].checked = 1;
                    ans.push_back(ball[j][k]);
                    ans2.push_back(ball[j][k]);
                    check_ball(ball, ball[j][k].x, ball[j][k].y, color, count, ans,ans2);
                }
            }
        }
    }
    if(ans2.size()>=3)
    {
        for (int i = 0; i <ans2.size() ; i++)
        {
            for (int j = 0; j <ball.size() ; j++)
            {
                for (int k = 0; k <ball[j].size() ; k++)
                {
                    if( (ball[j][k].x==ans2[i].x && ball[j][k].y==ans2[i].y) && ball[j][k].color!='B' )
                    {
                        ball[j][k].condition=0;
                    }
                }
            }
        }
    }
//cout<<ans.size()<<endl;
}
void circle (SDL_Renderer *Renderer ,int x, int y , int radius , char  color ){
    if(color=='A')  filledEllipseRGBA(Renderer , x,y,radius,radius,255,255,255,255);
    if(color=='B')  filledEllipseRGBA(Renderer , x,y,radius,radius,100,100,100,255);
    if(color=='r')  filledEllipseRGBA(Renderer , x,y,radius,radius,255,0,0,255);
    if(color=='b')  filledEllipseRGBA(Renderer , x,y,radius,radius,0,0,255,255);
    if(color=='g')  filledEllipseRGBA(Renderer , x,y,radius,radius,0,255,0,255);
    if(color=='y')  filledEllipseRGBA(Renderer , x,y,radius,radius,0,255,255,255);
    if(color=='p')  filledEllipseRGBA(Renderer , x,y,radius,radius,255,0,255,255);
}
void init_balls(){

 for (int i = 0; i <4 ; i++){
        ball[i] = vector<struct balls>(14);
        for (int j = 0; j <14; j++)
        {
            ball[i][j].radius=25;
            ball[i][j].condition=1;
            ball[i][j].canon=0;
            ball[i][j].checked=0;
            if(i%2==0)
            {
                ball[i][j].x=j*(2*ball[i][j].radius)+ball[i][j].radius;
                ball[i][j].y=i*ball[i][j].radius*sqrt(3)+ball[i][j].radius;
            }
            else
            {
                ball[i][j].x=j*(2*ball[i][j].radius)+(2*ball[i][j].radius);
                ball[i][j].y=i*ball[i][j].radius*sqrt(3)+ball[i][j].radius;
            }
        }
    }
    for (int i = 0; i <4 ; i++){
        for (int j = 0; j <14 ; j++)
        {
            ball[i][j].color= print_random_colors_ball(14,hardness)[j];
        }
    }
    for(int i=0;i<14;i++){
        new_ball[i].radius=25;
        new_ball[i].x=i*(2*new_ball[i].radius)+new_ball[i].radius;
        new_ball[i].y=new_ball[i].radius;
        new_ball[i].condition=1;
        new_ball[i].canon=0;
        new_ball[i].checked=0;
    }
    for (int i = 0; i <14 ; i++){
        new_ball[i].color= print_random_colors_ball(14,hardness)[i];
    }
    new_canon_ball.x=WINDOW_WIDTH/2;
    new_canon_ball.y=WINDOW_HEIGHT-25;
    new_canon_ball.radius=25;
    new_canon_ball.condition=1;
    new_canon_ball.canon=1;
    new_canon_ball.checked=0;
    canon_colors.push_back('A');
    canon_colors.push_back('r');
    canon_colors.push_back('g');
    canon_colors.push_back('b');
    canon_colors.push_back('y');
    canon_colors.push_back('p');
    canon_color = print_random_colors_canon_ball(7,hardness,canon_colors);
}
