#pragma once
#include <glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<gl_core_4_4.h>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();
	struct Vertex {
		glm::vec4 pos;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = 0);
	void initialiseQuad();
	void initialiseBox();
	virtual void draw();
protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

