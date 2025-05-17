#include <iostream>

#include "platform/platform.h"

int main(char* args[], int argCount)
{
    int result = std::system(
        "dxc --version");
    /*for (size_t i  =0; i < argCount; i++)
    {
        std::string file_name = args[i];
        engine::FileSystem* fs        = engine::FileHandler();
        if(fs->DoesFileExist(file_name))
        {
            
        }
    }*/
}