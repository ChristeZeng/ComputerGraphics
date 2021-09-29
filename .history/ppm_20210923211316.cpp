#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

void ppmRead(char* filename, unsigned char* data, int* w, int* h) {
	char header[1024];
	FILE* fp = NULL;
	int line = 0;

	fp = fopen(filename, "rb");
	while (line < 2) {
		fgets(header, 1024, fp);
		if (header[0] != '#') {
			++line;
		}
	}
	sscanf(header, "%d %d\n", w, h);
	fgets(header, 20, fp);
	fread(data, (*w)*(*h) * 3, 1, fp);

	fclose(fp);
}
void ppmWrite(const char* filename, unsigned char* data, int w, int h) {
	FILE* fp;
	fp = fopen(filename, "wb");

	fprintf(fp, "P6\n%d %d\n255\n", w, h);
	fwrite(data, w*h * 3, 1, fp);

	fclose(fp);
}

void MidBresenham(int a, int b, unsigned char data[])
{
	//确定第一个点的位置
	int x = 0;
	int y = b;

	data[y * 400 * 3 + x * 3] = 255;
	//初始误差
	double d = pow(b, 2) + pow(a, 2) * (b - 0.25);
	while(pow(a, 2) * (y - 0.5) > pow(b, 2) * (x + 1))
	{
		if(d < 0)
			d += pow(b, 2) * (2 * x + 3);
		else
		{
			d += pow(b, 2) *(2 * x + 3) + pow(a, 2) * (2 - 2 * y);
			y--;
		}
		x++;
		data[y * 400 * 3 + x * 3] = 255;
	}

	d = pow(b, 2) * pow(x + 0.5, 2) + pow(a, 2) * pow(y - 1, 2) - pow(a, 2) * pow(b, 2);
	while (y >= 0)
	{
		if(d >= 0)
			d += pow(a, 2) * (3 - 2 * y);
		else
		{
			d += pow(b, 2) * (2 * x + 2) + pow(a, 2) * (3- 2 * y);
			x++;
		}
		y--;
		data[y * 400 * 3 + x * 3] = 255;
	}
	
}

int main() {
	unsigned char data[400*300*3] = { 0 };
	// for(int i = 0; i < 300; i++)
	// 	for(int j = 0; j < 400; j++)
	// 		data[i * 400 * 3 + j * 3] = 255;
	
	int x, y, ra, rb, theta; 	//分别输入半长轴，半短轴和角度
	cout << "please input the a, b, theta" << endl;
	cin >> x >> y >> ra >> rb >> theta;
	/* 标准方程:b2(x-x0)2+a2(y-y0)2+na2b2(x-x0)(y-y0)=a2b2 */
	MidBresenham(ra, rb, data);
	ppmWrite("test.ppm", data, 400, 300);
	return 0;
}