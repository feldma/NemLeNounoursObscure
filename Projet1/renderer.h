#pragma once
#include "general.h"
#include "camera.h"

class Renderer
{
public:
	explicit Renderer();
	virtual ~Renderer();

	void display();
	void input(int, int, int);
	void keyboardInput(unsigned char, int, int);
	void colorcube();
	void quad(int, int, int, int);

private:
	GLfloat m_rotateX;
	GLfloat m_rotateY;
	Camera camera;
};