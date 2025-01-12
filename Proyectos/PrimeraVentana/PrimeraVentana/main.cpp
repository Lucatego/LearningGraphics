//https://learn.microsoft.com/es-es/windows/win32/
#include <Windows.h>
#include <new> //Para el (std::nothrow)

//Definir una estructura para mantener información sobre estados
struct StateInfo {
	// Algunos miembros
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnSize(HWND hwnd, UINT flag, int width, int height);

inline StateInfo * GetAppState(HWND hwnd);

//Los _In_ y _In_opt_ son opcionales, pero indican que los parametros de entrada son solo de lectura.
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {
	//Nombre de la ventana
	const wchar_t CLASS_NAME[] = L"Mi primera ventana";

	/*
	* Windows Classes:
	* Una abstracción, por ejemplo, los botones son similares pero cada ventana tiene sus datos de instancia
	* Recordar que una ventana no es una clase, sino una estructura de datos usada por el SO.
	*/

	//La estructura con los datos para la ventana
	WNDCLASS wc = {};

	//Es un puntero a una funcion definida por la aplicacion (procedimiento de ventana)
	//Define el comportamiento de la ventana
	wc.lpfnWndProc = WindowProc; 
	//Identificador de instancia de la aplicacion, es algo así como el pid.
	wc.hInstance = hInstance;
	//Es una cadena para dar nombre a la clase
	wc.lpszClassName = CLASS_NAME;

	/*
	* Los nombres de las clases son locales para el proceso que está ejecutando la ventana.
	* Por lo tanto, los nombres deben ser unicos. Inclusive los controles estandar de Windows, por lo que
	* se deben elegir nombres que no entren en conflicto. Por ejemplo, Button para botón.
	*/

	//Registrar la clase ventana con el SO
	RegisterClass(&wc);

	//Estrucutra para los datos -> Las deberiamos inicializar antes de Crear la ventana
	StateInfo * pState = new (std::nothrow)StateInfo;
	if (pState == NULL) return 0;

	//Crear la ventana, devuelve el identificador de ventana.
	HWND hwnd = CreateWindowEx(
		0, //Permite especificar comportamientos como transparencia. 0 == Predeterminado
		CLASS_NAME, //Nombre de la clase ventana
		L"Aprendiendo ventanas en Windows", //El texto de la barra de título de la ventana
		WS_OVERLAPPEDWINDOW, //El estilo de la ventana, son marcas de bits, dan título, borde, etc...
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, //Para la posicion y el tamaño
		NULL, //Ventana padre
		NULL, //Menu de la ventana
		hInstance, //Identificador de instancia, para que el SO identifique el ejecutable cuando esté cargado en memoria
		pState //Un puntero a datos arbitarios tipo (void *), podría ser NULL
	);

	//Si no se pudo crear
	if (hwnd == 0) return 0;

	//Mostramos la ventana
	ShowWindow(hwnd, nCmdShow);

	/*
	* La aplicación GUI debe responder a: Eventos del usuario y Eventos del SO.
	* Windows usa un modelo de paso de mensajes. El SO se comunica con la ventana.
	* Un mensaje es un código numérico que designa un eveneto determinado.
	* Por ejemplo: #define WM_LBUTTONDOWN 0X0201 //Mensaje enviado al pulsar el botón izquierdo.
	* Algunos mensajes tienen más información asociada, por ejemplo, las coordenadas X e Y del lugar de la pulsación.
	* El SO llama al procedimiento de ventana registrado a esa ventana.
	*/

	//Mensajes de ventana
	MSG msg = {};

	//En bucle, la aplicación recibe miles de mensajes. Por lo general, retorna valores diferentes a 0
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		//Hace una traducción de pulsaciones del teclado a caracteres para que puedan ser interpretados.
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
	* - Publicar un mensaje: Pasar el mensaje a la cola de mensajes y enviarla a través del bucle a GetMessage y DispatchMessage
	* - Enviar un mensaje: El mensaje se salta la cola y el SO llama directamente a WindowProc.
	*/

	return 0;
}

//El procedimiento de ventana. Esta es la funcion encargada para procesar los eventos y mensajes para la ventana
//CALLBACK: Es la convención de llamada para la función.
//LRESULT es un valor entero que el programa devuelve a Windows. Es decir, contiene la respuesta al mensaje.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*
	* hwnd: Identificador de la ventana
	* uMsg: El código del mensaje
	* wParam y lParam: Datos adicionales al mensaje dependiendo de su código. (32 y 64 bits)
	*/
	StateInfo * pState;
	if (uMsg == WM_CREATE){
		/*
		* En este tipo de mensajes, el parametro lParam es un puntero a una estructura CREATESTRUCT.
		* Esta estructura contiene el puntero (void *) que se envió al crear la ventana.
		*/
		//Primero, se extrae el puntero a la estructura de datos, de LPARAM a CREATESTRUCT.
		CREATESTRUCT * pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
		//Uno de los miembros de la estructura CREATESTRUCT es un puntero al pState que enviamos al crear la ventana.
		pState = reinterpret_cast<StateInfo *>(pCreate->lpCreateParams);
		//Con esta ultima llamada, almacenamos el puntero StateInfo en los datos de la instancia de la ventana. Gracias a esto,
		//ahora podemos siempre devolver el estado con GetWindowLongPtr;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else{
		pState = GetAppState(hwnd);
	}

