#include <GL\glut.h>

float fEarth = 2.0f;//地球绕太阳的旋转角度
float fMoon = 24.0f;//月球绕地球的旋转角度

void Init()
{
　　glEnable(GL_DEPTH_TEST);//启用深度测试
　　glClearColor(0.0f,0.0f,0.0f,0.8f);//背景为黑色
}

void Reshape(int width, int height)
{
　　if (0==height)
　　{
　　　　height = 1;
　　}
　　
　　glViewport(0,0,width,height);//设置视区尺寸
　　glMatrixMode(GL_PROJECTION);//指定当前操作投影矩阵堆栈
　　glLoadIdentity();//重置投影矩阵

　　//指定透视投影的观察空间
　　gluPerspective(45.0f,(float)width/(float)height,1.0f,1000.0f);
　　glMatrixMode(GL_MODELVIEW);
　　glLoadIdentity();
}

void Display(void)
{
　　//清除颜色和深度缓冲区
　　glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
　　//指定当前操作模型师徒矩阵堆栈
　　glMatrixMode(GL_MODELVIEW);
　　//重置模型视图矩阵
　　glLoadIdentity();

　　//图形沿Z轴负向移动
　　glTranslatef(0.0f,0.0f,-500.0f);
　　//绘制太阳
　　glColor3f(1.0f,0.0f,0.0f);
　　glutSolidSphere(50.0f,20,20);

　　glColor3f(0.0f,0.0f,1.0f);
　　//地球与太阳的黄赤交角
　　glRotatef(23.27,0.0,0.0,1.0);
　　glRotatef(fEarth,0.0f,1.0f,0.0f);

　　glTranslatef(200.0f,0.0f,0.0f);
　　//画地球
　　glutSolidSphere(20.0f,20,20);
　　glPopMatrix();
　　glPopMatrix();

　　glRotatef(6.0f,1.0f,1.0f,1.0f);
　　glRotatef(fMoon,0.0f,1.0f,0.0f);
　　glColor3f(1.0f,1.0f,0.0f);

　　glTranslatef(30.0f,0.0f,0.0f);
　　//月球
　　glutSolidSphere(5.0f,20,20);
　　glLoadIdentity();
　　glFlush();

　　glutSwapBuffers();
}

/*
在空闲时调用，动画效果
*/
void myIdle(void)
{
　　fEarth += 0.03f;//增加旋转步长，产生动画效果
　　if (fEarth>360.0f)
　　{
　　　　fEarth = 2.0f;
　　}

　　fMoon += 0.24f;
　　if (fMoon>360.0f)
　　{
　　　　　fMoon = 24.0f;
　　}
　　Display();
}

int main(int argc,char* argv[])
{
　　glutInit(&argc,argv);
　　//窗口使用RGB色，双缓存和深度缓存
　　glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
　　glutInitWindowPosition(200,100);//窗口位置

　　//窗口尺寸
　　glutInitWindowSize(600,460);
　　glutCreateWindow("基于Opengl的太阳系动画");
　　glutReshapeFunc(Reshape);

　　glutDisplayFunc(Display);
　　glutIdleFunc(&myIdle);
　　Init();

　　glutMainLoop();//
　　return 0;
}

 