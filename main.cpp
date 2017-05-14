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
void updateCam(Camera _cam);
void waitScreen(Camera _cam);

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
    mainCamera.camTarget = glm::vec3(0,0,0);
    mainCamera.up = glm::vec3(0,1,0);
    mainCamera.position = glm::vec3(0,0,1);
    mainCamera._fovy = 1.2f;
    mainCamera._aspect = float(1600/800);
    mainCamera._zNear = 0.05f;
    mainCamera._zFar = 1000.0f;
    // setup our default OpenGL window state
    initOpenGL(mainCamera);

    bool exitStat = false;

    //next is a variable for controlling which type of thing to run
    //0 = mainMenu, 1 = helpMenu, 2 = mainGameLoop, 3 = jumpScreen
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
    SDL_Rect *textPositions[12];

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
    menuControl.ExitGUI();

    srand (static_cast <unsigned> (time(0)));
    std::chrono::system_clock::time_point gameStartT;
    std::chrono::system_clock::time_point gameCurrentT;
    float gameTime = 0;
    std::chrono::system_clock::time_point startT;
    std::chrono::system_clock::time_point endT;
    int tickCntr;
    float deltaTime;

    //we also need a few variables for ship and camera control
    bool fireWeapons = false;
    int mouseX = 45;
    int mouseY = 25;
    //store player score in here
    float playerScore = 0.0f;

    gameStartT = std::chrono::system_clock::now();

    //scene generator and game object container
    SceneGenerator mainController;
    mainController.generateScene();
    //mainController.redoGeneration = true;

    //wait(3);

    while (exitStat != true) //MAIN GAME LOOP
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
            case SDL_QUIT : exitStat = true; break;
                // now we look for a keydown event
            case SDL_KEYDOWN:
            {
                if(gameState == 2) //do this only in game loop
                {
                    switch( event.key.keysym.sym )
                    {
                    // if it's the escape key quit
                    case SDLK_ESCAPE :  exitStat = true; break;
                        // make OpenGL draw wireframe
                    case SDLK_w :
                    {
                        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                        glDisable(GL_LIGHTING);
                        glDisable(GL_LIGHT0);
                        break;
                    }
                        // make OpenGL draw solid
                    case SDLK_s :
                    {
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glEnable(GL_LIGHTING);
                        glEnable(GL_LIGHT0);
                        break;
                    }
                    case SDLK_LSHIFT :
                    {
                        mainController.allShipObjects.at(0).IncreaseSpeed(deltaTime);
                        break;
                    }
                    case SDLK_LCTRL :
                    {
                        mainController.allShipObjects.at(0).IncreaseSpeed(-deltaTime);
                        break;
                    }
                    case SDLK_t :
                    {
                        fireWeapons = !fireWeapons;
                        break;
                    }
                    case SDLK_SPACE :
                    {
                        mainController.allShipObjects.at(0).FireBullet(mainController.allShipObjects.at(0).target, gameTime);
                        break;
                    }
                    case SDLK_x :
                    {
                        if(!mainController.allShipObjects.empty())
                        {
                            int curTag = (int)mainController.allShipObjects.at(0).tag;
                            ++curTag;
                            if(curTag >= 3){curTag = 0;}
                            mainController.allShipObjects.at(0).tag = static_cast<objTag>(curTag);
                        }
                        break;
                    }
                    case SDLK_z :
                    {
                        if(!mainController.allShipObjects.empty())
                        {
                            mainController.allShipObjects.at(0).isPlayer = !mainController.allShipObjects.at(0).isPlayer;
                        }
                        break;
                    }
                    default : break;
                    } // end of key process
                }
            } // end of keydown
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
                                //wait(1);
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
        mainCamera.oldX=mouseX;
        mainCamera.oldY=mouseY;
        mainCamera.oldZoom = mouseY;

        if(gameState == 0)
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
            glClearColor(0.0f,0.0f,0.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for(int i =0; i<3; ++i)
            {
                menuControl.drawButton(menuButtons[i], i*3, buttonStates[i]);
            }

            if(buttonStates[0] == 2)
            {
                gameState = 2;
                buttonStates[0] = 0;
                buttonStates[1] = 0;
                buttonStates[2] = 0;
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            }
            win.swapWindow();
        }

        if(gameState == 2)
        {
            if(mainController.redoGeneration == true)
            {
                mainController.flushObjectData();
                printf("\nHull Integrity Critical! Performing Emergency Jump!\n");
                //mainCamera.oldX=45;
                //mainCamera.oldY=25;
                //mainCamera.oldZoom = 1;
                waitScreen(mainCamera);
                win.swapWindow();
                wait(3);
                mainController.generateScene();
                //initOpenGL(mainCamera);
                glClearColor(mainController.BGcolor.x,mainController.BGcolor.y,mainController.BGcolor.z,1.0);
            }
            else
            {
                //update all object data
                for(int i=0; i<(int)mainController.allShipObjects.size(); ++i)
                {
                    if(i == 0 && mainController.allShipObjects.at(0).isPlayer == true)
                    {
                        mainController.allShipObjects.at(0).fireWeapons = fireWeapons;
                        mainCamera.getCamDir();
                        glm::vec3 temp = -mainCamera.forward;
                        temp += mainController.allShipObjects.at(0).position;
                        mainController.allShipObjects.at(0).target = temp;
                    }
                    mainController.allShipObjects.at(i).FlyShip(deltaTime, gameTime, playerScore);
                }
                mainController.checkForDead(gameTime); //check and remove any "dead" bullets
                //also "remove" and reset any dead ships, check if any ships out of bounds (kill and reset them if so)

                float bulletSpeed = deltaTime*5.0f;
                for(int i=0; i<(int)mainController.allBullets.size(); ++i)
                {
                    mainController.allBullets.at(i).moveObject(bulletSpeed);
                }
                //update camera vectors
                updateCam(mainCamera);
            }
            // draw scene
            mainController.draw(mainCamera);
            // update the buffer so we can see what we have drawn.
            win.swapWindow();
        }


       endT = std::chrono::system_clock::now();
       gameCurrentT = endT;
       tickCntr = std::chrono::duration_cast<std::chrono::microseconds>(endT - startT).count();
       deltaTime = (float)tickCntr/100000;
       tickCntr = std::chrono::duration_cast<std::chrono::seconds>(gameCurrentT - gameStartT).count();
       gameTime = (float)tickCntr;
    }
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

void waitScreen(Camera _cam)
{
    glClearColor(0.5f,0.01f,0.01f,1.0f);
    _cam.camPerspective();
    _cam.lookAtTgt();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}
