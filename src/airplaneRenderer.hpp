#ifndef AIRPLANE_RENDERER_HPP
#define AIRPLANE_RENDERER_HPP
class AirplaneRenderer
{
	protected:
	GLuint shaderProgramPlane;
	GLuint vertexArrayObject;
	std::vector<float> airplaneCoords;
	GLuint vertexBufferObjectPlanes;
	GLuint elementBufferObject;

	double old = -1;
	double current = -1;
	bool setOldTime = false;
	void updateVertexAttributes();
	
	public:
	bool bRenderTrails = true;	
	int planeTimeSegment = 0;
	int hourTimeSegment = 0;
	bool bIsFilter = false;
	bool bBackwards = false;
	double planeRenderSpeed = 1;
	
	void initializeAirplaneRenderer(Earth& earth);
	void renderAirplanes(Camera& camera,Earth& earth);
};


#endif
