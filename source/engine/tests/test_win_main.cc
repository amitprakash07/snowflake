#include <Windows.h>

#include "common/tree.h"
#include "common/heap_container.h"
#include "common/linked_list.h"
#include "common/maths_util.h"
#include "common/sort.h"
#include "common/stack.h"
#include "common/string_util.h"
#include "common/util.h"
#include "gpu/gpu_factory.h"
#include "gpu/gpu_device.h"
#include "gpu/shader/shader_handler.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MessageBox(nullptr, "Testing the Win Main", "Testing", MB_OK);

    {
        amit::GpuFactory gpu;

        if (gpu.Initialize())
        {
            amit::GpuDevice* device = gpu.GetDevice();
            if (device)
            {
                device->UnitTest();
            }
        }
    }

    {
        //amit::ShaderHandler::Init();
        amit::ShaderHandler::Instance()->CompileDefaultShaders();
    }

    {
        amit::HeapContainer<int>::UnitTest();
        amit::BinarySearchTree<int>::UnitTest();
    }

    {
        // Bubble sort
        std::vector<int> data = {5, 8, 9, 2, 6, 7, 3, 1, 4};
        std::cout << amit::util::ToStr(data);
        amit::Sort::BubbleSort(data);
        std::cout << amit::util::ToStr(data);
    }

    {
        std::cout << amit::maths::GetHCF(119, 544);
        amit::BinaryTree<int>::UnitTest();
        amit::Queue<int>::UnitTest();
        amit::Stack<int>::UnitTest();
    }

    {
        char*       to_char_array = amit::ToStr(32);
        std::string temp_string(to_char_array);
        std::cout << temp_string.c_str();
        std::cout << std::string(amit::ToStr(-6748)).c_str();
    }

    {
        amit::LinkedList<int>::UnitTest();
    }

    {
        std::cout << engine_string_util::SimplifyPath("/.../a/../b/c/../d/./");
        std::cout << engine_string_util::SimplifyPath("/../");
        std::cout << engine_string_util::SimplifyPath("/home/user/Documents/../Pictures");
        std::cout << engine_string_util::RemoveDuplicates("abbaca");
    }
}
