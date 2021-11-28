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
}

void setLight(){
    GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光
}

//旋转相机，绕y轴旋转
void orientMe(float ang)
{
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
	//把所看的点（即视线方向上的点）理解为在一个圆上旋转，那设置的点的坐标应该是旋转的，通过圆半径计算坐标
	//！！！画图好理解！！！
}

//前后移动相机
void move_Front_Back(int direction)
{
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
    //同时移动相机和所看的点坐标，只用修改x和z，视线参数不用修改，
}

//左右移动相机，一定要画图理解
void move_Left_Right(int direction)
{
    x = x + direction*(lz)*0.1;
	z = z - direction*(lx)*0.1;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void move_High_Low(int direction)
{
    y = y + direction * 0.1;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

//键盘响应
void inputKey(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q':
		angle -= 0.03f;
		orientMe(angle);
		break;
	case 'e':               //q,e键调用相机旋转
		angle += 0.03f;
		orientMe(angle);
		break;
    case 'w':
        move_Front_Back(1);
		break;
    case 's':
        move_Front_Back(-1);
		break;
    case 'a':
        move_Left_Right(1);
        break;
    case 'd':
        move_Left_Right(-1);
        break;              //wasd调整相机前后左右移动
    case '1':
        move_High_Low(1);
        break;
    case '2':
        move_High_Low(-1);
        break;              //1,2键上下移动相机
	default:
		break;
	}
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
    glutSolidTorus(0.01, 3.0, 100, 100);
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

void Display() {
    //清理缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //设置完成后切换到模型视图矩阵开始画图
    glMatrixMode(GL_MODELVIEW);
    //重新设置LookAt函数
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
    //绘制各星球
    //DisplaySun();
    DisplayEarthAndMoon();
    DisplayMercury();
    DisplayMars();
    glRotatef(-180, 0.0, 1.0, 0.0);
    OBJLoader objLoader("Car.obj");
    objLoader.LSystem("0", 3);
    float radius = 0.1;
    float bradius = 2.0;
    objLoader.Sweeping(radius, bradius);
    objLoader.Sweeping2();
    objLoader.DrawOBJ();
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
        //printf("%f %f\n", eyex, eyex + dx);
        eyex += dz * 0.1;
        eyez -= dx * 0.1;
        printf("%f %f %f\n", eyex, eyey, eyez);
        printf("%f %f %f\n", eyex + dx, eyey + dy, eyez + dz);
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
        ViewX = (x - MouseX); 
        ViewY = (y - MouseY); 
        MouseX = x;
        MouseY = y;
    }

    centerx += ViewX * 0.1;
    centery -= ViewY * 0.1;
    //重新设置LookAt函数
    glLoadIdentity();
    gluLookAt (eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
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
    setLight();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
    glutMainLoop();
    return 0;
}