
#include "win32_includes.h"
#include "win32_resource.h"
#include "platform/platform_systems.h"
#include "platform/platform_objects.h"
#include "common/string_util.h"

engine::FilePath::FilePath(const std::string& file_abs_path)
{
    Init(file_abs_path);
}

engine::FilePath::FilePath(const std::string& dir, const std::string& file_name)
{
    Init(dir + "\\" + file_name);
}

std::string_view engine::FilePath::ParentDirectory() const
{
    return file_parent_directory_;
}

void engine::FilePath::Init(const std::string& abs_path)
{
    if (!abs_path.empty())
    {
        file_abs_path_         = engine_string_util::ToWinFilePath(abs_path);
        file_parent_directory_ = engine_string_util::GetWinDirFromAbsPath(abs_path);
    }
}

engine::FileMetaData::FileMetaData(const FilePath& file_path)
{
    std::string temp_path_string = file_path.AsCharArray();

    if (!temp_path_string.empty())
    {
        size_t pos = temp_path_string.find_last_of('.');
        file_extension_ =
            std::string(temp_path_string.cbegin() + static_cast<size_t>(pos + 1), temp_path_string.cend());
        size_t last_separator        = temp_path_string.find_last_of('\\');
        file_name_without_extension_ = std::string(temp_path_string.cbegin() + static_cast<size_t>(last_separator + 1),
                                                   temp_path_string.cbegin() + static_cast<size_t>(pos));
        file_name_ =
            std::string(temp_path_string.cbegin() + static_cast<size_t>(last_separator + 1), temp_path_string.cend());
    }
}

engine::WindowAttributes::WindowAttributes(int in_width, int in_height)
{
    parent_window = nullptr;
    module_handle = GetModuleHandle(nullptr);
    icon          = nullptr;
    small_icon    = nullptr;
    cursor        = nullptr;
    background    = nullptr;
    width         = in_width;
    height        = in_width;
    class_name    = "Default window";
    menu_name     = "Default window";
    title_caption = "Default window";
    wnd_proc      = nullptr;
    show_state    = 1;
}

bool engine::Window::Initialize()
{
    constexpr DWORD window_style         = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    constexpr DWORD windowStyle_extended = WS_EX_OVERLAPPEDWINDOW;
    constexpr int   width                = CW_USEDEFAULT;
    constexpr int   height               = CW_USEDEFAULT;
    constexpr int   position_x           = CW_USEDEFAULT;
    constexpr int   position_y           = CW_USEDEFAULT;
    constexpr HWND  parent               = nullptr;
    constexpr HMENU menu                 = nullptr;
    const HINSTANCE instance             = static_cast<HINSTANCE>(wnd_attributes_.module_handle);
    void*           user_data            = nullptr;

    if (RegisterWindowClass())
    {
        HWND window_handle = CreateWindowEx(windowStyle_extended,
                                            wnd_attributes_.class_name.c_str(),
                                            wnd_attributes_.title_caption.c_str(),
                                            window_style,
                                            position_x,
                                            position_y,
                                            width,
                                            height,
                                            parent,
                                            menu,
                                            instance,
                                            user_data);

        if (window_handle == nullptr)
        {
            const char* error_caption = "No Main Window";
            std::string error_message("Windows failed to create the main window: ");
            error_message += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, error_message.c_str(), error_caption, MB_OK | MB_ICONERROR);
            return false;
        }

        const int desired_width  = wnd_attributes_.width;
        const int desired_height = wnd_attributes_.height;

        // Calculate how much of the window is coming from the "non-client area"
        // (the borders and title bar)
        RECT window_coordinates;
        struct
        {
            long width;
            long height;
        } non_client_area_size;

        // Get the coordinates of the entire window
        if (GetWindowRect(window_handle, &window_coordinates) == FALSE)
        {
            std::string error_message("Windows failed to get the coordinates of the main window: ");
            error_message += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, error_message.c_str(), nullptr, MB_OK | MB_ICONERROR);
            return false;
        }

        // Get the dimensions of the client area
        RECT client_dimensions;
        if (GetClientRect(window_handle, &client_dimensions) == FALSE)
        {
            std::string error_message(
                "Windows failed to get the dimensions of the main window's client "
                "area: ");
            error_message += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, error_message.c_str(), nullptr, MB_OK | MB_ICONERROR);
            return false;
        }

        // Get the difference between them
        non_client_area_size.width  = (window_coordinates.right - window_coordinates.left) - client_dimensions.right;
        non_client_area_size.height = (window_coordinates.bottom - window_coordinates.top) - client_dimensions.bottom;

        // Resize the window
        BOOL should_the_resized_window_be_redrawn = TRUE;
        if (MoveWindow(window_handle,
                       window_coordinates.left,
                       window_coordinates.top,
                       desired_width + non_client_area_size.width,
                       desired_height + non_client_area_size.height,
                       should_the_resized_window_be_redrawn) == FALSE)
        {
            std::string error_message("Windows failed to resize the main window: ");
            error_message += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, error_message.c_str(), nullptr, MB_OK | MB_ICONERROR);
            return false;
        }

        // Display the window in the initial state that Windows requested
        ShowWindow(window_handle, wnd_attributes_.show_state);
        wnd_handle_ = window_handle;

        return true;
    }

    return false;
}

