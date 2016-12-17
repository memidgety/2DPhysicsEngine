//written with the help of thebennybox at youtube.com
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class Shader{ //OpenGl shader class to color objects
public:
	Shader(const std::string& fileName);

	void Bind();

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];

};