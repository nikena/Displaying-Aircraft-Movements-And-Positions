
#include "inputHandler.hpp"


void InputHandler::updateInput(float deltaTime, GLFWwindow* window)
	{
		double xr=curCursorPosX-lastCursorPosX;
		double yr=curCursorPosY-lastCursorPosY;

		int heldMouseBtnL = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		int heldMouseBtnR = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

		if(heldMouseBtnL==GLFW_PRESS)
		{
			if((cameraRotVert+earthRotVert<=90)&((cameraRotVert+earthRotVert)>=-90))
			{
				earthRotHoriz+=xr*zoom;
			}else
			{
				earthRotHoriz-=xr*zoom;
			}
			earthRotVert+=yr*zoom;
			
			earthRotVert=std::max(earthRotVert,-90.0);
			earthRotVert=std::min(earthRotVert,90.0);
			if(earthRotHoriz>360)earthRotHoriz-=360;
			if(earthRotHoriz<0)earthRotHoriz+=360;
		}
		if(heldMouseBtnR==GLFW_PRESS)
		{
			cameraRotHoriz+=xr*zoom;
			cameraRotVert+=yr*zoom;
			cameraRotVert=std::max(cameraRotVert,-90.0);
			cameraRotVert=std::min(cameraRotVert,90.0);
			cameraRotHoriz=std::max(cameraRotHoriz,-90.0);
			cameraRotHoriz=std::min(cameraRotHoriz,90.0);
		}
		if(zoom!=targetZoom)
		{
			zoom=((1-deltaTime)*zoom+(deltaTime*targetZoom));
			if(zoom<0.01)targetZoom=zoom=0.01;
			if(zoom>1.1)targetZoom=zoom=1.1;
		}
	};

void InputHandler::lastUpdate(GLFWwindow* window)
{
	lastCursorPosX=curCursorPosX;
	lastCursorPosY=curCursorPosY;
	glfwGetCursorPos(window, &curCursorPosX, &curCursorPosY);
};

void scrollZoomCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	inputHandler.targetZoom-=yoffset/10;
};
