#include "cMain.h"

/*
 * Nuevamente, usamos macros, enviamos la clase que la usar� y su clase padre de esta.
 * Esto es necesario para asociar la funci�n que procesa el evento del bot�n con el bot�n en 
 * s�.
 */ 
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
// Enviamos el WindowID del bot�n y el nombre del m�todo
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

// Esta clase ser� la que contenga la GUI
cMain::cMain(): wxFrame(nullptr, wxID_ANY, "First_wxWidget_Window"){
	btn1 = new wxButton(this, 10001, "Soy un bot�n", wxPoint(10, 10), wxSize(100, 50));
	txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 80), wxSize(100, 20));
	lb1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(100, 100));
}

cMain::~cMain(){
	//wxWidgets se encargar� de hacer los deletes correspondientes cuando sea seguro.
}

// Metodos
void cMain::OnButtonClicked(wxCommandEvent & event){
	this->lb1->AppendString(txt1->GetValue());
	event.Skip();
}
