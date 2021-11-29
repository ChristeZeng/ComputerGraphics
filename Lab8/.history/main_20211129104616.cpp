#include "Car.h"

#define Pi 3.1415926
/*星球的公转*/
GLfloat fEarth        = 2.0f;
GLfloat fMoon         = 24.0f;
GLfloat fSun          = 2.0f;
GLfloat fMerrcury     = 5.0f;
GLfloat fMars         = 6.0f;
GLfloat fMarsSate1    = 20.0f;
GLfloat fMarsSate2    = 0.0f;

/*星球的自传*/
GLfloat Day;
GLfloat EarthYear;

/*Lookat函数参数*/
GLdouble eyex = 0.0, eyey = 0.0, eyez = 12;
GLdouble dx = 0.0, dy = 0.0, dz = -1.0;
GLdouble centerx, centery, centerz;
GLdouble upx, upy = 1, upz;
GLdouble radius;

/*公转轴*/
GLfloat rx = 0.0, ry = 1, rz = 0.1;

/*鼠标宏定义*/
bool isLeftMousePress;
float MouseX;
float MouseY;
float ViewX = 0;
float ViewY = 0;

void setLight(){
    GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; //光源的位置在世界坐标系圆心，齐次坐标形式
    GLfloat sun_light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f}; //RGBA模式的环境光，为0
    GLfloat sun_light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f}; //RGBA模式的漫反射光，全白光
    GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  //RGBA模式下的镜面光 ，全白光
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);     
    glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);  
    glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);   
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);     

    //开启灯光
    glEnable(GL_LIGHT0);    
    glEnable(GL_LIGHTING);   
    glEnable(GL_DEPTH_TEST);
//     GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
//     glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//     glEnable(GL_LIGHTING); //启用光源
//     glEnable(GL_LIGHT0);   //使用指定灯光
}

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
    gluPerspective(60.0f, (float)width / (float)height, 0.1f, 1000.0f);
    //设置完成后切换到模型视图矩阵开始画图
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, eyex + dx, eyey + dy, eyez + dz, upx, upy, upz);
    setLight();
}

void material_planet()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的环境光颜色
	GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的漫反射光颜色
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };   //定义材质的镜面反射光颜色
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void DisplaySun() {
    glPushMatrix();
    /*材质*/
    // GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的环境光颜色，为0
    // GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的漫反射光颜色，为0
    // GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，为0
    // GLfloat sun_mat_emission[] = {0.8f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射广颜色，为偏红色
    // GLfloat sun_mat_shininess   = 0.0f;        
    // glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);    
    // glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);   
    // glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);    
    // glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);   
    // glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);   
    /*绘制*/
    //glColor3f(1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0, 1.0, 0.0);
    glutSolidSphere(1.5f, 20, 20);
    glPopMatrix();
}

void DisplayMercury() {
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    
    glRotatef(atan(ry / (rz + 1.0)) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 3.0, 100, 100);
    glRotatef(-atan(ry / (rz + 1.0))* 180 / Pi, -1.0, 0.0, 0.0);

    glRotatef(fMerrcury, rx, ry, rz + 1.0);   
    glTranslatef(3.0f, 0.0f, 0.0f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();
}

void DisplayEarthAndMoon() {
    glPushMatrix();
    //glColor3f(0.0f, 0.0f, 1.0f);
    GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 1.0f, 1.0f};  //定义材质的环境光颜色，骗蓝色
    GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};  //定义材质的漫反射光颜色，偏蓝色
    GLfloat earth_mat_specular[] = {1.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
    GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射光颜色，为0
    GLfloat earth_mat_shininess   = 30.0f;       
    glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);   
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);    
    glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);     
    glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);   
    glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
    /*画地球*/
    //画星轨
    glRotatef(atan(ry / rz) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 6.0, 100, 100);
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
    glutSolidTorus(0.01, 1.5, 100, 100);
    glRotatef(-atan(1.0 / 0.3)* 180 / Pi, -1.0, 0.0, 0.0);

    glRotatef(fMoon, 0.0, 1.0, 0.3);
    glTranslatef(1.5f, 0.0f, 0.0f);
    glRotatef(Day, 0.0f, 1.0f, 0.0f);

    
    glutSolidSphere(0.2f, 20, 20);

    glPopMatrix();
}

void DisplayMars() {
    glPushMatrix();
    glColor3f(1.0f, 0.647f, 0.0f);
    /*画*/
    //画星轨
    glRotatef(atan(ry / (rz + 0.5)) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 5.0, 100, 100);
    glRotatef(-atan(ry / (rz + 0.5))* 180 / Pi, -1.0, 0.0, 0.0);
    //公转
    glRotatef(fMars, rx, ry, rz + 0.5);      
    glTranslatef(5.0f, 0.0f, 0.0f);
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
    glutSolidTorus(0.01, 1.5, 100, 100);
    glRotatef(-atan(1.0 / 0.3)* 180 / Pi, -1.0, 0.0, 0.0);
    glRotatef(fMarsSate1, 0.0, 1.0, 0.3);
    glTranslatef(1.5f, 0.0f, 0.0f);
    glRotatef(Day, 0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.2f, 20, 20);
    glPopMatrix();

    glColor3f(0.5f, 0.5f, 0.0f);
    glRotatef(atan(1.0 / 1.0) * 180 / Pi, -1.0, 0.0, 0.0);
    glutSolidTorus(0.01, 0.7, 100, 100);
    glRotatef(-atan(1.0 / 1.0)* 180 / Pi, -1.0, 0.0, 0.0);
    glRotatef(fMarsSate2, 0.0, 1.0, 1.0);
    glTranslatef(0.7f, 0.0f, 0.0f);
    glRotatef(Day, 0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.15f, 20, 20);

    glPopMatrix();
}

