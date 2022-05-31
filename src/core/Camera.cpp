#include "Camera.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>

Camera::Camera(glm::vec2 position)
    : m_Position(position)
    , m_ProjectionMatrix(glm::mat4())
    , m_ViewMatrix(glm::mat4())
{
    adjustProjection();
}

void Camera::adjustProjection()
{
    m_ProjectionMatrix = glm::mat4(1.0f);
    m_ProjectionMatrix *= glm::ortho(0.0f, 32.0f * 40.0f, 0.0f, 32.0f * 21.0f, 0.0f, 100.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
    m_ViewMatrix = glm::mat4(1.0f);

    m_ViewMatrix *= glm::lookAt(glm::vec3(m_Position.x, m_Position.y, 20.0f), cameraFront + glm::vec3(m_Position.x, m_Position.y, 0.0f), cameraUp);

    return m_ViewMatrix;
}
