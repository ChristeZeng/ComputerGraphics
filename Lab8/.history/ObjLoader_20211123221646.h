#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

void LoadObj(string filename){
    ifstream in(filename.c_str());
    if(!in){
        cerr<<"Can't open file "<<filename<<endl;
        exit(1);
    }
    string line;
    vector<vertex> v;
    vector<vertex> vt;
    vector<vertex> vn;
    vector<int> f;
    while(getline(in,line)){
        if(line.substr(0,2)=="v "){
            istringstream s(line.substr(2));
            vertex v1;
            s>>v1.x;
            s>>v1.y;
            s>>v1.z;
            v.push_back(v1);
        }
        else if(line.substr(0,3)=="vt "){
            istringstream s(line.substr(3));
            vertex v1;
            s>>v1.x;
            s>>v1.y;
            vt.push_back(v1);
        }
        else if(line.substr(0,3)=="vn "){
            istringstream s(line.substr(3));
            vertex v1;
            s>>v1.x;
            s>>v1.y;
            s>>v1.z;
            vn.push_back(v1);
        }
        else if(line.substr(0,2)=="f "){
            istringstream s(line.substr(2));
            int a,b,c;
            s>>a;
            f.push_back(a);
            s>>b;
            f.push_back(b);
            s>>c;
            f.push_back(c);
        }
    }
    in.close();
    glBegin(GL_TRIANGLES);
}
