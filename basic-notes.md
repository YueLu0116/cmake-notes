# CMake basics
> CMake基础学习笔记
## Reference
[modern cmake introduction](https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html)  
[bytetech blogs](https://tech.bytedance.net/articles/6887817085125623821)  
[cmake examples in github](https://github.com/ttroy50/cmake-examples)
## Lesson 1 CMake hello world
### CMake最基本的三行代码
1. 指定最小版本（or版本范围）  
   `cmake_minimum_required(VERSION 3.10)`
2. 项目名称  
   `project(hello_cmake)`  
   hello_cmake保存在变量名PROJECT_NAME中
3. 添加可执行文件  
   `add_executable(${PROJECT_NAME} main.cpp) `
### 指令流
在项目目录下
```
mkdir build
cd build
cmake ..
make
```
## Lesson 2 头文件包含
### CMake变量
有built-in和用户自定义的变量，built-in的变量可以参考[文档](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables)，而用户自定义变量可以通过`set`来设置，例如  
```
set(SOURCE src/hello.cpp src/main.cpp)
```
指定了SOURCE变量为所有源文件。
### 作用域
CMake中有作用域的概念，PRIVATE, INTERFACE, and PUBLIC。例如，动态链接库A包含了动态链接库B，如果（1）包含关系是PRIVATE的，则B提供的头文件只对A可见，调用A的用户不知道B的存在；（2）包含关系是INTERFACE的，则B的头文件只对外使用，A只可能用到B中定义的结构体，而B中的函数只对调用A的用户可见；（3）如果包含关系是PUBLIC的，则等于以上两种情况的和。  
如果是为一个库C添加头文件，scope的含义为：（1）包含关系是PRIVATE的，则该头文件只添加到该库；（2）包含关系是INTERFACE的，则该头文件只添加到链接该库的target里；（3）如果包含关系是PUBLIC的，则等于以上两种情况的和。  
具体可参考[文章](https://zhuanlan.zhihu.com/p/82244559)
### 包含头文件
通过`target_include_directories`来指定包含的头文件，基本调用格式为
```
target_include_directories(target SCOPE include_directory)
```
其中，target为execuable or library，SCOPE为上点所述关键字，include_directory为包含头文件的路径。[官方文档](https://cmake.org/cmake/help/latest/command/target_include_directories.html)

## Lesson 3 静态链接库
### 建立一个静态链接库
通过`add_library(lib_name, SOURCE_CODE_FILE)`可以添加一个静态链接库，通过`target_include_directories(libname, SCOPE, INCLUDE_FILES)`为该静态链接库指定包含的头文件。和添加可执行文件有相同的模式，即先add library，将源文件与target联系在一起，再指定包含目录。  

### 链接到一个静态链接库
通过`target_link_libraries(exe_name scope lib_name)`实现。  
关于scope参考Lesson 2。

## FAQ
1. [Are CMAKE_SOURCE_DIR and PROJECT_SOURCE_DIR the same in CMake?
](https://stackoverflow.com/questions/32028667/are-cmake-source-dir-and-project-source-dir-the-same-in-cmake)
   >  CMAKE_SOURCE_DIR does indeed refer to the folder where the top-level CMakeLists.txt is defined. However, PROJECT_SOURCE_DIR refers to the folder of the CMakeLists.txt containing the most recent project() command.