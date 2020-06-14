// TestAja.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<gl/glut.h>
#include <cmath>

float fx = 2.5, fy = 2, fz = 1.5; // koordinat posisi yang memandang (from where)
float tx = 0, ty = 0, tz = 0; // koordinat tujuan pandang (to where)
//float sudut = 0;
float yp = 0;

void LV()
{
    gluLookAt(fx, fy, fz, // melihat dari mana
        tx, ty, tz, // melihat ke mana
        0, 1, 0); // up vector
    GLfloat light_position[] = { 0, 50, 100, 0.0 }; // Posisi sumber cahaya
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_LIGHTING); //pencahayaan
    glEnable(GL_LIGHT0); //pencahayaan
    glEnable(GL_DEPTH_TEST);//efek 3d
    glEnable(GL_COLOR_MATERIAL); //mewarnai benda 
}

//Fungsi untuk meggambar Sphere planet dan matahari nya
void myWireSphere(GLfloat radius, int slices, int stacks) {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutWireSphere(radius, slices, stacks);
    glPopMatrix();
}

static int year = 0, day = 0; //Patokan perputaran / rotasi untuk planet

//Display func disini
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Menggambar matahahari
    glColor3f(1.0, 1.0, 0.0);
    myWireSphere(1.0, 15, 15);

    // Menggambar planet berwarna biru dengan jarak 2 radius dri matahari dengan garis putih sebagai axis nya
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    myWireSphere(0.2, 15, 15);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex3f(0, -0.3, 0);
    glVertex3f(0, 0.3, 0);
    glEnd();

    glPopMatrix();
    glLoadIdentity();
    LV();
    glFlush();
    glutSwapBuffers();
}

//Variabel untuk perputaran frame dari planet
static GLfloat u = 0.0;                 // curve parameter for comet pos
static GLfloat du = 0.1;                // amt to increment u each frame

void timer(int v) {
    yp += 10;
    if (yp >= 360) {
        yp = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

//Reshaping agar rapi
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

//Keyboard func dibawah ini
void keyboard1(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        fy += 2;
        break;
    case 's':
        fy -= 2;
        break;
    case 'a':
        fx -= 2;
        break;
    case 'd':
        fx += 2;
        break;
    case 'o':
        fz -= 2;
        break;
    case 'l':
        fz += 2;
        break;
    case 'z':
        u += du;
        day = (day + 1) % 360;
        year = (year + 2) % 360;
        break;
    case 'x':
        u -= du;
        day = (day - 1) % 360;
        year = (year - 2) % 360;
        break;
    case 27:
        exit(0);
        break;
    }
}
void keyboard2(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_PAGE_UP:
        tz -= 2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        tz += 2;
        break;
    case GLUT_KEY_RIGHT:
        tx += 2;
        break;
    case GLUT_KEY_LEFT:
        tx -= 2;
        break;
    case GLUT_KEY_UP:
        ty += 2;
        break;
    case GLUT_KEY_DOWN:
        ty -= 2;
        break;
    }
}

//MAIN
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("On a Comet");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard1);
    glutSpecialFunc(keyboard2);
    glutTimerFunc(100, timer, 0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
