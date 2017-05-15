///
/// @file SDLgui.cpp
/// @brief This module handles all text and GUI related methods

#include "SDLgui.h"

int SDLgui::InitGUI()
{
    printf("TTF init\n");
    if (TTF_Init() < 0) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }
    #ifdef WIN32
      m_font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", fontsize);
    #endif

    #if defined (__linux__)
      m_font = TTF_OpenFont("/usr/share/fonts/gnu-free/FreeSans.ttf", fontsize);
    #endif
    #ifdef __APPLE__
      m_font = TTF_OpenFont("/usr/share/fonts/gnu-free/FreeSans.ttf", fontsize);
    #endif

    if(!m_font)
    {
        printf("m_font load fail: %s",TTF_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
//----------------------------------------------------------------------------------------------------------------------
int SDLgui::freeSurfaces()
{
    if(m_mainMenu && m_helpMenu)
    {
        int mm = (int)(sizeof(m_mainMenu)/sizeof(m_mainMenu[0]));
        int hm = (int)(sizeof(m_helpMenu)/sizeof(m_helpMenu[0]));
        int nn = (int)(sizeof(m_numbers)/sizeof(m_numbers[0]));
        for(int i = 0; i<mm; ++i)
        {
            SDL_FreeSurface(m_mainMenu[i]);
        }
        for(int i = 0; i<hm; ++i)
        {
            SDL_FreeSurface(m_helpMenu[i]);
        }
        for(int i = 0; i<nn; ++i)
        {
            SDL_FreeSurface(m_numbers[i]);
        }
    }
    printf("\nExiting GUI\n");
    return EXIT_SUCCESS;
}
//----------------------------------------------------------------------------------------------------------------------
void SDLgui::deleteAllTextures()
{
    glDeleteTextures(35, m_TextureIDs);
}
//----------------------------------------------------------------------------------------------------------------------
int SDLgui::CreateGUIObjects()
{
    m_mainMenu[0] = TTF_RenderUTF8_Solid(m_font, m_labels[0], m_fontMainColor);
    m_mainMenu[1] = TTF_RenderUTF8_Solid(m_font, m_labels[0], m_fontHoverColor);
    m_mainMenu[2] = TTF_RenderUTF8_Solid(m_font, m_labels[0], m_fontPressedColor);
    m_mainMenu[3] = TTF_RenderUTF8_Solid(m_font, m_labels[1], m_fontMainColor);
    m_mainMenu[4] = TTF_RenderUTF8_Solid(m_font, m_labels[1], m_fontHoverColor);
    m_mainMenu[5] = TTF_RenderUTF8_Solid(m_font, m_labels[1], m_fontPressedColor);
    m_mainMenu[6] = TTF_RenderUTF8_Solid(m_font, m_labels[2], m_fontMainColor);
    m_mainMenu[7] = TTF_RenderUTF8_Solid(m_font, m_labels[2], m_fontHoverColor);
    m_mainMenu[8] = TTF_RenderUTF8_Solid(m_font, m_labels[2], m_fontPressedColor);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(35, m_TextureIDs);
    int mm = (int)(sizeof(m_mainMenu)/sizeof(m_mainMenu[0]));
    int hm = (int)(sizeof(m_helpMenu)/sizeof(m_helpMenu[0]));
    int nn = (int)(sizeof(m_numbers)/sizeof(m_numbers[0]));

    for(int i = 0; i<mm; ++i)
    {
        if(!m_mainMenu[i])
        {
            printf("Main menu texture creation fail");
            return EXIT_FAILURE;
        }
        else
        {
            SDL_Surface* newSurface = SDL_CreateRGBSurface(0, m_mainMenu[i]->w, m_mainMenu[i]->h, 24, 0xff000000, 0x00ff0000, 0x0000ff00, 0);
            SDL_BlitSurface(m_mainMenu[i], 0, newSurface, 0); // Blit onto a purely RGB Surface
            m_mainMenu[i] = newSurface;
            SDL_FreeSurface(newSurface);
            glBindTexture(GL_TEXTURE_2D, m_TextureIDs[i]);
            int Mode = GL_RGB;
            if(m_mainMenu[i]->format->BytesPerPixel == 4)
            {   // alpha
                if (m_mainMenu[i]->format->Rmask == 0x000000ff)
                    Mode = GL_RGBA;
                else
                    Mode = GL_BGRA_EXT;
            } else {             // no alpha
                if (m_mainMenu[i]->format->Rmask == 0x000000ff)
                    Mode = GL_RGB;
                else
                    Mode = GL_BGR_EXT;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, m_mainMenu[i]->format->BytesPerPixel, m_mainMenu[i]->w, m_mainMenu[i]->h, 0, Mode, GL_UNSIGNED_BYTE, m_mainMenu[i]->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        }
    }
    for(int y = 0; y<hm; ++y)
    {
        m_helpMenu[y] = TTF_RenderText_Solid(m_font, m_labels[3+y], m_fontMainColor);
        //add size of m_mainMenu array as those IDs are filled already
        if(!m_helpMenu[y])
        {
            printf("Help screen texture creation fail");
            return EXIT_FAILURE;
        }
        else
        {
            SDL_Surface* newSurface = SDL_CreateRGBSurface(0, m_helpMenu[y]->w, m_helpMenu[y]->h, 24, 0xff000000, 0x00ff0000, 0x0000ff00, 0);
            SDL_BlitSurface(m_helpMenu[y], 0, newSurface, 0); // Blit onto a purely RGB Surface
            m_helpMenu[y] = newSurface;
            SDL_FreeSurface(newSurface);
            glBindTexture(GL_TEXTURE_2D, m_TextureIDs[y+mm]);
            int Mode = GL_RGB;
            if(m_helpMenu[y]->format->BytesPerPixel == 4)
            {   // alpha
                if (m_helpMenu[y]->format->Rmask == 0x000000ff)
                    Mode = GL_RGBA;
                else
                    Mode = GL_BGRA_EXT;
            } else {             // no alpha
                if (m_helpMenu[y]->format->Rmask == 0x000000ff)
                    Mode = GL_RGB;
                else
                    Mode = GL_BGR_EXT;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, m_helpMenu[y]->format->BytesPerPixel, m_helpMenu[y]->w, m_helpMenu[y]->h, 0, Mode, GL_UNSIGNED_BYTE, m_helpMenu[y]->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        }
    }
    for(int u = 0; u<nn; ++u)
    {
        m_numbers[u] = TTF_RenderText_Solid(m_font, m_numLabels[u], m_fontMainColor);
        //add size of m_mainMenu and m_helpMenu array sizes as those IDs are filled already
        if(!m_numbers[u])
        {
            printf("Number texture creation fail");
            return EXIT_FAILURE;
        }
        else
        {
            SDL_Surface* newSurface = SDL_CreateRGBSurface(0, m_numbers[u]->w, m_numbers[u]->h, 24, 0xff000000, 0x00ff0000, 0x0000ff00, 0);
            SDL_BlitSurface(m_numbers[u], 0, newSurface, 0); // Blit onto a purely RGB Surface
            m_numbers[u] = newSurface;
            SDL_FreeSurface(newSurface);
            glBindTexture(GL_TEXTURE_2D, m_TextureIDs[u+mm+hm]);
            int Mode = GL_RGB;
            if(m_numbers[u]->format->BytesPerPixel == 4)
            {   // alpha
                if (m_numbers[u]->format->Rmask == 0x000000ff)
                    Mode = GL_RGBA;
                else
                    Mode = GL_BGRA_EXT;
            } else {             // no alpha
                if (m_numbers[u]->format->Rmask == 0x000000ff)
                    Mode = GL_RGB;
                else
                    Mode = GL_BGR_EXT;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, m_numbers[u]->format->BytesPerPixel, m_numbers[u]->w, m_numbers[u]->h, 0, Mode, GL_UNSIGNED_BYTE, m_numbers[u]->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        }
    }
    TTF_CloseFont(m_font);
    TTF_Quit();
    return EXIT_SUCCESS;
}
//----------------------------------------------------------------------------------------------------------------------
void SDLgui::drawText(SDL_Rect &_position, int _textID)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, 1600, 800, 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);

            glColor3f(1.0f,1.0f,1.0f);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _textID);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // Draw a textured quad
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex2f(_position.x, _position.y);
                glTexCoord2f(1, 0); glVertex2f(_position.x+_position.w, _position.y);
                glTexCoord2f(1, 1); glVertex2f(_position.x+_position.w, _position.y+_position.h);
                glTexCoord2f(0, 1); glVertex2f(_position.x, _position.y+_position.h);
            glEnd();
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
//----------------------------------------------------------------------------------------------------------------------
void SDLgui::drawButton(SDL_Rect &_position, int _buttonID, int &_state)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, 1600, 800, 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);

            //convert color values so they would fit into {0,1} instead of {0,255}
            /*if(_state == 0)
                glColor3f((float)m_buttonMainColor.r/255.0f,(float)m_buttonMainColor.g/255.0f,(float)m_buttonMainColor.b/255.0f);
            if(_state == 1)
                glColor3f((float)m_buttonHoverColor.r/255.0f,(float)m_buttonHoverColor.g/255.0f,(float)m_buttonHoverColor.b/255.0f);
            if(_state == 2)
                glColor3f((float)m_buttonPressedColor.r/255.0f,(float)m_buttonPressedColor.g/255.0f,(float)m_buttonPressedColor.b/255.0f);

            glBegin(GL_QUADS);
                glVertex3f(_position.x-5, _position.y-5, 1);
                glVertex3f(_position.x+_position.w+5, _position.y-5, 1);
                glVertex3f(_position.x+_position.w+5, _position.y+_position.h+5, 1);
                glVertex3f(_position.x-5, _position.y+_position.h+5, 1);
            glEnd();*/
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //increment by state to pick corresponding texture (ID is supposed to be correctly specified to 0 variant of button initially)
            glBindTexture(GL_TEXTURE_2D, m_TextureIDs[_buttonID+_state]);
            glEnable(GL_TEXTURE_2D);
            glColor3f(1.0f,1.0f,1.0f);
            // Draw a textured quad
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(_position.x, _position.y, -0.001);
                glTexCoord2f(0, 1); glVertex3f(_position.x, _position.y+_position.h, -0.001);
                glTexCoord2f(1, 1); glVertex3f(_position.x+_position.w, _position.y+_position.h, -0.001);
                glTexCoord2f(1, 0); glVertex3f(_position.x+_position.w, _position.y, -0.001);
            glEnd();
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
//----------------------------------------------------------------------------------------------------------------------
void SDLgui::updateGUIData(const float &_score, const float &_speed, const float &_hp, const float &_sp)
{
  m_score = _score;
  m_speed = _speed;
  m_curHealth = _hp;
  m_curShield = _sp;
}
//----------------------------------------------------------------------------------------------------------------------
void SDLgui::DrawAllStats(int _x, int _y)
{
  DrawNumbers(m_score, _x, _y);
  DrawNumbers(m_speed, _x, _y+30);
  DrawNumbers(m_curHealth, _x, _y+60);
  DrawNumbers(m_curShield, _x, _y+90);
}
//----------------------------------------------------------------------------------------------------------------------
void SDLgui::DrawNumbers(int &_value, int _x, int _y)
{
  SDL_Rect tempPos;
  tempPos.x = _x;
  tempPos.y = _y;
  tempPos.w = 10;
  tempPos.h = 25;
  std::string stringToCheck = Convert(_value); //convert integer input to a string
  if(!stringToCheck.empty()) //sanity check
  {
    for(int  i = 0; i<(int)stringToCheck.size(); ++i)
    {
      //pick corresponding textures based on input
      switch(stringToCheck.at(i))
      {
      case '1' :
      {
        drawText(tempPos, 26);
        tempPos.x+=12;
        break;
      }
      case '2' :
      {
        drawText(tempPos, 27);
        tempPos.x+=12;
        break;
      }
      case '3' :
      {
        drawText(tempPos, 28);
        tempPos.x+=12;
        break;
      }
      case '4' :
      {
        drawText(tempPos, 29);
        tempPos.x+=12;
        break;
      }
      case '5' :
      {
        drawText(tempPos, 30);
        tempPos.x+=12;
        break;
      }
      case '6' :
      {
        drawText(tempPos, 31);
        tempPos.x+=12;
        break;
      }
      case '7' :
      {
        drawText(tempPos, 32);
        tempPos.x+=12;
        break;
      }
      case '8' :
      {
        drawText(tempPos, 33);
        tempPos.x+=12;
        break;
      }
      case '9' :
      {
        drawText(tempPos, 34);
        tempPos.x+=12;
        break;
      }
      case '0' :
      {
        drawText(tempPos, 35);
        tempPos.x+=12;
        break;
      }
      default : break;
      }
    }
  }
}

