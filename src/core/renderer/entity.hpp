#pragma once

#include "core/renderer/ElementBufferObject.hpp"
#include "core/renderer/Mesh.hpp"
#include "core/renderer/VertexArrayObject.hpp"
#include "core/renderer/VertexBufferObject.hpp"

#include <memory>
#include <string>
#include <vector>

class entity
{
public:
    entity(std::string texturePath, unsigned int width, unsigned int height, float posX, float posY);

    void Move(float xPos, float yPos);
    void UpdateVerts();
    void UploadVerts();

    unsigned int GetIndiciesCount();
    unsigned int GetTextureSlot();

    float GetWidth() const;
    float GetHeight() const;

    float GetPosX() const;
    float GetPosY() const;

    void Bind();
    void Unbind();

private:
    std::vector<float> m_Verticies;
    std::vector<unsigned int> m_ElementArray;

    float m_Width, m_Height;
    float m_PosX, m_PosY;

    std::shared_ptr<DynamicVertexBufferObject> m_Vbo;
    std::shared_ptr<VertexArrayObject> m_Vao;
    std::shared_ptr<ElementBufferObject> m_Ebo;
    std::shared_ptr<Texture> m_Texture;

    std::unique_ptr<SmartMesh> m_Mesh;
};
