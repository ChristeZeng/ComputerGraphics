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

void MidBresenham(int x0, int y0, int a, int b, double lamda, unsigned char data[])
{
	/*The first Point*/
	int x = 0;
	int y = b;
	/*Draw the symmetry points*/
	int xi = x + x0;
	int yi = round(y + lamda * x + y0);
	if(!OutofRange(xi, yi))
		data[yi * 400 * 3 + xi * 3] = 255;
	xi = -x + x0;
	yi = round(y + lamda * (-x) + y0);
	if(!OutofRange(xi, yi))
		data[yi * 400 * 3 + xi * 3] = 255;
	xi = x + x0;
	yi = round(-y + lamda * x + y0);
	if(!OutofRange(xi, yi))
		data[yi * 400 * 3 + xi * 3] = 255;
	xi = -x + x0;
	yi = round(-y + lamda * (-x) + y0);
	if(!OutofRange(xi, yi))
		data[yi * 400 * 3 + xi * 3] = 255;
	
	/*the up part(step along x)*/
	double d = pow(b, 2) - pow(a, 2) * (b - 0.25);
	while(pow(a, 2) * (y - 0.5) > pow(b, 2) * (x + 1))
	{
		/*choose yi*/
		if(d < 0)
			d += pow(b, 2) * (2 * x + 3);
		/*choose yi-1*/
		else
		{
			d += pow(b, 2) *(2 * x + 3) + pow(a, 2) * (2 - 2 * y);
			y--;
		}
		x++;
		
		/*draw the points*/
		xi = x + x0;
		yi = round(y + lamda * x + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
		xi = -x + x0;
		yi = round(y + lamda * (-x) + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
		xi = x + x0;
		yi = round(-y + lamda * x + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
		xi = -x + x0;
		yi = round(-y + lamda * (-x) + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
	}

	/*The lower part(step along y)*/
	d = pow(b, 2) * pow(x + 0.5, 2) + pow(a, 2) * pow(y - 1, 2) - pow(a, 2) * pow(b, 2);
	while (y >= 0)
	{
		/*choose xi*/
		if(d >= 0)
			d += pow(a, 2) * (3 - 2 * y);
		/*choose xi+1*/
		else
		{
			d += pow(b, 2) * (2 * x + 2) + pow(a, 2) * (3- 2 * y);
			x++;
		}
		y--;

		/*draw the points*/
		xi = x + x0;
		yi = round(y + lamda * x + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
		xi = -x + x0;
		yi = round(y + lamda * (-x) + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
		xi = x + x0;
		yi = round(-y + lamda * x + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
		xi = -x + x0;
		yi = round(-y + lamda * (-x) + y0);
		if(!OutofRange(xi, yi))
			data[yi * 400 * 3 + xi * 3] = 255;
	}
	
}

int main() {
	unsigned char data[400*300*3] = { 0 };
	cout << "This is improved method!" << endl;
	int x, y, ra, rb, theta; 	
	cout << "please input the origin (x, y): ";
	cin >> x >> y;
	cout << "please input the semi-major axis a: ";
	cin >> ra;
	cout << "please input the semi-minor axis b: ";
	cin >> rb;
	cout << "please input the rotation angle theta: ";
	cin >> theta;

    /*the arguments of shear*/
    double t = atan( -(double)rb / (double)ra * tan(rad(theta)) );
	int a = round( abs( (double)ra * cos(t) * cos(rad(theta)) - (double)rb * sin(t) * sin(rad(theta)) ) );
	int b = round((double)ra * (double)rb / (double)a);
	double lamda = ( (double)ra * cos(t) * sin(rad(theta)) + (double)rb * sin(t) * cos(rad(theta)) ) / ( (double)ra * cos(t) * cos(rad(theta)) - (double)rb * sin(t) * sin(rad(theta)));
	MidBresenham(x, y, a, b, lamda, data);
	ppmWrite("test.ppm", data, 400, 300);
	return 0;
}