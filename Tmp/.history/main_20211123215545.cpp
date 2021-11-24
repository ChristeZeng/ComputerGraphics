ObjLoader monkey= ObjLoader("monkey.obj");
void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//像素传输
	setLight();//渲染光照
	monkey.Draw();
}
void main(int argc, char** argv)
{
	InitWindow(argc, argv);//执行初始化程序
	glutDisplayFunc(&display);//将图形信息送往窗口显示
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();//循环执行
}
