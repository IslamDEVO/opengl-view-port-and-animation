#include<GL/glut.h>
/*
الاسم : اسلام محمد عبد العزيز
سكشن : 1
قسم : تكنولوجياالمعلومات
الفرقه : الثالثه
*

/*
		3	|		|	4
			|	5	|	
		1	|		|	2
*/

#pragma region Initial square position and size for each object

// object 1
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
// object 2
GLfloat x2 = 50.0f;
GLfloat y2 = 50.0f;
// object 3
GLfloat x3 = -50.0f;
GLfloat y3 = -50.0f;
// object 4
GLfloat x4 = 0.0f;
GLfloat y4 = -70.0f;
// object 5
GLfloat x5 = 0.0f;
GLfloat y5 = 70.0f;

GLfloat rsize = 25.0f;

#pragma endregion


#pragma region Step size in x and y directions
// (number of pixels to move each time)
// object 1
GLfloat x1step = 1.0f;
GLfloat y1step = 1.0f;
// object 2
GLfloat x2step = 1.0f;
GLfloat y2step = 1.0f;
// object 3
GLfloat x3step = 1.0f;
GLfloat y3step = 1.0f;
// object 4
GLfloat x4step = 1.0f;
GLfloat y4step = 1.0f;
// object 5
GLfloat x5step = 1.0f;
GLfloat y5step = 1.0f;
#pragma endregion

// Keep track of windows changing width and height used in ReSize fun
GLfloat windowWidth;
GLfloat windowHeight;
//	the width and heieht of windows that used in viewports for each object
GLfloat w;
GLfloat h;

void Draw();
void ReSize(GLsizei w , GLsizei h);
void TimerFunction(int);
void Startup();

using namespace std;
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(850, 100);
	glutCreateWindow("Assignment 1");
	glutDisplayFunc(Draw);
	glutReshapeFunc(ReSize);
	glutTimerFunc(33, TimerFunction, 1);

	Startup();
	glutMainLoop();
}

void Draw() {
	GLfloat aspectRatio;
	glClear(GL_COLOR_BUFFER_BIT);
#pragma region object 1
	glColor3f(1.0, 1.0, 0.0);
	glViewport(0 , 0 , w / 4 , h / 4);
	glRectf(x1, y1, x1 + rsize, y1 - rsize);
	glFlush();
#pragma endregion

#pragma region object 2
	glColor3f(1.0, 0.0, 1.0);
	glViewport(0 + ( w/4 + w/2 ) , 0 , w / 4 , h / 4);
	glRectf(x2, y2, x2 + rsize, y2 - rsize);
	glFlush();
#pragma endregion
	
#pragma region object 3
	glColor3f(0.5, 0.0, 0.1);
	glViewport(0 , 0 + ( h/4 + h/2 ) , w / 4 , h / 4);
	glRectf(x3, y3, x3 + rsize, y3 - rsize);
	glFlush();
#pragma endregion

#pragma region object 4
	glColor3f(1.0, 0.1, 0.1);
	glViewport(0 + (w / 4 + w / 2), 0 + (h / 4 + h / 2) , w / 4, h / 4);
	glRectf(x4, y4, x4 + rsize, y4 - rsize);
	glFlush();
#pragma endregion

#pragma region object 5
	glColor3f(0.0, 1.0, 0.0);
	glViewport(0 + ( w/4 ), 0 + ( h/4 ), w / 2, h / 2);
	glRectf(x5, y5, x5 + rsize, y5 - rsize);
	glFlush();
#pragma endregion

}

void Startup() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void ReSize(GLsizei w, GLsizei h) {
	::w = w;
	::h = h;
	GLfloat aspectRatio;
		//test
		//std::cout << w << "\t" << h << "\n";
		//std::cout << windowWidth << "\t" << windowHeight << "\n";
	
		// Prevent a divide by zero
		if (h == 0)        h = 1;
		//glViewport(0, 0, w, h);
	
		// Reset coordinate system
		glMatrixMode(GL_PROJECTION);    glLoadIdentity();
	
		// Establish clipping volume (left, right, bottom, top, near, far)
		aspectRatio = (GLfloat)w / (GLfloat)h;
		if (w <= h) {
			windowWidth = 100;        windowHeight = 100 / aspectRatio;
			glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
			//glOrtho(0.0, 100.0, 0.0, windowHeight, 1.0, -1.0);
		}
		else {
			windowWidth = 100 * aspectRatio;        windowHeight = 100;
			glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
		}
	
		glMatrixMode(GL_MODELVIEW);    glLoadIdentity();
}

