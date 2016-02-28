
// Reference: http://www.glprogramming.com/red/chapter01.html
#undef STATIC

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stdlib.h>

static GLfloat spin = 0.0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

#if defined(STATIC)
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
	glEnd();
	glFlush();
#else
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);
	glPopMatrix();
	glutSwapBuffers();

#endif

}

void spinDisplay(void){
	spin = spin + 2.0;
	if ( spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
#if defined(STATIC)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
#else
	glShadeModel(GL_FLAT);
#endif

}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
	switch(button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
				glutIdleFunc(spinDisplay);
			break;
		case GLUT_MIDDLE_BUTTON:
			if (state== GLUT_DOWN)
				glutIdleFunc(NULL);
			break;
		default:
			break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();	
	return 0;

}
