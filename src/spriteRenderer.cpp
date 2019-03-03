#include "spriteRenderer.hpp"
/*
A renderer to draw textures, either as 2D images or as textures for objects
*/

void Sprite::setTo2DDimensions(float x, float y, float w, float h)
{
	//In UV, (0.0,0.0) is bottom left, (1.0,1.0) is top right
	float vertices[] = //3 position coords, 2 UV texture coords
	{x+w,y+h,0.0f, 1.0f,1.0f,
	x+w,y,0.0f, 1.0f,0.0f,
	x,y,0.0f, 0.0f,0.0f,
	x,y+h,0.0f, 0.0f,1.0f};
	unsigned int indices[] = {0,1,3,//first triangle
							  1,2,3};//second triangle
	bindVAO();
	setVertices(vertices,sizeof(vertices));
	setIndices(indices,sizeof(indices));
	updateVertexAttributes();
}

bool Sprite::loadNoInitShape(const char* imageNameR,int shader,bool debugPrint)
{
	std::string imageNameStr=findFileAbsLocFromRoot(imageNameR);
	const char* imageName =imageNameStr.c_str();
	
	if(debugPrint)std::cout<<"Loading sprite '"<<imageName<<"'\n";

	currentShader=shader;
	glGenVertexArrays(1,&vertexArrayObjectTex);
	glBindVertexArray(vertexArrayObjectTex);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenBuffers(1,&vertexBufferObjectTex);
	glGenBuffers(1,&elementBufferObjectTex);

	texData = stbi_load(imageName, &texWidth, &texHeight, &numColorChannels, 0);
	if(texData!=NULL)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		isLoaded=1;
		stbi_image_free(texData);
		if(debugPrint)std::cout<<"Loaded sprite '"<<imageName<<"'\n";
		return true;
	}else
	{
		if(debugPrint)std::cout<<"Couldn't load image '" << imageName << "'!\n";
		stbi_image_free(texData);
		return false;
	}
}
void Sprite::drawSprite()
{
	if(!isLoaded)
	{
		std::cout<<"FATAL ERROR: Sprite.drawSprite(): Sprite has not yet called load()\n";
		exit(EXIT_FAILURE);
	}
	if(getNumIndices()<=0)
	{
		std::cout<<"FATAL ERROR: numIndices="<<getNumIndices()
				 <<" <=0 on sprite["<<texture<<"] while calling drawSprite()\n";
		exit(EXIT_FAILURE);
	}
	bindVAO();
	if(dirtyVertexAttrib)
	{
  		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectTex);
  		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectTex);
		updateVertexAttributes();
	}
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glUseProgram(currentShader);	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectTex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectTex);
	glDrawElements(GL_TRIANGLES, getNumIndices(), GL_UNSIGNED_INT, 0);
};


void initializeSpriteRenderer()
{
	std::cout<<"Initializing Sprite Renderer\n";
	shaderProgramTex = createShaderProgramFromSrc(vertShaderTex,fragShaderTex);
	shaderProgramTexWithCamera = createShaderProgramFromSrc(vertShaderTexWithCamera,fragShaderTex);
	shaderProgramTexEarth = createShaderProgramFromSrc(vertShaderTexWithCamera,fragShaderTexEarth);
}
void spriteRendererUpdateCamera(Camera& camera)
{
	glUseProgram(shaderProgramTexWithCamera);
	GLint modelMatUniform2 = glGetUniformLocation(shaderProgramTexWithCamera,"modelMat"); //Passes the matrices to the texture shader
	glUniformMatrix4fv(modelMatUniform2,1,GL_TRUE,camera.getModelMat().values);
	GLint projMatUniform2 = glGetUniformLocation(shaderProgramTexWithCamera,"projMat");
	glUniformMatrix4fv(projMatUniform2,1,GL_TRUE,camera.getProjMat().values);

	glUseProgram(shaderProgramTexEarth);
	modelMatUniform2 = glGetUniformLocation(shaderProgramTexEarth,"modelMat");
	glUniformMatrix4fv(modelMatUniform2,1,GL_TRUE,camera.getModelMat().values);
	projMatUniform2 = glGetUniformLocation(shaderProgramTexEarth,"projMat");
	glUniformMatrix4fv(projMatUniform2,1,GL_TRUE,camera.getProjMat().values);
	
	float resOriginVec[4] = {0,0,0,1};
	camera.getModelMat().postMultiplyVec4(resOriginVec,resOriginVec);
	resOriginVec[2]+=300;
	camera.getProjMat().postMultiplyVec4(resOriginVec,resOriginVec);
	
	GLint transformedOriginUniform = glGetUniformLocation(shaderProgramTexEarth,"transformedOrigin");
	glUniform4f(transformedOriginUniform,resOriginVec[0],resOriginVec[1],resOriginVec[2],resOriginVec[3]);
}