void DisplayCar(){
    glPushMatrix();
    glRotatef(fMerrcury + 40, rx, ry, rz + 1.0);   
    glTranslatef(4.0f, 0.0f, 0.0f);

    glRotatef(-180, 0.0, 1.0, 0.0);
    OBJLoader objLoader("Car.obj");
    objLoader.LSystem("0", 3);
    float radius = 0.1;
    float bradius = 2.0;
    objLoader.Sweeping(radius, bradius);
    objLoader.Sweeping2();
    objLoader.DrawOBJ();
    glPopMatrix();
}
void Display() {
    //清理缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //设置完成后切换到模型视图矩阵开始画图
    glMatrixMode(GL_MODELVIEW);
    //重新设置LookAt函数
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, eyex + dx, eyey + dy, eyez + dz, upx, upy, upz);
    //绘制各星球
    DisplaySun();
    DisplayEarthAndMoon();
    DisplayMercury();
    DisplayMars();
    DisplayCar();
    // glRotatef(-180, 0.0, 1.0, 0.0);
    // OBJLoader objLoader("Car.obj");
    // objLoader.LSystem("0", 3);
    // float radius = 0.1;
    // float bradius = 2.0;
    // objLoader.Sweeping(radius, bradius);
    // objLoader.Sweeping2();
    // objLoader.DrawOBJ();
    //刷新与交换缓冲区
    glFlush();
    glutSwapBuffers();
}

void Idle() {
    //设置自转速度
    Day += 1.0;
    Day = Day >= 360 ? (Day - 360) : Day; 
    //设置公转速度
    fEarth = fEarth >= 360 ? (fEarth - 360) : (fEarth + 0.3f);
    fMoon  = fMoon  >= 360 ? (fMoon - 360) : (fMoon  + 2.4f);
    fMerrcury  = fMerrcury  >= 360 ? (fMerrcury - 360) : (fMerrcury + 0.4f);
    fMars  = fMars  >= 360 ? (fMars - 360) : (fMars  + 0.5f);
    fMarsSate1  = fMarsSate1  >= 360 ? (fMarsSate1 - 360) : (fMarsSate1  + 3.0f);
    fMarsSate2  = fMarsSate2  >= 360 ? (fMarsSate2 - 360) : (fMarsSate2  + 2.8f);
    //重新显示
    Display();
}

void GetInputKey(unsigned char key, int x, int y) {
    if(key == 'w') {
        eyex += dx * 0.1;
	    eyez += dz * 0.1;
        glLoadIdentity();
        gluLookAt(eyex, eyey, eyez, eyex + dx, eyey + dy, eyez + dz, upx, upy, upz);
    }
    else if(key == 's') {
        eyex -= dx * 0.1;
        eyez -= dz * 0.1;
        glLoadIdentity();
        gluLookAt(eyex, eyey, eyez, eyex + dx, eyey + dy, eyez + dz, upx, upy, upz);
    }
    else if(key == 'a') {
        eyex += dz * 0.1;
        eyez -= dx * 0.1;
        glLoadIdentity();
        gluLookAt(eyex, eyey, eyez, eyex + dx, eyey + dy, eyez + dz, upx, upy, upz);
    }
    else if(key == 'd') {
        eyex -= dz * 0.1;
        eyez += dx * 0.1;
        glLoadIdentity();
        gluLookAt(eyex, eyey, eyez, eyex + dx, eyey + dy, eyez + dz, upx, upy, upz);
    }
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
        ViewX += (x - MouseX) * 0.01f; 
        ViewY = (y - MouseY) * 0.01f; 
        MouseX = x;
        MouseY = y;
    }

    dx = sin(ViewX);
    dz = -cos(ViewX);
    dy -= ViewY;
    //重新设置LookAt函数
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, eyex + dx, eyey + dy, eyez + dz, upx, upy, upz);
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
    glutCreateWindow("DreamCar");
    //设置正确投影的函数
    glutReshapeFunc(Reshape);
    //设置显示函数
    glutDisplayFunc(Display);
    //设置空闲时期执行函数
    glutIdleFunc(&Idle);
    //处理键盘输入
    glutKeyboardFunc(GetInputKey);
    //处理鼠标点击
    glutMouseFunc(GetInputMouse);
    //处理鼠标移动
    glutMotionFunc(GetMotionMouse);
    //启用深度测试
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
    glutMainLoop();
    return 0;
}