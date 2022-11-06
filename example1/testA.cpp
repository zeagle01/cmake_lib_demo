
#include <iostream>
#include <fstream>
#include <string>
#include "A/a.h"
#include "B/b.h"




int main()
{
    A a;
    a.greet();

    B b;
    b.greet();

    std::string file_name = "test_data/test_data.txt";
    std::ifstream fin(file_name);
    if (fin.is_open())
    {
		std::string line;
		std::getline(fin, line);
		printf("%s \n", line.c_str());
    }
    else
    {
        printf(" can't open file %s \n", file_name.c_str());
    }

    std::getchar();

#ifdef IS_A
    printf("macro is a\n");
#endif

#ifdef IS_B
    printf("macro is b\n");
#endif

}


