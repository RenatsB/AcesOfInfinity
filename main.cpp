///
/// @file main.cpp
/// @brief This is the main module of the game controlling every other module of the game
/// Also handles all key and button input

#ifdef WIN32
  #include <Windows.h> // must be before gl.h include
#endif

#if defined (__linux__) || defined (WIN32)
  #include <GL/gl.h>
#endif
#ifdef __APPLE__
  #include <OpenGL/gl.h>
#endif

#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <string>
#include <chrono>

#include "SceneGenerator.h"
#include "SDLOpenGL.h"
#include "SDLgui.h"

#undef main

// function to init OpenGL scene
void initOpenGL(Camera _cam);
// function to update camera matrices
void updateCam(Camera _cam);
// function that creates a wait screen when travelling between scenes
void waitScreen(Camera _cam);
// function to delay processec for a specified amount of seconds
void wait ( int seconds );

int main()
{
    // create our SDLWindow
    SDLOpenGL win("AcesOfInfinity v1.0",100,100,1600,800);
    // this makes sure the window is active for OpenGL calls, if we have
    // more than one window we need to call this for the window we want to
    // set OpenGL for
    win.makeCurrent();
    //Create main Camera
    Camera mainCamera;
    //set up the camera
    mainCamera.m_camTarget = glm::vec3(0,0,0);
    mainCamera.m_up = glm::vec3(0,1,0);
    mainCamera.m_position = glm::vec3(0,0,1);
    mainCamera.m_fovy = 1.2f;
    mainCamera.m_aspect = float(1600/800);
    mainCamera.m_zNear = 0.05f;
    mainCamera.m_zFar = 1000.0f;
    // setup our default OpenGL window state
    initOpenGL(mainCamera);

    bool exitStatus = false;

    //next is a variable for controlling which type of thing to run
    //0 = m_mainMenu, 1 = m_helpMenu, 2 = mainGameLoop, 3 = jumpScreen
    int gameState = 0;
    //button states
    int buttonStates[3] = {0,0,0};
    SDL_Rect menuButtons[3];
    for(int i =0; i<3; ++i)
    {
        menuButtons[i].x = 400;
        menuButtons[i].w = 800;
        menuButtons[i].h = 200;
        menuButtons[i].y = 80+(200*i)+(20*i);
    }
    SDL_Rect textPositions[16];
    for(int i =0; i<10; ++i)
    {
        textPositions[i].x = 400;
        textPositions[i].w = 800;
        textPositions[i].h = 50;
        textPositions[i].y = 70+(50*i)+(10*i);
    }
    textPositions[10].x = 400;
    textPositions[10].w = 800;
    textPositions[10].h = 120;
    textPositions[10].y = 380;

    textPositions[11].x = 400;
    textPositions[11].w = 800;
    textPositions[11].h = 90;
    textPositions[11].y = 540;
    {
      int temp = 0;
      for(int i = 12; i<16; ++i)
      {
        textPositions[i].x = 20;
        textPositions[i].w = 80;
        textPositions[i].h = 20;
        textPositions[i].y = 20+(30*temp);
        ++temp;
      }
    }
    //[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
    //create and load gui
    SDLgui menuControl;
    if(menuControl.InitGUI() == 1)
    {
        return EXIT_FAILURE;
    }
    if(menuControl.CreateGUIObjects() == 1)
    {
        return EXIT_FAILURE;
    }
    menuControl.freeSurfaces();

    srand (static_cast <unsigned> (time(0)));
    std::chrono::system_clock::time_point gameStartT;
    std::chrono::system_clock::time_point gameCurrentT;
    float gameTime = 0;
    std::chrono::system_clock::time_point startT;
    std::chrono::system_clock::time_point endT;
    int tickCntr;
    float deltaTime;

    //we also need a few variables for ship and camera control
    bool m_fireWeapons = false;
    bool doAcceleration = false;
    bool doDeceleration = false;
    int mouseX = 45;
    int mouseY = 25;
    //store player m_score in here
    float playerScore = 0.0f;

    gameStartT = std::chrono::system_clock::now();

    //scene generator and game object container
    SceneGenerator mainController;

    while (exitStatus != true) //MAIN GAME LOOP
    {
        startT = std::chrono::system_clock::now();
        //handle mouse states first

        SDL_Event event;
        // grab the event from the window
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // this is the window x being clicked.
            case SDL_QUIT : exitStatus = true; break;
                // now we look for a keydown event
            case SDL_KEYDOWN:
            {
                if(gameState == 2) //do this only in game loop
                {
                    switch( event.key.keysym.sym )
                    {
                    // if it's the escape key quit
                    case SDLK_ESCAPE :
                    {
                        mainController.flushObjectData();
                        gameState = 0;
                        break;
                    }
                        // make OpenGL draw wireframe
                    case SDLK_w :
                    {
                        mainController.m_wireFrame = true;
                        break;
                    }
                        // make OpenGL draw solid
                    case SDLK_s :
                    {
                        mainController.m_wireFrame = false;
                        break;
                    }
                    case SDLK_LSHIFT :
                    {
                        doAcceleration = true;
                        doDeceleration = false;
                        break;
                    }
                    case SDLK_LCTRL :
                    {
                        doDeceleration = true;
                        doAcceleration = false;
                        break;
                    }
                    case SDLK_t :
                    {
                        m_fireWeapons = !m_fireWeapons;
                        break;
                    }
                    case SDLK_SPACE :
                    {
                        mainController.m_allShipObjects.at(0).FireBullet(mainController.m_allShipObjects.at(0).m_target, gameTime);
                        break;
                    }
                    case SDLK_x :
                    {
                        if(!mainController.m_allShipObjects.empty())
                        {
                            int curTag = (int)mainController.m_allShipObjects.at(0).m_tag;
                            ++curTag;
                            if(curTag >= 3){curTag = 0;}
                            mainController.m_allShipObjects.at(0).m_tag = static_cast<objTag>(curTag);
                        }
                        break;
                    }
                    case SDLK_z :
                    {
                        if(!mainController.m_allShipObjects.empty())
                        {
                            mainController.m_allShipObjects.at(0).m_toggleAI = !mainController.m_allShipObjects.at(0).m_toggleAI;
                        }
                        break;
                    }
                    default : break;
                    } // end of key process
                }
            } // end of keydown
            case SDL_KEYUP :
            {
              switch( event.key.keysym.sym )
              {
              case SDLK_LSHIFT :
              {
                  doAcceleration = false;
                  break;
              }
              case SDLK_LCTRL :
              {
                  doDeceleration = false;
                  break;
              }
              }
            }
            case SDL_MOUSEBUTTONDOWN :
            {
                if(gameState != 2) //not main game loop
                {
                    switch(event.button.button)
                    {
                    case SDL_BUTTON_LEFT :
                    {
                        if(gameState == 0)//in Main Menu
                        {
                            //check for position
                            for(int i =0; i<3; ++i)
                            if(mouseX > menuButtons[i].x && mouseX < (menuButtons[i].x+menuButtons[i].w) &&
                               mouseY > menuButtons[i].y && mouseY < (menuButtons[i].y+menuButtons[i].h))
                            {
                                buttonStates[i] = 2;
                            }
                        }
                        if(gameState == 1)//in help Menu
                        {
                            buttonStates[0] = 0;
                            buttonStates[1] = 0;
                            buttonStates[2] = 0;
                            gameState = 0; //just go back to main menu
                        }
                        break;
                    }
                    default : break;
                    }
                }
            }
            default : break;
            } // end of event switch
        }

        Uint32 mState;
        mState = SDL_GetMouseState(&mouseX, &mouseY);
        switch(mState)
        {
            case SDL_BUTTON_LMASK :
            {
                if(gameState == 2)
                {
                    mainCamera.camZoom(mouseY);
                }
                break;
            }
            case SDL_BUTTON_RMASK :
            {
                if(gameState == 2)
                {
                    mainCamera.camOrbit(mouseX, mouseY);
                }
                break;
            }
        default : break;
        }
        mainCamera.m_oldX=mouseX;
        mainCamera.m_oldY=mouseY;
        mainCamera.m_oldZoom = mouseY;

        if(gameState != 2)
        {
            glClearColor(0.0f,0.0f,0.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        switch(gameState)
        {
        case 0 :
        {
            for(int i =0; i<3; ++i)
            {
                if((mouseX > menuButtons[i].x) && (mouseX < (menuButtons[i].x+menuButtons[i].w)) &&
                   (mouseY > menuButtons[i].y) && (mouseY < (menuButtons[i].y+menuButtons[i].h)))
                {
                    if(buttonStates[i] != 2)
                    {
                        buttonStates[i] = 1;
                    }
                }
                else
                {
                    buttonStates[i] = 0;
                }
            }
            for(int i =0; i<3; ++i)
            {
                menuControl.drawButton(menuButtons[i], i*3, buttonStates[i]);
            }
            if(mainController.m_wireFrame == true)
            {
              glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
              glDisable(GL_LIGHTING);
              glDisable(GL_LIGHT0);
            }
            else
            {
              glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
              glEnable(GL_LIGHTING);
              glEnable(GL_LIGHT0);
            }
            win.swapWindow();
            if(buttonStates[0] == 2)
            {
                buttonStates[0] = 0;
                buttonStates[1] = 0;
                buttonStates[2] = 0;
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                mainController.generateScene();
                gameState = 2;
            }
            if(buttonStates[1] == 2)
            {
                buttonStates[0] = 0;
                buttonStates[1] = 0;
                buttonStates[2] = 0;
                gameState = 1;
            }
            if(buttonStates[2] == 2)
            {
                exitStatus = true;
            }
            break;
        }
        case 1 :
        {
            for(int i = 0; i<10; ++i) //0-9 will be 10 elements but draws only 9???
            {
                menuControl.drawText(textPositions[i], i+10);
            }
            if(mainController.m_wireFrame == true)
            {
              glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
              glDisable(GL_LIGHTING);
              glDisable(GL_LIGHT0);
            }
            else
            {
              glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
              glEnable(GL_LIGHTING);
              glEnable(GL_LIGHT0);
            }
            win.swapWindow();
            break;
        }
        case 2 :
        {
            if(mainController.m_redoGeneration == true)
            {
                gameState = 3;
            }
            else
            {
                if(doAcceleration == true)
                {
                  mainController.m_allShipObjects.at(0).IncreaseSpeed(deltaTime);
                }
                if(doDeceleration == true)
                {
                  mainController.m_allShipObjects.at(0).IncreaseSpeed(-deltaTime);
                }
                //update all object data
                for(int i=0; i<(int)mainController.m_allShipObjects.size(); ++i)
                {
                    if(i == 0 && mainController.m_allShipObjects.at(0).m_toggleAI == false)
                    {
                        mainController.m_allShipObjects.at(0).m_fireWeapons = m_fireWeapons;
                        mainCamera.getCamDir();
                        glm::vec3 temp = -mainCamera.m_forward;
                        temp += mainController.m_allShipObjects.at(0).m_position;
                        mainController.m_allShipObjects.at(0).m_target = temp;
                    }
                    mainController.m_allShipObjects.at(i).FlyShip(deltaTime, gameTime, playerScore);
                }
                mainController.checkForDead(gameTime); //check and remove any "dead" bullets
                //also "remove" and reset any dead ships, check if any ships out of bounds (kill and reset them if so)

                float bulletSpeed = deltaTime*5.0f;
                for(int i=0; i<(int)mainController.m_allBullets.size(); ++i)
                {
                    mainController.m_allBullets.at(i).moveObject(bulletSpeed);
                }
                if(mainController.m_wireFrame == true)
                {
                  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                  glDisable(GL_LIGHTING);
                  glDisable(GL_LIGHT0);
                }
                else
                {
                  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                  glEnable(GL_LIGHTING);
                  glEnable(GL_LIGHT0);
                }
                //update camera vectors
                updateCam(mainCamera);

            }
            menuControl.updateGUIData(playerScore, mainController.m_allShipObjects.at(0).GetCurrentSpeed(),
                                      mainController.m_allShipObjects.at(0).m_curHealth, mainController.m_allShipObjects.at(0).m_curShield);
            // draw scene
            mainController.draw(mainCamera);
            for(int i = 0; i<4; ++i)
            {
                menuControl.drawText(textPositions[i+12], i+22);
            }
            menuControl.DrawAllStats(100, 20);
            // update the buffer so we can see what we have drawn.
            win.swapWindow();
            break;
        }
        case 3 :
        {
          glClearColor(0.0f,0.0f,0.0f,1.0f);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            menuControl.drawText(textPositions[10], 20);
            menuControl.drawText(textPositions[11], 21);
            win.swapWindow();
            mainController.flushObjectData();
            printf("\nHull Integrity Critical! Performing Emergency Jump!\n");
            wait(3);
            mainController.generateScene();
            glClearColor(mainController.m_BGcolor.x,mainController.m_BGcolor.y,mainController.m_BGcolor.z,1.0);
            gameState = 2;
            if(mainController.m_wireFrame == true)
            {
              glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
              glDisable(GL_LIGHTING);
              glDisable(GL_LIGHT0);
            }
            else
            {
              glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
              glEnable(GL_LIGHTING);
              glEnable(GL_LIGHT0);
            }
            break;
        }
        }

       endT = std::chrono::system_clock::now();
       gameCurrentT = endT;
       tickCntr = std::chrono::duration_cast<std::chrono::microseconds>(endT - startT).count();
       deltaTime = (float)tickCntr/100000;
       tickCntr = std::chrono::duration_cast<std::chrono::seconds>(gameCurrentT - gameStartT).count();
       gameTime = (float)tickCntr;
    }
    menuControl.deleteAllTextures();
    return EXIT_SUCCESS;
}

void initOpenGL(Camera _cam)
{
  // this sets the background colour
  glClearColor(0.01,0.01,0.01,1.0);
  // this is how big our window is for drawing
  glViewport(0,0,1600,800);
  _cam.camPerspective();
  _cam.lookAtTgt();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glColor3f(1,1,0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

}

void updateCam(Camera _cam)
{
    _cam.camPerspective();
    _cam.lookAtTgt();
}

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}
