#include <iostream>

class Print{
public:
    static void hello(){
        std::cout << "I was fucked by simulating touch events these days." << std::endl;
    }
};

int main()
{
    Print::hello();
    return 0;
}