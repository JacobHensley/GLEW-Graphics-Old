#pragma once
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "Common.h"
static String ReadFile(const String& path) {
	FILE* file = fopen(path.c_str(), "rb");
	if (!file) {
		std::cout << "Fail to read File" << std::endl;
		return String();
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);

	String result(size, 0);
	fseek(file, 0, SEEK_SET);
	fread(&result[0], 1, size, file);
	fclose(file);

	result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
	return result;
}