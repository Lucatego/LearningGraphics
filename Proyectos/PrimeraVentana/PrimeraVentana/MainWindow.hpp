#include "BaseWindow.hpp"

//Una clase hija
class MainWindow :public BaseWindow<MainWindow> {
public:
    //Se define el nombre de la clase
	PCWSTR ClassName() const {
		return L"Ventana de ejemplo";
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){
        switch (uMsg){
            //Cerar la ventana
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            //Pintar
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(m_hwnd, &ps);
                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
                EndPaint(m_hwnd, &ps);
            }
                return 0;
            //Ninguna de las anteriores
            default:
                return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
        return TRUE;
    }
};

/*
//Como se verian los metodos usando clases
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow){
    //Una instancia de MainWindow
    MainWindow win;
    //Se crea usando el método de la clase abstracta
    if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW)){
        return 0;
    }
    //Se muestra la ventana
    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
*/