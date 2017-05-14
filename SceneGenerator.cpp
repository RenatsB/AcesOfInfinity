#include "SceneGenerator.h"
#include <iostream>
#include "mesh.h"
#include "Camera.h"

void SceneGenerator::generateScene()
{
    //first randimize all the scene stats
    randomizeStats();
    printf("\nGenerating scene...\n");
    //generate scene name
    wordBuilder.NameConstructor(name);
    std::cout<<"\nScene name is: "<<name<<std::endl;
    //create all other stuff
    if(sceneSize > sceneSizeVariations[0] && sceneSize < sceneSizeVariations[1]) //sanity check - if scene size is within limits
    {
        printf("\nCreating spawners...\n");
        int i;
        //create spawners
        do //need to calculate this at least once
        {
        i = (rand()%(sceneSizeVariations[1] + 1)*dangerLvl/42 + 4); //this will be the spawner count
        }
        while(i>52); //check if whithin specified amount
        //create the actual spawner positions
        for(int y=0; y<i; ++y)
        {
            glm::vec3 spawnerPos;
            spawnerPos.x = rand()%(int)(sceneSize*0.4) - (sceneSize*0.4)/2;
            spawnerPos.y = rand()%(int)(sceneSize*0.4) - (sceneSize*0.4)/2;
            spawnerPos.z = rand()%(int)(sceneSize*0.4) - (sceneSize*0.4)/2;
            allSpawnerPositions.push_back(spawnerPos); //add this position to vector
        }
        printf("\nSpawner count: %d\n", i);
        printf("\nDone creating spawners!\n");

        printf("\nCreating asteroids...\n");
        //create asteroids
        if(asteroidDensity<0){asteroidDensity*=(-1);} //check -> flip value if negative

        int asterDensity = (asteroidDensity * ((int)sqrt(sceneSize - sceneSizeVariations[0])))/2; //the number of asteroids
        printf("Asteroid count: %d", asterDensity);
        //create the esteroid objects
        for(int y=0; y<asterDensity; ++y)
        {
            glm::vec3 newPos, newRot;
            newPos.x = rand()%((int)sceneSize) - sceneSize/2;
            newPos.y = rand()%((int)sceneSize) - sceneSize/2;
            newPos.z = rand()%((int)sceneSize) - sceneSize/2;
            newRot.x = rand()%360;
            newRot.y = rand()%360;
            newRot.z = rand()%360;
            GameObject asteroid(newPos, newRot, NONE);
            asteroid.size = rand()%(int)sqrt((int)(sceneSize/sizeof(sceneSize)))+1;
            allGameObjects.push_back(asteroid);
        }
        printf("\nDone creating asteroids!\n");
        //now create ships
        printf("\nCreating player...\n");
        //first create player
        glm::vec3 zeroVec = {0,0,0};
        Ship player(zeroVec, zeroVec, TERRAN, true, &allGameObjects, &allShipObjects, &allBullets);
        player.forward = {0,0,10};
        allShipObjects.push_back(player);
        printf("\nDone creating player!\n");
        printf("\nCreating ships...\n");
        //then create all other ships
        for(int i=1; i<(int)(allSpawnerPositions.size()); ++i)
        {
            objTag tempTg;
            //also make each next ship have different tag
            if(i%3 == 0)
            {
                tempTg = ALIEN;
            }
            else if(i%3 == 1)
            {
                tempTg = PIRATE;
            }
            else
            {
                tempTg = TERRAN;
            }
            Ship AIship(allSpawnerPositions.at(i), zeroVec, tempTg, false, &allGameObjects, &allShipObjects, &allBullets);
            allShipObjects.push_back(AIship);
        }
        printf("\nDone creating ships!\n");
        printf("\nShip count: %d\n",allShipObjects.size());
        redoGeneration = false;
    }
    else //prevents scene from getting created if it has wrong size
    {
        printf("\nSomething went wrong! Scene distance is out of bounds.\n");
        flushObjectData();
        redoGeneration = true;
    }
}

