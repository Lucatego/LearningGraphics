#include <iostream>

#include <windows.h>

/*
 * ¿Que es lo que debemos saber?
 * 1. P: POINTER, W: WIDE
 * 2. Hungarian Notation: Añadir prefijos a los nombres de las variables, por
 * ejemplo, i de index, cb de "count of bytes" -> cbVariable, o iList
 * 3. Windows usa cadenas Unicode, es decir, usa caracteres de 16 bits y no
 * los clásicos de ANSI de 8.
 * 4. WCHAR: Wide Char, para UTF-16
 */

void probandoTipos(){
	//Colocamos L para indicar que son caracteres UTF-16
	wchar_t myName[32] = L"Juan Perez";
	//Ojo: wcout es para imprimir caracteres de 16 bits (wchar_t)
	std::wcout << L"Usando wcout: " << myName << std::endl;
	std::cout << "Usando cout: " << myName << std::endl;

	//Usando TCHAR, dependiendo de la plataforma, entonces usará char o wchar_t
	//No obstante, hoy en día, todas las aplicaciones deberian usar Unicode
	//para trabajar con Windows.
}

void probandoVentanas(){
	/*
	 * La clásica ventana, main window o aplication windows, tiene un frame con
	 * un title bar. Botones de minimizar y maximizar y otros elementos estandar
	 * de la UI.
	 * El frame es llamado non-client area de la ventana, esto es debido a que
	 * el sistema operativo se encarga de manejar esa porción de la ventana.
	 * El area dentro del marco (frame) se llama client area. Esta es la parte
	 * que nuestro programa maneja.
	 * De hecho, todos son ventanas, los botones, cajas y otros elementos UI,
	 * son en sí, ventanas.
	 * La diferencias entre los elementos UI (ventanas) y las ventanas de
	 * aplicación (application window) es que los elementos UI no existen por
	 * sí solos, dependen de un application window. Por esto, ambos deben
	 * comunicarse.
	 * Window: A programming construct, no solo un application windows.
	 *		- ocupa una parte de la pantalla
	 *		- Puede ser o no ser visible
	 *		- Sabe como dibujarse a sí mismo
	 *		- Responde a eventos del usuario o sistema operativo.
	 *
	 */
}

int main(int __argc, char ** __argv){
	//De la guia de Microsoft.
	probandoTipos();
	//Inicio con las ventanas
	probandoVentanas();
	return 0;
}
