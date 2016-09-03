#pragma once
#include "utils/FileUtils.h"
#include <GL/glew.h>

class Buffer {
private:
	uint m_BufferID;
	uint m_ComponentCount;
public:
	Buffer(GLfloat* data, GLsizei count, uint componentCount);

	void bind() const;
	void unbind() const;

	inline uint getComponentCount() const { return m_ComponentCount; }
};