#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Los _In_ y _In_opt_ son opcionales, pero indican que los parametros de entrada son solo de lectura.
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {
	//Nombre de la ventana
	const wchar_t CLASS_NAME[] = L"Mi primera ventana";

	//La estructura con los datos para la ventana
	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	//Registrar la ventana
	RegisterClass(&wc);

	//Crear la ventana
	HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Aprendiendo ventanas en Windows", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	//Si no se pudo crear
	if (hwnd == 0) return 0;

	//Mostramos la ventana
	ShowWindow(hwnd, nCmdShow);

	//En bucle
	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			//Aca ocurre el pintado
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
