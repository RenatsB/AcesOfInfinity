#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include <cmath>

/// \brief A container for all camera related properties
/// \author Renats Bikmajevs
/// \version 1.0
/// \date 12/05/17 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 21/01/17
/// \todo some tidying up and code optimizations

/// \class Camera
/// \brief A container of all camera and view related properties and methods

class Camera: public GameObject
{
public:
    Camera()=default; //default ctor

    //public properties
    glm::vec3 camTarget;
    glm::vec3 eye;
    float _fovy;
    float _aspect;
    float _zNear;
    float _zFar;
    float zoom = 1.0f;
    float rotX;
    float rotY;
    int oldX;
    int oldY;
    int oldZoom;

    //public methods
    void lookAtTgt();
    void camPerspective();
    void loadModelView(glm::mat4 _matrix);
    void loadProjection(glm::mat4 _matrix);
    void camOrbit(int &_x, int &_y);
    void camZoom(int &_y);
    void getCamDir();
}; //end of class

#endif // CAMERA_H
