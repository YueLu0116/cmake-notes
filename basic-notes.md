# CMake basics
> CMake基础学习笔记
## Reference
[modern cmake introduction](https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html)  
[bytetech blogs](https://tech.bytedance.net/articles/6887817085125623821)  
[cmake examples in github](https://github.com/ttroy50/cmake-examples)

[cmake wiki faq](https://gitlab.kitware.com/cmake/community/-/wikis/FAQ)

[effective modern cmake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)

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

## Lession 7 编译器标志

### 现代cmake定义编译器标志

使用`target_compile_definitions(<TARGET_NAME> SCOPE <FLAGS_> )`来定义，通过scope来指定该标识的可见范围，如果是public和interface的，则可以通过链接关系在不同targets间传递下去。

### make打印详细信息

`make VERBOSE=1`

## Lesson 8 引入第三方库
cmake提供了[find_package()](https://cmake.org/cmake/help/latest/command/find_package.html)函数来引入第三方库。有module模式与config模式。
### module模式
module模式下，cmake在搜索路径中寻找库对应的Find\<LibraryName\>.cmake文件。该文件为项目引入该库的头文件路径和库文件路径。  
module模式下的搜索路径：首先去项目指定的`CMAKE_MODULE_PATH`中，该路径[初值为空](https://cmake.org/cmake/help/latest/variable/CMAKE_MODULE_PATH.html#variable:CMAKE_MODULE_PATH)，需要自己指定；然后去cmake内置的modules路径下（mac中，通过homebrew安装cmake，该路径为：`/usr/local/Cellar/cmake/3.19.4/share/cmake/Modules`)  
关于FindLibraryName.cmake文件：例如motif库的该文件：
```
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindMotif
---------

Try to find Motif (or lesstif)

Once done this will define:

::

  MOTIF_FOUND        - system has MOTIF
  MOTIF_INCLUDE_DIR  - include paths to use Motif
  MOTIF_LIBRARIES    - Link these to use Motif
#]=======================================================================]

set(MOTIF_FOUND 0)

if(UNIX)
  find_path(MOTIF_INCLUDE_DIR
    Xm/Xm.h
    /usr/openwin/include
    )

  find_library(MOTIF_LIBRARIES
    Xm
    /usr/openwin/lib
    )

endif()

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Motif DEFAULT_MSG MOTIF_LIBRARIES MOTIF_INCLUDE_DIR)

mark_as_advanced(
  MOTIF_INCLUDE_DIR
  MOTIF_LIBRARIES
)
```
可以看出，该文件导出了一些变量：`MOTIF_FOUND`说明了该库有没有找到；`MOTIF_INCLUDE_DIR`和`MOTIF_LIBRARIES`说明了头文件和库文件的路径。  
通过这些导出的变量，可以在cmake工程中为target添加/链接相关的文件。现代cmake下，部分modules支持导出alias targets，例如boost库导出的targets使用boost::为标识，还明确了依赖关系。仅通过：
```
# link against the boost libraries
target_link_libraries( third_party_include
    PRIVATE
        Boost::filesystem
)
```
即可链接到boost库的filesystem。  
对于自己写的库，希望别的项目可以引用，则可以自己编写FindLN.cmake文件，然后通过上面的方式添加到其他项目中。
### config模式
如果module模式搜索失败，则cmake转入config模式进行搜索，找寻LibraryNameConfig.cmake和packagename-config.cmake文件。这些文件同样配置了头文件和库文件路径，提供变量给find_package()。一般非内置但是通过cmake编译安装的库会将配置文件拷贝到系统目录中。即对于使用者来说，先安装配置文件再使用cmake编译工程，此时find_package需要传入CONFIG参数。参考[回答](https://stackoverflow.com/a/20857070/11100389)。

## Lesson 9 指定编译器

指定使用clang编译工程：

`cmake .. -DCMAKE_C_COMPILER=clang-3.6 -DCMAKE_CXX_COMPILER=clang++-3.6`

在mac上直接使用以上命令会提示找不到cxx_compiler，解决办法可参考[回答](https://stackoverflow.com/a/9702678/11100389)

## Lesson 10 多个项目的工程

### header only

基本规则：

```
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
```

### 链接工程中的其他库

```
target_link_libraries(${PROJECT_NAME}
    sub::lib1
    sub::lib2
)
```

### top-level的CMakeLists.txt

需要添加子项目的目录：

```
add_subdirectory(sublibrary1)
add_subdirectory(sublibrary2)
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