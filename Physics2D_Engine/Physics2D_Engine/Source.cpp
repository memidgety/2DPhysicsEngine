#include <iostream>
#include <GL/glew.h>
#include "display.h"

int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;

	Display display(800, 600, "HelloWorld");

	while (!display.getIsClosed()) {
		display.fill(1.0f, 1.0f, 1.0f,1);
		display.Update();
	}
	return 0;
}