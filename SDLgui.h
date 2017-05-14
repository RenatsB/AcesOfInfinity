#ifndef SDLGUI_H
#define SDLGUI_H

#ifdef WIN32
  #include <Windows.h> // must be before gl.h include
#endif

#if defined (__linux__) || defined (WIN32)
  #include <GL/gl.h>
#endif
#ifdef __APPLE__
  #include <OpenGL/gl.h>
#endif

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class SDLgui
{
public:
    SDLgui()=default;

    int fontsize = 14;

    int InitGUI();

    int ExitGUI();

    int CreateGUIObjects();

    void drawText(SDL_Rect &_position, int textID);

    void drawButton(SDL_Rect &_position, int buttonID, int &_state);

    void updateGUIData(const  std::string _sceneName, const float _score, const float _speed);
private:
    GLuint *TextureIDs = new GLuint[19];

    TTF_Font *font;

    SDL_Color fontMainColor = {255,255,255,255};
    SDL_Color fontHoverColor = {244, 232, 66,255};
    SDL_Color fontPressedColor = {0,0,0,255};
    SDL_Color buttonMainColor = {0, 106, 255,255};
    SDL_Color buttonHoverColor = {255, 253, 183,255};
    SDL_Color buttonPressedColor = {255,255,255,255};
    const char* labels[15] = {"Play","Controls","Exit", "RMB+move = Orbit Camera","LMB+move = Zoom","W = Wireframe","S = Solid",
                            "Z = Toggle Autopilot","SPACE = Shoot Once","T = Toggle Weapons Fire","X = Switch Ship Type",
                           "LSHIFT = Accelerate","LCTRL = Decelerate","HULL INTEGRITY CRITICAL","Performing Emergency Jump"};
    const char* numLabels[10] = {"1","2","3","4","5","6","7","8","9","0"};
    int score;
    int speed;
    int curHealth;
    int curShield;
    std::string sceneName;
    SDL_Surface* mainMenu[9]; //3 buttons, 3 surfaces per button (text only)
    SDL_Surface* helpMenu[12]; //text only (1 state)
    SDL_Surface* numbers[10]; //need to have a library of numbers to avoid re-creating textures each frame
    //numbers used to display score, speed, shield and health
    //could use a full library of characters to also display an always random scene name, but that might be costly
};

#endif // SDLGUI_H
