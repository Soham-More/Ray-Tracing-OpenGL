#include "SSBO.h"

OGL::SSBO::SSBO() : ssboID(0)
{
	Call(glGenBuffers(1, &ssboID));
	Call(glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboID));
	Call(glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_STATIC_COPY));
	Call(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
}

void OGL::SSBO::Bind()
{
	Call(glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboID));
}

void OGL::SSBO::UnBind()
{
	Call(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
}

void OGL::SSBO::SetBase(unsigned int Base)
{
	Bind();
	Call(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Base, ssboID));
}

OGL::SSBO::~SSBO()
{
	;
}
