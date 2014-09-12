#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>


Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0){
		glDeleteBuffers(1, &_vboID);
	}
}


void Sprite::init(float x, float y, float width, float height){

	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0){
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	// First Triangle in quad
	
	vertexData[0].setPositon(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPositon(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPositon(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	
	// Second Triangle in quad
	vertexData[3].setPositon(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPositon(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPositon(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[4].setColor(0, 0, 255, 255);
		
	vertexData[4].setColor(0, 255, 0, 255);

	


	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void Sprite::draw(){

	//bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);


	// Tell opengl that we want to use the first attribute array.
	// We only need one array right now since we are only using position
	glEnableVertexAttribArray(0);

	//This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	
	//This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	
	// This is the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	//Draw the 6 vertices to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable the vertex attrib array. This is not optional.
	glDisableVertexAttribArray(0);

	//Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}