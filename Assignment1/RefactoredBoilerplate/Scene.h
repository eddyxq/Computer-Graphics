/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Geometry.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene();

	void displaySquaresAndDiamondsScene(int iteration);
	void displayParametricSprialScene(int iteration);
	void displaySierpinskiScene(int iteration);
	void displaySierpinskiTriangleReloadedScene(int iteration);
	void displayFractalGeometriesScene(int iteration);
	void drawSierpinski(double x1, double y1, double x2, double y2, double x3, double y3, Geometry triangle, int iteration, double r, double g, double b);
	void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int iteration, double r, double g, double b);

private:
	RenderingEngine* renderer;

	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */
