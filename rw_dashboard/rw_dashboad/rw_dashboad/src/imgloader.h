#pragma once
#include "glad/glad.h"

class imgloader
{
	public:
		static bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
};