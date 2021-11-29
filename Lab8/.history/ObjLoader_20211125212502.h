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
float HLength = 1.0;
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
    
    void LSystem(string cmd){
        glPushMatrix();
        for(int i = 0; i < cmd.length(); i++){
            if(cmd[i] == 'S'){
                glTranslatef(0.055895, 0.798012, -1.227384);
                glRotatef(-90, 1, 0, 0);
                gluCylinder(gluNewQuadric(), 0.06, 0.06, 1.0, 20, 20);
                glTranslatef(0.0, 0.0, 1.0);
            }
            else if(cmd[i] == 'L'){
                glRotatef(30, 0, 1, 0);
                gluCylinder(gluNewQuadric(), 0.06, 0.06, 1.0, 20, 20);
            }
            else if(cmd[i] == 'R'){
                glRotatef(-30, 0, 1, 0);
                gluCylinder(gluNewQuadric(), 0.06, 0.06, 1.0, 20, 20);
            }
        }
        glPopMatrix();
    }
    
    void drawH(float x, float y, float z, float x1, float y1, float z1){
        int lastofVertices = vertices.size();
        vertices.push_back(vec3{x - HWidth / 2, y - HThickness / 2, z});
        vertices.push_back(vec3{x - HWidth / 2, y + HThickness / 2, z});
        vertices.push_back(vec3{x1 - HWidth / 2, y1 + HThickness / 2, z1});
        vertices.push_back(vec3{x1 - HWidth / 2, y1 - HThickness / 2, z1});
        verticesIndex.push_back(lastofVertices + 0);
        verticesIndex.push_back(lastofVertices + 1);
        verticesIndex.push_back(lastofVertices + 2);
        verticesIndex.push_back(lastofVertices + 0);
        verticesIndex.push_back(lastofVertices + 2);
        verticesIndex.push_back(lastofVertices + 3);

        vertices.push_back(vec3{x + HWidth / 2, y + HThickness / 2, z});
        vertices.push_back(vec3{x + HWidth / 2, y - HThickness / 2, z});
        vertices.push_back(vec3{x1 + HWidth / 2, y1 - HThickness / 2, z1});
        vertices.push_back(vec3{x1 + HWidth / 2, y1 + HThickness / 2, z1});
        verticesIndex.push_back(lastofVertices + 4);
        verticesIndex.push_back(lastofVertices + 5);
        verticesIndex.push_back(lastofVertices + 6);
        verticesIndex.push_back(lastofVertices + 4);
        verticesIndex.push_back(lastofVertices + 6);
        verticesIndex.push_back(lastofVertices + 7);

        vertices.push_back(vec3{(x + x1) / 2 + HWidth / 2, (y + y1) / 2 - HThickness / 2, (z + z1) / 2});
        vertices.push_back(vec3{(x + x1) / 2 - HWidth / 2, (y + y1) / 2 - HThickness / 2, (z + z1) / 2});
        vertices.push_back(vec3{(x + x1) / 2 - HWidth / 2, (y + y1) / 2 + HThickness / 2, (z + z1) / 2});
        vertices.push_back(vec3{(x + x1) / 2 + HWidth / 2, (y + y1) / 2 + HThickness / 2, (z + z1) / 2});
        verticesIndex.push_back(lastofVertices + 8);
        verticesIndex.push_back(lastofVertices + 9);
        verticesIndex.push_back(lastofVertices + 10);
        verticesIndex.push_back(lastofVertices + 8);
        verticesIndex.push_back(lastofVertices + 10);
        verticesIndex.push_back(lastofVertices + 11);
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
