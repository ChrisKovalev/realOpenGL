#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include<math.h>

constexpr auto SCREEN_WIDTH = 1980;;
constexpr auto SCREEN_HEIGHT = 1080;

void DrawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
void DrawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
void DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // do some initlaizations

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        DrawCircle(500, 500, 0, 120, 400);
        DrawSquare(1000, 1000, 10, 10);
        DrawLine(50, 50, 200, 10, 50);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void DrawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides) {
    GLint numberOfVertices = numberOfSides + 2; //calculates the number of vertices -- including middle vertice since triangle built
    GLfloat doublePI = 2.0f * M_PI;

    GLfloat *circleVerticesX = new GLfloat[numberOfVertices];
    GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
    GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

    circleVerticesX[0] = x; //sets up center point for the circle
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;

    for(int i = 1; i < numberOfVertices; i++)
    {
        circleVerticesX[i] = x + (radius * cos(i * doublePI / numberOfSides));
        circleVerticesY[i] = y + (radius * sin(i * doublePI / numberOfSides));
        circleVerticesZ[i] = z; //2D shape
    }

    GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 3]; //*3 for x,y,z

    for (int i = 0; i < numberOfVertices; i++) {
        allCircleVertices[i * 3] = circleVerticesX[i]; //0 ---> x, 1 ---> y, 2 ---> z, 3 ----> x etc...
        allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
        allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
    glDisableClientState(GL_VERTEX_ARRAY); //DRAWS A TRIANGLE FAN FROM THE 3 VERTICES...
}

void DrawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    glBegin(GL_QUADS);

    glVertex2f(x + halfWidth, y + halfHeight);
    glVertex2f(x + halfWidth, y - halfHeight);
    glVertex2f(x - halfWidth, y - halfHeight);
    glVertex2f(x - halfWidth, y + halfHeight);

    glEnd();

}

void DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width) {
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
    glLineWidth(1);
}