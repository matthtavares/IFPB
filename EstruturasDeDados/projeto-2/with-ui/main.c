/**
 * Tutorial:
 * https://codewars.wordpress.com/2009/09/18/c-criando-janelas-usando-apenas-codigo/
 */

// Cabeçalhos necessários
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

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
#define APP_MENU_ID 7000
#define APP_LIST_ITENS 7001
#define APP_BTN_OK 8000
#define APP_KEY_EXIT 9000
#define APP_KEY_ABOUT 9001
#define APP_KEY_POVOAR 9002
#define APP_KEY_CREATE 9003
#define APP_KEY_EMPTY 9004
#define APP_KEY_UPDATE 9005
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

/// ID's Elements
#define ID_EDIT_PRT 500
#define ID_EDIT_USR 501
#define ID_EDIT_DOC 502
#define ID_EDIT_PAG 503

HWND parentHwnd = NULL;
char parentWndClass[] = "WindowMainAppl";

HWND childHwnd = NULL;
char childWndClass[] = "WindowChildAppl";

typedef struct {
   HWND prioridade;
   HWND usuario;
   HWND paginas;
   HWND documento;
} hwndImpressao;

hwndImpressao wndImpressao;

lista lst;

void MakeAboutWindow() {
	char *text = "2º Projeto de Estrutura de Dados.\n\nDesenvolvido por:\n- Mateus Tavares.\n- Ronily Gomes.\n\nProfessor:\n- Alex Sandro.";
   MessageBox(parentHwnd, text, "Sobre", MB_ICONINFORMATION | MB_OK);
}

void confirmExit() {
   int resp = MessageBox(parentHwnd, "Deseja realmente sair?", "Atenção!", MB_ICONWARNING | MB_YESNO);

   // If YES, do...
   if (resp == 6) {
      limpar(&lst);
      PostMessage(parentHwnd, WM_CLOSE, 0, 0);
   }
}

void EmptyList() {
   int resp = MessageBox(parentHwnd, "Deseja realmente esvaziar\na lista de impressão?", "Atenção!", MB_ICONWARNING | MB_YESNO);

   // If YES, do...
   if (resp == 6) {
      limpar(&lst);
   }
}

void CreateItem(){
   /**
    * Create the child window.
    */
   childHwnd = CreateWindowEx( // Criação da janela
      0,
      childWndClass, // Indicação da classe da janela
      "Criar novo item", // Nome da janela
      WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_SYSMENU, // Estilo da janela: Desabilitado resize - maximize
      APP_X, // x em relação ao desktop
      APP_Y, // y em relação ao desktop
      300, // largura da janela
      300, // altura da janela
      parentHwnd,
      NULL,
      NULL,
      NULL
   );

	CreateWindowEx (
		0,
		"STATIC",
		"Prioridade:",
		WS_CHILD | WS_VISIBLE,
		10, 10, 70, 20,
		childHwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);
	wndImpressao.prioridade = CreateWindow (
		"COMBOBOX",
		"",
		CBS_DROPDOWNLIST | CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		90, 10, 150, 80,
		childHwnd,
		(HMENU)ID_EDIT_PRT,
		GetModuleHandle(NULL),
		NULL
	);
   SendMessage(wndImpressao.prioridade, CB_ADDSTRING, 0, (LPARAM) "1");
   SendMessage(wndImpressao.prioridade, CB_ADDSTRING, 0, (LPARAM) "2");
   SendMessage(wndImpressao.prioridade, CB_ADDSTRING, 0, (LPARAM) "3");

   CreateWindowEx (
      0,
      "STATIC",
      "Usuário:",
      WS_CHILD | WS_VISIBLE,
      10, 40, 70, 20,
      childHwnd,
      NULL,
      GetModuleHandle(NULL),
      NULL
   );
   wndImpressao.usuario = CreateWindow (
      "EDIT",
      "",
      WS_VISIBLE|WS_CHILD|WS_BORDER,
      90, 40, 150, 20,
      childHwnd,
      (HMENU)ID_EDIT_USR,
      GetModuleHandle(NULL),
      NULL
   );
}

