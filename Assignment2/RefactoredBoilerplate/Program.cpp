/*
* Program.cpp
*
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

RenderingEngine* renderer;

Program::Program() {
	selectionState = SelectionState::NONE;
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine);
	renderer = renderingEngine;
	//Main render loop
	while (!glfwWindowShouldClose(window)) {
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 512;
	int height = 512;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	glfwSetWindowUserPointer(window, this);
	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);
	//Set the custom function that tracks scroll wheel 
	glfwSetScrollCallback(window, scroll_callback);
	//Set the custom function that tracks cursor position 
	glfwSetCursorPosCallback(window, cursor_position_callback);
	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}

void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		std::cout << "Please press 1-7 to select a foreground image.\n";
		program->selectionState = Program::SelectionState::FOREGROUND;
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		std::cout << "Please press 1-6 to select a background image.\n";
		program->selectionState = Program::SelectionState::BACKGROUND;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		std::cout << "Please press 1-4 to select a color effect.\n";
		program->selectionState = Program::SelectionState::COLOR_EFFECT;
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		std::cout << "Please press 1-7 to select a filter.\n";
		program->selectionState = Program::SelectionState::FILTER;
	}
	//press number keys from 1 to 7 to display each of the 7 images
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		if (program->selectionState == Program::SelectionState::FOREGROUND) {
			program->getScene()->selectForeground(0);
			renderer->l = 0;
		}
		else if (program->selectionState == Program::SelectionState::BACKGROUND) {
			program->getScene()->selectBackground(0);
		}
		else if (program->selectionState == Program::SelectionState::FILTER) {
			program->getScene()->selectFilter(0);
		}
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		if (program->selectionState == Program::SelectionState::FOREGROUND) {
			program->getScene()->selectForeground(1);
			renderer->l = 0;
		}
		else if (program->selectionState == Program::SelectionState::BACKGROUND) {
			program->getScene()->selectBackground(1);
		}
		else if (program->selectionState == Program::SelectionState::FILTER) {
			program->getScene()->selectFilter(1);
		}
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		if (program->selectionState == Program::SelectionState::FOREGROUND) {
			program->getScene()->selectForeground(2);
			renderer->l = 0;
		}
		else if (program->selectionState == Program::SelectionState::BACKGROUND) {
			program->getScene()->selectBackground(2);
		}
		else if (program->selectionState == Program::SelectionState::FILTER) {
			program->getScene()->selectFilter(2);
		}
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		if (program->selectionState == Program::SelectionState::FOREGROUND) {
			program->getScene()->selectForeground(3);
			renderer->l = 0;
		}
		else if (program->selectionState == Program::SelectionState::FILTER) {
			program->getScene()->selectFilter(3);
		}
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		if (program->selectionState == Program::SelectionState::FOREGROUND) {
			program->getScene()->selectForeground(4);
			renderer->l = 0;
		}
		else if (program->selectionState == Program::SelectionState::FILTER) {
			program->getScene()->selectFilter(4);
		}
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		if (program->selectionState == Program::SelectionState::FOREGROUND) {
			program->getScene()->selectForeground(5);
			renderer->l = 0;
		}
		else if (program->selectionState == Program::SelectionState::FILTER) {
			program->getScene()->selectFilter(5);
		}
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		if (program->selectionState == Program::SelectionState::FOREGROUND) {
			program->getScene()->selectForeground(6);
			renderer->l = 0;
		}
		else if (program->selectionState == Program::SelectionState::FILTER) {
			program->getScene()->selectFilter(6);
		}
	}
	//press number keys 8, 9, 0 to apply color tone
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		renderer->l = 1;
	}
	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		renderer->l = 2;
	}
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		renderer->l = 3;
	}
	//press s to apply a sepia tone
	if (key == GLFW_KEY_S && action == GLFW_PRESS){
		renderer->l = 4;
	}
	//press a to rotate counter clockwise
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		program->getScene()->rotateForeground(15.0f);
	}
	//press a to rotate clockwise
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		program->getScene()->rotateForeground(-15.0f);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	//scroll forward to zoom in
	if (yoffset == 1) {
		if (renderer->zoom < 3.0f) {
			renderer->zoom += 0.1f;
			program->getScene()->updateZoom(renderer->zoom);
		}
	}
	//scroll backward to zoom out
	else if (yoffset == -1){
		if (renderer->zoom > 0.5f) {
			renderer->zoom -= 0.1f;
			program->getScene()->updateZoom(renderer->zoom);
		}
	}
}
double rx;
double ry;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	GLboolean leftDown;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		leftDown = true;
	}
	else {
		leftDown = false;
	}
	if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)){
		rx = xpos;
		ry = ypos;
	}
	if (leftDown){
		program->getScene()->updateVertices((xpos-rx) / 256, (ypos - ry) / -256);
	}
	else {
		program->getScene()->stopVerticesUpdate();
	}
}