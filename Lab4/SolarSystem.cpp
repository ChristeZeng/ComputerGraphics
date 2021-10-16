#include <GL/glut.h>
#include <iostream>

float fEarth = 20.0f;    //地球绕太阳的旋转角度
float fMoon = 24.0f;    //月球绕地球的旋转角度

void Reshape(int width, int height) {
    //
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(180.0f, (float)width / (float)height, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -500.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(50.0f, 20, 20);

    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(23.27, 0.0, 0.0, 1.0);
    glRotatef(fEarth, 0.0, 1.0, 0.0);

    glTranslatef(200.0f, 0.0f, 0.0f);

    glutSolidSphere(20.0f, 20, 20);
    glPopMatrix();
    glPopMatrix();

    glRotatef(6.0f,1.0f,1.0f,1.0f);
    glRotatef(fMoon,0.0f,1.0f,0.0f);
    glColor3f(1.0f,1.0f,0.0f);

    glTranslatef(30.0f,0.0f,0.0f);
    glutSolidSphere(5.0f,20,20);
    glLoadIdentity();
    glFlush();
    glutSwapBuffers();

}

void Idle(void) {
    fEarth = fEarth > 360 ? 2.0f : (fEarth + 0.03f);
    fMoon  = fMoon  > 360 ? 24.0 : (fMoon  + 0.24f);
    Display();
}
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(720, 480);
    glutCreateWindow("SolarSystem");
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutIdleFunc(&Idle);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
    glutMainLoop();
    return 0;
}