void TimerFunction(int value) {
#pragma region moving fun object 1
	// Reverse direction when you reach left or right edge
	if (x1 > windowWidth - rsize /*0 > -25*/ || x1 < -windowWidth /*0 < -25*/)        x1step = -x1step; //rsize=25 , windowWidth=0 , xstep=1.0f

																									  // Reverse direction when you reach top or bottom edge
	if (y1 > windowHeight /*0 > 0*/ || y1 < -windowHeight + rsize /*0 < -25*/)        y1step = -y1step;

	// Actually move the square
	x1 += x1step;    y1 += y1step;

	// Check bounds. This is in case the window is made smaller while the rectangle is //bouncing and the rectangle suddenly finds itself outside the new clipping volume

	if (x1 >(windowWidth - rsize + x1step))        x1 = windowWidth - rsize - 1;
	else if (x1 < -(windowWidth + x1step))	x1 = -windowWidth - 1;

	if (y1 >(windowHeight + y1step))        y1 = windowHeight - 1;
	else if (y1 < -(windowHeight - rsize + y1step))	y1 = -windowHeight + rsize - 1;
#pragma endregion

#pragma region moving fun object 2
	// Reverse direction when you reach left or right edge
	if (x2 > windowWidth - rsize /*0 > -25*/ || x2 < -windowWidth /*0 < -25*/)        x2step = -x2step; //rsize=25 , windowWidth=0 , xstep=1.0f

																									  // Reverse direction when you reach top or bottom edge
	if (y2 > windowHeight /*0 > 0*/ || y2 < -windowHeight + rsize /*0 < -25*/)        y2step = -y2step;

	// Actually move the square
	x2 += x2step;    y2 += y2step;

	// Check bounds. This is in case the window is made smaller while the rectangle is //bouncing and the rectangle suddenly finds itself outside the new clipping volume

	if (x2 >(windowWidth - rsize + x2step))        x2 = windowWidth - rsize - 1;
	else if (x2 < -(windowWidth + x2step))	x2 = -windowWidth - 1;

	if (y2 >(windowHeight + y2step))        y2 = windowHeight - 1;
	else if (y2 < -(windowHeight - rsize + y2step))	y2 = -windowHeight + rsize - 1;
#pragma endregion
	
#pragma region moving fun object 3
	// Reverse direction when you reach left or right edge
	if (x3 > windowWidth - rsize /*0 > -25*/ || x3 < -windowWidth /*0 < -25*/)        x3step = -x3step; //rsize=25 , windowWidth=0 , xstep=1.0f

																									  // Reverse direction when you reach top or bottom edge
	if (y3 > windowHeight /*0 > 0*/ || y3 < -windowHeight + rsize /*0 < -25*/)        y3step = -y3step;

	// Actually move the square
	x3 += x3step;    y3 += y3step;

	// Check bounds. This is in case the window is made smaller while the rectangle is //bouncing and the rectangle suddenly finds itself outside the new clipping volume

	if (x3 >(windowWidth - rsize + x3step))        x3 = windowWidth - rsize - 1;
	else if (x3 < -(windowWidth + x3step))	x3 = -windowWidth - 1;

	if (y3 >(windowHeight + y3step))        y3 = windowHeight - 1;
	else if (y3 < -(windowHeight - rsize + y3step))	y3 = -windowHeight + rsize - 1;
#pragma endregion

#pragma region moving fun object 4
	// Reverse direction when you reach left or right edge
	if (x4 > windowWidth - rsize /*0 > -25*/ || x4 < -windowWidth /*0 < -25*/)        x4step = -x4step; //rsize=25 , windowWidth=0 , xstep=1.0f

																									  // Reverse direction when you reach top or bottom edge
	if (y4 > windowHeight /*0 > 0*/ || y4 < -windowHeight + rsize /*0 < -25*/)        y4step = -y4step;

	// Actually move the square
	x4 += x4step;    y4 += y4step;

	// Check bounds. This is in case the window is made smaller while the rectangle is //bouncing and the rectangle suddenly finds itself outside the new clipping volume

	if (x4 >(windowWidth - rsize + x4step))        x4 = windowWidth - rsize - 1;
	else if (x4 < -(windowWidth + x4step))	x4 = -windowWidth - 1;

	if (y4 >(windowHeight + y4step))        y4 = windowHeight - 1;
	else if (y4 < -(windowHeight - rsize + y4step))	y4 = -windowHeight + rsize - 1;
#pragma endregion

#pragma region moving fun object 4
	// Reverse direction when you reach left or right edge
	if (x5 > windowWidth - rsize /*0 > -25*/ || x5 < -windowWidth /*0 < -25*/)        x5step = -x5step; //rsize=25 , windowWidth=0 , xstep=1.0f

																										// Reverse direction when you reach top or bottom edge
	if (y5 > windowHeight /*0 > 0*/ || y5 < -windowHeight + rsize /*0 < -25*/)        y5step = -y5step;

	// Actually move the square
	x5 += x5step;    y5 += y5step;

	// Check bounds. This is in case the window is made smaller while the rectangle is //bouncing and the rectangle suddenly finds itself outside the new clipping volume

	if (x5 >(windowWidth - rsize + x5step))        x5 = windowWidth - rsize - 1;
	else if (x5 < -(windowWidth + x5step))	x5 = -windowWidth - 1;

	if (y5 >(windowHeight + y5step))        y5 = windowHeight - 1;
	else if (y5 < -(windowHeight - rsize + y5step))	y5 = -windowHeight + rsize - 1;
#pragma endregion

		// Redraw the scene with new coordinates
		glutPostRedisplay();
		glutTimerFunc(33, TimerFunction, 1);
}