void SceneGenerator::randomizeStats()
{
    printf("\nStarting stat randomization...\n");
    //prevent sceneSize from being not in range or nan
    while(sceneSize < sceneSizeVariations[0] || sceneSize > sceneSizeVariations[1] || sceneSize != sceneSize)
    {
        sceneSize = rand()%(sceneSizeVariations[1]-sceneSizeVariations[0] + 1) + sceneSizeVariations[0];
    }
    printf("\nScene size is: %f\n", sceneSize);
    warnBorderDist = 0.9*sceneSize; //scene border
    printf("\nBorder distance is: %f\n", warnBorderDist);
    dangerLvl = rand()%maxDangerLvl;
    printf("\nDanger level is: %d\n", dangerLvl);
    do
    {
        asteroidDensity = rand()%(int)(sceneSize)/3;
    }
    while(asteroidDensity >= 1200);
    printf("\nAsteroid density is: %d\n", asteroidDensity);
    //randomize background colour
    BGcolor.x = (float)(rand()%(15)+1)/100;
    BGcolor.y = (float)(rand()%(15)+1)/100;
    BGcolor.z = (float)(rand()%(15)+1)/100;
    printf("\nBackground colour: %f, %f, %f\n", BGcolor.x, BGcolor.y, BGcolor.z);
    //randomize light colour
    lightIntensity.x = (float)(rand()%80 + 20)/100;
    lightIntensity.y = (float)(rand()%80 + 20)/100;
    lightIntensity.z = (float)(rand()%80 + 20)/100;
    printf("\nBG light intensity: %f, %f, %f\n", lightIntensity.x, lightIntensity.y, lightIntensity.z);
    //randomize light direction
    lightDir.x = (float)((rand()%200)-100)/100;
    lightDir.y = (float)((rand()%200)-100)/100;
    lightDir.z = (float)((rand()%200)-100)/100;
    lightDir = glm::normalize(lightDir); //make sure it's normalized
    printf("\nBG light direction: %f, %f, %f\n", lightDir.x, lightDir.y, lightDir.z);
    //starfieldDensity = asteroidDensity;
    //printf("\nStarfield density is: %d\n", starfieldDensity);
    /*numOfStations = rand()%2;
    if(numOfStations == 1)
    {
        printf("\nA space station is detected in this sector\n");
    }*/
    int lll = rand()%3;
    faction = static_cast<objTag>(lll);
    std::string tempStr;
    switch(faction)
    {
        case TERRAN: tempStr = "Terrans"; break;
        case ALIEN: tempStr = "Aliens"; break;
        case PIRATE: tempStr = "Pirates"; break;
        default: tempStr = "None"; break;
    }

    printf("\nThis sector is controlled by: %s\n", tempStr.c_str());
}

void SceneGenerator::flushObjectData()
{
    printf("\nPerforming Object Data Flush...\n");
    printf("\nDeleting scene data...\n");
    allGameObjects.clear();
    allGameObjects.resize(0);
    allShipObjects.clear();
    allShipObjects.resize(0);
    allSpawnerPositions.clear();
    allSpawnerPositions.resize(0);
    printf("\nResetting variables...\n");
    sceneSize = 0;
    warnBorderDist = 0;
    dangerLvl = 0;
    asteroidDensity = 0;
    starfieldDensity = 0;
    numOfStations = 0;
    faction = NONE;
    name.clear();
    name.resize(0);
    printf("\nScene data reset!\n");
}

void SceneGenerator::infiniteStarfield(Camera *_camObj)
{

}

void SceneGenerator::checkForDead(float &_curTime)
{
    //loop through all ships
    for(int i = 0; i<(int)allShipObjects.size(); ++i)
    {
        if(i==0) //if player
        {
            if(allShipObjects.at(i).curHealth <= 0) //no health = dead
            {
                redoGeneration = true;
            }
            if(glm::length(allShipObjects.at(i).position) >= warnBorderDist) //out of bounds = dead
            {
                redoGeneration = true;
            }
        }
        else //not player
        {
            int tempSpawnNum = rand()%allSpawnerPositions.size();//prevent duplicate calculations
            //each dead ship will appear at a random spawner position. This prevents from "camping"
            //which in terms of simple AI is likely to happen
            if(allShipObjects.at(i).curHealth <= 0) //no health = dead
            {
                allShipObjects.at(i).position = allSpawnerPositions.at(tempSpawnNum); //move to spawner
                allShipObjects.at(i).resetShip(); //reset
            }
            if(glm::length(allShipObjects.at(i).position) >= warnBorderDist) //out of bounds = dead
            {
                allShipObjects.at(i).position = allSpawnerPositions.at(tempSpawnNum); //move to spawner
                allShipObjects.at(i).resetShip(); //reset
            }
        }
    }
    //loop through all bullets
    for(int i=0; i<(int)allBullets.size(); ++i)
    {
        if(_curTime >= allBullets.at(i).dieTime) //if it's time to die
        {
            allBullets.erase(allBullets.begin()+i); //remove bullet
        }
    }
}

