#pragma once
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <Glm/glm.hpp>
#include <Glm/gtc/type_ptr.hpp>

class Shader
{
public:

	// State
	GLuint id;
	// Constructor
	Shader();
	// Sets the current shader as active
	Shader  &Use();
	// Compiles the shader from given source code
	void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); // Note: geometry source code is optional 
	// Utility functions
	void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void    SetVector2F(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2F(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void    SetVector3F(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3F(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void    SetVector4F(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4F(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
	// Checks if compilation or linking failed and if so, print the error logs
	static void    CheckCompileErrors(GLuint object, const std::string& type);
};
