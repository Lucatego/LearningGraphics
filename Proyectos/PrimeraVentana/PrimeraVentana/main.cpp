#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Los _In_ y _In_opt_ son opcionales, pero indican que los parametros de entrada son solo de lectura.
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {
	//Nombre de la ventana
	const wchar_t CLASS_NAME[] = L"Mi primera ventana";

	/*
	* Windows Classes:
	* Una abstracci�n, por ejemplo, los botones son similares pero cada ventana tiene sus datos de instancia
	* Recordar que una ventana no es una clase, sino una estructura de datos usada por el SO.
	*/

	//La estructura con los datos para la ventana
	WNDCLASS wc = {};

	//Es un puntero a una funcion definida por la aplicacion (procedimiento de ventana)
	//Define el comportamiento de la ventana
	wc.lpfnWndProc = WindowProc; 
	//Identificador de instancia de la aplicacion, es algo as� como el pid.
	wc.hInstance = hInstance;
	//Es una cadena para dar nombre a la clase
	wc.lpszClassName = CLASS_NAME;

	/*
	* Los nombres de las clases son locales para el proceso que est� ejecutando la ventana.
	* Por lo tanto, los nombres deben ser unicos. Inclusive los controles estandar de Windows, por lo que
	* se deben elegir nombres que no entren en conflicto. Por ejemplo, Button para bot�n.
	*/

	//Registrar la clase ventana con el SO
	RegisterClass(&wc);

	//Crear la ventana, devuelve el identificador de ventana.
	HWND hwnd = CreateWindowEx(
		0, //Permite especificar comportamientos como transparencia. 0 == Predeterminado
		CLASS_NAME, //Nombre de la clase ventana
		L"Aprendiendo ventanas en Windows", //El texto de la barra de t�tulo de la ventana
		WS_OVERLAPPEDWINDOW, //El estilo de la ventana, son marcas de bits, dan t�tulo, borde, etc...
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, //Para la posicion y el tama�o
		NULL, //Ventana padre
		NULL, //Menu de la ventana
		hInstance, //Identificador de instancia, para que el SO identifique el ejecutable cuando est� cargado en memoria
		NULL //Un puntero a datos arbitarios tipo (void *)
	);

	//Si no se pudo crear
	if (hwnd == 0) return 0;

	//Mostramos la ventana
	ShowWindow(hwnd, nCmdShow);

	/*
	* La aplicaci�n GUI debe responder a: Eventos del usuario y Eventos del SO.
	* Windows usa un modelo de paso de mensajes. El SO se comunica con la ventana.
	* Un mensaje es un c�digo num�rico que designa un eveneto determinado.
	* Por ejemplo: #define WM_LBUTTONDOWN 0X0201 //Mensaje enviado al pulsar el bot�n izquierdo.
	* Algunos mensajes tienen m�s informaci�n asociada, por ejemplo, las coordenadas X e Y del lugar de la pulsaci�n.
	* El SO llama al procedimiento de ventana registrado a esa ventana.
	*/

	//Mensajes de ventana
	MSG msg = {};

	//En bucle, la aplicaci�n recibe miles de mensajes. Por lo general, retorna valores diferentes a 0
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		//Hace una traducci�n de pulsaciones del teclado a caracteres para que puedan ser interpretados.
		TranslateMessage(&msg);
		/*
		* Informa al SO para que llame al procedimiento de ventana (WindowProc).
		* 1. El SO coloca un mensaje en la cola
		* 2. El programa llama a GetMessage.
		* 3. GetMessage extrae el  mensaje de la cola y llena la estructura msg.
		* 4. Se llaman a TranslateMessage y DispatchMessage.
		* 5. En DispatchMessage el SO llama a WindowProc.
		* 6. El procedimiento de ventana decide que hacer con el mensaje.
		*/
		DispatchMessage(&msg);
	}

	/*
	* Uso de PostQuitMessage: Coloca un mensaje WM_QUIT, en la cola de mensajes, este mensaje es especial, ya que, 
	* fuerza a GetMessage a devolver 0.
	*/

	/*
	* - Publicar un mensaje: Pasar el mensaje a la cola de mensajes y enviarla a trav�s del bucle a GetMessage y DispatchMessage
	* - Enviar un mensaje: El mensaje se salta la cola y el SO llama directamente a WindowProc.
	*/

	return 0;
}

//El procedimiento de ventana. Esta es la funcion encargada para procesar los eventos y mensajes para la ventana
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
