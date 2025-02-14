#include <Windows.h>

template <class DERIVED_TYPE>
class BaseWindow{
public:
    //El procedimiento de ventana, debe ser est�tico ya que debe ser pasado como puntero a funci�n.
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
        DERIVED_TYPE * pThis = NULL;

        if (uMsg == WM_NCCREATE){
            CREATESTRUCT * pCreate = (CREATESTRUCT *)lParam;
            pThis = (DERIVED_TYPE *)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hwnd = hwnd;
        }
        else{
            pThis = (DERIVED_TYPE *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }

        if (pThis){
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else{
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    //Constructor para inicializar ese parametro en NULL
    BaseWindow() : m_hwnd(NULL) {/*Ac� el par�metro ya est� inicilaizado*/}

    //Ac� se crea la ventana
    BOOL Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, 
            int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, HWND hWndParent = 0, HMENU hMenu = 0){

        WNDCLASS wc = { 0 };

        wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        RegisterClass(&wc);
        //Creamos la ventana y la guardamos en el atributo de HWND
        m_hwnd = CreateWindowEx(
            dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
        );
        //Por ahora no hay loop
        return (m_hwnd ? TRUE : FALSE);
    }

    HWND Window() const { return m_hwnd; }

protected:
    //Lo vuelve abstracta
    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
    //Lo que se inicializa
    HWND m_hwnd;
};
