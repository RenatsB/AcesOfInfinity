#include "SDLgui.h"

int SDLgui::InitGUI()
{
    printf("TTF init\n");
    if (TTF_Init() < 0) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }
    //newFont = TTF_OpenFont("C:/Windows/Fonts/terminat.ttf", 48);
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", fontsize);
    //font = TTF_OpenFont("debug/ZeroGravity.ttf", fontsize);
    if(!font)
    {
        printf("Font load fail: %s",TTF_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int SDLgui::ExitGUI()
{
    if(mainMenu && helpMenu)
    {
        int sizeTemp = (int)(sizeof(mainMenu)/sizeof(SDL_Surface))+(int)(sizeof(helpMenu)/sizeof(SDL_Surface));
        for(int i = 0; i<sizeTemp; ++i)
        {
            if(i<sizeTemp)
            {
                SDL_FreeSurface(mainMenu[i]);
            }
            else
            {
                SDL_FreeSurface(helpMenu[i-sizeTemp]);
            }
            glDeleteTextures(19, TextureIDs);
        }
    }
    printf("\nExiting GUI\n");
    return EXIT_SUCCESS;
}

int SDLgui::CreateGUIObjects()
{
    mainMenu[0] = TTF_RenderUTF8_Solid(font, labels[0], fontMainColor);
    //SDL_SaveBMP(mainMenu[0], "./Test.bmp"); //<-- THIS WORKS FINE (outputs correct image)
    mainMenu[1] = TTF_RenderUTF8_Solid(font, labels[0], fontHoverColor);
    mainMenu[2] = TTF_RenderUTF8_Solid(font, labels[0], fontPressedColor);
    mainMenu[3] = TTF_RenderUTF8_Solid(font, labels[1], fontMainColor);
    mainMenu[4] = TTF_RenderUTF8_Solid(font, labels[1], fontHoverColor);
    mainMenu[5] = TTF_RenderUTF8_Solid(font, labels[1], fontPressedColor);
    mainMenu[6] = TTF_RenderUTF8_Solid(font, labels[2], fontMainColor);
    mainMenu[7] = TTF_RenderUTF8_Solid(font, labels[2], fontHoverColor);
    mainMenu[8] = TTF_RenderUTF8_Solid(font, labels[2], fontPressedColor);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(19, TextureIDs);

    for(int i = 0; i<(int)(sizeof(mainMenu)/sizeof(SDL_Surface)); ++i)
    {
        if(!mainMenu[i])
        {
            printf("Main menu texture creation fail");
            return EXIT_FAILURE;
        }
        else
        {
            //glGenTextures(1, &TextureIDs[i]);
            glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);
            int Mode = GL_RGB;
            if(mainMenu[i]->format->BytesPerPixel == 4)
            {   // alpha
                if (mainMenu[i]->format->Rmask == 0x000000ff)
                    Mode = GL_RGBA;
                else
                    Mode = GL_BGRA_EXT;
            } else {             // no alpha
                if (mainMenu[i]->format->Rmask == 0x000000ff)
                    Mode = GL_RGB;
                else
                    Mode = GL_BGR_EXT;
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
               //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mainMenu[i]->w, mainMenu[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, mainMenu[i]->pixels);
            //glTexImage2D(GL_TEXTURE_2D, 0, mainMenu[i]->format->BytesPerPixel, mainMenu[i]->w, mainMenu[i]->h, 0, Mode, GL_UNSIGNED_BYTE, mainMenu[i]->pixels);
            //glTexImage2D(GL_TEXTURE_2D, 0, colors = surface->format->BytesPerPixel, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);
            //SDL_FreeSurface(mainMenu[i]);
        }
    }
    for(int y = 0; y<(int)(sizeof(helpMenu)/sizeof(SDL_Surface)); ++y)
    {
        helpMenu[y] = TTF_RenderText_Solid(font, labels[3+y], fontMainColor);
        int i = y+(int)(sizeof(mainMenu)/sizeof(SDL_Surface)); //add size of mainMenu array as those IDs are filled already
        if(!helpMenu[y])
        {
            printf("Help screen texture creation fail");
            return EXIT_FAILURE;
        }
        else
        {
            //SDL_SaveBMP(surfaceMessage, "./Test.bmp"); //<-- THIS WORKS FINE (outputs correct image)
            //glGenTextures(1, &TextureIDs[i]);
            glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);
            int Mode = GL_RGB;
            if(helpMenu[y]->format->BytesPerPixel == 4)
            {   // alpha
                if (helpMenu[y]->format->Rmask == 0x000000ff)
                    Mode = GL_RGBA;
                else
                    Mode = GL_BGRA_EXT;
            } else {             // no alpha
                if (helpMenu[y]->format->Rmask == 0x000000ff)
                    Mode = GL_RGB;
                else
                    Mode = GL_BGR_EXT;
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_CLAMP);*/
            glTexImage2D(GL_TEXTURE_2D, 0, helpMenu[y]->format->BytesPerPixel, helpMenu[y]->w, helpMenu[y]->h, 0, Mode, GL_UNSIGNED_BYTE, helpMenu[y]->pixels);
            //SDL_FreeSurface(helpMenu[y]);
        }
    }
    for(int u = 0; u<(int)(sizeof(numbers)/sizeof(SDL_Surface)); ++u)
    {
        numbers[u] = TTF_RenderText_Solid(font, numLabels[u], fontMainColor);
        //add size of mainMenu and helpMenu array sizes as those IDs are filled already
        int i = u+(int)(sizeof(mainMenu)/sizeof(SDL_Surface))+(int)(sizeof(helpMenu)/sizeof(SDL_Surface));
        if(!numbers[u])
        {
            printf("Number texture creation fail");
            return EXIT_FAILURE;
        }
        else
        {
            //SDL_SaveBMP(surfaceMessage, "./Test.bmp"); //<-- THIS WORKS FINE (outputs correct image)
            glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);
            int Mode = GL_RGB;
            if(numbers[u]->format->BytesPerPixel == 4)
            {   // alpha
                if (numbers[u]->format->Rmask == 0x000000ff)
                    Mode = GL_RGBA;
                else
                    Mode = GL_BGRA_EXT;
            } else {             // no alpha
                if (numbers[u]->format->Rmask == 0x000000ff)
                    Mode = GL_RGB;
                else
                    Mode = GL_BGR_EXT;
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_CLAMP);*/
            glTexImage2D(GL_TEXTURE_2D, 0, numbers[u]->format->BytesPerPixel, numbers[u]->w, numbers[u]->h, 0, Mode, GL_UNSIGNED_BYTE, numbers[u]->pixels);
        }
    }
    TTF_CloseFont(font);
    TTF_Quit();
    return EXIT_SUCCESS;
}

