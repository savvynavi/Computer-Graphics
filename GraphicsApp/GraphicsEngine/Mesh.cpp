#include "Mesh.h"



Mesh::Mesh() : triCount(0), vao(0), vbo(0), ibo(0){

}


Mesh::~Mesh(){
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialise(unsigned int vertexCount, const Vertex * vertices, unsigned int indexCount, unsigned int* indices){
	assert(vao == 0);
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//bind indices if any
	if (indexCount != 0) {
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		triCount = indexCount / 3;

	}else {
		triCount = vertexCount / 3;
	}

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::initialiseQuad(){
	//checks that the mesh hasn't been initialised already
	assert(vao == 0);
	//generate teh buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex arr (mesh wrapper)/buffer
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//creating the quad vertices + fill the vertex buffer
	Vertex vertices[6];
	vertices[0].pos = {-0.5f, 0, 0.5f, 1};
	vertices[1].pos = {0.5f, 0, 0.5f, 1};
	vertices[2].pos = {-0.5f, 0, -0.5f, 1};
	
	vertices[3].pos = {-0.5f, 0, -0.5f, 1};
	vertices[4].pos = {0.5f, 0, 0.5f, 1};
	vertices[5].pos = {0.5f, 0, -0.5f, 1};

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//enable first element as the pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//unbind the buffers/set tricount
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	triCount = 2;
}

//finish after obj loading works
void Mesh::initialiseBox(){
	////checks that the mesh hasn't been initialised already
	//assert(vao == 0);
	////generate teh buffers
	//glGenBuffers(1, &vbo);
	//glGenVertexArrays(1, &vao);

	////bind vertex arr (mesh wrapper)/buffer
	//glBindVertexArray(vao);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	////creating box vertices + fill buffer
}

void Mesh::draw(){
	glBindVertexArray(vao);
	if (ibo != 0) {
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}else {
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}
