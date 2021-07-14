# CMake basics
> CMake基础学习笔记
## Reference
[modern cmake introduction](https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html)  
[bytetech blogs](https://tech.bytedance.net/articles/6887817085125623821)  
[cmake examples in github](https://github.com/ttroy50/cmake-examples)

[cmake wiki faq](https://gitlab.kitware.com/cmake/community/-/wikis/FAQ)

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
target_include_directories(<target> SCOPE <include_directory>)
```
其中，target为execuable or library，SCOPE为上点所述关键字，include_directory为包含头文件的路径。[官方文档](https://cmake.org/cmake/help/latest/command/target_include_directories.html)

## Lesson 3 静态链接库
### 建立一个静态链接库
通过`add_library(<lib_name> STATIC <SOURCE_CODE_FILE>)`可以添加一个静态链接库，通过`target_include_directories(<lib_name> <SCOPE> <INCLUDE_FILES>)`为该静态链接库指定包含的头文件。和添加可执行文件有相同的模式，即先add library，将源文件与target联系在一起，再指定包含目录。  

### 链接到一个静态链接库
通过`target_link_libraries(<exe_name> <SCOPE> <lib_name>)`实现。  
关于scope参考Lesson 2。

## Lesson 4 动态链接库
### 建立一个动态链接库
同Lesson 3，唯一的变化是把`add_library(<lib_name> STATIC <SOURCE_CODE_FILE>)`中的STATIC变为SHARED

### 为target起别名
`add_library(<name> ALIAS <target>)`  
参考[文档](https://cmake.org/cmake/help/latest/command/add_library.html#alias-libraries)：The <name> may not be used to modify properties of <target>, that is, it may not be used as the operand of set_property(), set_target_properties(), target_link_libraries() etc. An ALIAS target may not be installed or exported.

## Lesson 5 install

### install的用处是什么

Cmake 里的install实现make install功能，例如当自己写了一个库，需要将库文件和头文件之类的放到相应的目录下。可参考[论坛](https://www.reddit.com/r/cpp/comments/6m7sp6/cmake_and_c_whats_the_deal_with_installing/)以及[文章](https://zhuanlan.zhihu.com/p/52898952)

### 安装路径

默认是`/usr/local`下，也可以通过`cmake .. -DCMAKE_INSTALL_PREFIX=/install/location`来指定。如果想先安装到一个临时目录下，查看安装内容是否齐全

### 不同类型的安装

分为binaries, libraries, files, and directories。示例：

```
# Binaries
install (TARGETS cmake_examples_inst_bin
    DESTINATION bin)

# Library
# Note: may not work on windows
install (TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include)

# Config
install (FILES cmake-examples.conf
    DESTINATION etc)
```

### build步骤

```
mkdir build
cd build
cmake ..
make
make install
```

会生成一个install_manifest.txt文件，里面记录了install的地址。

如果想预先安装到一个临时文件，检查安装内容是否齐全，则可以

`make install DESTDIR=/tmp/stage`

## Lession 6 构建类型

> 参考so[问题](https://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake)，更推荐out of source build
>
> 另外一个[post](https://stackoverflow.com/questions/48754619/what-are-cmake-build-type-debug-release-relwithdebinfo-and-minsizerel)下回答了不同build types的含义，以及cmake默认是release build type

例如要采用debug build

```
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## FAQ
1. [Are CMAKE_SOURCE_DIR and PROJECT_SOURCE_DIR the same in CMake?
    ](https://stackoverflow.com/questions/32028667/are-cmake-source-dir-and-project-source-dir-the-same-in-cmake)

  >  CMAKE_SOURCE_DIR does indeed refer to the folder where the top-level CMakeLists.txt is defined. However, PROJECT_SOURCE_DIR refers to the folder of the CMakeLists.txt containing the most recent project() command.  

2. [How to enable c++17 in cmake](https://stackoverflow.com/questions/45688522/how-to-enable-c17-in-cmake)  
   Use `target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)`. More information is in the [official document](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id5)  

3. How to use cmake tools in vscode?  
   On mac  
   
   1. Open the Command Palette and run cmake:configure;
   2. Select the complier (clang);
   3. Build.  
   
   More information is in the [official document](https://code.visualstudio.com/docs/cpp/cmake-linux).