#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

class InputHandler
{
	public:

	double earthRotHoriz=0;
	double earthRotVert=0;
	double cameraRotHoriz=0;
	double cameraRotVert=0;
	double lastCursorPosX=0;
	double lastCursorPosY=0;
	double curCursorPosX=0;
	double curCursorPosY=0;
	double zoom = 1;
	double targetZoom=zoom;

	public:
	
	//Controls input concerning mouse clicks and movements
	//		deltaTime - the time it took from last frame to this one in seconds
	//		window    - the window from which to grab mouse input
	void updateInput(float deltaTime, GLFWwindow* window);
	
	//Updates the cursor position to the next.
	//		window - the window from which to grab the cursor from
	void lastUpdate(GLFWwindow* window);
		
	//getters for last cursor position
	double getlastCursorPosX(){
		return lastCursorPosX;
	}
	double getlastCursorPosY(){
		return lastCursorPosY;
	}
	//getters for current cursor position
	double getcurCursorPosX() const{
		return curCursorPosX;
	}
	double getcurCursorPosY() const{
		return curCursorPosY;
	}
	
	//getters for earth rotation
	double getEarthRotHoriz() const{
		return earthRotHoriz;
	}
	double getEarthRotVert() const{
		return earthRotVert;
	}
	
	//getters for camera rotation
	double getCameraRotHoriz() const{
		return cameraRotHoriz;
	}
	double getCameraRotVert() const{
		return cameraRotVert;
	}
	//setters for camera rotation
	void setCameraRotHoriz(double cRH)
	{
		cameraRotHoriz=cRH;
	}
	void setCameraRotVert(double cRV)
	{
		cameraRotVert=cRV;
	}
	
	//gets the current zoom factor
	double getZoom() const{
		return zoom;
	}
	//gets the target zoom
	double getTargetZoom() const{
		return targetZoom;
	}
	//sets the target zoom
	//		tZoom - the desired zoom factor
	void setTargetZoom(double tZoom){
		targetZoom=tZoom;
	}
};
InputHandler inputHandler;
void scrollZoomCallback(GLFWwindow* window, double xoffset, double yoffset);
#endif

