#pragma once

#include "utils/FileUtils.h"
#include <GL/glew.h>
#include <vector>
#include "Buffer.h"

class VertexArray {
private:
	uint m_ArrayID;
	std::vector<Buffer*> m_Buffers;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(Buffer* buffer, uint index);

	void bind() const;
	void unbind() const;
};