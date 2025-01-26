#include "cApp.h"

// Una macro que debe usarse una unica vez con la clase que tendra el programa
wxIMPLEMENT_APP(cApp);

// Esta clase no mostrará nada, solo nos da el punto de inicio
cApp::cApp(){}

cApp::~cApp(){}

bool cApp::OnInit(){
	mainFrame = new cMain();
	mainFrame->Show();
	return true;
}
