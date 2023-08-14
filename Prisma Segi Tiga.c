/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <windows.h>
#include <GL/glut.h>

/* Global variables */
char title[] = "Prisma Segi Tiga";

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
int prevMouseX = 0;
int prevMouseY = 0;

/* Initialize OpenGL Graphics */
void initGL() 
{
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Pencahayaan
    GLfloat lightPos[]  = { 0.0f, 0.0f, 1.0f, 0.0f };
    GLfloat lightAmb[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiff[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);	
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
float _angle = 60.0f;
void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);                          // To operate on model-view matrix

// Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();                                    // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -6.0f);                     // Move right and into the screen
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

glBegin(GL_QUADS);                                       // Begin drawing the color cube with 6 quads
// Bagian Persegi Bawah
glColor3f(1.0f, 0.0f, 0.0f);    // Red
glVertex3f(-1.0f, -1.0f, 1.0f); // Titik 1 (bawah)
glVertex3f(1.0f, -1.0f, 1.0f);  // Titik 2 (bawah)
glVertex3f(1.0f, 1.0f, 1.0f);   // Titik 3 (bawah)
glVertex3f(-1.0f, 1.0f, 1.0f);  // Titik 4 (bawah)
// Titik Atas
glColor3f(0.0f, 0.0f, 1.0f);    // Blue
glVertex3f(0.0f, 1.0f, -1.0f);  // Titik 1 (atas)
glVertex3f(0.0f, 1.0f, -1.0f);	// Titik 2 (atas)
// Bagian Segitiga Atas
glColor3f(0.0f, 1.0f, 1.0f);    // Green
glVertex3f(-1.0f, 1.0f, 1.0f);  // Titik 1 (atas)
glVertex3f(1.0f, 1.0f, 1.0f);   // Titik 2 (atas)
glVertex3f(0.0f, 1.0f, -1.0f);  // Titik 3 (atas)
// Bagian Segitiga Bawah
glColor3f(0.0f, 1.0f, 0.0f);    // Green
glVertex3f(-1.0f, -1.0f, 1.0f); // Titik 1 (bawah)
glVertex3f(1.0f, -1.0f, 1.0f);  // Titik 2 (bawah)
glColor3f(0.0f, 0.0f, 1.0f);    // Blue
glVertex3f(0.0f, -1.0f, -1.0f); // Titik 3 (bawah)
// Jajar Genjang Kanan
glColor3f(0.0f, 1.0f, 0.0f);    // Green 
glVertex3f(1.0f, 1.0f, 1.0f);   // Titik 1 (kanan)
glColor3f(1.0f, 0.5f, 0.0f);    // Orange
glVertex3f(0.0f, 1.0f, -1.0f);  // Titik 2 (kanan)
glColor3f(0.0f, 0.0f, 1.0f);    // Blue
glVertex3f(0.0f, -1.0f, -1.0f); // Titik 3 (kanan)
glColor3f(1.0f, 0.0f, 0.0f);    // Red
glVertex3f(1.0f, -1.0f, 1.0f);  // Titik 4 (kanan)
//Jajar Genjang Kiri
glColor3f(0.0f, 1.0f, 0.0f);    // Green
glVertex3f(-1.0f, -1.0f, 1.0f); // Titik 1 (kiri)
glColor3f(1.0f, 0.5f, 0.0f);    // Orange
glVertex3f(-1.0f, 1.0f, 1.0f);  // Titik 2 (kiri)
glColor3f(0.0f, 0.0f, 1.0f);    // Blue
glVertex3f(0.0f, 1.0f, -1.0f);  // Titik 3 (kiri)
glColor3f(1.0f, 0.0f, 0.0f);    // Red
glVertex3f(0.0f, -1.0f, -1.0f); // Titik 4 (kiri)
glEnd();                                                // End of drawing color-cube
glutSwapBuffers();                                      // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)             // GLsizei for non-negative integer
{
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
	
	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

// Prevew mouse
void mouseMove(int x, int y)
{
	int deltaX = x - prevMouseX;
	int deltaY = y - prevMouseY;
	
	rotationX += deltaY;
	rotationY += deltaX;
	
	prevMouseX = x;
	prevMouseY = y;
	
	glutPostRedisplay();	
}

void mouseButton(int button, int state, int x, int y) 
{
	if (state == GLUT_DOWN) 
        {
		prevMouseX = x;
		prevMouseY = y;
	}
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) 
{
	glutInit(&argc, argv);                                    // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
	glutInitWindowSize(1280, 720);                            // Set the window's initial width & height
	glutInitWindowPosition(100, 100);                         // Position the window's initial top-left corner
	glutCreateWindow(title);                                  // Create window with the given title
	glutDisplayFunc(display);                                 // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);                                 // Register callback handler for window re-size event
	glutMotionFunc(mouseMove);                                
	glutMouseFunc(mouseButton);
	initGL();                                                 // Our own OpenGL initialization
	glutMainLoop();                                           // Enter the infinite event-processing loop
	return 0;
}

