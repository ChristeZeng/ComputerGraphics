#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#define PI 3.141592653589793
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

double rad(int theta)
{
	return (double)theta / 180 * PI;
}

bool OutofRange(int x, int y)
{
	return (x > 400 || x < 0 || y > 300 || y < 0) ? true : false;
}

int main() {
	unsigned char data[400*300*3] = { 0 };
	int x, y, ra, rb, theta; 	
	cout << "please input the origin (x, y): ";
	cin >> x >> y;
	cout << "please input the semi-major axis a: ";
	cin >> ra;
	cout << "please input the semi-minor axis b: ";
	cin >> rb;
	cout << "please input the rotation angle theta: ";
	cin >> theta;

	
	ppmWrite("test.ppm", data, 400, 300);
	return 0;
}