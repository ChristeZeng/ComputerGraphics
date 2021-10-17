#include <GL/glut.h>
#include <iostream>

/*Time*/
GLfloat fEarth        = 2.0f;
GLfloat fMoon         = 24.0f;
GLfloat fSun          = 2.0f;

GLfloat Day;
GLfloat EarthYear;

/*Lookat*/
GLdouble eyex, eyey, eyez = 10;
GLdouble centerx, centery, centerz;
GLdouble upx, upy = 1, upz;

/*gongzhuan*/
GLfloat rx = 0.0, ry = 1, rz = 1;

void Reshape(int width, int height) {
    //修改视口
    glViewport(0, 0, width, height);
    /*  
    glMatrixMode()命令将当前矩阵设置成参数所指定的模式，以满足不同绘图所需执行的矩阵变换。
    一般而言，在需要绘制出对象或要对所绘制对象进行几何变换时，需要将变换矩阵设置成模型视图模式；
    而当需要对绘制的对象设置某种投影方式时，则需要将变换矩阵设置成投影模式；
    只有在进行纹理映射时，才需要将变换矩阵设置成纹理模式。
    对投影矩阵堆栈应用随后的矩阵操作, 为我们的场景增加透视。
    */
    glMatrixMode(GL_PROJECTION);
    //重置当前指定的矩阵为单位矩阵
    glLoadIdentity();
    //gluPerspective定义的就是相机的内在镜头参数
    gluPerspective(60.0f, (float)width / (float)height, 1.0f, 20.0f);
    //设置完成后切换到模型视图矩阵开始画图
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //
    gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void DisplaySun() {
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0, 1.0, 0.0);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();
}

void DisplayMercury() {
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(Day, 0.0, 1.0, 0.0);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();
}

void DisplayEarthAndMoon() {
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);

    glRotatef(fEarth, rx, ry, rz);       //gong
    glTranslatef(5.0f, 0.0f, 0.0f);
    //glRotatef(Day, 0.0, 1.0, 0.0);       //zizhuan
    glutSolidSphere(0.5f, 20, 20);

    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(fMoon, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.4f, 0.0f, 0.0f);
    //glRotatef(Day, 0.0f, 1.0f, 0.0f);

    
    glutSolidSphere(0.2f, 20, 20);

    glPopMatrix();
}


void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

    DisplaySun();
    DisplayEarthAndMoon();

    glFlush();
    glutSwapBuffers();

}

void Idle() {
    Day += 1.0;
    Day = Day >= 360 ? (Day - 360) : Day; 
    fEarth = fEarth >= 360 ? 2.0f : (fEarth + 0.03f);
    fMoon  = fMoon  >= 360 ? 24.0 : (fMoon  + 0.24f);
    Display();
}

void GetInputKey(unsigned char key, int x, int y) {
    if(key == 'w')
        eyez -= 2;
    else if(key == 's')
        eyez += 2;
    else if(key == 'a')
        centerx -= 2;
    else if(key == 'd')
        centerx += 2;
}

int main(int argc, char* argv[]) {
    
    //初始化GLUT库
    glutInit(&argc, argv);
    //指定显示模式，使用双缓冲区
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //设置窗口位置
    glutInitWindowPosition(200, 200);
    //设置窗口大小
    glutInitWindowSize(720, 480);
    //新建窗口并命名
    glutCreateWindow("SolarSystem");
    //设置正确投影的函数
    glutReshapeFunc(Reshape);
    //设置显示函数
    glutDisplayFunc(Display);
    //设置空闲时期执行函数
    glutIdleFunc(&Idle);
    //
    glutKeyboardFunc(GetInputKey);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
    glutMainLoop();
    return 0;
}