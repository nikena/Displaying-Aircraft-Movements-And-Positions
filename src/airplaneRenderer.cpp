#include "airplaneRenderer.hpp"
#include "planeLoader.hpp"
#include "earthAirportPrototype.hpp"


void AirplaneRenderer::updateVertexAttributes()
{
	glBindVertexArray(vertexArrayObject);
	
	GLint posAttribPos = glGetAttribLocation(shaderProgramPlane, "position"); //Passes the vertices to the Plane shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
	GLint posAttribVColor = glGetAttribLocation(shaderProgramPlane, "vColor"); //Passes the color to the Plane shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
	
	GLint modelMatUniform3 = glGetUniformLocation(shaderProgramPlane, "modelMat"); //Passes the matrices to the plane shader
	glUniformMatrix4fv(modelMatUniform3, 1, GL_TRUE, camera.getModelMat().values);
	GLint projMatUniform3 = glGetUniformLocation(shaderProgramPlane, "projMat");
	glUniformMatrix4fv(projMatUniform3, 1, GL_TRUE, camera.getProjMat().values);
}

void AirplaneRenderer::initializeAirplaneRenderer(Earth& earth)
{
	GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertShaderPlaneSrc);
	GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragShaderPlaneSrc);
	shaderProgramPlane = createShaderProgram(vertShader, fragShader);
	glGenVertexArrays(1, &vertexArrayObject);
	
	getPlaneVerticesAsPoints(airplaneCoords, earth,0, 0);
	
	glGenBuffers(1, &vertexBufferObjectPlanes);
	glGenBuffers(1,&elementBufferObject);

	glBindVertexArray(vertexArrayObject);
	GLint posAttribPos = glGetAttribLocation(shaderProgramPlane, "position"); //Passes the positions to the Plane shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	GLint posAttribVColor = glGetAttribLocation(shaderProgramPlane, "vColor"); //Passes the color to the Plane shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void AirplaneRenderer::renderAirplanes(Camera& camera,Earth& earth)
{
	//Draws the planes

	glBindVertexArray(vertexArrayObject);

	glUseProgram(shaderProgramPlane); //Uses the Plane shader

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectPlanes);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPlanePos), verticesPlanePos, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, airplaneCoords.size()*sizeof(float), airplaneCoords.data(), GL_DYNAMIC_DRAW);


	setIndices((unsigned int*)(&(indicesPlaneVector.data()[0])),sizeof(indicesPlaneVector.data()),elementBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicesPlaneVector.size()*sizeof(unsigned int),indicesPlaneVector.data(),GL_DYNAMIC_DRAW);

	updateVertexAttributes();

	if(bRenderTrails == true) glDrawElements(GL_LINES, getNumPlaneIndices(), GL_UNSIGNED_INT,0);
	glDrawElements(GL_POINTS, getNumPlaneIndices(), GL_UNSIGNED_INT,0);


	if (!setOldTime) 
	{
		old=glfwGetTime();
		setOldTime=true;
	}
	current=glfwGetTime();
	
	bool timeChanged = ((current-old)*planeRenderSpeed >= 1);
	
	if(timeChanged)
	{
		if(!bBackwards) {
			planeTimeSegment += 1;
		}
		else {
			planeTimeSegment -=1;
		}
		if (planeTimeSegment >= 60) 
		{
			planeTimeSegment = 0;
			hourTimeSegment += 1;
			setOldTime=false;
		}
		/*if(hourTimeSegment >= 24)
		{
			hourTimeSegment = 0;
		}*/

		if (planeTimeSegment <0){
			planeTimeSegment = 59;
			hourTimeSegment -= 1;
			setOldTime = false;
		}
		/*if(hourTimeSegment < 0)
		{
			hourTimeSegment = 23;
		}*/
		if(hourTimeSegment<0)
		{
			hourTimeSegment=hourVector.size()-1;
		}
		if(hourTimeSegment>=hourVector.size())
		{
			hourTimeSegment=0;
		}
		

		old=glfwGetTime();
	}
	if (timeChanged | textInput!=textInputOld | maxAltFt!=oldMaxAltFt)
	{
		getPlaneVerticesAsPoints(airplaneCoords, earth, planeTimeSegment,hourTimeSegment);
		textInputOld=textInput;
		oldMaxAltFt=maxAltFt;
	}
	std::string timeDirStr = "(Paused)";
	if(planeRenderSpeed!=0)
	{
		if(bBackwards)
		{
			timeDirStr = "(Rewind)";
		}
		else
		{
			timeDirStr = "(Fast-forward)";
		}
	}
	unsigned long long int curUniqueHourTimeTemp=0;// YYYYMMDDHH00
	unsigned long long int curUniqueHourTime=0;
	Hour* curHour = nullptr;
	try
	{
		curHour = &(hourVector.at(hourTimeSegment));
		curUniqueHourTimeTemp = curUniqueHourTime = curHour->getUniqueHourTime();
	}catch (const std::out_of_range& exception){}
	
	int curYear = (curUniqueHourTimeTemp-(curUniqueHourTimeTemp%100000000))/100000000;
	curUniqueHourTimeTemp-=((unsigned long long int )curYear)*100000000;
	
	int curMonth = (curUniqueHourTimeTemp-(curUniqueHourTimeTemp%1000000))/1000000;
	curUniqueHourTimeTemp-=((unsigned long long int )curMonth)*1000000;
	
	int curDay = (curUniqueHourTimeTemp-(curUniqueHourTimeTemp%10000))/10000;
	curUniqueHourTimeTemp-=curDay*10000;
	
	int curHourNum = (curUniqueHourTimeTemp-(curUniqueHourTimeTemp%100))/100;
	curUniqueHourTimeTemp-=curHourNum*100;
	
	std::string dateStr = std::to_string(curYear)+"/"+std::to_string(curMonth)+"/"+std::to_string(curDay);
	
	std::string timeStr = dateStr+" @ "
							+std::to_string(curHourNum)+":"
							+std::to_string(planeTimeSegment) 
							+"(x"+std::to_string(60*(int)(planeRenderSpeed*100)/100)+")"+timeDirStr;
							
	if(curHour==nullptr)
	{
		timeStr = "No data loaded.";
	}
	
	std::string tLeftStr = timeStr + "( "+ std::to_string((int)maxAltFt)+" Ft. Max altitude )";
	fontRenderer.drawText(tLeftStr,0.35, -1.0, 1.0);
}
