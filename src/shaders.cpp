#include "shaders.hpp"

GLuint compileShader(GLenum type, const	char *shaderSrc,bool printOnError)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader,1,&shaderSrc,NULL);
	glCompileShader(shader);

	GLint compileStatus=0;	
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compileStatus);
	if((compileStatus==GL_FALSE)&(printOnError))
	{
		std::cout<<"Failed to compile shader:\n";
		std::cout<<"\n\n"<<shaderSrc<<"|\n";
	}
	return shader;
}

GLuint createShaderProgram(GLuint vertShader, GLuint fragShader,bool printOnCompile)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertShader);
	glAttachShader(shaderProgram,fragShader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glLinkProgram(shaderProgram);
	if(printOnCompile)
		std::cout<<"Compiled new shader["<<shaderProgram<<"]\n";
	return shaderProgram;
}

GLuint createShaderProgramFromSrc(const char* vertShaderSrc,const char* fragShaderSrc,bool printOnCompile)
{
	GLuint vertShader = compileShader(GL_VERTEX_SHADER,vertShaderSrc);
	GLuint fragShader = compileShader(GL_FRAGMENT_SHADER,fragShaderSrc);
	return createShaderProgram(vertShader,fragShader,printOnCompile);
}
