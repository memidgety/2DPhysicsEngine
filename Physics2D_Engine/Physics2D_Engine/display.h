//written with the help of thebennybox at youtube.com
#pragma once
#include<SDL2/SDL.h>
#include<string>

class Display { //OpenGL display class used to create new windows
public:
	Display(int width, int hieght, const std::string& title);

	void fill(float r, float g, float b, float a);
	void Update();
	bool getIsClosed() { return isClosed; };
	void setIsClosed(bool closed) { isClosed = closed; }

	virtual ~Display();

	int width, hieght;

private:
	Display(const Display& other) {}
	Display& operator=(const Display& other) {}

	SDL_Window* m_window;
	SDL_GLContext glContext;
	bool isClosed;
};
