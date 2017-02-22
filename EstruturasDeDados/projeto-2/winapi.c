/**
 * Tutorial:
 * https://codewars.wordpress.com/2009/09/18/c-criando-janelas-usando-apenas-codigo/
 */

// Cabeçalhos necessários
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * SCRW: Screen Width
 * SCRH: Screen Height
 */
#define SCRW GetSystemMetrics(SM_CXSCREEN)
#define SCRH GetSystemMetrics(SM_CYSCREEN)

/**
 * Dados da Aplicação
 */
#define APP_WIDTH 800
#define APP_HEIGHT 600
#define APP_X ( (SCRW - APP_WIDTH) / 2 )
#define APP_Y ( (SCRH - APP_HEIGHT) / 2 )
#define APP_TITLE "Fila de Impressão"

/**
 * Códigos da Aplicação
 */
#define APP_BTN_OK 8000
#define APP_KEY_EXIT 9000
#define APP_KEY_ABOUT 9001
#define APP_KEY_POVOAR 9002
#define APP_KEY_CREATE 9003
#define APP_KEY_EMPTY 9004
#define APP_KEY_MSG 9999

#define IDC_MAIN_EDIT   101
#define IDC_MAIN_TOOL   102
#define IDC_MAIN_STATUS 103
#define IDR_MAINMENU                    102
#define ID_FILE_OPEN                    40002
#define ID_FILE_SAVEAS                  40003
#define ID_FILE_NEW                     40004

#define IDR_MYMENU 101
#define ID_FILE_EXIT 9001
#define ID_STUFF_GO 9002

void MakeAboutWindow(HWND hwnd) {
	char * text = "2º Projeto de Estrutura de Dados.\n\nDesenvolvido por:\n- Mateus Tavares.\n- Ronily Gomes.\n\nProfessor:\n- Alex Sandro.";
   MessageBox(hwnd, text, "Sobre", MB_ICONINFORMATION | MB_OK);
}

void confirmExit(HWND hwnd) {
   int resp = MessageBox(hwnd, "Deseja realmente sair?", "Atenção!", MB_ICONWARNING | MB_YESNO);

   // If YES, do...
   if (resp == 6) {
      PostMessage(hwnd, WM_CLOSE, 0, 0);
   }
}

void EmptyList(HWND hwnd) {
   int resp = MessageBox(hwnd, "Deseja realmente esvaziar\na lista de impressão?", "Atenção!", MB_ICONWARNING | MB_YESNO);

   // If YES, do...
   if (resp == 6) {
      // Limpa a lista
   }
}

HWND usuario;
void CreateItem(HWND hwnd){
	CreateWindowEx (
		0,
		"STATIC",
		"Cateto a",
		WS_VISIBLE|WS_CHILD,
		30, 20, 60, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);

	usuario = CreateWindowEx (
		WS_EX_CLIENTEDGE,
		"EDIT",
		"",
		WS_VISIBLE|WS_CHILD|WS_BORDER,
		30, 50, 50, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
}

void AutoCreate(HWND hwnd){
	CreateWindowEx (
		0,
		"STATIC",
		"Cateto a",
		WS_VISIBLE|WS_CHILD,
		30, 20, 60, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
}

void DrawAppMenuBar(HWND hwnd) {
   // Create menu
   HMENU hMenu, hSubMenu;

   hMenu = CreateMenu();

   hSubMenu = CreatePopupMenu();
   AppendMenu(hSubMenu, MF_STRING, APP_KEY_CREATE, "&Nova Impressão");
   AppendMenu(hSubMenu, MF_STRING, APP_KEY_POVOAR, "&Auto Inserir");
   AppendMenu(hSubMenu, MF_STRING, APP_KEY_EMPTY, "&Limpar Lista");
   AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hSubMenu, "&Impressões");

   AppendMenu(hMenu, MF_STRING, APP_KEY_MSG, "&Message");
   AppendMenu(hMenu, MF_STRING, APP_KEY_ABOUT, "S&obre");
   AppendMenu(hMenu, MF_STRING, APP_KEY_EXIT, "&Sair");

   SetMenu(hwnd, hMenu);
}

void DrawAppStatusBar(HWND hwnd) {
   // Create Status bar
   HWND hStatus;
   int statwidths[] = {
      150,
      300,
      -1
   }; // Pixel Coordenates

   hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
      WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
      hwnd, (HMENU) IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);

   SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths) / sizeof(int), (LPARAM) statwidths);

   char total[50];
   sprintf(total, "Total: %d", 30);
   SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM) total);

   sprintf(total, "Pendentes: %d", 30);
   SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM) total);

   sprintf(total, "De novo: %d", 30);
   SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM) total);
}

