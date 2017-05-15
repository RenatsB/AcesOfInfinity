#ifndef SHIP_H
#define SHIP_H
#include "GameObject.h"

/// \brief Main object (ship) handling module
/// \author Renats Bikmajevs

/// \class Ship
/// \brief This class includes all properties and AI necessary for automatic event handling

class Ship: public GameObject
{
public:
    Ship()=default;
    Ship(glm::vec3 _pos, glm::vec3 &_rot, objTag _tag, bool _isPlr,
         std::vector<GameObject> *_allGOS, std::vector<Ship> *_allShips, std::vector<GameObject> *_allBullets)
    {
        m_position = _pos;
        m_rotation = _rot;
        m_tag = _tag;
        isPlayer = _isPlr;
        allGOs = _allGOS;
        allShips = _allShips;
        allBuls = _allBullets;
    }
    bool isPlayer = false;
    bool autopilotOn = false;
    glm::vec3 target = {0,0,0};
    float m_curHealth = 100.0f;
    float maxHealth = 100.0f;
    float m_curShield = 120.0f;
    float maxShield = 120.0f;
    float regenSpeed = 2.5f;

    bool fireWeapons = false;
    float fireDelay = 0.15f;
    float nextFire = 0.0f;

    void IncreaseSpeed(float _value);

    void FireBullet(glm::vec3 &_curTgt, float &_curTime);

    void FlyShip(float &_deltaTime, float &_curTime, float &_score);

    void ControlShip(float &_deltaTime, bool &_isFire, bool &_isAccel, bool &_isFollow);

    void CollisionDetect(GameObject *refObj, Ship *refShipEn, Ship *refShipAl, GameObject *refBullet, float &_deltaTime, float &_score);

    void DamageShip(float _sDmg, float _hDmg);

    void resetShip();

    int GetCurrentSpeed();

    template<typename T1> T1* GetNearestTgtObj (std::vector<T1>* _allObjs, objTag tagg[], bool _isBul);
private:
    float m_collisionDist = 2.0f;

    glm::vec3 m_navpoint;
    std::vector<GameObject> *allGOs;
    std::vector<GameObject> *allBuls;
    std::vector<Ship> *allShips;
    enum SHIPSTATES{PATROL, FOLLOW, EVADE, BATTLE, IDLE};
    SHIPSTATES shipStates = IDLE;
    //patrol|follow|evade|battle
    float actionDistances[3] = {4.2f, 31.0f, 1000.0f};
    //min, attack, active
    float speeds[7] = {0.0f, 0.05f, 0.8f, 0.1f, 0.0f, 0.005f, 0.05f};
    //current, min, max, accel, curRot, minRot, maxRot

    void SetCurRotSpd()
    {
        //MIN + (CURRENT SPEED PERCENTAGE) * MAX
        speeds[4] = speeds[5] + (speeds[0]/speeds[2])*speeds[6];
    }
    void FollowTarget(float &_deltaTime);
    void Evade(float &_deltaTime, Ship *_curTgt, float &_navDist);
    void Patrol(float &_deltaTime, Ship *_curTgt, float &_tgtDist, float &_navDist);
    void Follow(float &_deltaTime, Ship *_curTgt, float &_dist);
    void Battle(float &_deltaTime, Ship *_curTgt, float &_dist);

    glm::vec3 RandCoords(glm::vec3 _refPos);
}; //end of class

#endif // SHIP_H
