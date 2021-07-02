# CMake basics
> CMake基础学习笔记
## Reference
[modern cmake introduction](https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html)  
[bytetech blogs](https://tech.bytedance.net/articles/6887817085125623821)  
[cmake examples in github](https://github.com/ttroy50/cmake-examples)
## Lesson 1
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
