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
具体可参考[文章](https://zhuanlan.zhihu.com/p/82244559)
### 包含头文件
通过`target_include_directories`来指定包含的头文件，基本调用格式为
```
target_include_directories(target SCOPE include_directory)
```
其中，target为execuable or library，SCOPE为上点所述关键字，include_directory为包含头文件的路径。[官方文档](https://cmake.org/cmake/help/latest/command/target_include_directories.html)
