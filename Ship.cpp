///
/// @file Ship.cpp
/// @version 1.0
/// @brief This module handles AI and movement of a ship object

#include "Ship.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

void Ship::IncreaseSpeed(float _value)
{
    //this is mainly for being able to change m_speed from the outside (speeds are private)
    //although used internally as well
    m_speeds[0] += m_speeds[3]*_value;
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::FollowTarget(float &_deltaTime)
{
    //rotate and translate towards m_target
    //take default direction vector on Z axis
    glm::vec3 fromVec = glm::vec3(0,0,10);
    //take m_target direction as resulting vector
    glm::vec3 toVec = m_target - m_position;
    //find rotation as quaternion necessary to apply to object to make it face resulting vector (inputs get normalised)
    glm::quat newRot = RotationBetweenVectors(fromVec, toVec);
    //convert current rotation angles to radians as quats use radians
    glm::vec3 tempooo = glm::radians(m_rotation);
    //convert current radian rotation to a quat
    glm::quat tmp1 = anglesToQuat(tempooo);
    //SLERP between current and resulting rotation
    glm::quat temp = RotateTowards(tmp1, newRot, m_speeds[4]*_deltaTime);
    //convert result back to degrees and assign to rotation variable
    m_rotation = glm::degrees(glm::eulerAngles(temp));
    //recalculate direction vectors
    anglesToAxes();

    //handle speed
    if(m_toggleAI == true) //player ship's m_speed is handled elsewhere
    {
        //increase speed
        if(m_speeds[0]<m_speeds[2]) //current < Max
        {
            IncreaseSpeed(_deltaTime);
        }
        if(m_speeds[0] > m_speeds[2]) //current > Max
        {
            m_speeds[0] = m_speeds[2];
        }
    }
    //handle translation
    glm::vec3 newMV = m_forward;
    //since forward vector is normalised timing it by speed will change its magnitude to the value of speed
    newMV.x *= m_speeds[0]*_deltaTime;
    newMV.y *= m_speeds[0]*_deltaTime;
    newMV.z *= m_speeds[0]*_deltaTime;
    //add result to current position
    m_position+=newMV;
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::Evade(float &_deltaTime, Ship *_curTgt, float &_navDist)
{
    //Evade is called whenever the ship gets too close to another ship or asteroid
    if(m_target == m_position) //special case when evasion is called for the first time
    {
        //generate a random point within weapons range from the ship
        do //we have to at least do it once
        {
            m_target = RandCoords(m_position); //random coords relative to this position
        }
        while(glm::dot(m_forward, m_target-m_position) > 0); //make sure the evasion point is not right in front of us
        //as this would not make sense and we would hit the objects we are trying to evade
        FollowTarget(_deltaTime);
    }
    else //if we already have a m_navpoint to follow
    {
        if (_navDist <= m_actionDistances[0]) //reached evasion coords
        {
            m_target = _curTgt->m_position; //set target position back to original ship target
            m_shipStates = FOLLOW;
        }
        else //still flying towards the navpoint
        {
            FollowTarget(_deltaTime);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::Patrol(float &_deltaTime, Ship *_curTgt, float &_tgtDist, float &_navDist)
{
    //Patrol is called whenever there are no enemies within active detection range
    if(_curTgt!=nullptr) //sanity check
    {
        if(_tgtDist <= m_actionDistances[2]) //target in range
        {
            m_target = _curTgt->m_position; //set target as enemy ship position
            m_shipStates = FOLLOW;
        }
        else //no targets in range but targets present beyond detection range
        {
            //in this case we ARE actually patrolling
            if(_navDist < m_actionDistances[0]) //reached m_navpoint position
            //also is run when patrol is called for the first time and navpoint(target) is set to current position
            {
                //generate position within active detection range to navpoint
                m_target = RandCoords(m_navpoint);
                FollowTarget(_deltaTime);
            }
            else //already have coordinates to go to
            {
                FollowTarget(_deltaTime);
            }
        }
    }
    else //if there are no targets at all
    //unlikely but possible scenario - when all enemy ships are destroyed at once
    {
        //perform partrol
        if(_navDist <= m_actionDistances[0]) //reached target position
        {
            //generate position within active detection range to navpoint
            m_target = RandCoords(m_navpoint);
            FollowTarget(_deltaTime);
        }
        else //already have a navpoint to follow
        {
            FollowTarget(_deltaTime);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::Follow(float &_deltaTime, Ship *_curTgt, float &_dist)
{
    //Follow is called whenever there is a target within active detection range
    if(_dist > m_actionDistances[2]) //enemy escaped from detection range
    {
        //switch to patrol
        m_navpoint = m_position;
        m_target = m_position;
        m_shipStates = PATROL;
    }
    else //enemy still within ranges
    {
        if(_dist <= m_actionDistances[1]) //enemy is within weapons range
        {
            //switch m_navpoint to enemy position
            m_target = _curTgt->m_position;
            //still follow the enemy as BATTLE will only be called in the next frame
            FollowTarget(_deltaTime);
            //switch to battle state
            m_shipStates = BATTLE;
        }
        else //enemy is outside weapons range
        {
            //follow the enemy
            m_target = _curTgt->m_position;
            FollowTarget(_deltaTime);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::Battle(float &_deltaTime, Ship *_curTgt, float &_dist)
{
    //Battle is called whenever enemy is within weapons range
    if (_dist <= m_actionDistances[1]) //if enemy is still within weapons range
    {
        if(_dist <= m_actionDistances[0]) //if enemy is too close
        {
            if(m_target != m_position && m_shipStates != EVADE) //no evasion activated yet
            {
                m_fireWeapons = false;
                m_target = m_position;
                m_shipStates = EVADE;
            }
        }
        else //enemy is just withing weapons range
        {
            m_target = _curTgt->m_position;
            if (glm::dot(m_forward,glm::normalize(m_target-m_position)) > 0.8f) //if enemy is in front
            {
                m_fireWeapons = true;
            }
            else //enemy is not in front
            {
                m_fireWeapons = false;
            }
            FollowTarget(_deltaTime);
        }
    }
    else //enemy is not withing weapons range anymore
    {
        m_fireWeapons = false;
        if(_dist >= m_actionDistances[2]) //if target is out of detection range (might happen after enemy destruction and respawn)
        {
            m_target = m_position;
            m_navpoint = m_position;
            m_shipStates = PATROL;
        }
        else //enemy is within detection range
        {
            m_shipStates = FOLLOW;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::FireBullet(glm::vec3 &_curTgt, float &_curTime)
{
    //handle rotation of bullet
    //(this is almost the same as for ship rotation)
    glm::vec3 bulRotation;
    glm::vec3 fromVec = glm::vec3(0,0,10); //default orientation
    glm::vec3 toVec = _curTgt - m_position; //target direction
    glm::quat newRot = RotationBetweenVectors(fromVec, toVec); //rotation quat
    bulRotation = glm::degrees(glm::eulerAngles(newRot)); //convert rotation quat to vec3
    //create the bullet object
    GameObject newBullet;
    //set all necessary properties
    newBullet.m_position = m_position + (m_forward * 0.05f);
    newBullet.m_rotation = bulRotation;
    newBullet.m_tag = m_tag; //the same as this ship's tag
    newBullet.m_forward = m_forward; //the same as this ship's forward
    newBullet.m_dieTime = _curTime+5.0f;
    if(m_isPlayer == true) //for player bullets
    {
        newBullet.m_tag = PLAYER;
    }
    m_allBuls->push_back(newBullet); //add this bullet to the all bullet vector
}
//----------------------------------------------------------------------------------------------------------------------
glm::vec3 Ship::RandCoords(glm::vec3 _refPos)
{
    glm::vec3 randCoord;
    randCoord.x = _refPos.x + (rand()%(int)(m_actionDistances[1]*2) - m_actionDistances[1]);
    randCoord.y = _refPos.y + (rand()%(int)(m_actionDistances[1]*2) - m_actionDistances[1]);
    randCoord.z = _refPos.z + (rand()%(int)(m_actionDistances[1]*2) - m_actionDistances[1]);
    return randCoord;
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::FlyShip(float &_deltaTime, float &_curTime, float &_score)
{
    //The main controller for the ship object
    SetCurRotSpd(); //update rotation speed
    //determine enemy tags based on current tag
    objTag tgtTag[2];
    switch(m_tag)
    {
        case TERRAN:
        {
            tgtTag[0] = PIRATE;
            tgtTag[1] = ALIEN;
            break;
        }
        case PIRATE:
        {
            tgtTag[0] = TERRAN;
            tgtTag[1] = ALIEN;
            break;
        }
        case ALIEN:
        {
            tgtTag[0] = TERRAN;
            tgtTag[1] = PIRATE;
            break;
        }
        default : break;
    }
    //find closest objects to this one
    GameObject *tmpObj = nullptr;
    GameObject *tmpBullet = nullptr;
    Ship *tmpShEn = nullptr;
    Ship *tmpSh = nullptr;
    objTag tempTags[2] = {m_tag, m_tag}; //only necessary for allies
    tmpShEn = GetNearestTgtObj(m_allShips, tgtTag, false); //closest enemy
    objTag noneTemp[] = {NONE, NONE}; //only necessary for asteroids
    tmpObj = GetNearestTgtObj(m_allGOs, noneTemp, false); //closest asteroid
    tmpSh = GetNearestTgtObj(m_allShips, tempTags, false); //closest ally
    tmpBullet = GetNearestTgtObj(m_allBuls, tgtTag, true); //closest enemy bullet

    //for ship m_actionDistances:
    //0 = min, 1 = attack, 2 = active

    //detect and handle any ocurring collisions
    CollisionDetect(tmpObj, tmpShEn, tmpSh, tmpBullet, _deltaTime, _score);

    if(m_toggleAI == true) //NPC ship
    {
        //store this in a variable to avoid multiple duplicate calculations
        float tgtDistance = glm::distance(m_position, tmpShEn->m_position);
        //if any of the closest objects are too close
        if(tgtDistance <= m_actionDistances[0]||
           glm::distance(m_position, tmpObj->m_position) <= m_actionDistances[0]||
           glm::distance(m_position, tmpSh->m_position) <= m_actionDistances[0])
        {
            if(m_target != m_position && m_shipStates != EVADE) //if no evasion active yet
            {
                m_target = m_position;
                m_shipStates = EVADE;
            }
            Evade(_deltaTime, tmpShEn, tgtDistance);
        }

        //store this in a variable to avoid multiple duplicate calculations
        float navDistance = glm::distance(m_position, m_target);
        //perform actions based on current ship state
        switch(m_shipStates)
        {
            case IDLE: //no states set yet
            {
                m_navpoint = m_position;
                m_target = m_position;
                m_shipStates = PATROL;
                break;
            }
            case PATROL: //no target, wander around a nav point
            {
                Patrol(_deltaTime, tmpShEn, tgtDistance, navDistance);
                break;
            }
            case EVADE: //avoiding collision
            {
                Evade(_deltaTime, tmpShEn, navDistance);
                break;
            }
            case FOLLOW: //target present in range, following
            {
                Follow(_deltaTime, tmpShEn, tgtDistance);
                break;
            }
            case BATTLE: //target present in weapons range, fire
            {
                Battle(_deltaTime, tmpShEn, tgtDistance);
                break;
            }
        }
    }
    else //if this ship is a player
    {
        //first check if speed is correct
        if(m_speeds[0] > m_speeds[2])
        {
            m_speeds[0] = m_speeds[2];
        }
        if(m_speeds[0] < 0)
        {
            m_speeds[0] = 0;
        }
        //make player ship just follow the target (which is camera direction)
        FollowTarget(_deltaTime);
    }
    //weapon fire control is the same for every ship
    if(m_fireWeapons == true)
    {
        if(_curTime >= m_nextFire) //if end of delay
        {
            //launch a bullet
            FireBullet(m_target, _curTime);
            //update delay
            m_nextFire = _curTime + m_fireDelay;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::CollisionDetect(GameObject *_refObj, Ship *_refShipEn, Ship *_refShipAl, GameObject *_refBullet, float &_deltaTime, float &_score)
{
    //regenerate shield if less than max
    if(m_curShield < m_maxShield)
    {
        m_curShield+=m_regenSpeed*_deltaTime;
    }
    if(_refObj != nullptr) //for collision with an Asteroid
    {
        //in terms of geometry asteroids are slightly bigger than ships, so use half their size to adjust distance check
        if(glm::distance(_refObj->m_position, m_position)-_refObj->m_size/2 <= m_collisionDist)
        {
            DamageShip(40.0f*_deltaTime, 50.0f*_deltaTime);
        }
    }
    if(_refShipEn != nullptr) //for collision with Enemy Ship
    {
        if(glm::distance(_refShipEn->m_position, m_position) <= m_collisionDist)
        {
            DamageShip(50.0f*_deltaTime, 70.0f*_deltaTime);
        }
    }
    if(_refShipAl != nullptr) //for collision with Ally Ship
    {
        if(glm::distance(_refShipAl->m_position, m_position) <= m_collisionDist)
        {
            DamageShip(50.0f*_deltaTime, 70.0f*_deltaTime);
        }
    }
    if(_refBullet != nullptr) //for collision with a bullet
    {
        //bullets are smaller than ships, so adjust distance check by reducing collision distance half its size
        if(glm::distance(_refBullet->m_position, m_position) <= m_collisionDist/2)
        {
            DamageShip(15.0f, 10.0f);
            if(_refBullet->m_tag == PLAYER) //if a bullet was shot by player
            {
                //add hit m_score to player
                _score+=0.5f;
                if(m_curHealth <= 0)
                {
                    //add kill m_score to player
                    _score+=7.5f;
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::DamageShip(float _sDmg, float _hDmg)
{
    //if shields are still online
    if(m_curShield > 0)
    {
        //check if current shields are enough to sustain damage
        if(m_curShield >= _sDmg)
        {
            m_curShield -= _sDmg;
        }
        else //shield value is smaller than damage
        {
            int temp = _sDmg - m_curShield; //get the difference
            m_curShield = 0;
            //also reduce health
            m_curHealth -= temp;
        }
    }
    else //no shields online
    {
        m_curHealth -= _hDmg;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Ship::resetShip()
{
    //create a variable to avoid duplicate expressions
    glm::vec3 zeroVec = {0,0,0};
    //set everything to zero, switch to Idle and turn off weapons
    m_rotation = zeroVec;
    m_speeds[0] = 0.0f;
    m_speeds[4] = 0.0f;
    m_target = zeroVec;
    m_shipStates = IDLE;
    m_fireWeapons = false;
    //reset shields and health
    m_curHealth = m_maxHealth;
    m_curShield = m_maxShield;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename T1> T1* Ship::GetNearestTgtObj (std::vector<T1>* _allObjs, objTag tagg[], bool _isBul)
{
    T1 *closestSH; //store a pointer closest object
    if(_allObjs->size() <= 1) //if there is only one ship (i.e. this one)
    {
        return nullptr;
    }
    int minDist = 99999999; //could be math.infinity or something like that, but the distance will never get past scene size anyway
    if(!_allObjs->empty()) //sanity check
    {
        int arrSize = _allObjs->size(); //avoid multiple calculations
        for(int i=0; i<arrSize; ++i)
        {
            //if object's tag is one of those we are looking for and if it's closer than previous closest one
            if((_allObjs->at(i).m_tag == tagg[0] || _allObjs->at(i).m_tag == tagg[1] || _allObjs->at(i).m_tag == PLAYER)
                && glm::distance(m_position, _allObjs->at(i).m_position) < minDist)
            {
                if(_isBul == true) //bullets will never be the same as calling object, this might speed things up
                    //when we have many bullets in the scene (can be up to several thousands)
                {
                        if(m_isPlayer == false)
                        {
                          closestSH = &(_allObjs->at(i));
                          minDist = glm::distance(m_position, _allObjs->at(i).m_position);
                        }
                        else
                        {
                          if(_allObjs->at(i).m_tag != PLAYER)
                          {
                            closestSH = &(_allObjs->at(i));
                            minDist = glm::distance(m_position, _allObjs->at(i).m_position);
                          }
                        }
                }
                else //even though we will have to perform this check for all non-bullet objects as well,
                    //their number is much smaller that that of the bullets (potentially)
                {
                    if(this != &(_allObjs->at(i))) //check if we are not looking at ourselves
                    {
                        closestSH = &(_allObjs->at(i));
                        minDist = glm::distance(m_position, _allObjs->at(i).m_position);
                    }
                }
            }
        }
        return closestSH; //upon success return pointer to the closest object
    }
    return nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
int Ship::GetCurrentSpeed()
{
  return (int)(m_speeds[0]*100);
}
