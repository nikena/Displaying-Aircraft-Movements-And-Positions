#include "earth.hpp"


void Earth::getVerticesAsLinesLatLong(float output[EARTH_LINES_VERTEX_NUM])
{
	double t =0;
	double b =0;
	double p=180;
	int o=0;
	for(t=-p/2;t<p/2;t+=(p/2)/numVerticesLat)
	{
		for(b=-p;b<p;b+=(p)/numVerticesLong)
		{
			double t2=t+(p/2)/numVerticesLat;
			double b2=b+(p)/numVerticesLong;
			output[o++]=getXFromLatLong(radius,t,b);
			output[o++]=getYFromLatLong(radius,t,b);
			output[o++]=getZFromLatLong(radius,t,b);

			output[o++]=getXFromLatLong(radius,t2,b);
			output[o++]=getYFromLatLong(radius,t2,b);
			output[o++]=getZFromLatLong(radius,t2,b);

			output[o++]=getXFromLatLong(radius,t,b);
			output[o++]=getYFromLatLong(radius,t,b);
			output[o++]=getZFromLatLong(radius,t,b);

			output[o++]=getXFromLatLong(radius,t,b2);
			output[o++]=getYFromLatLong(radius,t,b2);
			output[o++]=getZFromLatLong(radius,t,b2);
		}
	}
};
//Wraps a Sprite around a 3D surface of a UV Sphere.
void Earth::setTexVerticesAndIndices(Sprite& sprite)
{
	std::vector<float> outputV;
	unsigned int outputI[4*EARTH_RES_LAT*EARTH_RES_LONG*6];
	
	float r=radius-0.000001f;
	double p=180;
	double t =-p/2 + ((p/2)/numVerticesLat);
	double b =-p + ((p)/numVerticesLong);
	int o=0,oi=0,ov=0;
	for(t=-p/2;t<p/2;t+=(p/2)/numVerticesLat)
	{
		for(b=-p;b<p;b+=(p)/numVerticesLong)
		{
			float uOff=0.0f;
			double t2=t+(p/2)/numVerticesLat;
			double b2=b+(p)/numVerticesLong;

			outputV.push_back(getXFromLatLong(r,t,b));
			outputV.push_back(getYFromLatLong(r,t,b));
			outputV.push_back(getZFromLatLong(r,t,b));
			outputV.push_back(0.5f*((b+p)/p +uOff));
			outputV.push_back((t+p/2)/p);

			outputV.push_back(getXFromLatLong(r,t2,b));
			outputV.push_back(getYFromLatLong(r,t2,b));
			outputV.push_back(getZFromLatLong(r,t2,b));
			outputV.push_back(0.5f*((b+p)/p +uOff));
			outputV.push_back((t2+p/2)/p);

			outputV.push_back(getXFromLatLong(r,t,b2));
			outputV.push_back(getYFromLatLong(r,t,b2));
			outputV.push_back(getZFromLatLong(r,t,b2));
			outputV.push_back(0.5f*((b2+p)/p +uOff));
			outputV.push_back((t+p/2)/p);

			outputV.push_back(getXFromLatLong(r,t2,b2));
			outputV.push_back(getYFromLatLong(r,t2,b2));
			outputV.push_back(getZFromLatLong(r,t2,b2));
			outputV.push_back(0.5f*((b2+p)/p +uOff));
			outputV.push_back((t2+p/2)/p);

			outputI[oi++]=ov+0;
			outputI[oi++]=ov+1;
			outputI[oi++]=ov+2;
			outputI[oi++]=ov+2;
			outputI[oi++]=ov+1;
			outputI[oi++]=ov+3;
			ov+=4;
		}
	}

	sprite.bindVAO();
	sprite.setVertices(outputV.data(),outputV.size()*sizeof(float));
	sprite.setIndices(outputI,oi*sizeof(unsigned int));
	sprite.updateVertexAttributes();

	outputV.clear();
};
void Earth::renderEarthTexture()
{
	glEnable(GL_DEPTH_TEST);
	earthTex.drawSprite();
};
void Earth::renderLatLongLines(Camera camera)
{
	glBindVertexArray(vertexArrayObjectEarth);

	glUseProgram(shaderProgramEarth); //Uses the earth shader
	GLint modelMatUniform = glGetUniformLocation(shaderProgramEarth,"modelMat");//Passes the matrices to the earth shader
	glUniformMatrix4fv(modelMatUniform,1,GL_TRUE,camera.getModelMat().values);
	GLint projMatUniform = glGetUniformLocation(shaderProgramEarth,"projMat");
	glUniformMatrix4fv(projMatUniform,1,GL_TRUE,camera.getProjMat().values);

	glDrawArrays(GL_LINES, 0, sizeof(verticesEarthPos)/sizeof(float)); //Draws the current binded earth vbo
};
void Earth::renderAirports(Camera camera)
{
	glBindVertexArray(vertexArrayObjectAirport);

	glUseProgram(shaderProgramAirport); //Uses the airport shader
	GLint modelMatUniform2 = glGetUniformLocation(shaderProgramAirport,"modelMat"); //Passes the matrices to the airport shader
	glUniformMatrix4fv(modelMatUniform2,1,GL_TRUE,camera.getModelMat().values);
	GLint projMatUniform2 = glGetUniformLocation(shaderProgramAirport,"projMat");
	glUniformMatrix4fv(projMatUniform2,1,GL_TRUE,camera.getProjMat().values);

	glDrawArrays(GL_POINTS, 0, numAirportCoords*3/2); //Draws the current binded airport vbo
};
void Earth::render(Camera camera)
{
	renderEarthTexture();
	renderAirports(camera);
};
void Earth::initialize()
{
	shaderProgramEarth = createShaderProgramFromSrc(vertShaderSrc,fragShaderEarthSrc);
	shaderProgramAirport = createShaderProgramFromSrc(vertShaderSrc,fragShaderAirportSrc);

	getAirportVerticesAsPoints(verticesAirportPos,radius);
	getVerticesAsLinesLatLong(verticesEarthPos);

	glGenBuffers(1,&vertexBufferObjectEarth);
	glGenBuffers(1,&vertexBufferObjectAirports);

	glGenVertexArrays(1,&vertexArrayObjectEarth);
	glBindVertexArray(vertexArrayObjectEarth);


	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferObjectEarth);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verticesEarthPos),verticesEarthPos,GL_STATIC_DRAW);
	GLint posAttrib = glGetAttribLocation(shaderProgramEarth,"position");//Passes the vertices to earth shader
	glVertexAttribPointer(posAttrib,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(posAttrib);

	glGenVertexArrays(1,&vertexArrayObjectAirport);
	glBindVertexArray(vertexArrayObjectAirport);

	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferObjectAirports);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verticesAirportPos),verticesAirportPos,GL_STATIC_DRAW);

	GLint posAttrib2 = glGetAttribLocation(shaderProgramAirport,"position"); //Passes the vertices to the airport shader
	glVertexAttribPointer(posAttrib2,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(posAttrib2);

	earthTex.loadNoInitShape("assets/shadedrelief-earth-no-clouds-small-p2.png",shaderProgramTexEarth);
	setTexVerticesAndIndices(earthTex);
};
