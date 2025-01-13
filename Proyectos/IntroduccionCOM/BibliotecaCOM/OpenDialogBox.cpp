#include <windows.h>
#include <shobjidl.h>

/*
    Para mostrar la ventana para abrir un archivo, usamos un objeto COM llamado
    Common Item Dialog, el cual implementa una interfaz llama IFileOpenDialog.
    - Estas estan incluidas en shobjidl.h

*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow){
    // Inicializamos la librería COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    
    if(SUCCEEDED(hr)){
        IFileOpenDialog * pFileOpen;

        // Creamos el objeto FileOpenDialog, Dialogo de elemeto común y obtenemos un puntero a la interfaz
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, 
            IID_IFileOpenDialog, reinterpret_cast<void ** >(&pFileOpen));
        
        if(SUCCEEDED(hr)){
            // Mostramos el Dialog Box al usuario
            hr = pFileOpen->Show(NULL);

            // Obtenemos el nombre del archivo desde el dialog box
            if(SUCCEEDED(hr)){
                IShellItem * pItem;
                /*
                    En este punto devolvemos un puntero a un objeto COM llamado
                    objeto de elemento shell, el cual implementa la interfaz 
                    IShellItem, representando al archivo seleccionado.
                */
                hr = pFileOpen->GetResult(&pItem);

                if(SUCCEEDED(hr)){
                    PWSTR pszFilePath;
                    // Obtiene la ruta de acceso al archivo
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Mostramos el nombre del archivo al usuario
                    if(SUCCEEDED(hr)){
                        MessageBoxW(NULL, pszFilePath, L"File Path: ", MB_OK);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        // Anular la inicializacion de la biblioteca COM
        CoUninitialize();
    }
    return 0;
}