void SceneGenerator::draw(Camera &_cam)
{
  //Main draw function.
  //since it has to deal a lot with all scene objects, it was added to this particular class instead of any other
  glClearColor(BGcolor.x,BGcolor.y,BGcolor.z,1.0); //fill background with BGcolor
  glm::vec3 red(1,0,0);
  glm::vec3 green(0,1,0);
  glm::vec3 blue(0,0,1);
  glm::vec3 white(1,1,1);
  //glm::vec3 yellow(1,1,0);
  glm::vec3 grey(0.5f,0.5f,0.5f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  //adjust view to camera properties
  glTranslatef(0,-0.25,-(_cam.zoom));
  glTranslatef(_cam.eye.x, _cam.eye.y, _cam.eye.z);
  glRotatef(-_cam.rotX, 1, 0, 0);
  glRotatef(-_cam.rotY, 0, 1, 0);

  glTranslatef(-allShipObjects.at(0).position.x, -allShipObjects.at(0).position.y, -allShipObjects.at(0).position.z);
  //set up the lights
  GLfloat light0_diffuse[] = {lightIntensity.x, lightIntensity.y, lightIntensity.z};
  GLfloat light0_direction[] = {lightDir.x, lightDir.y, lightDir.z, 0.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
  //draw all Asteroids
  for(int i = 0; i<(int)allGameObjects.size();++i)
  {
    allGameObjects.at(i).rotation += glm::vec3(0.005,0.005,0.005); //add some rotation
    glPushMatrix();
        glColor4f(grey.x,grey.y,grey.z,0.0f);
        glTranslatef(allGameObjects.at(i).position.x, allGameObjects.at(i).position.y, allGameObjects.at(i).position.z);
        glRotatef(allGameObjects.at(i).rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(allGameObjects.at(i).rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(allGameObjects.at(i).rotation.z, 0.0f, 0.0f, 1.0f);
        Mesh::asteroid(allGameObjects.at(i).size);
    glPopMatrix();
  }
  //draw all Ships
  for(int i = 0; i<(int)allShipObjects.size();++i)
  {
    glPushMatrix();
        glTranslatef(allShipObjects.at(i).position.x, allShipObjects.at(i).position.y, allShipObjects.at(i).position.z);
        glRotatef(allShipObjects.at(i).rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(allShipObjects.at(i).rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(allShipObjects.at(i).rotation.z, 0.0f, 0.0f, 1.0f);
        if(allShipObjects.at(i).tag == TERRAN)
        {
            glColor4f(blue.x,blue.y,blue.z,0.0f);
            Mesh::ship1(allShipObjects.at(i).size);
        }
        if(allShipObjects.at(i).tag == PIRATE)
        {
            glColor4f(red.x,red.y,red.z,0.0f);
            Mesh::ship2(allShipObjects.at(i).size);
        }
        if(allShipObjects.at(i).tag == ALIEN)
        {
            glColor4f(green.x,green.y,green.z,0.0f);
            Mesh::ship3(allShipObjects.at(i).size);
        }
    glPopMatrix();
  }
  //draw all Bullets
  if(!allBullets.empty()) //sanity check
  {
      for(int i = 0; i<(int)allBullets.size();++i)
      {
        glPushMatrix();
            if(allBullets.at(i).tag == TERRAN)
                glColor4f(blue.x,blue.y,blue.z,0.0f);
            if(allBullets.at(i).tag == PIRATE)
                glColor4f(red.x,red.y,red.z,0.0f);
            if(allBullets.at(i).tag == ALIEN)
                glColor4f(green.x,green.y,green.z,0.0f);
            if(allBullets.at(i).tag == PLAYER)
                glColor4f(white.x,white.y,white.z,0.0f);
            glTranslatef(allBullets.at(i).position.x, allBullets.at(i).position.y, allBullets.at(i).position.z);
            glRotatef(allBullets.at(i).rotation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(allBullets.at(i).rotation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(allBullets.at(i).rotation.z, 0.0f, 0.0f, 1.0f);
            Mesh::bullet(allBullets.at(i).size);
        glPopMatrix();
      }
  }
}
