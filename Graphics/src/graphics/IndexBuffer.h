#pragma once

#include "utils/FileUtils.h"
#include <GL/glew.h>

class IndexBuffer {
private:
	uint m_Count;
	uint m_BufferID;
public:
	IndexBuffer(uint* data, GLsizei count);

	void draw() const;

	void bind() const;
	void unbind() const;

	inline uint getCount() const { return m_Count; }
};
