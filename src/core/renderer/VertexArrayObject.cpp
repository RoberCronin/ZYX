#include "core/renderer/VertexArrayObject.hpp"
#include "core/include.hpp"
#include <stdexcept>

VertexArrayObject::VertexArrayObject()
    : m_VaoID(0)
{
    GLCall(glGenVertexArrays(1, &m_VaoID));
}

void VertexArrayObject::AddVertexAttribute(const int& count, const int& type)
{
    ValidateVertexAttributeType(type);
    ValidateVertexAttributeCount(count);

    m_VertexAttributes.push_back({
        (unsigned int)m_VertexAttributes.size(), // index
        count,                                   // componentCount
        type,                                    // type
        CalculateOffset()                        // pointer
    });
}

void VertexArrayObject::SetVertexAttributes()
{
    int stride = CalculateStride();

    for (const auto& item : m_VertexAttributes)
    {
        GLCall(glVertexAttribPointer(item.index, item.componentCount, item.type, GL_FALSE, stride, (const void*)item.pointer));
        GLCall(glEnableVertexAttribArray(item.index));
    }
}

void VertexArrayObject::Bind()
{
    GLCall(glBindVertexArray(m_VaoID));
}

void VertexArrayObject::Unbind()
{
    GLCall(glBindVertexArray(0));
}

int VertexArrayObject::CalculateStride()
{
    int stride = 0;

    for (const auto& item : m_VertexAttributes)
    {
        stride += item.componentCount * SizeOfGLType(item.type);
    }

    return stride;
}

int VertexArrayObject::CalculateOffset()
{
    int offset = 0;

    for (const auto& item : m_VertexAttributes)
    {
        offset += item.componentCount * SizeOfGLType(item.type);
    }

    return offset;
}

void VertexArrayObject::ValidateVertexAttributeType(const int& type)
{
    switch (type)
    {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_FLOAT:
    case GL_DOUBLE:
        break;
    case GL_HALF_FLOAT:
    case GL_INT_2_10_10_10_REV:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
        throw std::invalid_argument("Unsupported type when creating vertex attribute");
        break;
    default:
        throw std::range_error("Need to specify correct GL type when creating vertex attributes");
        break;
    }
}

void VertexArrayObject::ValidateVertexAttributeCount(const int& count)
{
    switch (count)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    default:
        throw std::range_error("Vertex attribute count needs to be a number between 1 and 4");
        break;
    }
}

int VertexArrayObject::SizeOfGLType(const int& type)
{
    switch (type)
    {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
        return sizeof(char);
        break;
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
        return sizeof(short);
        break;
    case GL_INT:
    case GL_UNSIGNED_INT:
        return sizeof(int);
        break;
    case GL_FLOAT:
        return sizeof(float);
        break;
    case GL_DOUBLE:
        return sizeof(double);
        break;
    case GL_HALF_FLOAT:
    case GL_INT_2_10_10_10_REV:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
        throw std::invalid_argument("Unsupported type when creating vertex attribute");
        break;
    default:
        throw std::range_error("Need to specify correct GL type when creating vertex attributes");
        break;
    }
    return 0;
}
