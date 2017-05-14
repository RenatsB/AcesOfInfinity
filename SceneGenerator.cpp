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
    m_wordBuilder.NameConstructor(m_name);
    std::cout<<"\nScene name is: "<<m_name<<std::endl;
    //create all other stuff
    if(m_sceneSize > m_sceneSizes[0] && m_sceneSize < m_sceneSizes[1]) //sanity check - if scene size is within limits
    {
        printf("\nCreating spawners...\n");
        int i;
        //create spawners
        do //need to calculate this at least once
        {
        i = (rand()%(m_sceneSizes[1] + 1)*m_dangerLvl/42 + 4); //this will be the spawner count
        }
        while(i>52); //check if whithin specified amount
        //create the actual spawner positions
        for(int y=0; y<i; ++y)
        {
            glm::vec3 spawnerPos;
            spawnerPos.x = rand()%(int)(m_sceneSize*0.4) - (m_sceneSize*0.4)/2;
            spawnerPos.y = rand()%(int)(m_sceneSize*0.4) - (m_sceneSize*0.4)/2;
            spawnerPos.z = rand()%(int)(m_sceneSize*0.4) - (m_sceneSize*0.4)/2;
            m_allSpawnerPositions.push_back(spawnerPos); //add this position to vector
        }
        printf("\nSpawner count: %d\n", i);
        printf("\nDone creating spawners!\n");

        printf("\nCreating asteroids...\n");
        //create asteroids
        if(m_asteroidDensity<0){m_asteroidDensity*=(-1);} //check -> flip value if negative

        int asterDensity = (m_asteroidDensity * ((int)sqrt(m_sceneSize - m_sceneSizes[0])))/2; //the number of asteroids
        printf("Asteroid count: %d", asterDensity);
        //create the esteroid objects
        for(int y=0; y<asterDensity; ++y)
        {
            glm::vec3 newPos, newRot;
            newPos.x = rand()%((int)m_sceneSize) - m_sceneSize/2;
            newPos.y = rand()%((int)m_sceneSize) - m_sceneSize/2;
            newPos.z = rand()%((int)m_sceneSize) - m_sceneSize/2;
            newRot.x = rand()%360;
            newRot.y = rand()%360;
            newRot.z = rand()%360;
            GameObject asteroid(newPos, newRot, NONE);
            asteroid.m_size = rand()%(int)sqrt((int)(m_sceneSize/sizeof(m_sceneSize)))+1;
            m_allGameObjects.push_back(asteroid);
        }
        printf("\nDone creating asteroids!\n");
        //now create ships
        printf("\nCreating player...\n");
        //first create player
        glm::vec3 zeroVec = {0,0,0};
        Ship player(zeroVec, zeroVec, TERRAN, true, &m_allGameObjects, &m_allShipObjects, &m_allBullets);
        player.m_forward = {0,0,10};
        m_allShipObjects.push_back(player);
        printf("\nDone creating player!\n");
        printf("\nCreating ships...\n");
        //then create all other ships
        for(int i=1; i<(int)(m_allSpawnerPositions.size()); ++i)
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
            Ship AIship(m_allSpawnerPositions.at(i), zeroVec, tempTg, false, &m_allGameObjects, &m_allShipObjects, &m_allBullets);
            m_allShipObjects.push_back(AIship);
        }
        printf("\nDone creating ships!\n");
        printf("\nShip count: %d\n",m_allShipObjects.size());
        m_redoGeneration = false;
    }
    else //prevents scene from getting created if it has wrong size
    {
        printf("\nSomething went wrong! Scene distance is out of bounds.\n");
        flushObjectData();
        m_redoGeneration = true;
    }
}

