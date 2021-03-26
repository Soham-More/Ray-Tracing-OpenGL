#include "Shader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

struct ShaderProgSrc
{
    std::string VertexSource;
    std::string FragmentSource;
	std::string GeometrySource;
};

std::string ParseShaderIncludes(const std::string& root_path, const std::string& filename, std::vector<std::string> IncludeList = {})
{
	std::string File = root_path + filename;
	std::fstream s(File.c_str(), std::ios::in);

	std::cout << "Processing Files: " << File << "\n";

	if (s.fail())
	{
		std::cerr << "\nFailed to open File: " << File << "\n";
	}

	int type = 0;
	bool IncludeFile = false;

	std::string FileName;

	std::string line;
	std::stringstream ss;

	while (getline(s, line))
	{
		if (line.find("#include") != std::string::npos)
		{
			FileName = "";

			for (char& c : line)
			{
				if (c == '\"')
				{
					IncludeFile = true;
					type = 1 - type;
				}

				if (type)
				{
					if (c == '\"') continue;
					FileName += c;
				}
			}

		}
		else
		{
			ss << line << "\n";
		}

		if (IncludeFile)
		{
			if (!IncludeList.empty())
			{
				if (std::find(IncludeList.begin(), IncludeList.end(), FileName) == IncludeList.end())
				{
					IncludeList.push_back(FileName);

					std::string Header_File = ParseShaderIncludes(root_path, FileName, IncludeList);

					ss << Header_File;
				}
			}
			else
			{
				IncludeList.push_back(FileName);

				std::string Header_File = ParseShaderIncludes(root_path, FileName, IncludeList);

				ss << Header_File;
			}

			IncludeFile = false;
		}
	}
	return ss.str();
}

static ShaderProgSrc ParseShader(const std::string& filename)
{
    std::fstream s(filename.c_str(), std::ios::in);

    int type = -1;

    std::string line;
    std::stringstream ss[3];

    while(getline(s,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = 0;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = 1;
            }
			else if(line.find("geometry") != std::string::npos)
			{
				type = 2;
			}

        }
        else
        {
            ss[type] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str(), ss[2].str()};
}


//Global Functions
OGL::Shader::Shader(const std::string& Shader_Root_Folder, const std::string& Main_Shader, Shader_Type st) : fp(""), rid(0), ShaderID(ShaderCount++)
{
	unsigned int prog = 0;
	std::string file = Shader_Root_Folder + Main_Shader;

	if (st == DEFAULT)
	{
		ShaderProgSrc src = ParseShader(file);

		if (src.GeometrySource != "")
		{
			shader.loadFromMemory(src.VertexSource, src.GeometrySource, src.FragmentSource);
		}
		else
		{
			shader.loadFromMemory(src.VertexSource, src.FragmentSource);
		}

		prog = rid = shader.getNativeHandle();

	}
	else
	{
		std::string Compute_Shader = ParseShaderIncludes(Shader_Root_Folder, Main_Shader);

		std::fstream outfile("ParsedFile.pf", std::ios::out | std::ios::trunc);
		outfile << Compute_Shader << "\n";
		outfile.flush();
		outfile.close();

		std::string line;

		GLuint id = glCreateShader(GL_COMPUTE_SHADER);
		const char* src = Compute_Shader.c_str();
		Call(glShaderSource(id, 1, &src, nullptr));
		Call(glCompileShader(id));

		// Check Compile Errors
		int result;
		Call(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int len;
			Call(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
			char* msg = new char[len];
			Call(glGetShaderInfoLog(id, len, &len, msg));
			std::cout << "ERROR in: Compute Shader Due To :-\n" << msg << std::endl;
			Call(glDeleteShader(id));
		}

		// Create Prog and link shader
		prog = rid = glCreateProgram();
		Call(glAttachShader(prog, id));
		Call(glLinkProgram(prog));
	}

	int result;
	glGetProgramiv(prog, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int len;
		Call(glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len));
		char* msg = new char[len];
		Call(glGetProgramInfoLog(prog, len, &len, msg));
		std::cout << "ERROR in Linking Shader Due To :-\n" << msg << std::endl;
		Call(glDeleteProgram(prog));

		assert(true);
	}

	Call(glValidateProgram(prog));
}

OGL::Shader::~Shader()
{
    //dtor
}

void OGL::Shader::Bind()
{
	if (currentShader == ShaderID) return;

	currentShader = ShaderID;
    Call(glUseProgram(rid));
}

void OGL::Shader::Bind_Compute(int x, int y, int z)
{
	Call(glUseProgram(rid));
	Call(glDispatchCompute( (GLuint)x, (GLuint)y, (GLuint)z ));

	// make sure writing to image has finished before read
	//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void OGL::Shader::Unbind()
{
    Call(glUseProgram(0));
}

void OGL::Shader::SetUniform(const std::string& name, float r, float g, float b, float al)
{
	Bind();
    glUniform4f(GetUniformLocation(name), r, g, b, al);
}

unsigned int OGL::Shader::GetUniformLocation(const std::string& name)
{
    int loc = 0;
    loc = glGetUniformLocation(rid, name.c_str());
    return loc;
}

void OGL::Shader::SetUniform1i(const std::string& name, float f1)
{
	Bind();
    glUniform1i(GetUniformLocation(name), f1);
}

void OGL::Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
	Bind();
    glUniformMatrix4fv( GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void OGL::Shader::SetBarrier(Barrier_Type BarrierType)
{
	glMemoryBarrier(BarrierType);
}
