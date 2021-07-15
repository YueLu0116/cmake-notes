#include <iostream>

int main()
{
    std::cout << "what is compile flags?" << std::endl;
    
#ifdef EX3
  std::cout << "hello ex3" << std::endl;
#endif

    return 0;
}