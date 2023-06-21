#include <stdio.h>
#include <GL/glut.h>
#include <string.h>

int x1, y1, x2, y2;
int endpoints[8][4];
int n;

void draw_pixel(int x, int y)
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS); // GL_POINTS not point
    glVertex2i(x, y);
    glEnd();
}
void draw_text(int x, int y, int z, char *s)
{
    int i;
    glRasterPos3f(x, y, z);
    for (i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void draw_line(int x1, int y1, int x2, int y2)
{
    int p, i, dx, dy;
    int x, y;
    int inc1, inc2, incx, incy;
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    incx = 1;
    incy = 1;
    if (y2 < y1)
        incy = -1;
    if (x2 < x1)
        incx = -1;
    x = x1;
    y = y1;
    if (dx > dy)
    {
        draw_pixel(x, y);
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        p = 2 * dy - dx;
        for (i = 0; i < dx; i++)
        {
            if (p >= 0)
            {
                y += incy;
                p += inc1;
            }
            else
            {
                p += inc2;
            }
            x += incx;
            draw_pixel(x, y);
        }
    }
    else
    {
        draw_pixel(x, y);
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        p = 2 * dx - dy;
        for (i = 0; i < dy; i++)
        {
            if (p >= 0)
            {
                x += incx;
                p += inc1;
            }
            else
                p += inc2;
            y += incy;
            draw_pixel(x, y);
        }
    }
}
char *con(char *res, char *s1, char *s2)
{
    char two[2] = ")";
    strcat(res, s1);
    strcat(res, ",");
    strcat(res, s2);
    strcat(res, two);
    return res;
}
void bresh()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    for (i = 0; i < n; i++)
    {
        draw_text(50.0, 299.0, 0.0, "1BI20CS160");
        x1 = endpoints[i][0];
        y1 = endpoints[i][1];
        x2 = endpoints[i][2];
        y2 = endpoints[i][3];
        char c1[10], c2[10], c3[10], c4[10];
        char res[15] = "(";
        char res2[15] = "(";

        sprintf(c1, "%d", x1);
        sprintf(c2, "%d", y1);
        sprintf(c3, "%d", x2);
        sprintf(c4, "%d", y2);

        draw_line(x1, y1, x2, y2);

        draw_text(x1 - 15, y1 - 15, 0.0, con(res, c1, c2));
        draw_text(x2 + 5, y2 + 5, 0.0, con(res2, c3, c4));

        glColor3f(1.0, 0.0, 0.0);

        glBegin(GL_LINES); // GL_LINES not line
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);

        glEnd();
        glFlush();
    }
}

void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
    int i;
    printf("Enter the number of lines\n");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &endpoints[i][0], &endpoints[i][1], &endpoints[i][2], &endpoints[i][3]);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(200, 200);
    glutCreateWindow("line");
    glutDisplayFunc(bresh);
    myInit();
    glutMainLoop();
}