void UpdatePriority(){
   /**
    * Create the child window.
    */
   childHwnd = CreateWindowEx( // Criação da janela
      0,
      childWndClass, // Indicação da classe da janela
      "Alterar Prioridade", // Nome da janela
      WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, // Estilo da janela: Desabilitado resize - maximize
      APP_X, // x em relação ao desktop
      APP_Y, // y em relação ao desktop
      300, // largura da janela
      300, // altura da janela
      parentHwnd,
      NULL,
      NULL,
      NULL
   );

   CreateWindowEx (
      0,
      "STATIC",
      "Prioridade:",
      WS_CHILD | WS_VISIBLE,
      10, 10, 70, 20,
      childHwnd,
      NULL,
      GetModuleHandle(NULL),
      NULL
   );
   wndImpressao.prioridade = CreateWindowEx (
      WS_EX_CLIENTEDGE,
      "EDIT",
      "",
      WS_VISIBLE|WS_CHILD|WS_BORDER,
      90, 10, 150, 20,
      childHwnd,
      (HMENU)ID_EDIT_PRT,
      GetModuleHandle(NULL),
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

   // Temporarios
   AppendMenu(hMenu, MF_STRING, APP_KEY_UPDATE, "Atualizar &Prioridade");
   AppendMenu(hMenu, MF_STRING, APP_KEY_MSG, "&Message");
   // Temporarios

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
   sprintf(total, "Total: %d", tamanho(lst));
   SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM) total);

   sprintf(total, "Pendentes: %d", 30);
   SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM) total);

   // sprintf(total, "De novo: %d", 30);
   // SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM) total);
}

void DrawAppList(HWND hwnd){
    no *aux = lst.inicio;
    int i = 30;
    int count = 100;
    if( !vazia(lst) ){
        while( aux != NULL ){
            char item[15];
            sprintf(item, "Item %3d: ", count);
            count++;
            CreateWindowEx (
               0,
               "STATIC",
               item,
               WS_VISIBLE|WS_CHILD|WS_CAPTION,
               30, i, 70, 20,
               hwnd,
               (HMENU) APP_MENU_ID,
               GetModuleHandle(NULL),
               NULL
            );
            i += 30;
            CreateWindowEx (
               0,
               "STATIC",
               "Usuário:",
               WS_VISIBLE|WS_CHILD,
               30, i, 60, 20,
               hwnd,
               (HMENU) APP_MENU_ID,
               GetModuleHandle(NULL),
               NULL
            );
            i += 30;
            CreateWindowEx (
               0,
               "STATIC",
               aux->dados.usuario,
               WS_VISIBLE|WS_CHILD,
               30, i, 60, 20,
               hwnd,
               NULL,
               GetModuleHandle(NULL),
               NULL
            );
            i += 30;
            // printf("Usuario: %s\n", aux->dados.usuario);
            // printf("Documento: %s\n", aux->dados.documento);
            // printf("Paginas: %d\n\n", aux->dados.paginas);
            aux = aux->prox;
        }
   } else {
      CreateWindowEx (
         0,
         "STATIC",
         "Não há itens para impressão!",
         WS_VISIBLE|WS_CHILD,
         30, 30, 200, 20,
         hwnd,
         NULL,
         GetModuleHandle(NULL),
         NULL
      );
   }
}

