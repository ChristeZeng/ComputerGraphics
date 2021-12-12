# AS#9: Texturing Your Solar System

### 文件结构

Car.h：绘制Dream Car的相关函数

Car.obj：车子的主体

main.cpp：主函数，程序框架

compile.sh：编译运行的shell命令

main：可执行文件

Texture/：存放星球Texture的文件夹

Skybox/：存放skybox贴图的文件夹

stb_image.h/stb_image.cpp：图片处理库



### 运行方式

#### 编译方式

```shell
g++ main.cpp Car.h stb_image.cpp -o main -lGL -lGLU -lglut
```

或者使用compile.sh编译运行

