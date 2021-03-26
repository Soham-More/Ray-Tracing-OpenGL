#include "CubeMap.h"

OGL::CubeMap::CubeMap()
{
	;
}

void OGL::CubeMap::SourceFiles(std::vector<std::string>& FileNames)
{
	Call(glGenTextures(1, &TextureID));
	Call(glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID));

	for (int i = 0; i < FileNames.size(); i++)
	{
		sf::Image img;
		img.loadFromFile(FileNames[i]);

		Call(glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr()
		));
	}

	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	UnBind();
}

void OGL::CubeMap::Bind(unsigned int slot)
{
	Call(glActiveTexture(GL_TEXTURE0 + slot));
	Call(glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID));
}

void OGL::CubeMap::UnBind()
{
	Call(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}


OGL::CubeMap::~CubeMap()
{
}
