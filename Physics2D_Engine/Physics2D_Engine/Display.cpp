#include "Display.h"
#include <GL/glew.h>
#include <iostream>

using namespace std;

Display::Display(int width, int hieght, const std::string& title) : width(width), hieght(hieght) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, hieght, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		cerr << "Glew fail to initialize" << endl;
	}
	isClosed = false;
}

void Display::fill(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

Display::~Display() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Update() {
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			isClosed = true;
	}

}