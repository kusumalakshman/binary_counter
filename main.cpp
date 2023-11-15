#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

int number = 0; // Global variable to store the current number

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(50, 550, 50, 450);

    glColor3f(0.0f, 0.0f, 0.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 1.0f, 1.0f);

        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Set the line width for the circuit pattern
    glLineWidth(1.0f);

    // Set the color for the circuit pattern
    glColor3f(0.0f, 0.5f, 0.0f); // Light gray color for the circuit elements

    // Draw the circuit pattern
    for (int i = 0; i < windowWidth; i += 10)
    {
        glBegin(GL_LINES);
        glVertex2f(i, 0);
        glVertex2f(i, windowHeight);
        glEnd();
    }

    for (int i = 0; i < windowHeight; i += 10)
    {
        glBegin(GL_LINES);
        glVertex2f(0, i);
        glVertex2f(windowWidth, i);
        glEnd();
    }

    // Draw rectangle border
    glBegin(GL_QUADS);
    glVertex2f(100, 100);
    glVertex2f(500, 100);
    glVertex2f(500, 400);
    glVertex2f(100, 400);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Draw circles
    float startX = 150.0f;
    float centerY = 250.0f;
    float radius = 40.0f;
    int numSegments = 100;
    float angleStep = 2.0f * 3.14159f / numSegments;

    for (int i = 0; i < 4; i++)
    {
        float centerX = startX + i * 100.0f;

        // Determine the color based on the binary digit
        int digit = (number >> (3 - i)) & 1;
        if (digit == 1)
            glColor3f(0.0f, 1.0f, 0.0f); // Red color for 1
        else
            glColor3f(1.0f, 0.0f, 0.0f); // Green color for 0

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY);
        for (int j = 0; j <= numSegments; j++)
        {
            float angle = j * angleStep;
            float x = centerX + radius * cos(angle);
            float y = centerY + radius * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();

        // Draw box below the circle
        float boxWidth = 25.0f;
        float boxHeight = 20.0f;
        float boxX = centerX - boxWidth / 2.0f;
        float boxY = centerY - radius - boxHeight - 10.0f;

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(boxX, boxY);
        glVertex2f(boxX + boxWidth, boxY);
        glVertex2f(boxX + boxWidth, boxY + boxHeight);
        glVertex2f(boxX, boxY + boxHeight);
        glEnd();
    }

    // Draw box below all the circles
    float totalWidth = 4 * 80.0f;
    float boxWidth = 50.0f;
    float totalBoxX = startX + totalWidth / 2.0f - boxWidth / 2.0f -10.0f;// Subtract 2 to move left
    float totalBoxY = 110.0f+20.0f;
    float boxHeight = 25.0f;

    glBegin(GL_QUADS);
    glVertex2f(totalBoxX, totalBoxY);
    glVertex2f(totalBoxX + boxWidth, totalBoxY);
    glVertex2f(totalBoxX + boxWidth, totalBoxY + boxHeight);
    glVertex2f(totalBoxX, totalBoxY + boxHeight);
    glEnd();



    // Display binary  from 0 to 16 inside each box
    glColor3f(0.0f, 0.0f, 0.0f);
    float textX = totalBoxX / 2.0f + 8.0f;
    float textY = totalBoxY + boxHeight / 2.0f + 42.0f;

    // Display each digit of the binary number
    for (int i = 0; i < 4; i++)
    {
        char digit = '0' + ((number >> (3 - i)) & 1);
        glRasterPos2f(textX + i * 100.0f, textY);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, digit);
    }

    // Display the decimal equivalent of the number
    glColor3f(0.0f, 0.0f, 0.0f);
    float textX1 = totalBoxX + 20.0f;
    float textY1 = totalBoxY + boxHeight / 2.0f - 4.5f;

    char text[3];
    sprintf(text, "%d", number);

    glRasterPos2f(textX1, textY1);

    for (int j = 0; text[j] != '\0'; j++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[j]);
    }

    // Display the text "BINARY COUNTER" with a highlighted background
    char title[] ="BINARY COUNTER";
    float titleX = totalBoxX / 2 +72;
    float titleY = totalBoxY + boxHeight / 2.0f + 250.0f;
    float titleWidth = 200.0f;
    float titleHeight = 30.0f;

    // Draw the black background rectangle
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(titleX - 5, titleY - 20);
    glVertex2f(titleX + titleWidth -15, titleY - 20);
    glVertex2f(titleX + titleWidth -15, titleY + titleHeight + 5);
    glVertex2f(titleX - 5, titleY + titleHeight + 5);
    glEnd();

    // Draw the highlighted text
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(titleX, titleY);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(20,20);
    glVertex2f(20,120);
    glVertex2f(360,120);
    glVertex2f(360,20);
    glEnd();

    for (int i = 0; title[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    }

    // Display the options on three different lines
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(60.0f, 100.0f);
    const char* line1 = "Press 's' or 'S' to increment the number";
    const char* line2 = "Press 'r' or 'R' to decrement the number";
    const char* line3 = "Press 'z' or 'Z' to reset the number";

    // Render the first line
    for (int i = 0; line1[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line1[i]);
    }

    // Position the cursor for the second line
    glRasterPos2f(60.0f, 80.0f);

    // Render the second line
    for (int i = 0; line2[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line2[i]);
    }

    // Position the cursor for the third line
    glRasterPos2f(60.0f, 60.0f);

    // Render the third line
    for (int i = 0; line3[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line3[i]);
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 's' || key == 'S')
    {
        number = (number + 1) % 16; // Increment number and wrap around at 16
    }
    else if (key == 'r' || key == 'R')
    {
        number = (number - 1 + 16) % 16; // Decrement number and wrap around at 0
    }
    else if (key == 'z' || key == 'Z')
    {
        number = 0; // Reset number to 0
    }

    // Display the binary equivalent of the number
    printf("Binary: %d%d%d%d\n", (number >> 3) & 1, (number >> 2) & 1, (number >> 1) & 1, number & 1);

    glutPostRedisplay(); // Mark the window for redisplay
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Binary Counter");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set clear color to light gray

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Register the keyboard function

    glutMainLoop();

    return 0;
}
