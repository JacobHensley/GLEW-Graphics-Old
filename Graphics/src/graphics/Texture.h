#pragma once
#include "Common.h"
class Texture
{
public:

	Texture();
	Texture(const char* path);
	
	const char* path;

	inline int getWidth() { return width; }
	inline int getHeight() { return height; }
	inline int getBPC() { return bpc; }
private:
	int width, height, bpc;

	void load();
};