	switch (uMsg) {
		/*
		* Ya sea con el botón de cerrar o con ALT + F4, la ventana recibirá el mensaje VM_CLOSE.
		* Este mensaje ofrece la oportunidad de pedir al usuario una confirmación antes de cerrar la ventana.
		*/
		case WM_CLOSE:
			if (MessageBox(hwnd, L"¿Desea salir?", L"Mi ventana P1", MB_OKCANCEL) == IDOK) {
				//Para cerrar la ventana completamente
				DestroyWindow(hwnd);
			}
			//Caso contrario, no hace nada
			return 0;
		case WM_DESTROY:
			//Coloca una señal en a cola para que el bucle finalice
			PostQuitMessage(0);
			break;
		/*
		* Pintar la ventana:
		* Es decir, mostrar algo en la ventana.
		* Esto ocurrirar cuando el programa tenga que actualizar la apariencia de la ventana o cuando el SO mande
		* un mensaje para volver a pintar alguna parte de la ventana.
		* La primera vez que se muestra una ventana, se debe pintar toda el area de cliente. Nosotros somos los 
		* responsables de pintar esta área, los marcos y el resto del exterior será trabajo del SO.
		* La región de actualización debe ser borrada al terminar de pintar el área del cliente. Cada vez que alguna 
		* otra ventana oculte una parte de nuestra ventana, entonces, se tiene que volver a pintar esa parte luego de
		* que deje de estar oculta.
		* También, se tiene que volver a pintar al hacer resize a la ventana.
		* 
		*/
		case WM_PAINT: {
			//Estructura con datos para el pintado de la ventana.
			PAINTSTRUCT ps;
			//Esta funcion rellena la estructura PAINTSTRUCT con información sobre la solicitud de reintentos.
			//La región de actualización se indica en el atributo rcPaint de la estructura.
			HDC hdc = BeginPaint(hwnd, &ps);
			/*
			* Aca ocurre el pintado.
			* Hay 2 opciones: 
			* - Pintar todo el área del cliente, independientemente de la región de actualización pero
			* se recorta todo lo que quede fuera de la región de actualización. (Más sencillo)
			* - Solo pintar la parte de la ventana dentro de la región de actualización. (Más eficaz)
			* 
			* Esta línea rellena la región de actualización con el color de fondo definido por COLOR_WINDOW (Este
			* depende de lo elegido por el usuario.
			* En el segundo parametro enviamos las coordenadas a pintar.
			*/
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			//Esta función borra la región de actualización. Indica a Windows que se ha terminado la pintura.
			EndPaint(hwnd, &ps);
			return 0;
		}
		//Ejemplo de resize
		case WM_SIZE: {
			//LOWORD y HIWORD son macros. Su función es obtener los valores de ancho y alto de 16 bits de lParam.
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			//Respuesta en una función aparte.
			OnSize(hwnd, (UINT)wParam, width, height);
		}
	}
	//Esta función es la acción predeterminada para un mensaje, que varía según el tipo de mensaje.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

	/*
	* Evitar cuellos de botella:
	* Al ejecutar un procedimiento de ventana, bloquea cualquier otro mensaje para las ventanas creadase en el mismo 
	* subproceso. Así, evita un procesamiento largo del procedimiento de ventana.
	* Por ejemplo: 
	* Si el programa realiza una conexión TCP y espera indefinidamente al servidor. Si es que realizamos esa acción 
	* de conexión dentro del WindowProc, entonces, la ventana NO podrá procesar ningún otro mensaje hasta que le llegue
	* la respuesta del servidor.
	* Alternativas: Mover el trabajo a otro subproceso mediante la multitarea de Windows. (Hilos y procesos)
	* - Craer un nuevo subproceso.
	* - Usar un grupo de subprocesos.
	* - Llamadas de E/S asíncronas.
	* - Llamadas a procediminetos asíncronos
	*/
}

void OnSize(HWND hwnd, UINT flag, int width, int height) {
	//Aca se maneja el resize.
}

/*
* Cada ventana tiene sus propios datos de instancia, por lo que a cada una se le debe asignar su propia estrucutra de datos.
* Por ejemplo, si se define una clase ventana y se crean más ventanas de esa clase, podemos crear una clase de control personalizada.
* Resulta conveniente ajustar GetWindowLongPtr a una pequeña función.
*/
inline StateInfo * GetAppState(HWND hwnd){
	//Obtenemos el puntero a la estrucutra de datos.
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	//Convertir de el puntero a uno tipo StateInfo (La estructura de datos)
	StateInfo * pState = reinterpret_cast<StateInfo*>(ptr);
	return pState;
}