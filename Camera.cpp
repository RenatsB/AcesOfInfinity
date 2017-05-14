///
///  @file Name.cpp
///  @brief A short description of the module

#include "Camera.h"
#ifdef WIN32
  #include <Windows.h> // must be before gl.h include
#endif

#if defined (__linux__) || defined (WIN32)
  #include <GL/gl.h>
#endif
#ifdef __APPLE__
  #include <OpenGL/gl.h>
#endif
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera::lookAtTgt()
{
    eye = position+camTarget;
    loadModelView(glm::lookAt(eye, camTarget, glm::vec3(0,1,0)));
}

void Camera::camPerspective()
{
    loadProjection(glm::perspective(_fovy, _aspect, _zNear, _zFar));
}

void Camera::loadModelView(glm::mat4 _matrix)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf((const float*)glm::value_ptr(_matrix));
}

void Camera::loadProjection(glm::mat4 _matrix)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf((const float*)glm::value_ptr(_matrix));
    glMatrixMode(GL_MODELVIEW);
}

void Camera::camOrbit(int &_x, int &_y)
{    
    int diffx=_x-oldX;
    int diffy=_y-oldY;
    rotX += (float) 0.5f * diffy;
    rotY += (float) 0.5f * diffx;
    //prevent from flipping camera
    if(rotX > 85.0f)
    {
        rotX = 85.0f;
    }
    if(rotX < -85.0f)
    {
        rotX = -85.0f;
    }
    //make sure we're not dealing with overly big angles
    if(rotY > 360.0f)
    {
        rotY -= 360.0f;
    }
    if(rotY < -360.0f)
    {
        rotY += 360.0f;
    }
}

void Camera::camZoom(int &_y)
{
    int diffy=_y-oldZoom;
    zoom -= (float)0.05f * diffy;
    //max zoom
    if(zoom > 25.0f)
    {
        zoom = 25.0f;
    }
    //min zoom
    if(zoom < 1.0f)
    {
        zoom = 1.0f;
    }
}

void Camera::getCamDir()
{
    rotation.y = rotY;
    rotation.x = 0;
    rotation.z = 0;
    anglesToAxes();

    forward = ((float)cos(glm::radians(rotX))*forward) + ((float)sin(glm::radians(rotX))*glm::cross(left, forward)) +
            ((1 - (float)cos(glm::radians(rotX)))*(glm::dot(left,forward))*forward);
    forward*=20.0f;
}