void DrawComponents(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
   DrawAppMenuBar(hwnd);
   DrawAppStatusBar(hwnd);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
   switch (message) {
   case WM_CREATE: // Criação da janela
      DrawComponents(hwnd, message, wParam, lParam);
      break;
   case WM_COMMAND:
      switch (LOWORD(wParam)) {
      	case APP_KEY_CREATE:
      		CreateItem(hwnd);
      		break;
      	case APP_KEY_POVOAR:
      		AutoCreate(hwnd);
      		//UpdateWindow(hwnd);
      		break;
	      case APP_KEY_EXIT:
	         confirmExit(hwnd);
	         break;
	      case APP_KEY_MSG:
	         MessageBox(NULL, "10", "Resultado", MB_OK);
	         break;
	      case APP_KEY_ABOUT:
	      	MakeAboutWindow(hwnd);
	         break;
	      case APP_KEY_EMPTY:
	         EmptyList(hwnd);
	         //UpdateWindow(hwnd);
	         break;
      }
      break;
   case WM_DESTROY: // Destruição da janela
      PostQuitMessage(0);
      break;
   default:
      return DefWindowProc(hwnd, message, wParam, lParam);
   }
   return 0;
}

// WinMain, a função main em janelas
int WINAPI WinMain(HINSTANCE hThisInstance,
   HINSTANCE hPrevInstance,
   LPSTR lpszArgument,
   int nFunsterStil) {

   HWND hwnd; // O objeto para indicar a janela
   MSG messages; // Objeto mensagem do Windows para controlar o acionamento de botões
   WNDCLASSEX wincl; // O objeto para criar a janela

   wincl.hInstance = hThisInstance;
   wincl.lpszClassName = "WindowsAppl"; // Nome da classe da janela
   wincl.lpfnWndProc = WindowProcedure;
   wincl.style = CS_DBLCLKS;
   wincl.cbSize = sizeof(WNDCLASSEX);
   wincl.hIcon = (HICON) LoadImage( // returns a HANDLE so we have to cast to HICON
      NULL, // hInstance must be NULL when loading from a file
      "impressora.ico", // the icon file name
      IMAGE_ICON, // specifies that the file is an icon
      0, // width of the image (we'll specify default later on)
      0, // height of the image
      LR_LOADFROMFILE | // we want to load a file (as opposed to a resource)
      LR_DEFAULTSIZE | // default metrics based on the type (IMAGE_ICON, 32x32)
      LR_SHARED // let the system release the handle when it's no longer used
   );
   wincl.hIconSm = (HICON) LoadImage( // returns a HANDLE so we have to cast to HICON
      NULL, // hInstance must be NULL when loading from a file
      "impressora.ico", // the icon file name
      IMAGE_ICON, // specifies that the file is an icon
      0, // width of the image (we'll specify default later on)
      0, // height of the image
      LR_LOADFROMFILE | // we want to load a file (as opposed to a resource)
      LR_DEFAULTSIZE | // default metrics based on the type (IMAGE_ICON, 32x32)
      LR_SHARED // let the system release the handle when it's no longer used
   );
   wincl.hCursor = LoadCursor(NULL, IDC_ARROW); //Cursor default
   wincl.lpszMenuName = NULL;
   wincl.cbClsExtra = 0;
   wincl.cbWndExtra = 0;
   wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND + 1; // Cor cinza de background

   if (!RegisterClassEx( & wincl)) // Se o registro da classe foi mal-sucedido return 0
      return 0;

   hwnd = CreateWindowEx( // Criação da janela
      0,
      "WindowsAppl", // Indicação da classe da janela
      APP_TITLE, // Nome da janela
      (WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU), // Estilo da janela: Desabilitado resize - maximize
      APP_X, // x em relação ao desktop
      APP_Y, // y em relação ao desktop
      APP_WIDTH, // largura da janela
      APP_HEIGHT, // altura da janela
      HWND_DESKTOP,
      NULL,
      hThisInstance,
      NULL
   );

   ShowWindow(hwnd, nFunsterStil); // Mostrar a janela

   while (GetMessage( & messages, NULL, 0, 0)) // Recuperar mensagens
   {
      TranslateMessage( & messages);
      DispatchMessage( & messages);
   }

   return messages.wParam;
}
