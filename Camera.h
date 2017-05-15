#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include <cmath>

/// \brief A container for all camera related properties
/// \author Renats Bikmajevs
/// \version 1.0

/// \class Camera
/// \brief A container of all camera and view related properties and methods

class Camera: public GameObject
{
public:
    /// \brief Default ctor
    Camera()=default;

    //public properties
    /// \brief coordinates which camera is pointing to
    glm::vec3 m_camTarget;
    /// \brief position of the camera
    glm::vec3 m_eye;
    /// \brief field of view
    float m_fovy;
    /// \brief aspect ratio
    float m_aspect;
    /// \brief near clipping plane
    float m_zNear;
    /// \brief far clipping plane
    float m_zFar;
    /// \brief camera zoom
    float m_zoom = 1.0f;
    /// \brief vertical rotation of the camera
    float m_rotX;
    /// \brief horizontal rotation of the camera
    float m_rotY;
    /// \brief old vertical rotation stored for finding relative rate of change
    int m_oldX;
    /// \brief old horizontal rotation stored for finding relative rate of change
    int m_oldY;
    /// \brief old zoom stored for finding relative rate of change
    int m_oldZoom;

    //public methods
    /// \brief method to adjust eye and call loadModelView
    void lookAtTgt();
    /// \brief method to call loadProjection
    void camPerspective();
    /// \brief method to update camera rotation angles
    /// \param[in] _x current x coordinates of the mouse
    /// \param[in] _y current y coordinates of the mouse
    void camOrbit(int &_x, int &_y);
    /// \brief method to update camera zoom
    /// \param[in] _y current y coordinates of the mouse
    void camZoom(int &_y);
    /// \brief method to find current camera orientation vector
    void getCamDir();
private:
    //private methods
    /// \brief method to load ModelView matrix
    void loadModelView(glm::mat4 _matrix);
    /// \brief method to load Projection matrix
    void loadProjection(glm::mat4 _matrix);
}; //end of class

#endif // CAMERA_H
