#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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

int main() {
	unsigned char data[400*300*3] = { 1 };
	ppmWrite("test.ppm", data, 400, 300);
	int x, y, ra, rb, theta; 	//分别输入半长轴，半短轴和角度
	//cout << "please input the a, b, theta" << endl;
	//cin >> x >> y >> ra >> rb >> theta;
	/* 标准方程:b2(x-x0)2+a2(y-y0)2+na2b2(x-x0)(y-y0)=a2b2 */
	
	return 0;
}