
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

bool engine::Window::Initialize()
{
    if (wnd_attributes_.title_caption.empty())
    {
        wnd_attributes_.title_caption = "Amit Prakash's - WindowsUtil Game";
    }

    constexpr DWORD window_style         = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    constexpr DWORD windowStyle_extended = WS_EX_OVERLAPPEDWINDOW;
    constexpr int   width                = CW_USEDEFAULT;
    constexpr int   height               = CW_USEDEFAULT;
    constexpr int   position_x           = CW_USEDEFAULT;
    constexpr int   position_y           = CW_USEDEFAULT;
    constexpr HWND  parent               = nullptr;
    constexpr HMENU menu                 = nullptr;
    const HINSTANCE instance             = static_cast<HINSTANCE>(wnd_attributes_.module_handle);
    void*           userData             = nullptr;

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
                                            userData);
        if (window_handle == nullptr)
        {
            const char* errorCaption = "No Main Window";
            std::string errorMessage("Windows failed to create the main window: ");
            errorMessage += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR);
            return nullptr;
        }

        const int desiredWidth  = wnd_attributes_.width;
        const int desiredHeight = wnd_attributes_.height;

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
            std::string errorMessage("Windows failed to get the coordinates of the main window: ");
            errorMessage += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, errorMessage.c_str(), nullptr, MB_OK | MB_ICONERROR);
            return nullptr;
        }

        // Get the dimensions of the client area
        RECT client_dimensions;
        if (GetClientRect(window_handle, &client_dimensions) == FALSE)
        {
            std::string errorMessage(
                "Windows failed to get the dimensions of the main window's client "
                "area: ");
            errorMessage += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, errorMessage.c_str(), nullptr, MB_OK | MB_ICONERROR);
            return nullptr;
        }

        // Get the difference between them
        non_client_area_size.width  = (window_coordinates.right - window_coordinates.left) - client_dimensions.right;
        non_client_area_size.height = (window_coordinates.bottom - window_coordinates.top) - client_dimensions.bottom;

        // Resize the window
        BOOL shouldTheResizedWindowBeRedrawn = TRUE;
        if (MoveWindow(window_handle,
                       window_coordinates.left,
                       window_coordinates.top,
                       desiredWidth + non_client_area_size.width,
                       desiredHeight + non_client_area_size.height,
                       shouldTheResizedWindowBeRedrawn) == FALSE)
        {
            std::string errorMessage("Windows failed to resize the main window: ");
            errorMessage += ErrorHandler()->GetFormattedLastError();
            MessageBox(nullptr, errorMessage.c_str(), nullptr, MB_OK | MB_ICONERROR);
            return nullptr;
        }

        // Display the window in the initial state that Windows requested
        ShowWindow(window_handle, wnd_attributes_.show_state);

        return true;
    }

    return false;
}

bool engine::Window::Shutdown()
{
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
        const char* errorCaption = "No Main Window Class";
        std::string errorMessage("Windows failed to register the main window's class: ");
        errorMessage += ErrorHandler()->GetFormattedLastError();
        MessageBox(nullptr, errorMessage.c_str(), errorCaption, MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}