void SceneGenerator::randomizeStats()
{
    printf("\nStarting stat randomization...\n");
    //prevent sceneSize from being not in range or nan
    while(m_sceneSize < m_sceneSizes[0] || m_sceneSize > m_sceneSizes[1] || m_sceneSize != m_sceneSize)
    {
        m_sceneSize = rand()%(m_sceneSizes[1]-m_sceneSizes[0] + 1) + m_sceneSizes[0];
    }
    printf("\nScene size is: %f\n", m_sceneSize);
    m_borderDist = 0.9*m_sceneSize; //scene border
    printf("\nBorder distance is: %f\n", m_borderDist);
    m_dangerLvl = rand()%m_maxDangerLvl;
    printf("\nDanger level is: %d\n", m_dangerLvl);
    do
    {
        m_asteroidDensity = rand()%(int)(m_sceneSize)/3;
    }
    while(m_asteroidDensity >= 1200);
    printf("\nAsteroid density is: %d\n", m_asteroidDensity);
    //randomize background colour
    m_BGcolor.x = (float)(rand()%(15)+1)/100;
    m_BGcolor.y = (float)(rand()%(15)+1)/100;
    m_BGcolor.z = (float)(rand()%(15)+1)/100;
    printf("\nBackground colour: %f, %f, %f\n", m_BGcolor.x, m_BGcolor.y, m_BGcolor.z);
    //randomize light colour
    m_lightIntensity.x = (float)(rand()%80 + 20)/100;
    m_lightIntensity.y = (float)(rand()%80 + 20)/100;
    m_lightIntensity.z = (float)(rand()%80 + 20)/100;
    printf("\nBG light intensity: %f, %f, %f\n", m_lightIntensity.x, m_lightIntensity.y, m_lightIntensity.z);
    //randomize light direction
    m_lightDir.x = (float)((rand()%200)-100)/100;
    m_lightDir.y = (float)((rand()%200)-100)/100;
    m_lightDir.z = (float)((rand()%200)-100)/100;
    m_lightDir = glm::normalize(m_lightDir); //make sure it's normalized
    printf("\nBG light direction: %f, %f, %f\n", m_lightDir.x, m_lightDir.y, m_lightDir.z);
    int lll = rand()%3;
    m_faction = static_cast<objTag>(lll);
    std::string tempStr;
    switch(m_faction)
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
    m_allGameObjects.clear();
    m_allGameObjects.resize(0);
    m_allShipObjects.clear();
    m_allShipObjects.resize(0);
    m_allSpawnerPositions.clear();
    m_allSpawnerPositions.resize(0);
    printf("\nResetting variables...\n");
    m_sceneSize = 0;
    m_borderDist = 0;
    m_dangerLvl = 0;
    m_asteroidDensity = 0;
    m_faction = NONE;
    m_name.clear();
    m_name.resize(0);
    printf("\nScene data reset!\n");
}

void SceneGenerator::checkForDead(float &_curTime)
{
    //loop through all ships
    for(int i = 0; i<(int)m_allShipObjects.size(); ++i)
    {
        if(i==0) //if player
        {
            if(m_allShipObjects.at(i).curHealth <= 0) //no health = dead
            {
                m_redoGeneration = true;
            }
            if(glm::length(m_allShipObjects.at(i).m_position) >= m_borderDist) //out of bounds = dead
            {
                m_redoGeneration = true;
            }
        }
        else //not player
        {
            int tempSpawnNum = rand()%m_allSpawnerPositions.size();//prevent duplicate calculations
            //each dead ship will appear at a random spawner position. This prevents from "camping"
            //which in terms of simple AI is likely to happen
            if(m_allShipObjects.at(i).curHealth <= 0) //no health = dead
            {
                m_allShipObjects.at(i).m_position = m_allSpawnerPositions.at(tempSpawnNum); //move to spawner
                m_allShipObjects.at(i).resetShip(); //reset
            }
            if(glm::length(m_allShipObjects.at(i).m_position) >= m_borderDist) //out of bounds = dead
            {
                m_allShipObjects.at(i).m_position = m_allSpawnerPositions.at(tempSpawnNum); //move to spawner
                m_allShipObjects.at(i).resetShip(); //reset
            }
        }
    }
    //loop through all bullets
    for(int i=0; i<(int)m_allBullets.size(); ++i)
    {
        if(_curTime >= m_allBullets.at(i).m_dieTime) //if it's time to die
        {
            m_allBullets.erase(m_allBullets.begin()+i); //remove bullet
        }
    }
}

