#pragma once

#include "wx/wx.h"

// The starter of the GUI
class cMain: public wxFrame{
public: // Atributos
	wxButton * btn1 = nullptr;
	wxTextCtrl * txt1 = nullptr;
	wxListBox * lb1 = nullptr;

public: // Constructores
	cMain();
	~cMain();

public: // Metodos
	void OnButtonClicked(wxCommandEvent & event);

	// Macro que define una tabla de eventos para la GUI
	wxDECLARE_EVENT_TABLE();
};

