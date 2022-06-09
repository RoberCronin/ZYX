#include "Texture.hpp"
#include "core/Debug.hpp"
#include "stb_image/stb_image.h"

#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

Texture::Texture(std::string filePath, unsigned int slot)
    : m_FilePath(filePath)
    , m_LocalBuffer(nullptr)
    , m_RendererID(0)
    , m_Width(0)
    , m_Height(0)
    , m_BPP(0)
    , m_Slot(slot)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // generate texture on GPU
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    // set texture parameters
    // repeat image in all directions
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    // when stretching image, pixalate
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    // when shrinking image, pixalate
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    // upload image to GPU
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

    // unbind texture
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    // free image memory
    if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
