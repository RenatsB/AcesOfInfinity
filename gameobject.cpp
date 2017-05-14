#include <GameObject.h>
#include <cmath>
#include <glm/gtx/norm.hpp>

void GameObject::moveObject(float &_objSpeed)
{
    anglesToAxes(); //recalculate direction vectors
    position += forward*_objSpeed;
}

void GameObject::anglesToAxes()
{
    float sx, sy, sz, cx, cy, cz, theta;

    // rotation angle about X-axis (pitch)
    theta = glm::radians(rotation.x);
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = glm::radians(rotation.y);
    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = glm::radians(rotation.z);
    sz = sinf(theta);
    cz = cosf(theta);

    // determine left axis
    left.x = cy*cz;
    left.y = sx*sy*cz + cx*sz;
    left.z = -cx*sy*cz + sx*sz;

    // determine up axis
    up.x = -cy*sz;
    up.y = -sx*sy*sz + cx*cz;
    up.z = cx*sy*sz + sx*cz;

    // determine forward axis
    forward.x = sy;
    forward.y = -sx*cy;
    forward.z = cx*cy;
}

glm::quat GameObject::anglesToQuat(glm::vec3 &_eulers)
{
    float sx, sy, sz, cx, cy, cz;
    sx = sin(_eulers.x/2); sy = sin(_eulers.y/2); sz = sin(_eulers.z/2);
    cx = cos(_eulers.x/2); cy = cos(_eulers.y/2); cz = cos(_eulers.z/2);

    return glm::quat( cx*cy*cz + sx*sy*sz,
       sx*cy*cz - cx*sy*sz,
       cx*sy*cz + sx*cy*sz,
       cx*cy*sz - sx*sy*cz ); // for XYZ application order
}

glm::quat GameObject::RotationBetweenVectors(glm::vec3 &start, glm::vec3 &dest)
{
        start = glm::normalize(start);
        dest = glm::normalize(dest);

        float cosTheta = dot(start, dest);
        glm::vec3 rotationAxis;

        if (cosTheta < -1 + 0.001f){
                // special case when vectors in opposite directions:
                // there is no "ideal" rotation axis
                // So guess one; any will do as long as it's perpendicular to start
                rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
                if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
                        rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

                rotationAxis = glm::normalize(rotationAxis);
                return glm::angleAxis(180.0f, rotationAxis);
        }

        rotationAxis = glm::cross(start, dest);

        float s = sqrt( (1+cosTheta)*2 );
        float invs = 1 / s;

        return glm::quat(
                s * 0.5f,
                rotationAxis.x * invs,
                rotationAxis.y * invs,
                rotationAxis.z * invs
        );
}

glm::quat GameObject::RotateTowards(glm::quat q1, glm::quat q2, float maxAngle){

        if( maxAngle < 0.001f ){
                // No rotation allowed. Prevent dividing by 0 later.
                return q1;
        }

        float cosTheta = glm::dot(q1, q2);

        // q1 and q2 are already equal.
        // Force q2 just to be sure
        if(cosTheta > 0.9999f){
                return q2;
        }

        // Avoid taking the long path around the sphere
        if (cosTheta < 0){
            q1 = q1*-1.0f;
            cosTheta *= -1.0f;
        }

        float angle = acos(cosTheta);

        // If there is only a 2&deg; difference, and we are allowed 5&deg;,
        // then we arrived.
        if (angle < maxAngle){
                return q2;
        }

        float fT = maxAngle / angle;
        angle = maxAngle;

        glm::quat tmp1;
        tmp1.x = q1.x * sin((1.0f - fT) * angle);
        tmp1.y = q1.y * sin((1.0f - fT) * angle);
        tmp1.z = q1.z * sin((1.0f - fT) * angle);
        tmp1.w = q1.w * sin((1.0f - fT) * angle);
        glm::quat tmp2;
        tmp2.x = q2.x * sin(fT * angle);
        tmp2.y = q2.y * sin(fT * angle);
        tmp2.z = q2.z * sin(fT * angle);
        tmp2.w = q2.w * sin(fT * angle);
        glm::quat tmp3 = tmp1+tmp2;
        glm::quat res;
        res.x = tmp3.x/ sin(angle);
        res.y = tmp3.y/ sin(angle);
        res.z = tmp3.z/ sin(angle);
        res.w = tmp3.w/ sin(angle);
        res = normalize(res);
        return res;
}
