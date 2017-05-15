#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

/// \brief Main object class used in this game
/// \author Renats Bikmajevs

/// \brief Enumerated data type objTag is widely used in AI IFF and rendering
typedef enum OBJTAG{TERRAN,PIRATE,ALIEN,PLAYER,NONE}objTag;

/// \class GameObject
/// \brief Contains all necessary functionality for vector calculations
class GameObject
{
public:
    /// \brief Default ctor
    GameObject()=default;
    /// \brief Custom ctor
    /// \param[in] _pos position of the GameObject
    /// \param[in] _rot rotation of the GameObject
    /// \param[in] _tag tag of the GameObject
    GameObject(glm::vec3 _pos, glm::vec3 _rot, objTag _tag)
    {
        m_position = _pos;
        m_rotation = _rot;
        m_tag = _tag;
    }
    //public members
    /// \brief position vector
    glm::vec3 m_position;
    /// \brief rotation vector (Axis Angles in degrees)
    glm::vec3 m_rotation;
    /// \brief Orientation vector. Local Z
    glm::vec3 m_forward;
    /// \brief local X
    glm::vec3 m_left;
    /// \brief local Y
    glm::vec3 m_up;
    /// \brief delay used in bullet life time check
    float m_dieTime = 0.0f;
    /// \brief size of the geometry (always 1 except for the asteroids)
    float m_size = 1;
    /// \brief GameObject's game tag
    objTag m_tag;

    //public methods
    /// \brief method to calculate local axis based on current rotation angles
    void anglesToAxes();
    /// \brief method to translate a simple object (that has no "m_speed" variable)
    /// \param[in] _objSpeed m_speed of the object
    void moveObject(float &_objSpeed);
    /// \brief method to convert vec3 rotation (degrees) to a quaternion (radians)
    /// \param[in] _angles rotation angles
    glm::quat anglesToQuat(glm::vec3 &_angles);
    /// \brief method to calculate a quaternion rotation necessary to apply to current to get resulting rotation
    /// \param[in] _start initial rotation angles
    /// \param[in] _dest resulting rotation angles
    glm::quat RotationBetweenVectors(glm::vec3 &_start, glm::vec3 &_dest);
    /// \brief method alternative to glm::max to SLERP between two quaternion rotations
    /// \param[in] _q1 initial quaternion
    /// \param[in] _q2 end quaternion
    /// \param[in] _maxAngle current rotation change limitations (change rate)
    glm::quat RotateTowards(glm::quat &_q1, glm::quat &_q2, float _maxAngle);
}; //end of class

#endif // GAMEOBJECT_H
