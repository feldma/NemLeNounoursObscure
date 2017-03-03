#include "general.h"
#include "renderer.h"
Renderer *renderer = new Renderer();

void specialKeys(int key, int x, int y)
{
	renderer->input(key, x, y);
}

void keyboardInput(unsigned char key, int x, int y)
{
	renderer->keyboardInput(key, x, y);
}

void display()
{
	renderer->display();
}

void init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("TP");
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboardInput);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

int main(int argc, char **argv)
{
	init(argc, argv);
	return 0;
}