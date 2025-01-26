#include "cMain.h"

/*
 * Nuevamente, usamos macros, enviamos la clase que la usará y su clase padre de esta.
 * Esto es necesario para asociar la función que procesa el evento del botón con el botón en 
 * sí.
 */ 
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
// Enviamos el WindowID del botón y el nombre del método
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

// Esta clase será la que contenga la GUI
cMain::cMain(): wxFrame(nullptr, wxID_ANY, "First_wxWidget_Window"){
	btn1 = new wxButton(this, 10001, "Soy un botón", wxPoint(10, 10), wxSize(100, 50));
	txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 80), wxSize(100, 20));
	lb1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(100, 100));
}

cMain::~cMain(){
	//wxWidgets se encargará de hacer los deletes correspondientes cuando sea seguro.
}

// Metodos
void cMain::OnButtonClicked(wxCommandEvent & event){
	this->lb1->AppendString(txt1->GetValue());
	event.Skip();
}
