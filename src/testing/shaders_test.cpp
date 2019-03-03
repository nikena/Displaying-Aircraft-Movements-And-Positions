#include "testUtils.hpp"
#include "../shaders.hpp"


bool test_Shaders_compileShader()
{
	PRINT_TEST_START;
	GLint compileStatus=0;
	GLuint vertShader = compileShader(GL_VERTEX_SHADER,vertShaderSrc,false);
	glGetShaderiv(vertShader,GL_COMPILE_STATUS,&compileStatus);
	if(compileStatus==GL_FALSE)
	{
		std::cout<<"[1/4]";
		return false;
	}
	GLuint fragShader = compileShader(GL_FRAGMENT_SHADER,fragShaderEarthSrc,false);	
	glGetShaderiv(fragShader,GL_COMPILE_STATUS,&compileStatus);
	if(compileStatus==GL_FALSE)
	{
		std::cout<<"[2/4]";
		return false;
	}
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	
	GLuint badvertShader = compileShader(GL_FRAGMENT_SHADER,vertShaderSrc,false);
	glGetShaderiv(badvertShader,GL_COMPILE_STATUS,&compileStatus);
	if(compileStatus==GL_FALSE)
	{
		std::cout<<"[3/4]";
		return false;
	}
	GLuint badfragShader = compileShader(GL_VERTEX_SHADER,fragShaderEarthSrc,false);	
	glGetShaderiv(badfragShader,GL_COMPILE_STATUS,&compileStatus);
	if(compileStatus==GL_FALSE)
	{
		std::cout<<"[4/4]";
		return false;
	}
	
	glDeleteShader(badvertShader);
	glDeleteShader(badfragShader);
	
	return true;
}
bool test_Shaders_createShaderProgram()
{
	PRINT_TEST_START;
	glGetError();//Clears any glErrors from prior tests
	GLuint vertShader = compileShader(GL_VERTEX_SHADER,vertShaderSrc);
	GLuint fragShader = compileShader(GL_FRAGMENT_SHADER,fragShaderEarthSrc);
	GLuint shader = createShaderProgram(vertShader,fragShader,false);
	if(glGetError()!=GL_NO_ERROR)
	{
		return false;
	}
	glDeleteProgram(shader);
	return true;
}
bool test_Shaders_createShaderProgramFromSrc()
{
	PRINT_TEST_START;
	glGetError();//Clears any glErrors from prior tests
	GLuint shader = createShaderProgramFromSrc(vertShaderSrc,fragShaderEarthSrc,false);
	if(glGetError()!=GL_NO_ERROR)
	{
		return false;
	}
	glDeleteProgram(shader);
	return true;
}
void test_Shaders()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_Shaders_compileShader());
	printIfOK(test_Shaders_createShaderProgram());
	printIfOK(test_Shaders_createShaderProgramFromSrc());
}