void SDLgui::drawText(SDL_Rect &_position, int textID)
{
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
            glBindTexture(GL_TEXTURE_2D, textID);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // Draw a textured quad
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex2i(_position.x, _position.y);
                glTexCoord2f(1, 0); glVertex2i(_position.x+_position.w, _position.y);
                glTexCoord2f(1, 1); glVertex2i(_position.x+_position.w, _position.y+_position.h);
                glTexCoord2f(0, 1); glVertex2i(_position.x, _position.y+_position.h);
            glEnd();
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void SDLgui::drawButton(SDL_Rect &_position, int buttonID, int &_state)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, 1600, 800, 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //convert color values so they would fit into {0,1} instead of {0,255}
            if(_state == 0)
                glColor3f((float)buttonMainColor.r/255.0f,(float)buttonMainColor.g/255.0f,(float)buttonMainColor.b/255.0f);
            if(_state == 1)
                glColor3f((float)buttonHoverColor.r/255.0f,(float)buttonHoverColor.g/255.0f,(float)buttonHoverColor.b/255.0f);
            if(_state == 2)
                glColor3f((float)buttonPressedColor.r/255.0f,(float)buttonPressedColor.g/255.0f,(float)buttonPressedColor.b/255.0f);

            glBegin(GL_QUADS);
                glVertex2i(_position.x-5, _position.y-5);
                glVertex2i(_position.x+_position.w+5, _position.y-5);
                glVertex2i(_position.x+_position.w+5, _position.y+_position.h+5);
                glVertex2i(_position.x-5, _position.y+_position.h+5);
            glEnd();



            //increment by state to pick corresponding texture (ID is supposed to be correctly specified to 0 variant of button initially)
            glBindTexture(GL_TEXTURE_2D, TextureIDs[buttonID+_state]);
            glEnable(GL_TEXTURE_2D);
            //glEnable(GL_BLEND);
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1.0f,1.0f,1.0f);

            // Draw a textured quad
            glBegin(GL_QUADS);
              //glNormal3i(0, -1, 0);
                glTexCoord2f(0, 0); glVertex2i(_position.x, _position.y);
                glTexCoord2f(0, 1); glVertex2i(_position.x, _position.y+_position.h);
                glTexCoord2f(1, 1); glVertex2i(_position.x+_position.w, _position.y+_position.h);
                glTexCoord2f(1, 0); glVertex2i(_position.x+_position.w, _position.y);
            glEnd();
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}
