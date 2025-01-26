#pragma once

#include "wx/wx.h"

// The starter of the GUI
class cMain: public wxFrame{
public: // Atributos
	int fieldWidth = 10;
	int fieldHeight = 10;
	wxButton ** btnArr = nullptr;

	int * field = nullptr;
	bool firstClick = true;

public: // Constructores
	cMain();
	~cMain();

public: // Metodos
	void OnButtonClicked(wxCommandEvent & event);

	// Macro que define una tabla de eventos para la GUI
	wxDECLARE_EVENT_TABLE();
};

