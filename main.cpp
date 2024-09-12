#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

// Funciones globales
void mostrar(void);
void inicializacion(void);
void teclado(unsigned char c, int i, int arg);
inline int customRound(const float a) { return int(a + 0.5); }

// Variables globales
int anchopantalla = 600, altopantalla = 800;

// Set a pixel
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// DDA algorithm
void lineDDA(int x0, int y0, int xEnd, int yEnd) {
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);
    setPixel(customRound(x), customRound(y));
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        setPixel(customRound(x), customRound(y));
    }
}

// Bresenham algorithm
void lineBresenham(int x0, int y0, int xEnd, int yEnd) {
    int dx = abs(xEnd - x0);
    int dy = abs(yEnd - y0);
    int sx = (xEnd > x0) ? 1 : -1;
    int sy = (yEnd > y0) ? 1 : -1;
    int err = dx - dy;

    setPixel(x0, y0);

    while (x0 != xEnd || y0 != yEnd) {
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
        setPixel(x0, y0);
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(anchopantalla, altopantalla);
    glutCreateWindow("Algoritmo DDA");

    inicializacion();
    glutDisplayFunc(mostrar);
    glutKeyboardFunc(teclado); // Registra la función de teclado
    glutMainLoop();
    return 0;
}

void mostrar(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Lines, one next to the other
    glColor3f(1.0, 0.0, 0.0); // Rojo
    lineDDA(100, 100, 300, 500);

    glColor3f(0.0, 0.0, 1.0); // Azul
    lineBresenham(150, 100, 350, 500);

    glColor3f(2.0 / 255.0, 48.0 / 255.0, 32.0 / 255.0); // Verde
    glBegin(GL_LINES);
        glVertex2i(200, 100);
        glVertex2i(400, 500);


    glEnd();
    glFlush();
}

void inicializacion(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, anchopantalla, 0.0, altopantalla);
}

void teclado(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q') {
        exit(0); // Cierra la aplicación
    }

    // Esc key for exit
    if (key == 27) {
        exit(0);
    }
}

