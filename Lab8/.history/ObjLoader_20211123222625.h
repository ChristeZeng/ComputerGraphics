#include <GL/glut.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;

struct vec3
{
    float x;
    float y;
    float z;
};

class OBJLoader {
private:
    vector<vec3> vertices;
    vector<unsigned int> verticesIndex;

public:

	OBJLoader(string filename) {
		FILE* fp = fopen((filename + ".obj").c_str(), "r");
		if(!fp) {
			printf("Open OBJ file failed!");
			exit(0);
		}

		int lenofvertices = 0;
		int lenofindex = 0;

		while (true) {
			char firstword[300] = {0};
			if (fscanf(fp, "%s", firstword) == EOF) {
				break;
			}
			if (!strcmp(firstword, "v")) {
				vec3 vertex;
				fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
				lenofvertices++;
			}
			else if (!strcmp(firstword, "f")) {
				unsigned int vertexIndex[3];
				int matches = fscanf(fp, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
				for (int i = 0; i < 3; i++) {
					int curIndex = vertexIndex[i] - 1;
					verticesIndex.push_back(vertexIndex[i] - 1);
					lenofindex++;
				}
			}
		}
		
		float vertexArray[10000];
		memset(vertexArray, 0, 10000);
		for (int i = 0; i < lenofvertices; i++) {
			vertexArray[i * 3 + 0] = vertices[i].x;
			vertexArray[i * 3 + 1] = vertices[i].y;
			vertexArray[i * 3 + 2] = vertices[i].z;
		}

		int indiceArray[10000];
		memset(indiceArray, 0, 10000);
		for (int i = 0; i < lenofindex; i++) {
			indiceArray[i] = verticesIndex[i];
		}
	}
};
