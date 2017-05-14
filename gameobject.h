#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

typedef enum OBJTAG{TERRAN,PIRATE,ALIEN,PLAYER,NONE}objTag;

class GameObject
{
public:
    GameObject()=default;
    GameObject(glm::vec3 _pos, glm::vec3 _rot, objTag _tag)
    {
        position = _pos;
        rotation = _rot;
        tag = _tag;
    }
    glm::vec3 position;
    glm::vec3 rotation;

    glm::vec3 forward;
    glm::vec3 left;
    glm::vec3 up;

    float dieTime = 0.0f;
    float size = 1;
    objTag tag;

    void anglesToAxes();

    void moveObject(float &_objSpeed);

    glm::quat anglesToQuat(glm::vec3 &_eulers);

    glm::quat RotationBetweenVectors(glm::vec3 &start, glm::vec3 &dest);

    glm::quat RotateTowards(glm::quat q1, glm::quat q2, float maxAngle);
};

#endif // GAMEOBJECT_H
