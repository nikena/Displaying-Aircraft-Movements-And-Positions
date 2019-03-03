#include "testUtils.hpp"
#include "../spriteRenderer.hpp"


bool test_SpriteRenderer_updateVertexAttributes()
{
	PRINT_TEST_START;
	glGetError();//Clears any glError from any prior test.
	Sprite spriteDebugTest;
	if(!spriteDebugTest.loadNoInitShape("assets/debugTex.png",shaderProgramTex,false))
	{
		std::cout<<"[1/2]";
		return false;
	}
	spriteDebugTest.updateVertexAttributes();
	if(glGetError()!=GL_NO_ERROR)
	{
		std::cout<<"[2/2]";
		return false;
	}
	return true;
}
bool test_SpriteRenderer_setVertices()
{
	PRINT_TEST_START;
	glGetError();//Clears any glError from any prior test.
	Sprite spriteDebugTest;
	if(!spriteDebugTest.loadNoInitShape("assets/debugTex.png",shaderProgramTex,false))
	{
		std::cout<<"[1/2]";
		return false;
	}
	float x=-0.5f;
	float y=-0.5f;
	float w= 1.0f;
	float h=1.0f;
	float vertices[] = //3 position coords, 2 UV texture coords
		{x+w,y+h,0.0f, 1.0f,1.0f,
		x+w,y,0.0f, 1.0f,0.0f,
		x,y,0.0f, 0.0f,0.0f,
		x,y+h,0.0f, 0.0f,1.0f};
	spriteDebugTest.bindVAO();
	spriteDebugTest.setVertices(vertices,sizeof(vertices));
	spriteDebugTest.updateVertexAttributes();
	
	if(glGetError()!=GL_NO_ERROR)
	{
		std::cout<<"[2/2]";
		return false;
	}
	return true;
}
bool test_SpriteRenderer_setIndices()
{
	PRINT_TEST_START;
	glGetError();//Clears any glError from any prior test.
	Sprite spriteDebugTest;
	if(!spriteDebugTest.loadNoInitShape("assets/debugTex.png",shaderProgramTex,false))
	{
		std::cout<<"[1/2]";
		return false;
	}
	unsigned int indices[] = {0,1,3,//first triangle
							  1,2,3};//second triangle
	spriteDebugTest.bindVAO();
	spriteDebugTest.setIndices(indices,sizeof(indices));
	spriteDebugTest.updateVertexAttributes();
	
	if(glGetError()!=GL_NO_ERROR)
	{
		std::cout<<"[2/2]";
		return false;
	}
	return true;
}
bool test_SpriteRenderer_setTo2DDimensions()
{
	PRINT_TEST_START;
	glGetError();//Clears any glError from any prior test.
	Sprite spriteDebugTest;
	if(!spriteDebugTest.loadNoInitShape("assets/debugTex.png",shaderProgramTex,false))
	{
		std::cout<<"[1/2]";
		return false;
	}
	spriteDebugTest.setTo2DDimensions(-0.5f,-0.5f, 1.0f,1.0f);
	if(glGetError()!=GL_NO_ERROR)
	{
		std::cout<<"[2/2]";
		return false;
	}
	return true;
}
bool test_SpriteRenderer_load()
{
	PRINT_TEST_START;
	Sprite spriteDebugNull;
	Sprite spriteDebugTest;
	if(spriteDebugNull.load("",shaderProgramTex,false))
	{
		std::cout<<"[1/2]";
		return false;
	}
	if(!spriteDebugTest.load("assets/debugTex.png",shaderProgramTex,false))
	{
		std::cout<<"[2/2]";
		return false;
	}
	return true;
}
bool test_SpriteRenderer_loadNoInitShape()
{
	PRINT_TEST_START;
	Sprite spriteDebugNull;
	Sprite spriteDebugTest;
	if(spriteDebugNull.loadNoInitShape("",shaderProgramTex,false))
	{
		std::cout<<"[1/2]";
		return false;
	}
	if(!spriteDebugTest.loadNoInitShape("assets/debugTex.png",shaderProgramTex,false))
	{
		std::cout<<"[2/2]";
		return false;
	}
	return true;
}
bool test_SpriteRenderer_drawSprite()
{
	glGetError();//Clears any glError from any prior test.
	PRINT_REQ_MANUAL_CHECK_NO_RETURN;
	if(glGetError()!=GL_NO_ERROR)
	{
		return false;
	}
	return true;
}
bool test_SpriteRenderer_bindVAO()
{
	PRINT_REQ_MANUAL_CHECK;
	glGetError();//Clears any glError from any prior test.
	Sprite spriteDebugTest;
	if(!spriteDebugTest.loadNoInitShape("assets/debugTex.png",shaderProgramTex,false))
	{
		std::cout<<"[1/2]";
		return false;
	}
	spriteDebugTest.bindVAO();
	if(glGetError()!=GL_NO_ERROR)
	{
		std::cout<<"[2/2]";
		return false;
	}
	return true;
}
bool test_SpriteRenderer_updateCamera()
{
	PRINT_REQ_MANUAL_CHECK_NO_RETURN;
	glGetError();//Clears any glError from any prior test.
	spriteRendererUpdateCamera(camera);
	if(glGetError()!=GL_NO_ERROR)
	{
		return false;
	}
	return true;
}
void test_SpriteRenderer()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_SpriteRenderer_updateVertexAttributes());
	printIfOK(test_SpriteRenderer_setVertices());
	printIfOK(test_SpriteRenderer_setIndices());
	printIfOK(test_SpriteRenderer_setTo2DDimensions());
	printIfOK(test_SpriteRenderer_load());
	printIfOK(test_SpriteRenderer_loadNoInitShape());
	printIfOK(test_SpriteRenderer_drawSprite());
	printIfOK(test_SpriteRenderer_bindVAO());
	printIfOK(test_SpriteRenderer_updateCamera());
}
