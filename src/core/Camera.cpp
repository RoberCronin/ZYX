#include "core/include.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>

Camera::Camera(glm::vec2 position, unsigned int screenSpaceWidth, unsigned int screenSpacHeight)
    : m_Position(position)
    , m_ProjectionMatrix(glm::mat4())
    , m_ViewMatrix(glm::mat4())
    , m_ScreenSpaceWidth(screenSpaceWidth)
    , m_ScreenSpacHeight(screenSpacHeight)
{
    adjustProjection();
}

void Camera::adjustProjection()
{
    m_ProjectionMatrix = glm::mat4(1.0f);
    m_ProjectionMatrix *= glm::ortho(0.0f, (float)m_ScreenSpaceWidth, (float)m_ScreenSpacHeight, 0.0f, 0.0f, 100.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
    m_ViewMatrix = glm::mat4(1.0f);

    m_ViewMatrix *= glm::lookAt(glm::vec3(m_Position.x, m_Position.y, 20.0f), cameraFront + glm::vec3(m_Position.x, m_Position.y, 0.0f), cameraUp);

    return m_ViewMatrix;
}

void Camera::SetScreenWidth(const int& width)
{
    m_ScreenSpaceWidth = width;
}

void Camera::SetScreenHeight(const int& height)
{
    m_ScreenSpacHeight = height;
}

void Camera::MoveX(const float& moveDelta)
{
    m_Position.x += moveDelta;
}

void Camera::MoveY(const float& moveDelta)
{
    m_Position.y += moveDelta;
}
