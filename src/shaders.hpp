#ifndef SHADERS_HPP
#define SHADERS_HPP

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <iostream>
#endif

const char* vertShaderPlaneSrc = 
"#version 330 core\n\
layout (location = 0) in vec4 position;\n\
layout (location = 1) in vec4 vColor;\n\
uniform mat4 modelMat;\n\
uniform mat4 projMat;\n\
out vec4 vertexColor;\n\
void main() {\n\
	gl_PointSize = 4.0;\n\
	gl_Position = (projMat * modelMat) * position;\n\
	vertexColor = vColor;\n\
}";
const char* vertShaderSrc = 
"#version 150\n\
in vec4 position;\n\
uniform mat4 modelMat;\n\
uniform mat4 projMat;\n\
void main() {\n\
	gl_PointSize = 4.0;\n\
	gl_Position = (projMat * modelMat) * position;\n\
}";
const char* fragShaderEarthSrc = 
"#version 150\n\
out vec4 out_color;\n\
void main() {\n\
	out_color = (gl_FragCoord.z>0.5) ?vec4(0.1, 0.7, 0.9, 1.0) :vec4(0.8, 0.3, 0.9, 0.0) ;\n\
}";
const char* fragShaderAirportSrc = 
"#version 150\n\
out vec4 out_color;\n\
void main() {\n\
	out_color = (gl_FragCoord.z>-500.5) ?vec4(0.0, 1.0, 0.0, 1.0):vec4(0.0, 1.0, 0.0, 0.0);\n\
}";

const char* fragShaderPlaneSrc =
"#version 330 core\n\
out vec4 out_color;\n\
in vec4 vertexColor;\n\
void main() {\n\
	out_color = (gl_FragCoord.z>0.5) ?vertexColor:vec4(1.0, 0.0, 0.0, 0.0);\n\
}";
//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/gl_FragCoord.xhtml
//gl_FragCoord allows shaders to access the 3d-space 'pixel' the shape maps to.
//This allows us to erase the vertices far away, which is still hacky compared to culling,
//but gives us the effect without having to track faces of the earth.

const char* vertShaderTex = 
"#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
layout (location = 1) in vec2 aTexCoord;\n\
out vec2 texCoord;\n\
void main()\n\
{\n\
	gl_Position = vec4(aPos, 1.0);\n\
	texCoord = vec2(aTexCoord.x, 1.0-aTexCoord.y);\n\
}";

const char* vertShaderTexWithCamera = 
"#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
layout (location = 1) in vec2 aTexCoord;\n\
uniform mat4 modelMat;\n\
uniform mat4 projMat;\n\
out vec2 texCoord;\n\
void main()\n\
{\n\
	gl_Position = (projMat * modelMat) * vec4(aPos, 1.0);\n\
	texCoord = vec2(aTexCoord.x, 1.0-aTexCoord.y);\n\
}";
const char* fragShaderTex = 
"#version 330 core\n\
out vec4 fragColor;\n\
in vec2 texCoord;\n\
uniform sampler2D tex;\n\
void main()\n\
{\n\
	fragColor = texture(tex, texCoord);\n\
}";
const char* fragShaderTexEarth = 
"#version 330 core\n\
out vec4 fragColor;\n\
in vec2 texCoord;\n\
uniform sampler2D tex;\n\
uniform vec4 transformedOrigin;\n\
void main()\n\
{\n\
	vec4 texColor = texture(tex, texCoord);\n\
	float d = (2.0*(gl_FragCoord.z+(1.0-transformedOrigin.z)/2.0)-2.0);\n\
	fragColor = vec4((texColor.x-d),(texColor.y-d),(texColor.z-d),1.0);\n\
}";


//Returns a compiled vertex or fragment shader.
//	type - GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
//	shaderSrc - the string containing the shader
//	printOnError - whether to print errors
GLuint compileShader(GLenum type, const	char *shaderSrc,bool printOnError=true);

//Returns a shader program using a fragment and a vertex shader
//	vertShader - the vertex shader
//	fragShader - the fragment shader
//	printOnCompile - whether to print errors
GLuint createShaderProgram(GLuint vertShader, GLuint fragShader,bool printOnCompile=true);

//Returns a shader program using a fragment and a vertex shader
//	vertShaderSrc - the vertex shader's source string
//	fragShaderSrc - the fragment shader's source string
//	printOnCompile - whether to print errors
GLuint createShaderProgramFromSrc(const char* vertShaderSrc,const char* fragShaderSrc,bool printOnCompile=true);
#endif
