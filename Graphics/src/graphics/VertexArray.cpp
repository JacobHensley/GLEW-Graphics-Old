#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_Buffers.size(); i++)
		delete m_Buffers[i];
}

void VertexArray::addBuffer(Buffer* buffer, uint index)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, false, buffer->getComponentCount() * sizeof(float), 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (const void*)(3 * sizeof(float)));
	
	buffer->unbind();
	unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_ArrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
