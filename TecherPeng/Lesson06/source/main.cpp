#include <iostream>
#include <string>
#include <fstream>
#include <damnjone_util.h>


void check_LOG()
{
    std::ofstream fout("LOG.txt", std::ios::out);
    if (!fout.is_open())
    {
        DAMNJONE_LOG(std::cout, "Failed to open file!");
        return;
    }
    DAMNJONE_LOG(fout, "Succeeded in writing file!");
}

void check_get_type()
{
    struct MyClass {};
    std::cout << "Type name: " << DamnJoneUtil::get_type_name(MyClass()) << std::endl;
    std::cout << "Type name: " << DamnJoneUtil::get_type_name(check_get_type) << std::endl;
}

int main(void)
{
    check_LOG();
    check_get_type();

    return 0;
}