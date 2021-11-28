#include <GL/glut.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;

//1.331094
#define PI 3.1415926535897932384626433832795
float HLength = 0.2;
float HWidth = 0.5;
float HThickness = 0.2;

struct vec3
{
    float x;
    float y;
    float z;
};

class OBJLoader {
private:
    vector<vec3> vertices;  //v / 3
    vector<int> verticesIndex; //f / 3

public:

	OBJLoader(string filename) {
		FILE* fp = fopen(filename.c_str(), "r");
		if(!fp) {
			printf("Open OBJ file failed!");
			exit(0);
		}

		while (true) {
			char firstword[300] = {0};

			if (fscanf(fp, "%s", firstword) == EOF) {
				break;
			}
			if (!strcmp(firstword, "v")) {
				vec3 vertex;
				fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
			}
			else if (!strcmp(firstword, "f")) {
				int vertexIndex[3];
				int matches = fscanf(fp, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
				for (int i = 0; i < 3; i++) {
					verticesIndex.push_back(vertexIndex[i] - 1);
				}
			}
		}
        fclose(fp);
	}
    
    string Iterator(string str, int n) {
        //rules: 1 -> 11 / 0 -> 1[0]0
        string result = "";
        for(int i = 0; i < n; i++) {
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == '1') {
                    result += "11";
                }
                else if (str[i] == '0') {
                    result += "1[0]0";
                }
                else {
                    result += str[i];
                }
            }
            str = result;
            result = "";
        }
        return str;
    }
    
    void LSystem(string str, int n) {
        string cmd = Iterator(str, n);
        glPushMatrix();
        glTranslatef(0.055895, 0.798012, -1.227384);
        glRotatef(-90, 1, 0, 0);
        for(int i = 0; i < cmd.length(); i++){
            if(cmd[i] == '0'){
                gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.05, 20, 20);
                glTranslatef(0.0, 0.0, 0.05);
            }
            else if(cmd[i] == '1'){
                gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.1, 20, 20);
                glTranslatef(0.0, 0.0, 0.1);
            }
            //[: push position and angle, turn left 45 degrees
            else if(cmd[i] == '['){
                glPushMatrix();
                glRotatef(-30, 0, 1, 0);
            }
            //]: pop position and angle, turn right 45 degrees
            else if(cmd[i] == ']'){
                glPopMatrix();
                glRotatef(30, 0, 1, 0);
            }
        }
        glPopMatrix();
    }
    
    void Sweeping(float radius, float bendRadius) {
        glPushMatrix();
        glRotatef(-180, 0, 1, 0);
        glTranslatef(0.069733, 0.890669, 1.134200 - 3.0);
        
        for(int i = 0; i < 20; i++) {
            float w0 = (float)i / 20;
            float w1 = (float)(i+1) / 20;
        
            float ang0 = -bendRadius * 1.0f / 2.0f + (bendRadius * 1.0f / 2.0f + bendRadius * 1.0f / 2.0f) * w0;
            float ang1 = -bendRadius * 1.0f / 2.0f + (bendRadius * 1.0f / 2.0f + bendRadius * 1.0f / 2.0f) * w1;

            glBegin(GL_QUAD_STRIP);
            for (int j = 0; j <= 360; j++) {
                float angle = PI * (float)j * PI / 180.0f;
                float x = radius * cos(angle) + bendRadius;
                float y = radius * sin(angle);
                glVertex3f( x * sin(ang0), y, x * cos(ang0));
                glVertex3f( x * sin(ang1), y, x * cos(ang1));
            }
            glEnd();
        }
        glPopMatrix();
    }

    void DrawACircle(float R, int n){
        glBegin(GL_POLYGON);
        for(int i=0;i<n;i++){
            glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));   //定义顶点
        }
        glEnd();
    }
    void Sweeping2(){
        glPushMatrix();
        int Max = 100;
        float angle = 360.0 / (float)Max;
        for(int i = 0; i < Max; i++){
            glRotatef(angle, 0, 1, 0);
            //DrawACircle(0.05, 20);
            glutSolidTorus(0.01, 0.05, 20, 20);
            glTranslatef(0.0, 0.0, 0.01);
        }
        
        glPopMatrix();
    }
    void DrawOBJ(){
        glPushMatrix();
        
        glBegin(GL_TRIANGLES);
        for(int i = 0; i < verticesIndex.size() / 3; i++){
            vec3 normal; //法线

            GLfloat v1[3], v2[3], v3[3];
            v1[0] = vertices[verticesIndex[i * 3 + 0]].x - vertices[verticesIndex[i * 3 + 1]].x;
            v1[1] = vertices[verticesIndex[i * 3 + 0]].y - vertices[verticesIndex[i * 3 + 1]].y;
            v1[2] = vertices[verticesIndex[i * 3 + 0]].z - vertices[verticesIndex[i * 3 + 1]].z;

            v2[0] = vertices[verticesIndex[i * 3 + 1]].x - vertices[verticesIndex[i * 3 + 2]].x;
            v2[1] = vertices[verticesIndex[i * 3 + 1]].y - vertices[verticesIndex[i * 3 + 2]].y;
            v2[2] = vertices[verticesIndex[i * 3 + 1]].z - vertices[verticesIndex[i * 3 + 2]].z;

            v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
            v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
            v3[2] = v1[0] * v2[1] - v1[1] * v2[0];

            GLfloat distance = sqrt(v3[0] * v3[0] + v3[1] * v3[1] + v3[2] * v3[2]);

            normal.x = v3[0] / distance;
            normal.y = v3[1] / distance;
            normal.z = v3[2] / distance;

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(vertices[verticesIndex[i * 3 + 0]].x, vertices[verticesIndex[i * 3 + 0]].y, vertices[verticesIndex[i * 3 + 0]].z);
            glVertex3f(vertices[verticesIndex[i * 3 + 1]].x, vertices[verticesIndex[i * 3 + 1]].y, vertices[verticesIndex[i * 3 + 1]].z);
            glVertex3f(vertices[verticesIndex[i * 3 + 2]].x, vertices[verticesIndex[i * 3 + 2]].y, vertices[verticesIndex[i * 3 + 2]].z);
        }
        glEnd();
        glPopMatrix();
    }
};
