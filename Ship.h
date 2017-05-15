#ifndef SHIP_H
#define SHIP_H
#include "GameObject.h"

/// \brief Main object (ship) handling module
/// \author Renats Bikmajevs
/// \version 1.0

/// \class Ship
/// \brief This class includes all properties and AI necessary for automatic event handling

class Ship: public GameObject
{
public:
    /// \brief default ctor
    Ship()=default;
    /// \brief custom ctor for instantiation by SceneGenerator
    /// \param[in] _pos position of the ship
    /// \param[in] _rot rotation of the ship
    /// \param[in] _tag tag of the ship
    /// \param[in] _isPlr boolen to determine if it is a player ship
    /// \param[in] _allGOS a pointer to array comtaining all Asteroids
    /// \param[in] _allShips a pointer to array containing all Ship objects
    /// \param[in] _allBullets a pointer to array containing all Bullet objects
    Ship(glm::vec3 _pos, glm::vec3 &_rot, objTag _tag, bool _isPlr,
         std::vector<GameObject> *_allGOS, std::vector<Ship> *_allShips, std::vector<GameObject> *_allBullets)
    {
        m_position = _pos;
        m_rotation = _rot;
        m_tag = _tag;
        m_isPlayer = _isPlr;
        m_allGOs = _allGOS;
        m_allShips = _allShips;
        m_allBuls = _allBullets;
    }

    /// \brief boolean determining player ship
    bool m_isPlayer = false;
    /// \brief booean to toggle AI of the ship. Always on in NPCs, can be toggled for player ship
    bool m_toggleAI = true;
    /// \brief current target position (can be used as either position of enemy ship or a navpoint)
    glm::vec3 m_target = {0,0,0};
    /// \brief current health value
    float m_curHealth = 100.0f;
    /// \brief maximum health value
    float m_maxHealth = 100.0f;
    /// \brief current shield value
    float m_curShield = 120.0f;
    /// \brief maximum shield value
    float m_maxShield = 120.0f;
    /// \brief shield regeneration speed
    float m_regenSpeed = 2.5f;
    /// \brief weapons fire toggle
    bool m_fireWeapons = false;
    /// \brief firing delay
    float m_fireDelay = 0.15f;
    /// \brief variable to store end of the delay time
    float m_nextFire = 0.0f;

    /// \brief method for applying acceleration
    /// \param[in] _value used as either delta time or negative delta time
    void IncreaseSpeed(float _value);
    /// \brief method for instantiating a Bullet object (GameObject)
    /// \param[in] _curTgt currently tracked target
    /// \param[in] _curTime current game time since start
    void FireBullet(glm::vec3 &_curTgt, float &_curTime);
    /// \brief main Ship cointroller. updates all data
    /// \param[in] _deltaTime current delta time
    /// \param[in] _curTime current game time since start
    /// \param[o] _score player score
    void FlyShip(float &_deltaTime, float &_curTime, float &_score);
    /// \brief method - collision detection system
    /// \param[in] _refObj a pointer to closest Asteroid object
    /// \param[in] _refShipEn a pointer to closest Enemy Ship
    /// \param[in] _refShipAl a pointer to closest Ally Ship
    /// \param[in] _refBullet a pointer to closest Bullet object
    /// \param[in] _deltaTime current delta time
    /// \param[o] _score player score to override
    void CollisionDetect(GameObject *_refObj, Ship *_refShipEn, Ship *_refShipAl, GameObject *_refBullet, float &_deltaTime, float &_score);
    /// \brief method to apply damage
    /// \param[in] _sDmg damage applied to shield
    /// \param[in] _hDmg damage applied to health
    void DamageShip(float _sDmg, float _hDmg);
    /// \brief method for resetting a ship
    void resetShip();
    /// \brief accessor method for speed (that is, speeds[0])
    int GetCurrentSpeed();
    /// \brief template method for determining closest object (can be a GameObject(bullets and asteroids) or a Ship)
    template<typename T1> T1* GetNearestTgtObj (std::vector<T1>* _allObjs, objTag tagg[], bool _isBul);
private:
    /// \brief collision distance
    float m_collisionDist = 2.0f;
    /// \brief similar to m_target, is a position for navigation. Used in patrol sequence to determine starting point
    glm::vec3 m_navpoint;
    /// \brief a pointer to array containing all Asteroids
    std::vector<GameObject> *m_allGOs;
    /// \brief a pointer to array containing all Bullets
    std::vector<GameObject> *m_allBuls;
    /// \brief a pointer to array containing all Ships
    std::vector<Ship> *m_allShips;
    /// \brief enumerated data type representing ship states
    enum SHIPSTATES{PATROL, FOLLOW, EVADE, BATTLE, IDLE};
    /// \brief current state of the ship
    SHIPSTATES m_shipStates = IDLE;
    /// \brief distance values used in AI situation awareness checks
    /// //min, attack, active
    float m_actionDistances[3] = {4.2f, 31.0f, 1000.0f};
    /// \brief speed related properties such as current speed, acceleration, rotation speed etc.
    //current, min, max, accel, curRot, minRot, maxRot
    float m_speeds[7] = {0.0f, 0.05f, 0.8f, 0.1f, 0.0f, 0.005f, 0.05f};

    /// \brief method to update rotation speed based on movement speed
    void SetCurRotSpd()
    {
        //MIN + (CURRENT SPEED PERCENTAGE) * MAX
        m_speeds[4] = m_speeds[5] + (m_speeds[0]/m_speeds[2])*m_speeds[6];
    }
    /// \brief method to rotate and translate a ship towards its target
    /// \param[in] _deltaTime current delta time
    void FollowTarget(float &_deltaTime);
    /// \brief method to evade an obstacle (part of AI algorithm)
    /// \param[in] _deltaTime current delta time
    /// \param[in] _curTgt a pointer to current closest enemy
    /// \param[in] _navDist distance to current evasion point
    void Evade(float &_deltaTime, Ship *_curTgt, float &_navDist);
    /// \brief method patrol area around a point if no targets present in range (part of AI algorithm)
    /// \param[in] _deltaTime current delta time
    /// \param[in] _curTgt a pointer to current closest enemy
    /// \param[in] _tgtDist distance to the enemy
    /// \param[in] _navDist distance to patrol sequence starting point (m_navpoint)
    void Patrol(float &_deltaTime, Ship *_curTgt, float &_tgtDist, float &_navDist);
    /// \brief method to follow an enemy ship (part of AI algorithm)
    /// \param[in] _deltaTime current delta time
    /// \param[in] _curTgt a pointer to current closest enemy
    /// \param[in] _dist distance to the enemy
    void Follow(float &_deltaTime, Ship *_curTgt, float &_dist);
    /// \brief method to toggle fire at enemy ship (part of AI algorithm)
    /// \param[in] _deltaTime current delta time
    /// \param[in] _curTgt a pointer to current closest enemy
    /// \param[in] _dist distance to the enemy
    void Battle(float &_deltaTime, Ship *_curTgt, float &_dist);
    /// \brief method for generating a random position within range of initial position
    /// \param[in] _refPos initial position (origin)
    glm::vec3 RandCoords(glm::vec3 _refPos);
}; //end of class

#endif // SHIP_H