bool engine::Window::Shutdown()
{
    bool success = true;
    if (wnd_attributes_.module_handle != nullptr)
    {
        if (UnregisterClass(wnd_attributes_.class_name.c_str(),
                            static_cast<HINSTANCE>(wnd_attributes_.module_handle)) == FALSE)
        {
            const char* error_caption = "Couldn't Unregister Main Window Class";
            std::string error_message("Windows failed to unregister the main window's class: ");
            error_message += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, error_message.c_str(), error_caption, MB_OK | MB_ICONERROR);
            success &= false;
        }
        else
        {
            wnd_attributes_.module_handle = nullptr;
        }
    }

    if (success)
    {
        if (DestroyWindow(static_cast<HWND>(wnd_handle_)) == FALSE)
        {
            const char* error_caption = "Couldn't Destroy Main Window";
            std::string error_message("Windows failed to destroy the main window: ");
            error_message += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, error_message.c_str(), error_caption, MB_OK | MB_ICONERROR);
            success &= false;
        }
        else
        {
            wnd_handle_ = nullptr;
        }
    }

    return success;
}

void engine::Window::Show()
{
    while (1)
    {
        
    }
}

bool engine::Window::RegisterWindowClass()
{
    WNDCLASSEX wnd_class_ex = {};
    wnd_class_ex.cbSize     = sizeof(WNDCLASSEX);
    wnd_class_ex.hInstance  = static_cast<HINSTANCE>(wnd_attributes_.module_handle);
    wnd_class_ex.style      = 0;

    if (wnd_attributes_.wnd_proc == nullptr)
    {
        wnd_class_ex.lpfnWndProc = DefWindowProc;
    }

    wnd_class_ex.cbClsExtra = 0;

    wnd_class_ex.cbWndExtra = 0;
    if (wnd_attributes_.icon == nullptr)
    {
        wnd_class_ex.hIcon = LoadIcon(wnd_class_ex.hInstance, MAKEINTRESOURCE(IDI_BIG));
    }

    if (wnd_attributes_.small_icon == nullptr)
    {
        wnd_class_ex.hIconSm = LoadIcon(wnd_class_ex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    }

    if (wnd_attributes_.cursor == nullptr)
    {
        wnd_class_ex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    }

    if (wnd_attributes_.background)
    {
        wnd_class_ex.hbrBackground = static_cast<HBRUSH>(IntToPtr(COLOR_BACKGROUND + 1));
    }

    wnd_class_ex.lpszMenuName  = wnd_attributes_.menu_name.c_str();
    wnd_class_ex.lpszClassName = wnd_attributes_.class_name.c_str();

    const ATOM registered_class = RegisterClassEx(&wnd_class_ex);

    if (registered_class == NULL)
    {
        const char* error_caption = "No Main Window Class";
        std::string error_message("Windows failed to register the main window's class: ");
        error_message += ErrorHandler()->GetFormattedLastError();
        MessageBox(nullptr, error_message.c_str(), error_caption, MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}
