///
/// @file GameObject.cpp
/// @brief This module handles vector and rotation maths
/// and contains all basic game object properties

#include <GameObject.h>
#include <cmath>
#include <glm/gtx/norm.hpp>

void GameObject::moveObject(float &_objSpeed)
{
    anglesToAxes(); //recalculate direction vectors
    m_position += m_forward*_objSpeed;
}
//----------------------------------------------------------------------------------------------------------------------
/// The following section was adapted from :-
/// Song Ho Ann (2013). OpenGL Angles to Axes [online]. [Accessed 2017].
/// Available from: "http://www.songho.ca/opengl/gl_anglestoaxes.html".
void GameObject::anglesToAxes()
{
    float sx, sy, sz, cx, cy, cz, theta;

    // rotation angle about X-axis (pitch)
    theta = glm::radians(m_rotation.x);
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = glm::radians(m_rotation.y);
    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = glm::radians(m_rotation.z);
    sz = sinf(theta);
    cz = cosf(theta);

    // determine left axis
    m_left.x = cy*cz;
    m_left.y = sx*sy*cz + cx*sz;
    m_left.z = -cx*sy*cz + sx*sz;

    // determine up axis
    m_up.x = -cy*sz;
    m_up.y = -sx*sy*sz + cx*cz;
    m_up.z = cx*sy*sz + sx*cz;

    // determine forward axis
    m_forward.x = sy;
    m_forward.y = -sx*cy;
    m_forward.z = cx*cy;
}
/// end of Citation
//----------------------------------------------------------------------------------------------------------------------
/// The following section was taken from :-
/// Richard Fabian (2011). Thread: GLM:Euler Angles to Quaternion [online]. Answered Jun 10 2011 at 10:05 [Accessed 2017].
/// Available from: "https://gamedev.stackexchange.com/questions/13436/glm-euler-angles-to-quaternion".
glm::quat GameObject::anglesToQuat(glm::vec3 &_angles)
{
    float sx, sy, sz, cx, cy, cz;
    sx = sin(_angles.x/2); sy = sin(_angles.y/2); sz = sin(_angles.z/2);
    cx = cos(_angles.x/2); cy = cos(_angles.y/2); cz = cos(_angles.z/2);

    return glm::quat( cx*cy*cz + sx*sy*sz,
       sx*cy*cz - cx*sy*sz,
       cx*sy*cz + sx*cy*sz,
       cx*cy*sz - sx*sy*cz ); // for XYZ application order
}
//----------------------------------------------------------------------------------------------------------------------
/// The following section was taken from :-
/// Arnaud Masserann (2013). quaternion_utils.cpp(Github) [online]. [Accessed 2017].
/// Available from: "https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp".
glm::quat GameObject::RotationBetweenVectors(glm::vec3 &_start, glm::vec3 &_dest)
{
        _start = glm::normalize(_start);
        _dest = glm::normalize(_dest);

        float cosTheta = dot(_start, _dest);
        glm::vec3 rotationAxis;

        if (cosTheta < -1 + 0.001f){
                // special case when vectors in opposite directions:
                // there is no "ideal" rotation axis
                // So guess one; any will do as long as it's perpendicular to start
                rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), _start);
                if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
                        rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), _start);

                rotationAxis = glm::normalize(rotationAxis);
                return glm::angleAxis(180.0f, rotationAxis);
        }

        rotationAxis = glm::cross(_start, _dest);

        float s = sqrt( (1+cosTheta)*2 );
        float invs = 1 / s;

        return glm::quat(
                s * 0.5f,
                rotationAxis.x * invs,
                rotationAxis.y * invs,
                rotationAxis.z * invs
        );
}
//----------------------------------------------------------------------------------------------------------------------
/// The following section was taken from :-
/// Arnaud Masserann (2013). quaternion_utils.cpp(Github) [online]. [Accessed 2017].
/// Available from: "https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp".
glm::quat GameObject::RotateTowards(glm::quat &_q1, glm::quat &_q2, float _maxAngle){

        if( _maxAngle < 0.001f ){
                // No rotation allowed. Prevent dividing by 0 later.
                return _q1;
        }

        float cosTheta = glm::dot(_q1, _q2);

        // q1 and q2 are already equal.
        // Force q2 just to be sure
        if(cosTheta > 0.9999f){
                return _q2;
        }

        // Avoid taking the long path around the sphere
        if (cosTheta < 0){
            _q1 = _q1*-1.0f;
            cosTheta *= -1.0f;
        }

        float angle = acos(cosTheta);

        // If there is only a 2&deg; difference, and we are allowed 5&deg;,
        // then we arrived.
        if (angle < _maxAngle){
                return _q2;
        }

        float fT = _maxAngle / angle;
        angle = _maxAngle;

        glm::quat tmp1;
        tmp1.x = _q1.x * sin((1.0f - fT) * angle);
        tmp1.y = _q1.y * sin((1.0f - fT) * angle);
        tmp1.z = _q1.z * sin((1.0f - fT) * angle);
        tmp1.w = _q1.w * sin((1.0f - fT) * angle);
        glm::quat tmp2;
        tmp2.x = _q2.x * sin(fT * angle);
        tmp2.y = _q2.y * sin(fT * angle);
        tmp2.z = _q2.z * sin(fT * angle);
        tmp2.w = _q2.w * sin(fT * angle);
        glm::quat tmp3 = tmp1+tmp2;
        glm::quat res;
        res.x = tmp3.x/ sin(angle);
        res.y = tmp3.y/ sin(angle);
        res.z = tmp3.z/ sin(angle);
        res.w = tmp3.w/ sin(angle);
        res = normalize(res);
        return res;
}
