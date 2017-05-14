#ifndef SCENEGENERATOR_H
#define SCENEGENERATOR_H
#include "NameGenerator.h"
#include "ship.h"
#include "Camera.h"

/// \brief A module for generating all ingame data
/// \author Renats Bikmajevs

/// \class SceneGenerator
/// \brief Generates arrays of objects and randomizes scene properties

class SceneGenerator
{
public:
    /// \brief default ctor
    SceneGenerator()=default;
    /// \brief an array containing all Asteroids
    std::vector<GameObject> m_allGameObjects;
    /// \brief an array containing all Bullets
    std::vector<GameObject> m_allBullets;
    /// \brief an array containing all Ships
    std::vector<Ship> m_allShipObjects;
    /// \brief an array containing all ship Spawner positions
    std::vector<glm::vec3> m_allSpawnerPositions;
    /// \brief the name of the current space system (scene)
    std::string m_name;
    /// \brief background colour value range = {0,1}
    glm::vec3 m_BGcolor = {0.01f, 0.01f, 0.01f};
    /// \brief light intensity (colour)
    glm::vec3 m_lightIntensity;
    /// \brief light direction vector
    glm::vec3 m_lightDir;
    /// \brief boolean for generation control
    bool m_redoGeneration = false;

    /// \brief method for generating the scene
    void generateScene();
    /// \brief method for randomizing scene properties
    void randomizeStats();
    /// \brief method for cleanup
    void flushObjectData();
    /// \brief method for checking and removind any "dead" objects
    /// \param[in] _curTime current game time since start
    void checkForDead(float &_curTime);
    /// \brief method for viewport adjustment and geometry drawing
    /// \param[in] _cam camera in use
    void draw(Camera &_cam);
private:
    /// \brief word builed object
    NameGenerator m_wordBuilder;
    /// \brief max and min size of the scene
    int m_sceneSizes[2] = {500, 1500};
    /// \brief scene size
    float m_sceneSize;
    /// \brief actual scene border
    float m_borderDist;
    /// \brief max danger level (affects ship density)
    int m_maxDangerLvl = 3;
    /// \brief actual danger level
    int m_dangerLvl;
    /// \brief asteroid density
    int m_asteroidDensity;
    /// \brief scene tag
    objTag m_faction;
}; //end of class

#endif // SCENEGENERATOR_H
