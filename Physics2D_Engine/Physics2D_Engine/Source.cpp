#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"

int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;

	Display display(800, 600, "HelloWorld");

	Shader shader("./res/basicShader");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0)),
						  Vertex(glm::vec3(0,0.5,0)),
						  Vertex(glm::vec3(0.5,-0.5,0))};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	while (!display.getIsClosed()) {
		display.fill(.1f, .1f, .1f,1);

		shader.Bind();
		mesh.Draw();

		display.Update();
	}
	return 0;
}