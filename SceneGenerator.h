#ifndef SCENEGENERATOR_H
#define SCENEGENERATOR_H
#include "NameGenerator.h"
#include "ship.h"
#include "Camera.h"

class SceneGenerator
{
public:
    SceneGenerator()=default;
    std::vector<GameObject> allGameObjects;
    std::vector<GameObject> allBullets;
    std::vector<Ship> allShipObjects;
    std::vector<glm::vec3> allSpawnerPositions;
    std::string name;
    glm::vec3 BGcolor = {0.01f, 0.01f, 0.01f};
    glm::vec3 lightIntensity;
    glm::vec3 lightDir;
    bool redoGeneration = false;

    void generateScene();
    void randomizeStats();
    void flushObjectData();
    void infiniteStarfield(Camera *_camObj);
    void checkForDead(float &_curTime);
    void draw(Camera &_cam);
private:
    NameGenerator wordBuilder;
    int sceneSizeVariations[2] = {500, 1500};
    float sceneSize;
    float warnBorderDist;
    int maxDangerLvl = 3;
    int dangerLvl;
    int asteroidDensity;
    int numOfStations;
    objTag faction;
    int starfieldDensity;
};

#endif // SCENEGENERATOR_H
