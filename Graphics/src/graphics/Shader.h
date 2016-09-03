#pragma once
#include "Common.h"

class Shader {
private:
	uint m_ShaderID;
	String m_VertPath, m_FragPath;
public:
	Shader(const String& vertPath, const String& fragPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	inline uint GetID() const { return m_ShaderID; }
private:
	uint Load();
};