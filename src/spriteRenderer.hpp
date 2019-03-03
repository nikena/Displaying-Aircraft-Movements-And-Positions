#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include "camera.hpp"
#include "directoryHandler.hpp"
#include <vector>
/*
A renderer to draw textures, either as 2D images or as textures for objects
*/
GLuint shaderProgramTex;
GLuint shaderProgramTexWithCamera;
GLuint shaderProgramTexEarth;
class Sprite
{
	public:
	int texWidth, texHeight, numColorChannels;
	GLuint elementBufferObjectTex;
	GLuint vertexBufferObjectTex;
	GLuint vertexArrayObjectTex;
	GLuint currentShader;
	
	int isLoaded=0;
	private:
	int numIndices=-1;
	unsigned char* texData;
	unsigned int texture;
	int dirtyVertexAttrib=1;
	
	protected:
	
	int& getNumIndices()
	{
		return numIndices;
	}
	
	public:
	Sprite(){};
	Sprite(const char* imageName,int shader)
	{
		load(imageName,shader);
	};
	
	//Binds the vertex array object of this sprite.
	void bindVAO()
	{
		glBindVertexArray(vertexArrayObjectTex);
	};
	
	//Updates the vertex attributes of this sprite.
	void updateVertexAttributes()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		dirtyVertexAttrib=0;
	}
	
	//Sets the vertices of this sprite.
	//	vertices - the pointer to the array of vertices
	//	sizeOfVertices - how large the array is, in bytes.
	void setVertices(float *vertices, int sizeOfVertices)
	{
  		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectTex);
   		glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);
		dirtyVertexAttrib=1;
	};
	//Sets the indices of this sprite.
	//	indices - the pointer to the array of indices
	//	sizeOfIndices - how large the array is, in bytes.
	void setIndices(unsigned int *indices, int sizeOfIndices)
	{
  		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectTex);
   		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
		dirtyVertexAttrib=1;

		numIndices=(sizeOfIndices/sizeof(unsigned int));
	};
	//Sets the vertices and indices of this sprite.
	//	vertices - the pointer to the array of vertices
	//	sizeOfVertices - how large the vertex array is, in bytes.
	//	indices - the pointer to the array of indices
	//	sizeOfIndices - how large the index array is, in bytes.
	void setVerticesAndIndices(float *vertices, int sizeOfVertices, unsigned int *indices, int sizeOfIndices)
	{
		bindVAO();
		setVertices(vertices,sizeOfVertices);
		setIndices(indices,sizeOfIndices);
		updateVertexAttributes();
	};
	//Specifically for 2D images, such as in UI
	void setTo2DDimensions(float x, float y, float w, float h);
	
	//Loads a sprite with default 2D indices and vertices, and returns whether it loaded properly
	//		imageName - the image file name (ie "assets/debugTex.png")
	//		debugPrint - whether to print it's current progress
	bool load(const char* imageName, bool debugPrint=false)
	{
		return load(imageName,shaderProgramTex,debugPrint);
	}
	//Loads a sprite with default 2D indices and vertices, and returns whether it loaded properly
	//		imageName - the image file name (ie "assets/debugTex.png")
	//		shader - which shader to use for the image
	//		debugPrint - whether to print it's current progress
	bool load(const char* imageName,int shader, bool debugPrint=false)
	{
		if(loadNoInitShape(imageName,shader,debugPrint))
		{
			setTo2DDimensions(-0.5f,-0.5f, 1.0f,1.0f);
			return true;
		}else
		{
			return false;
		}
	}
	//Loads a sprite without vertices or indices, and returns whether it loaded properly
	//		imageName - the image file name (ie "assets/debugTex.png")
	//		shader - which shader to use for the image
	//		debugPrint - whether to print it's current progress
	bool loadNoInitShape(const char* imageName,int shader, bool debugPrint=false);
	
	void drawSprite();
	
};

void initializeSpriteRenderer();

//Updates the shaders with the camera positioning and orientation
//	camera - reference to a camera
void spriteRendererUpdateCamera(Camera& camera);
#endif