void DrawComponents(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
   DrawAppMenuBar(hwnd);
   DrawAppList(hwnd);
   DrawAppStatusBar(hwnd);
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
   DestroyWindow(hwnd);
   return TRUE; // must return TRUE; If return is FALSE it stops the recursion
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
   switch (message) {
   case WM_CREATE: {
         // Criação da janela
         DrawComponents(hwnd, message, wParam, lParam);
      }
      break;
   case WM_COMMAND: {
         switch (LOWORD(wParam)) {
            case APP_KEY_CREATE:
               CreateItem();
         		break;
         	case APP_KEY_POVOAR:
               povoar(&lst);
               // Atualiza dados da Janela
               EnumChildWindows(hwnd, EnumChildProc, 0);
               DrawComponents(hwnd, message, wParam, lParam);
               InvalidateRect(hwnd, NULL, TRUE);
         		break;
   	      case APP_KEY_EXIT:
   	         confirmExit();
   	         break;
            case APP_KEY_UPDATE:
               UpdatePriority();
               break;
   	      case APP_KEY_MSG:
   	         MessageBox(NULL, "10", "Resultado", MB_OK);
   	         break;
   	      case APP_KEY_ABOUT:
   	      	MakeAboutWindow();
   	         break;
   	      case APP_KEY_EMPTY:
   	         EmptyList();
               // Atualiza dados da Janela
               EnumChildWindows(hwnd, EnumChildProc, 0);
               DrawComponents(hwnd, message, wParam, lParam);
               InvalidateRect(hwnd, NULL, TRUE);
   	         break;
         }
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

LRESULT CALLBACK WindowChildProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
   switch (message) {
   case WM_CREATE: {
         // Criação da janela
         //MessageBox(NULL, "Child open", "Resultado", MB_OK);
      }
      break;
   case WM_DESTROY: // Destruição da janela
      DestroyWindow(hwnd);
      break;
   default:
      return DefWindowProc(hwnd, message, wParam, lParam);
   }
   return 0;
}

// WinMain, a função main em janelas
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil) {

   MSG messages; // Objeto mensagem do Windows para controlar o acionamento de botões
   WNDCLASSEX wincl, childCl; // O objeto para criar a janela

   /**
    * Register the main window class.
    */
   wincl.hInstance = hThisInstance;
   wincl.lpszClassName = parentWndClass; // Nome da classe da janela
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
   wincl.lpszMenuName = MAKEINTRESOURCE(APP_MENU_ID);
   wincl.cbClsExtra = 0;
   wincl.cbWndExtra = 0;
   wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND + 1; // Cor cinza de background

   if (!RegisterClassEx( & wincl)) // Se o registro da classe foi mal-sucedido return 0
      return 0;

   /**
    * Register child window class.
    */
   childCl.hInstance = hThisInstance;
   childCl.lpszClassName = childWndClass; // Nome da classe da janela
   childCl.lpfnWndProc = WindowChildProcedure;
   childCl.style = CS_DBLCLKS;
   childCl.cbSize = sizeof(WNDCLASSEX);
   childCl.hIcon = (HICON) LoadImage( // returns a HANDLE so we have to cast to HICON
      NULL, // hInstance must be NULL when loading from a file
      "impressora.ico", // the icon file name
      IMAGE_ICON, // specifies that the file is an icon
      0, // width of the image (we'll specify default later on)
      0, // height of the image
      LR_LOADFROMFILE | // we want to load a file (as opposed to a resource)
      LR_DEFAULTSIZE | // default metrics based on the type (IMAGE_ICON, 32x32)
      LR_SHARED // let the system release the handle when it's no longer used
   );
   childCl.hIconSm = (HICON) LoadImage( // returns a HANDLE so we have to cast to HICON
      NULL, // hInstance must be NULL when loading from a file
      "impressora.ico", // the icon file name
      IMAGE_ICON, // specifies that the file is an icon
      0, // width of the image (we'll specify default later on)
      0, // height of the image
      LR_LOADFROMFILE | // we want to load a file (as opposed to a resource)
      LR_DEFAULTSIZE | // default metrics based on the type (IMAGE_ICON, 32x32)
      LR_SHARED // let the system release the handle when it's no longer used
   );
   childCl.hCursor = LoadCursor(NULL, IDC_ARROW); //Cursor default
   childCl.lpszMenuName = MAKEINTRESOURCE(APP_MENU_ID);
   childCl.cbClsExtra = 0;
   childCl.cbWndExtra = 0;
   childCl.hbrBackground = (HBRUSH) COLOR_BACKGROUND + 1; // Cor cinza de background

   if (!RegisterClassEx( & childCl)) // Se o registro da classe foi mal-sucedido return 0
      return 0;

   /**
    * Iniciliza lista de impressão.
    */
   inicializa(&lst);

   /**
    * Create the main window.
    */
   parentHwnd = CreateWindowEx( // Criação da janela
      0,
      parentWndClass, // Indicação da classe da janela
      APP_TITLE, // Nome da janela
      WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // Estilo da janela: Desabilitado resize - maximize
      APP_X, // x em relação ao desktop
      APP_Y, // y em relação ao desktop
      APP_WIDTH, // largura da janela
      APP_HEIGHT, // altura da janela
      HWND_DESKTOP,
      NULL,
      hThisInstance,
      NULL
   );

   ShowWindow(parentHwnd, nFunsterStil); // Mostrar a janela
   UpdateWindow(parentHwnd);

   while (GetMessage( & messages, NULL, 0, 0)) // Recuperar mensagens
   {
      TranslateMessage( & messages);
      DispatchMessage( & messages);
   }

   return messages.wParam;
}
