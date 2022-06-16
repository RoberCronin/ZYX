#include "entity.hpp"

#include "core/include.hpp"
#include <memory>

entity::entity(std::string texturePath, unsigned int width, unsigned int height, float posX, float posY)
    : m_Width(width)
    , m_Height(height)
    , m_PosX(posX)
    , m_PosY(posY)
{
    // default vertex locations, has to be multiplied by width and height to get final locations
    m_Verticies = {
        // position       // UV coordinates
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
    };

    m_Verticies[5] *= (float)m_Width;
    m_Verticies[10] *= (float)m_Width;

    m_Verticies[11] *= (float)m_Height;
    m_Verticies[16] *= (float)m_Height;

    // counter-clockwise order
    m_ElementArray = {
        0, 1, 2, // top right tri
        0, 2, 3, // bottom left tri
    };

    // load texture
    m_Texture = std::make_shared<Texture>(texturePath, 0);
    m_Texture->Bind();

    // create vao
    m_Vao = std::make_shared<VertexArrayObject>();
    m_Vao->Bind();

    // create vbo buffer
    m_Vbo = std::make_shared<DynamicVertexBufferObject>(20);

    // create the ebo buffer
    m_Ebo = std::make_shared<ElementBufferObject>(m_ElementArray);

    // add vertex attributes
    m_Vao->AddVertexAttribute(3, GL_FLOAT); // position
    // vao.AddVertexAttribute(4, GL_FLOAT); // color
    m_Vao->AddVertexAttribute(2, GL_FLOAT); // uv coordinates
    m_Vao->SetVertexAttributes();

    // SmartMesh meshMain(m_Vbo, m_Vao, m_Ebo, m_Texture);

    m_Mesh = std::make_unique<SmartMesh>(m_Vbo, m_Vao, m_Ebo, m_Texture);
}

void entity::Move(float xPos, float yPos)
{
    m_PosX = xPos;
    m_PosY = yPos;
    UpdateVerts();
}

void entity::UploadVerts()
{
    m_Vbo->UploadVerticies(m_Verticies);
}

void entity::Bind()
{
    m_Mesh->Bind();
}

void entity::Unbind()
{
    m_Mesh->Unbind();
}

void entity::UpdateVerts()
{
    m_Verticies[0] = m_PosX;
    m_Verticies[5] = m_PosX + m_Width;
    m_Verticies[10] = m_PosX + m_Width;
    m_Verticies[15] = m_PosX;

    m_Verticies[1] = m_PosY + m_Height;
    m_Verticies[6] = m_PosY + m_Height;
    m_Verticies[11] = m_PosY;
    m_Verticies[16] = m_PosY;
}

unsigned int entity::GetIndiciesCount()
{
    return m_Mesh->GetIndiciesCount();
}

unsigned int entity::GetTextureSlot()
{
    return m_Mesh->GetTextureSlot();
}

float entity::GetWidth() const
{
    return m_Width;
}

float entity::GetHeight() const
{
    return m_Height;
}

float entity::GetPosX() const
{
    return m_PosX;
}

float entity::GetPosY() const
{
    return m_PosY;
}
