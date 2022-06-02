#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
    Camera(glm::vec2 position);

    void adjustProjection();
    glm::mat4 getViewMatrix();
    inline glm::mat4 getProjectionMatrix() { return m_ProjectionMatrix; }

    void MoveX(const float& moveDelta);
    void MoveY(const float& moveDelta);

private:
    glm::vec2 m_Position;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
};
