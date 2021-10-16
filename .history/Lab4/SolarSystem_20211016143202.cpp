#include <GL/glut.h>
#include <iostream>

void Reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (float)width / (float)height, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

    gultMainLoop();
    return 0;
}