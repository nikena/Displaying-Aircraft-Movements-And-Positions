#ifndef GLFW_ERROR_HANDLER_HPP
#define GLFW_ERROR_HANDLER_HPP
void glfwErrorCallback(int errorNum, const char* errorStr)
{
    std::cout << errorStr;
}
#endif
