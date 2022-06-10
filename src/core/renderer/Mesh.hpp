#pragma once

#include "core/Texture.hpp"
#include "core/renderer/ElementBufferObject.hpp"
#include "core/renderer/VertexArrayObject.hpp"
#include "core/renderer/VertexBufferObject.hpp"

class Mesh
{
public:
    Mesh(DynamicVertexBufferObject* vbo, VertexArrayObject* vao, ElementBufferObject* ebo, Texture* texture);

    void Bind();
    void Unbind();

    unsigned int GetIndiciesCount();
    unsigned int GetTextureSlot();

private:
    DynamicVertexBufferObject* m_VboPointer;
    VertexArrayObject* m_VaoPointer;
    ElementBufferObject* m_EboPointer;
    Texture* m_Texture;
};
