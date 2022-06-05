#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
    Camera(glm::vec2 position, unsigned int screenSpaceWidth, unsigned int screenSpacHeight);

    void adjustProjection();
    glm::mat4 getViewMatrix();
    inline glm::mat4 getProjectionMatrix() { return m_ProjectionMatrix; }

    void SetScreenWidth(const int& width);
    void SetScreenHeight(const int& height);

    void MoveX(const float& moveDelta);
    void MoveY(const float& moveDelta);

private:
    glm::vec2 m_Position;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;

    unsigned int m_ScreenSpaceWidth, m_ScreenSpacHeight;
};
