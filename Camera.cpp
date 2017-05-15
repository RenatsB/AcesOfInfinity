///
/// @file Camera.cpp
/// @brief This module handles all camera related methods
/// including loading matrices and adjusting camera properties

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
    m_eye = m_position+m_camTarget;
    loadModelView(glm::lookAt(m_eye, m_camTarget, glm::vec3(0,1,0)));
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::camPerspective()
{
    loadProjection(glm::perspective(m_fovy, m_aspect, m_zNear, m_zFar));
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::loadModelView(glm::mat4 _matrix)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf((const float*)glm::value_ptr(_matrix));
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::loadProjection(glm::mat4 _matrix)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf((const float*)glm::value_ptr(_matrix));
    glMatrixMode(GL_MODELVIEW);
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::camOrbit(int &_x, int &_y)
{    
    int diffx=_x-m_oldX;
    int diffy=_y-m_oldY;
    m_rotX += (float) 0.5f * diffy;
    m_rotY += (float) 0.5f * diffx;
    //prevent from flipping camera
    /*if(m_rotX > 85.0f)
    {
        m_rotX = 85.0f;
    }
    if(m_rotX < -85.0f)
    {
        m_rotX = -85.0f;
    }*/
    //make sure we're not dealing with overly big angles
    if(m_rotY > 360.0f)
    {
        m_rotY -= 360.0f;
    }
    if(m_rotY < -360.0f)
    {
        m_rotY += 360.0f;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::camZoom(int &_y)
{
    int diffy=_y-m_oldZoom;
    m_zoom -= (float)0.05f * diffy;
    //max zoom
    if(m_zoom > 25.0f)
    {
        m_zoom = 25.0f;
    }
    //min zoom
    if(m_zoom < 1.0f)
    {
        m_zoom = 1.0f;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::getCamDir()
{
    m_rotation.y = m_rotY;
    m_rotation.x = 0;
    m_rotation.z = 0;
    anglesToAxes();

    m_forward = ((float)cos(glm::radians(m_rotX))*m_forward) + ((float)sin(glm::radians(m_rotX))*glm::cross(m_left, m_forward)) +
            ((1 - (float)cos(glm::radians(m_rotX)))*(glm::dot(m_left,m_forward))*m_forward);
    m_forward*=20.0f;
}
