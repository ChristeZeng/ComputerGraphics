#include <GL/glut.h>
#include <iostream>

int main(int argc, char* argv[])
{
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