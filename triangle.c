#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLfloat triangle[3][3] = {{100.0, 250.0, 175.0}, {100.0, 100.0, 300.0}, {0.0, 0.0, 1.0}};
GLfloat rotatemat[3][3] = {{0}, {0}, {0}};
GLfloat arbitrary_x = 0.0;
GLfloat arbitrary_y = 0.0;
GLfloat ang;
GLfloat result[3][3] = {{0}, {0}, {0}};

void multiply()
{
    int i, j, k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            result[i][j] = 0;
            for (k = 0; k < 3; k++)
            {
                result[i][j] += rotatemat[i][k] * triangle[k][j];
            }
        }
}

void rotate()
{
    int m, n;
    m = arbitrary_x * (1 - cos(ang)) + arbitrary_y * (sin(ang));
    n = arbitrary_y * (1 - cos(ang)) - arbitrary_x * (cos(ang));
    rotatemat[0][0] = cos(ang);
    rotatemat[0][1] = -sin(ang);
    rotatemat[0][2] = m;
    rotatemat[1][0] = sin(ang);
    rotatemat[1][1] = cos(ang);
    rotatemat[1][2] = n;
    rotatemat[2][0] = 0;
    rotatemat[2][1] = 0;
    rotatemat[2][2] = 1;
    multiply();
}

void tri()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(triangle[0][0], triangle[1][0]);
    glVertex2f(triangle[0][1], triangle[1][1]);
    glVertex2f(triangle[0][2], triangle[1][2]);
    glEnd();
}

void rotatetri()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(result[0][0], result[1][0]);
    glVertex2f(result[0][1], result[1][1]);
    glVertex2f(result[0][2], result[1][2]);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    tri();
    rotatetri();
    glFlush();
}

void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    int ch;
    printf("Enter your choice\n1.Rotation about origin\n2.Rotation about a fixed point\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        printf("Enter the rotation angle in degree: ");
        scanf("%f", &ang);
        ang = (3.14 * ang) / 180;
        rotate();
        break;
    case 2:
        printf("Enter the fixed points: ");
        scanf("%f%f", &arbitrary_x, &arbitrary_y);
        printf("Enter the rotation angle in degree: ");
        scanf("%f", &ang);
        ang = (3.14 * ang) / 180;
        rotate();
        break;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("triangle");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}