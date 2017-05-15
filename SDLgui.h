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
#include <sstream>

/// \brief m_font and gui handler
/// \author Renats Bikmajevs

/// \class SDLgui
/// \brief m_font and gui handler based on SDL2 and openGL

class SDLgui
{
public:
    /// \brief default ctor
    SDLgui()=default;
    /// \brief size of the m_font
    int fontsize = 76;

    /// \brief method for initialization
    int InitGUI();
    /// \brief method for releasing unused surfaces
    int freeSurfaces();
    /// \brief method for cleaning up texture occupied memory
    void deleteAllTextures();
    /// \brief method to create all surfaces and textures for gui
    int CreateGUIObjects();
    /// \brief method to draw text on screen
    /// \param[in] _position rectangle to fill
    /// \param[in] _textID texture ID to be used
    void drawText(SDL_Rect &_position, int _textID);
    /// \brief method to draw a button
    /// \param[in] _position rectangle to fill
    /// \param[in] _buttonID texture ID to use
    /// \param[in] _state texture ID offset to use
    void drawButton(SDL_Rect &_position, int _buttonID, int &_state);
    /// \brief update object data
    /// \param[in] _sceneName name of the current scene
    /// \param[in] _score player score
    /// \param[in] _speed player speed
    /// \param[in] _hp player health
    /// \param[in] _sp player shield
    void updateGUIData(const float &_score, const float &_speed, const float &_hp, const float &_sp);
    /// \brief method for drawing all numerical player stats on screen
    /// \param[in] _x x coordinates to draw to
    /// \param[in] _y y coordinates to draw to
    void DrawAllStats(int _x, int _y);
private:
    /// \brief all texture IDs
    GLuint *m_TextureIDs = new GLuint[35];
    /// \brief True Type Font in use
    TTF_Font *m_font;
    /// \brief main colour of the button font
    SDL_Color m_fontMainColor = {255,255,255,255};
    /// \brief hover colour of the button font
    SDL_Color m_fontHoverColor = {244, 232, 66,255};
    /// \brief pressed colour of the button font
    SDL_Color m_fontPressedColor = {0,0,0,255};
    /// \brief main colour of the button background
    //SDL_Color m_buttonMainColor = {0, 106, 255,255};
    /// \brief hover colour of the button background
    //SDL_Color m_buttonHoverColor = {255, 253, 183,255};
    /// \brief pressed colour of the button background
    //SDL_Color m_buttonPressedColor = {255,255,255,255};
    /// \brief button text and info text labels
    const char* m_labels[19] = {"Play","Controls","Exit", "RMB+move = Orbit Camera","LMB+move = Zoom","W = Wireframe","S = Solid",
                            "Z = Toggle Autopilot","SPACE = Shoot Once","T = Toggle Weapons Fire","X = Switch Ship Type",
                           "LSHIFT = Accelerate","LCTRL = Decelerate","HULL INTEGRITY CRITICAL","Performing Emergency Jump",
                             "Score:","Shield:","Hull:","Speed:"};
    /// \brief m_numbers to generate textures for
    const char* m_numLabels[10] = {"1","2","3","4","5","6","7","8","9","0"};
    /// \brief internal storage of player score
    int m_score;
    /// \brief internal storage of player speed
    int m_speed;
    /// \brief internal storage of player health
    int m_curHealth;
    /// \brief internal storage of player shield
    int m_curShield;
    /// \brief main menu buttons (3 states per button)
    SDL_Surface* m_mainMenu[9]; //3 buttons, 3 surfaces per button (text only)
    /// \brief informational text
    SDL_Surface* m_helpMenu[16]; //text only (1 state)
    /// \brief m_numbers text
    SDL_Surface* m_numbers[10]; //need to have a library of m_numbers to avoid re-creating textures each frame
    //m_numbers used to display m_score, m_speed, shield and health
    //could use a full library of characters to also display an always random scene name, but that might be costly

    /// \brief method to convert int to string
    /// \param[in] _number a number to convert
    std::string Convert (int &_number){
        std::ostringstream buff;
        buff<<_number;
        return buff.str();
    }
    /// \brief method for drawing numerical stats of player on screen
    /// \param[in] _value the value to print
    /// \param[in] _x x coordinates on screen to draw to
    /// \param[in] _y y coordinates on screen to draw to
    void DrawNumbers(int &_value, int _x, int _y);
}; //end of class

#endif // SDLGUI_H
