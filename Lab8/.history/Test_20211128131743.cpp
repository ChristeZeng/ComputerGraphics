#include <GL/glut.h>
#include <math.h>
#include "Car.h"

static float angle = 0.0;//angle绕y轴的旋转角
static float x = 0.0f, y = 1.75f, z = 5.0f;//相机位置
static float lx = 0.0f, ly = 0.0f, lz = -1.0f;//视线方向，初始设为沿着Z轴负方向

//定义观察方式
void changeSize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);    //投影变换
	glLoadIdentity();
	//设置视口为整个窗口大小
	glViewport(0, 0, w, h);
	//设置可视空间
	gluPerspective(45, 1.0f*w / h, 1, 1000); //角度45， 窗口纵横比， 眼睛所及距离（近和远）

	glMatrixMode(GL_MODELVIEW);     //模型变换
	glLoadIdentity();
	//相机（人眼）位置， 眼睛看的点（相机位置+视线方向）， 观察者本身方向（角度，比如正立）
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

//绘制雪人
void drawSnowMan()
{
	glColor3f(1.0f, 1.0f, 1.0f);    //白色

	//画身体
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20); //画圆

	//画头
	glTranslatef(0.0f,1.0f,0.0f);
	glutSolidSphere(0.25f,20,20);   //画圆

	//画眼睛
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);  //黑色
	glTranslatef(0.05f,0.10f,0.18f);
	glutSolidSphere(0.05f,10,10);   //画圆
	glTranslatef(-0.1f,0.0f,0.0f);
	glutSolidSphere(0.05f,10,10);   //画圆
	glPopMatrix();

	//画鼻子
	glColor3f(1.0f,0.5f,0.5f);  //有点像粉色
	glRotatef(0.0f,1.0f,0.0f,0.0f);
	glutSolidCone(0.08f,0.5f,10,2); //画圆锥  参数：：半径，高
}

//渲染场景，画地面，画雪人
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲

	//画地面
	glBegin(GL_QUADS);  //四边形
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

    OBJLoader.Load("car.obj");
    OBJLoader.Draw();
	//画36个雪人
	for (int i= -3; i< 3; i++)
		for (int j = -3; j< 3; j++) {
			glPushMatrix(); //把当前矩形压栈，这样后面的操作不会影响到原矩形（标准位置/变换的矩形）
			//问题：那现在操作的是哪个矩形呢？？压栈保存了原矩形，但是当前的矩形还是标准（原）矩形，可以操作
			glTranslatef(i*10.0, 0, j*10.0);
			drawSnowMan();  //绘制雪人
			glPopMatrix();  //当把标准矩形移到了预期位置，再把原矩形弹栈恢复，给下次操作提供标准矩形
		}
	glutSwapBuffers();  //交换缓冲区
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

int main(int argc,char **argv)
{
    //初始化，建立窗口
	glutInit(&argc, argv);
	//深度缓冲，双缓冲，颜色缓冲
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutCreateWindow("snowman test");

	glEnable(GL_DEPTH_TEST);        //开启深度缓冲区
	glutKeyboardFunc(inputKey);     //键盘响应事件
	glutDisplayFunc(renderScene);   //绘制回调函数
	glutIdleFunc(renderScene);      //闲置时回调函数
	glutReshapeFunc(changeSize);    //调整窗口大小回调函数
	glutMainLoop();
    return 0;
}
//有待深入学习，理解
//glClear()的清楚深度缓冲区啥意思
//具体的绘图细节，需要搭建模型，具体设计
//关于矩形的弹出弹入
//changeSize的用法，窗口回调函数
