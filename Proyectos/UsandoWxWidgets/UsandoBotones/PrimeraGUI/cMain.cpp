#include "cMain.h"

/*
 * Nuevamente, usamos macros, enviamos la clase que la usar� y su clase padre de esta.
 * Esto es necesario para asociar la funci�n que procesa el evento del bot�n con el bot�n en 
 * s�.
 */ 
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

// Esta clase ser� la que contenga la GUI
cMain::cMain(): wxFrame(nullptr, wxID_ANY, "First_wxWidget_Window"){
	// Creamos los n * m botones que deseamos
	btnArr = new wxButton * [fieldHeight * fieldWidth];
	field = new int[fieldHeight * fieldWidth];
	// Usamos una matriz para ubicar a todos los botones
	wxGridSizer * grid = new wxGridSizer(fieldWidth, fieldHeight, 0, 0);
	// Recorreos la matriz de botones para crearlos
	for (int x = 0; x < fieldWidth; x++){
		for (int y = 0; y < fieldHeight; y++){
			int pos = y * fieldWidth + x;
			// Uno por uno
			btnArr[pos] = new wxButton(this, 10000 + (pos));
			/*
			 * Agregamos los botone a la matriz
			 * wxEXPAND y wxALL indican que ocupen todo el espacio disponible y que se expandan lo necesario
			 */
			grid->Add(btnArr[pos], 1, wxEXPAND | wxALL);
			// Enlazamos el bot�n con la funci�n
			btnArr[pos]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
		}
	}
	// Especificamos a nuestra ventana que tipo de grilla usar.
	this->SetSizer(grid);
	// Indicamos que se reestructure seg�n los nuevos datos
	grid->Layout();
}

cMain::~cMain(){
	// wxWidgets se encargar� de hacer los deletes correspondientes cuando sea seguro (de s� mismo).
	// No es necesario eliminar los botones en s�, pero s� el arreglo que contiene a los punteros a botones
	delete[] btnArr;
}

// Metodos
void cMain::OnButtonClicked(wxCommandEvent & event){
	int x = (event.GetId() - 10000) % fieldWidth;
	int y = (event.GetId() - 10000) / fieldWidth;

	if(firstClick){
		int mines = 15;
		while(mines){

		}
	}

	event.Skip();
}
