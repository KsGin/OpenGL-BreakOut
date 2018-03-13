#include "Shader.h"
#include <iostream>


Shader::Shader(): id(0) {
}

Shader &Shader::Use()
{
    glUseProgram(this->id);
    return *this;
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
    GLuint gShader = 0;
    // Vertex Shader
	const auto sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, nullptr);
    glCompileShader(sVertex);
    CheckCompileErrors(sVertex, "VERTEX");
    // Fragment Shader
	const auto sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, nullptr);
    glCompileShader(sFragment);
    CheckCompileErrors(sFragment, "FRAGMENT");
    // If geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, nullptr);
        glCompileShader(gShader);
        CheckCompileErrors(gShader, "GEOMETRY");
    }
    // Shader Program
    this->id = glCreateProgram();
    glAttachShader(this->id, sVertex);
    glAttachShader(this->id, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->id, gShader);
    glLinkProgram(this->id);
    CheckCompileErrors(this->id, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::SetFloat(const GLchar *name, const GLfloat value, const GLboolean useShader){
    if (useShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->id, name), value);
}
void Shader::SetInteger(const GLchar *name, const GLint value, const GLboolean useShader){
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->id, name), value);
}
void Shader::SetVector2F(const GLchar *name, const GLfloat x, const GLfloat y, const GLboolean useShader){
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->id, name), x, y);
}
void Shader::SetVector2F(const GLchar *name, const glm::vec2 &value, const GLboolean useShader) {
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}
void Shader::SetVector3F(const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z, const GLboolean useShader)  {
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}
void Shader::SetVector3F(const GLchar *name, const glm::vec3 &value, const GLboolean useShader){
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void Shader::SetVector4F(const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w, const GLboolean useShader){
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}
void Shader::SetVector4F(const GLchar *name, const glm::vec4 &value, const GLboolean useShader){
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, const GLboolean useShader){
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::CheckCompileErrors(const GLuint object, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}