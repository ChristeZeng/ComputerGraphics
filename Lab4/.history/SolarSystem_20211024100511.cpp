#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define Pi 3.1415926
/*星球的公转*/
GLfloat fEarth        = 2.0f;
GLfloat fMoon         = 24.0f;
GLfloat fSun          = 2.0f;
GLfloat fMerrcury     = 5.0f;

/*星球的自传*/
GLfloat Day;
GLfloat EarthYear;

/*Lookat函数参数*/
GLdouble eyex, eyey, eyez = 10;
GLdouble centerx, centery, centerz;
GLdouble upx, upy = 1, upz;
GLdouble radius;

/*公转轴*/
GLfloat rx = 0.0, ry = 1, rz = 0.1;

/*鼠标宏定义*/
bool isLeftMousePress;
float MouseX;
float MouseY;
float ViewX;
float ViewY;

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
    gluPerspective(60.0f, (float)width / (float)height, 0.1f, 100.0f);
    //设置完成后切换到模型视图矩阵开始画图
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void DisplaySun() {
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0, 1.0, 0.0);
    glutSolidSphere(1.5f, 20, 20);
    glPopMatrix();
}

void DisplayMercury() {
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    
    glRotatef(atan(ry / (rz + 1.0)) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 3.0, 64, 100);
    glRotatef(-atan(ry / (rz + 1.0))* 180 / Pi, -1.0, 0.0, 0.0);

    glRotatef(fMerrcury, rx, ry, rz + 1.0);   
    glTranslatef(3.0f, 0.0f, 0.0f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();
}

void DisplayEarthAndMoon() {
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    /*画地球*/
    //画星轨
    glRotatef(atan(ry / rz) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 6.0, 64, 100);
    glRotatef(-atan(ry / rz)* 180 / Pi, -1.0, 0.0, 0.0);
    //公转
    glRotatef(fEarth, rx, ry, rz);      
    glTranslatef(6.0f, 0.0f, 0.0f);
    //自转
    glPushMatrix();
    glRotatef(Day, 0.0, 1.0, 0.0);       //zizhuan
    glutSolidSphere(0.8f, 20, 20);
    glPopMatrix();

    /*画月球*/
    glColor3f(1.0f, 1.0f, 0.0f);
    //画星规
    glRotatef(atan(1.0 / 0.3) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 1.5, 64, 100);
    glRotatef(-atan(1.0 / 0.3)* 180 / Pi, -1.0, 0.0, 0.0);

    glRotatef(fMoon, 0.0, 1.0, 0.3);
    glTranslatef(1.5f, 0.0f, 0.0f);
    glRotatef(Day, 0.0f, 1.0f, 0.0f);

    
    glutSolidSphere(0.2f, 20, 20);

    glPopMatrix();
}

void DisplayAandB() {
    glPushMatrix();
    glColor3f(1.0f, 0.647f, 0.0f);
    /*画*/
    //画星轨
    glRotatef(atan(ry / (rz + 1.5)) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 6.0, 64, 100);
    glRotatef(-atan(ry / (rz + 1.5))* 180 / Pi, -1.0, 0.0, 0.0);
    //公转
    glRotatef(fEarth, rx, ry, rz + 1.5);      
    glTranslatef(6.0f, 0.0f, 0.0f);
    //自转
    glPushMatrix();
    glRotatef(Day, 0.0, 1.0, 0.0);       //zizhuan
    glutSolidSphere(0.6f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    /*画月球*/
    glColor3f(0.5f, 0.0f, 0.5f);
    //画星规
    glRotatef(atan(1.0 / 0.3) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 1.5, 64, 100);
    glRotatef(-atan(1.0 / 0.3)* 180 / Pi, -1.0, 0.0, 0.0);
    glRotatef(fMoon, 0.0, 1.0, 0.3);
    glTranslatef(1.5f, 0.0f, 0.0f);
    glRotatef(Day, 0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.2f, 20, 20);
    glPopMatrix();

    // glRotatef(atan(1.0 / 1.0) * 180 / Pi, -1.0, 0.0, 0.0);
    // glutSolidTorus(0.01, 1.5, 64, 100);
    // glRotatef(-atan(1.0 / 1.0)* 180 / Pi, -1.0, 0.0, 0.0);
    // glRotatef(fMoon + 0.02, 0.0, 1.0, 1.0);
    // glTranslatef(1.5f, 0.0f, 0.0f);
    // glRotatef(Day, 0.0f, 1.0f, 0.0f);
    // glutSolidSphere(0.15f, 20, 20);

    glPopMatrix();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

    DisplaySun();
    DisplayEarthAndMoon();
    DisplayMercury();
    DisplayAandB();

    glFlush();
    glutSwapBuffers();

}

void Idle() {
    Day += 1.0;
    Day = Day >= 360 ? (Day - 360) : Day; 
    fEarth = fEarth >= 360 ? (fEarth - 360) : (fEarth + 0.3f);
    fMoon  = fMoon  >= 360 ? (fMoon - 360) : (fMoon  + 2.4f);
    fMerrcury  = fMerrcury  >= 360 ? (fMerrcury - 360) : (fMoon  + 2.4f);
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

    //gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
    glutPostRedisplay();

}

void GetInputMouse(int button, int state, int x, int y) {

    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN)
            isLeftMousePress = true;
        else if (state == GLUT_UP)
            isLeftMousePress = false;
    }

    MouseX = x;
    MouseY = y;
}

void GetMotionMouse(int x, int y) {
    
    if(isLeftMousePress) {
        ViewX += (y - MouseY) * 0.1f;
        ViewY += (x - MouseX) * 0.1f;
        MouseX = x;
        MouseY = y;
    }

    float distance = sqrt(pow(eyex, 2) + pow(eyey, 2) + pow(eyez, 2));
    eyez = distance * sin(ViewX) * cos(ViewY);
    eyex = distance * sin(ViewX) * sin(ViewY);
    eyey = distance * cos(ViewX);
    glutPostRedisplay();
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
    //
    glutMouseFunc(GetInputMouse);
    //
    glutMotionFunc(GetMotionMouse);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
    glutMainLoop();
    return 0;
}