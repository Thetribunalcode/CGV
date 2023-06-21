#include <stdio.h>
#include <GL/glut.h>

GLfloat vertices[][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};
GLfloat normals[][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};
GLfloat colors[][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(colors[a]);
    glNormal3fv(normals[a]);
    glVertex3fv(vertices[a]);

    glColor3fv(colors[b]);
    glNormal3fv(vertices[b]);
    glVertex3fv(colors[b]);

    glColor3fv(colors[c]);
    glNormal3fv(vertices[c]);
    glVertex3fv(colors[c]);

    glColor3fv(colors[d]);
    glNormal3fv(vertices[d]);
    glVertex3fv(colors[d]);

    glEnd();
}

void color()
{
    polygon(0, 3, 2, 1);
    polygon(2, 3, 7, 6);
    polygon(0, 4, 7, 3);
    polygon(4, 5, 6, 7);
    polygon(0, 1, 5, 4);
}
static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 2;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    color();
    glFlush();
    glSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if (btn = GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
}

void spincube()
{
    theta[axis] += 1.0;
    if (theta[axis] > 360.0)
        theta[axis] -= 360.0;
    glutPostRedisplay();
}

void main(int argc, char **argv)
{
}