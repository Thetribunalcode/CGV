#include <GL/glut.h>
#include <stdio.h>

typedef GLfloat point[3];
point vertex[] = {{-1.0, -0.5, 0.0}, {1.0, -0.5, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}; //
GLfloat color[4][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}};
int n; //

void draw_text(int x, int y, int z, char *s)
{
    int i;
    glRasterPos3f(x, y, z);
    for (i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void triangle(point a, point b, point c)
{
    glBegin(GL_POLYGON);
    glVertex3fv(a); //
    glVertex3fv(b); // 3 dimension not 2D
    glVertex3fv(c); //
    glEnd();        // forgot
}

void tetrahedron(point a, point b, point c, point d)
{
    glColor3fv(color[0]);
    triangle(a, b, c);
    glColor3fv(color[1]);
    triangle(a, b, d);
    glColor3fv(color[2]);
    triangle(a, c, d);
    glColor3fv(color[3]);
    triangle(b, c, d);
}

void divide_tetra(point a, point b, point c, point d, int m)
{
    int i;
    point mid[6];
    if (m > 0)
    {
        for (i = 0; i < 3; i++)
        {
            mid[0][i] = (a[i] + b[i]) / 2.0; // float not int
            mid[1][i] = (a[i] + c[i]) / 2.0; //
            mid[2][i] = (a[i] + d[i]) / 2.0; //
            mid[3][i] = (b[i] + c[i]) / 2.0;
            mid[4][i] = (c[i] + d[i]) / 2.0;
            mid[5][i] = (b[i] + d[i]) / 2.0;
        }
        divide_tetra(a, mid[0], mid[1], mid[2], m - 1);
        divide_tetra(mid[0], b, mid[3], mid[5], m - 1);
        divide_tetra(mid[1], mid[3], c, mid[4], m - 1);
        divide_tetra(mid[2], mid[5], mid[4], d, m - 1);
    }
    else
    {
        tetrahedron(a, b, c, d);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0); // 4 param
    divide_tetra(vertex[0], vertex[1], vertex[2], vertex[3], n);
    draw_text(10, 20, 0.0, "1BI20CS160");
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h); // not capital Port, only port
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // forgot
    if (w <= h)
    {
        glOrtho(-1.0, 1.0, -1.0 * ((GLfloat)h / (GLfloat)w), 1.0 * ((GLfloat)w / (GLfloat)h), -1.0, 1.0); // start=-1.0, end=1.0... h/w and not w/h
    }
    else
        glOrtho(-1.0 * ((GLfloat)h / (GLfloat)w), 1.0 * ((GLfloat)h / (GLfloat)w), -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay(); // forgot function name
}

void myinit()
{
}

void main(int argc, char **argv)
{
    printf("Enter number of divisions");
    scanf("%d", &n);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE); // mode and not window, all variables are GLUT
    glutInitWindowSize(400, 400);
    glutCreateWindow("tetra");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST); // forgot
    glutMainLoop();
}