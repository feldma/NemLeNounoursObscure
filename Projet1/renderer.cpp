#include "renderer.h"

float ver[8][3] =
{
	{ -1.0,-1.0,1.0 },
	{ -1.0,1.0,1.0 },
	{ 1.0,1.0,1.0 },
	{ 1.0,-1.0,1.0 },
	{ -1.0,-1.0,-1.0 },
	{ -1.0,1.0,-1.0 },
	{ 1.0,1.0,-1.0 },
	{ 1.0,-1.0,-1.0 },
};

GLfloat color[8][3] =
{
	{ 0.0,0.0,0.0 },
	{ 1.0,0.0,0.0 },
	{ 1.0,1.0,0.0 },
	{ 0.0,1.0,0.0 },
	{ 0.0,0.0,1.0 },
	{ 1.0,0.0,1.0 },
	{ 1.0,1.0,1.0 },
	{ 0.0,1.0,1.0 },
};

Renderer::Renderer() : m_rotateX(0), m_rotateY(0)
{}

Renderer::~Renderer()
{}

void	Renderer::quad(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
	glColor3fv(color[a]);
	glVertex3fv(ver[a]);

	glColor3fv(color[b]);
	glVertex3fv(ver[b]);

	glColor3fv(color[c]);
	glVertex3fv(ver[c]);

	glColor3fv(color[d]);
	glVertex3fv(ver[d]);
	glEnd();
}

void	Renderer::colorcube()
{
	quad(0, 3, 2, 1);
	quad(2, 3, 7, 6);
	quad(0, 4, 7, 3);
	quad(1, 2, 6, 5);
	quad(4, 5, 6, 7);
	quad(0, 1, 5, 4);
}

void	Renderer::input(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
		m_rotateY += 5;
	else if (key == GLUT_KEY_LEFT)
		m_rotateY -= 5;
	else if (key == GLUT_KEY_UP)
		m_rotateX += 5;
	else if (key == GLUT_KEY_DOWN)
		m_rotateX -= 5;
	glutPostRedisplay();
}

void	Renderer::keyboardInput(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		camera.m_eye.x += 1;
		std::cout << "w" << std::endl;
		break;
	case 'a':
		camera.m_eye.y -= 1;
		std::cout << "a" << std::endl;
		break;
	case 's':
		camera.m_eye.x -= 1;
		std::cout << "s" << std::endl;
		break;
	case 'd':
		camera.m_eye.y += 1;
		std::cout << "d" << std::endl;
		break;
	}
	glutPostRedisplay();
}

void	Renderer::display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60, w / h, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
	(
		camera.m_eye.x, 0, camera.m_eye.y,
		0, 0, 0,
		0, 1, 0
	);

	glRotatef(m_rotateX, 1.0, 0.0, 0.0);
	glRotatef(m_rotateY, 0.0, 1.0, 0.0);
	colorcube();

	glutSwapBuffers();
}