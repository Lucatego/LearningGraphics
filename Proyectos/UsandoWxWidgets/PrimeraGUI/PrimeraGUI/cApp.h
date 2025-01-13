#pragma once

/*
 * WxWidgets: Usa WinApi para los proyectos en Widows.
 * Recordar que debemos configurar la solución para que sea compatible con las librerías.
 */

#include "wx/wx.h"

#include "cMain.h"

// The launcher for the application
class cApp : public wxApp{
private:
	cMain * mainFrame = nullptr;
public:
	cApp();
	~cApp();

	virtual bool OnInit();
};

