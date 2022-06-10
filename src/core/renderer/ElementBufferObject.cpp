#include "ElementBufferObject.hpp"
#include "core/Debug.hpp"

#include <bits/iterator_concepts.h>

ElementBufferObject::ElementBufferObject(std::vector<unsigned int> indicies)
    : m_Count(indicies.size())
{
    GLCall(glGenBuffers(1, &m_EboID));
    Bind();
    // upload indicies
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_DYNAMIC_DRAW));
}

void ElementBufferObject::Bind()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID));
}

void ElementBufferObject::Unbind()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int ElementBufferObject::GetCount()
{
    return m_Count;
}
