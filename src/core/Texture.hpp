#pragma once

#include <string>

class Texture
{
public:
    Texture(std::string filePath, unsigned int slot);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() { return m_Width; }
    inline int GetHegiht() { return m_Height; }

private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    unsigned int m_Slot;
};