void SceneGenerator::draw(Camera &_cam)
{
  //Main draw function.
  //since it has to deal a lot with all scene objects, it was added to this particular class instead of any other
  glClearColor(m_BGcolor.x,m_BGcolor.y,m_BGcolor.z,1.0); //fill background with BGcolor
  glm::vec3 red(1,0,0);
  glm::vec3 green(0,1,0);
  glm::vec3 blue(0,0,1);
  glm::vec3 white(1,1,1);
  //glm::vec3 yellow(1,1,0);
  glm::vec3 grey(0.5f,0.5f,0.5f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  //adjust view to camera properties
  glTranslatef(0,-0.25,-(_cam.m_zoom));
  glTranslatef(_cam.m_eye.x, _cam.m_eye.y, _cam.m_eye.z);
  glRotatef(-_cam.m_rotX, 1, 0, 0);
  glRotatef(-_cam.m_rotY, 0, 1, 0);

  glTranslatef(-m_allShipObjects.at(0).m_position.x, -m_allShipObjects.at(0).m_position.y, -m_allShipObjects.at(0).m_position.z);
  //set up the lights
  GLfloat light0_diffuse[] = {m_lightIntensity.x, m_lightIntensity.y, m_lightIntensity.z};
  GLfloat light0_direction[] = {m_lightDir.x, m_lightDir.y, m_lightDir.z, 0.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
  //draw all Asteroids
  for(int i = 0; i<(int)m_allGameObjects.size();++i)
  {
    m_allGameObjects.at(i).m_rotation += glm::vec3(0.005,0.005,0.005); //add some rotation
    glPushMatrix();
        glColor4f(grey.x,grey.y,grey.z,0.0f);
        glTranslatef(m_allGameObjects.at(i).m_position.x, m_allGameObjects.at(i).m_position.y, m_allGameObjects.at(i).m_position.z);
        glRotatef(m_allGameObjects.at(i).m_rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(m_allGameObjects.at(i).m_rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(m_allGameObjects.at(i).m_rotation.z, 0.0f, 0.0f, 1.0f);
        Mesh::asteroid(m_allGameObjects.at(i).m_size);
    glPopMatrix();
  }
  //draw all Ships
  for(int i = 0; i<(int)m_allShipObjects.size();++i)
  {
    glPushMatrix();
        glTranslatef(m_allShipObjects.at(i).m_position.x, m_allShipObjects.at(i).m_position.y, m_allShipObjects.at(i).m_position.z);
        glRotatef(m_allShipObjects.at(i).m_rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(m_allShipObjects.at(i).m_rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(m_allShipObjects.at(i).m_rotation.z, 0.0f, 0.0f, 1.0f);
        if(m_allShipObjects.at(i).m_tag == TERRAN)
        {
            glColor4f(blue.x,blue.y,blue.z,0.0f);
            Mesh::ship1(m_allShipObjects.at(i).m_size);
        }
        if(m_allShipObjects.at(i).m_tag == PIRATE)
        {
            glColor4f(red.x,red.y,red.z,0.0f);
            Mesh::ship2(m_allShipObjects.at(i).m_size);
        }
        if(m_allShipObjects.at(i).m_tag == ALIEN)
        {
            glColor4f(green.x,green.y,green.z,0.0f);
            Mesh::ship3(m_allShipObjects.at(i).m_size);
        }
    glPopMatrix();
  }
  //draw all Bullets
  if(!m_allBullets.empty()) //sanity check
  {
      for(int i = 0; i<(int)m_allBullets.size();++i)
      {
        glPushMatrix();
            if(m_allBullets.at(i).m_tag == TERRAN)
                glColor4f(blue.x,blue.y,blue.z,0.0f);
            if(m_allBullets.at(i).m_tag == PIRATE)
                glColor4f(red.x,red.y,red.z,0.0f);
            if(m_allBullets.at(i).m_tag == ALIEN)
                glColor4f(green.x,green.y,green.z,0.0f);
            if(m_allBullets.at(i).m_tag == PLAYER)
                glColor4f(white.x,white.y,white.z,0.0f);
            glTranslatef(m_allBullets.at(i).m_position.x, m_allBullets.at(i).m_position.y, m_allBullets.at(i).m_position.z);
            glRotatef(m_allBullets.at(i).m_rotation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(m_allBullets.at(i).m_rotation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(m_allBullets.at(i).m_rotation.z, 0.0f, 0.0f, 1.0f);
            Mesh::bullet(m_allBullets.at(i).m_size);
        glPopMatrix();
      }
  }
}
