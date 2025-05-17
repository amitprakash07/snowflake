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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MessageBox(nullptr, "Testing the Win Main", "Testing", MB_OK);

    {
       /* engine::GpuFactory gpu;

        if (gpu.Initialize())
        {
            engine::GpuDevice* device = gpu.GetDevice();
            device->UnitTest();
        }*/
    }

    {
        engine::HeapContainer<int>::UnitTest();
        engine::BinarySearchTree<int>::UnitTest();
    }

    {
        // Bubble sort
        std::vector<int> data = {5, 8, 9, 2, 6, 7, 3, 1, 4};
        std::cout << engine::util::ToStr(data);
        engine::Sort::BubbleSort(data);
        std::cout << engine::util::ToStr(data);
    }

    {
        std::cout << engine::maths::GetHCF(119, 544);
        engine::BinaryTree<int>::UnitTest();
        engine::Queue<int>::UnitTest();
        engine::Stack<int>::UnitTest();
    }

    {
        char*       to_char_array = engine::ToStr(32);
        std::string temp_string(to_char_array);
        std::cout << temp_string.c_str();
        std::cout << std::string(engine::ToStr(-6748)).c_str();
    }

    {
        engine::LinkedList<int>::UnitTest();
    }

    {
        std::cout << engine::util::SimplifyPath("/.../a/../b/c/../d/./");
        std::cout << engine::util::SimplifyPath("/../");
        std::cout << engine::util::SimplifyPath("/home/user/Documents/../Pictures");
        std::cout << engine::util::RemoveDuplicates("abbaca");
    }
}
