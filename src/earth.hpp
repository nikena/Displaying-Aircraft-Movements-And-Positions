#ifndef EARTH_HPP
#define EARTH_HPP

#include <vector>
#include "shaders.hpp"
#include "globemath.hpp"
#include "camera.hpp"
#include "spriteRenderer.hpp"
#include "ofAirportLoader.hpp"
#define EARTH_RES_LAT 90
#define EARTH_RES_LONG 90
#define EARTH_LINES_VERTEX_NUM EARTH_RES_LAT*EARTH_RES_LONG*3*4*4 * 10 / 4

class Earth
{
	public:
	double radius=300;
	double numVerticesLat=EARTH_RES_LAT;
	double numVerticesLong=EARTH_RES_LONG;
	Sprite earthTex;
	GLuint shaderProgramEarth;
	GLuint shaderProgramAirport;
	GLuint vertexArrayObjectAirport;
	GLuint vertexArrayObjectEarth;
	GLfloat verticesEarthPos[EARTH_LINES_VERTEX_NUM];//The vbo for earth lines
	GLfloat verticesAirportPos[MAX_AIRPORT_COORDS_BUFFER*3/2];//The vbo for airport coords
	GLuint vertexBufferObjectEarth;
	GLuint vertexBufferObjectAirports;
	

	//Gets vertices of the latitude/longitude lines
	//		output - the array to put vertices in.
	void getVerticesAsLinesLatLong(float output[EARTH_LINES_VERTEX_NUM]);
	
	//Wraps a Sprite around a 3D surface of a UV Sphere.
	//		sprite - the earth texture which will be drawn
	void setTexVerticesAndIndices(Sprite& sprite);
	
	//Tells the program to draw the earth texture(as a sphere)
	void renderEarthTexture();
	
	//Tells the program to draw the earth latitude/longitude lines
	void renderLatLongLines(Camera camera);
	
	//Tells the program to draw the airports
	//		camera - the Camera needed for transformations
	void renderAirports(Camera camera);
	
	public:
	//Tells the program to draw the earth and its airports
	//		camera - the Camera needed for transformations
	void render(Camera camera);
	
	//Intitializes the earth, loading textures and shaders
	void initialize();

};
#endif
