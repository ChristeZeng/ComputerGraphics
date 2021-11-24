#include <GL/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

struct vec3
{
    float x;
    float y;
    float z;
};

class OBJLoader {

public:

	OBJLoader(string filename) {
		FILE* fp = fopen((filename + ".obj").c_str(), "r");
		if(!fp) {
			printf("Open OBJ file failed!");
			exit(0);
		}
		vector<vec3> vertices;
		vector<unsigned int> verticesIndex, texturesIndex, normalsIndex;

		int lenofvertices = 0;
		int lenofindex = 0;

		while (true) {
			char firstword[300];
			memset(firstword, 0, 300);

			if (fscanf(fp, "%s", firstword) == EOF) {
				break;
			}
			if (!strcmp(firstword, "v")) {
				glm::vec3 vertex;
				fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
				lenofvertices++;
			}
			else if (!strcmp(firstword, "vt")) {
				glm::vec2 texture;
				fscanf(fp, "%f %f\n", &texture.x, &texture.y);
				//texture.y = -texture.y
				textures.push_back(texture);
				lenoftextures++;
			}
			else if (!strcmp(firstword, "vn")) {
				glm::vec3 normal;
				fscanf(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);
				lenofnormals++;
			}
			else if (!strcmp(firstword, "f")) {
				unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];
				int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textureIndex[0], &normalIndex[0], 
									&vertexIndex[1], &textureIndex[1], &normalIndex[1], 
									&vertexIndex[2], &textureIndex[2], &normalIndex[2]);
				for (int i = 0; i < 3; i++) {
					int curIndex = vertexIndex[i] - 1;
					verticesIndex.push_back(vertexIndex[i] - 1);

					normalArray[curIndex * 3 + 0] = normals[normalIndex[i] - 1].x;
					normalArray[curIndex * 3 + 1] = normals[normalIndex[i] - 1].y;
					normalArray[curIndex * 3 + 2] = normals[normalIndex[i] - 1].z;
					texturesIndex.push_back(textureIndex[i] - 1);
					normalsIndex.push_back(normalIndex[i] - 1);

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
		Model ret;
		return ret;//loader.LoadToV(vertexArray, lenofvertices * 3, indiceArray, lenofindex, normalArray, lenofvertices * 3);
	}
};
