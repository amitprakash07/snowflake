#include <iostream>

#include "common/string_pool.h"
#include "win32_includes.h"
#include "win32_resource.h"
#include "platform/platform_systems.h"

void engine::Window::SetToFullResolution()
{
    HWND desktopResolution = GetDesktopWindow();
    RECT fullResolution;
    GetWindowRect(desktopResolution, &fullResolution);
    wnd_attributes_.width  = fullResolution.right;
    wnd_attributes_.height = fullResolution.bottom;
}

engine::WindowingSystem::WindowingSystem(int win_main_display_state)
    : IPlatformSystem(PlatformHandlerType::Windowing)
    , main_window_(nullptr)
    , main_window_handle_(nullptr)
    , win_main_display_state_(win_main_display_state)
{
    if (main_window_ == nullptr)
    {
        main_window_ = new Window();
        main_window_->Initialize();
    }
}

//engine::ResultPtr CALLBACK engine::WindowingSystem::DefaultWndProc(Window*    window,
//                                                                   WndMessage message,
//                                                                   Param      w_param,
//                                                                   Param      l_param)
//{
//    switch (message)
//    {
//    case WM_CHAR:
//    {
//        // This isn't usually the best way to handle keyboard input in a real-time
//        // game, but it is a convenient way to handle an exit key (The WPARAM
//        // input parameter indicates which key was pressed, but this example
//        // program only cares about the escape key)
//        // if (i_wParam == VK_ESCAPE)
//        //{
//        //	// You do _not_ need to do this in your game,
//        //	// but this example program shows you how to display a "message
//        // box"
//        //	// that asks the user for confirmation
//        //	int result;
//        //	{
//        //		const char* caption = "Exit Program?";
//        //		const char* message = "Are you sure you want to quit?";
//        //		result = MessageBox(s_mainWindow, message, caption,
//        // MB_YESNO | MB_ICONQUESTION);
//        //	}
//        //	if (result == IDYES)
//        //	{
//        //		// Instruct Windows to send a WM_QUIT message
//        //		{
//        //			// The exit code is ignored,
//        //			// but just as an example of what's possible a
//        // different exit code is sent here
//        //			// than when the user closes the program in the
//        // usual way
//        //			// (by clicking the X in the upper-right hand
//        // corner).
//        //			/*int exitCode = 0;
//        //			PostQuitMessage(exitCode);*/
//        //			SendMessage(i_window, WM_NCDESTROY, i_wParam,
//        // i_lParam);
//        //		}
//        //		// For WM_CHAR messages, return 0 to indicate that it
//        // was processed 		return 0;
//        //	}
//        //	else
//        //	{
//        //		// If the user doesn't select "Yes" to quit
//        //		// then do nothing to keep running the program
//        //	}
//
//        //}
//        // If the key press wasn't handled pass it on to Windows to process in the
//        // default way
//        engine::utils::StringHash temp = engine::EngineCore::getStringPool()->FindString("KeyDown");
//        engine::SharedPointer<engine::Windows::WindowingSystem> tempWindowingSystem =
//            engine::EngineCore::getWindowingSystem();
//        engine::EngineCore::getMessagingSystem()->sendMessage(
//            temp, tempWindowingSystem.CastSharedPointer<engine::RTTI>(), reinterpret_cast<void*>(i_wParam));
//        break;
//    }
//    case WM_KEYDOWN:
//    {
//        engine::utils::StringHash temp = engine::EngineCore::getStringPool()->FindString("KeyDown");
//        engine::SharedPointer<engine::Windows::WindowingSystem> tempWindowingSystem =
//            engine::EngineCore::getWindowingSystem();
//        engine::EngineCore::getMessagingSystem()->sendMessage(
//            temp, tempWindowingSystem.CastSharedPointer<engine::RTTI>(), reinterpret_cast<void*>(i_wParam));
//        break;
//    }
//    case WM_LBUTTONDOWN:
//    {
//        engine::utils::StringHash temp = engine::EngineCore::getStringPool()->FindString("MouseButtonDownEvent");
//        engine::SharedPointer<engine::MouseController> tempMouseController =
//            engine::EngineCore::getMouseInputController();
//        WindowsParam windowsParameter;
//        windowsParameter.windowsMessage = i_message;
//        windowsParameter.wParam         = i_wParam;
//        windowsParameter.lParam         = i_lParam;
//        engine::EngineCore::getMessagingSystem()->sendMessage(
//            temp, tempMouseController.CastSharedPointer<engine::RTTI>(), reinterpret_cast<void*>(&windowsParameter));
//        break;
//    }
//    case WM_MOUSEMOVE:
//    {
//        engine::utils::StringHash temp = engine::EngineCore::getStringPool()->FindString("MouseMoveEvent");
//        engine::SharedPointer<engine::MouseController> tempMouseController =
//            engine::EngineCore::getMouseInputController();
//        WindowsParam windowsParameter;
//        windowsParameter.windowsMessage = i_message;
//        windowsParameter.wParam         = i_wParam;
//        windowsParameter.lParam         = i_lParam;
//        engine::EngineCore::getMessagingSystem()->sendMessage(
//            temp, tempMouseController.CastSharedPointer<engine::RTTI>(), reinterpret_cast<void*>(&windowsParameter));
//        break;
//    }
//    case WM_LBUTTONUP:
//    {
//        engine::utils::StringHash temp = engine::EngineCore::getStringPool()->FindString("MouseButtonUpEvent");
//        engine::SharedPointer<engine::MouseController> tempMouseController =
//            engine::EngineCore::getMouseInputController();
//        WindowsParam windowsParameter;
//        windowsParameter.windowsMessage = i_message;
//        windowsParameter.wParam         = i_wParam;
//        windowsParameter.lParam         = i_lParam;
//        engine::EngineCore::getMessagingSystem()->sendMessage(
//            temp, tempMouseController.CastSharedPointer<engine::RTTI>(), reinterpret_cast<void*>(&windowsParameter));
//        break;
//    }
//
//    // The window's nonclient area is being destroyed
//    case WM_NCDESTROY:
//    {
//        // mWindowingSystem->s_mainWindow = nullptr;
//        // When the main window is destroyed
//        // a WM_QUIT message should be sent
//        // (if this isn't done the application would continue to run with no
//        // window). This is where the exitCode in WaitForShutdown() comes from:
//        // mWindowingSystem->s_mainWindow = nullptr;
//        engine::EngineCore::getWindowingSystem()->s_mainWindow = nullptr;
//        int exitCode                                           = 0;  // Arbitrary de facto success code
//        PostQuitMessage(exitCode);                                   // This sends a WM_QUIT message
//                                                                     // For WM_NCDESTROY messages, return 0 to
//                                                                     // indicate that it was processed
//
//        return 0;
//    }
//    }  // Switch
//       // Pass any messages that weren't handled on to Windows
//    return DefWindowProc(window, message, w_param, l_param);
//}

engine::WindowingSystem::~WindowingSystem()
{
    for (size_t window_iter = 0; window_iter < window_list_.size(); window_iter++)
    {
        window_list_[window_iter]->Shutdown();
        delete window_list_[window_iter];
        window_list_[window_iter] = nullptr;
    }

    window_list_.clear();

    if (main_window_)
    {
        main_window_->Shutdown();
        delete main_window_;
        main_window_ = nullptr;
    }
}
