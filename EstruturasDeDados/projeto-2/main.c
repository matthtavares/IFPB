/**
 * Projeto de Estrutura de Dados
 * - Lista de Impressão Ordenada
 *
 * Implementação da UI da aplicação utilizando a API do Windows.
 *
 * @author  Mateus Tavares
 * @author  Ronily Gomes
 */
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "app.h"

hwndImpressao wndImpressao;
lista lst;

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
   wincl.style = CS_HREDRAW | CS_VREDRAW;
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
   childCl.style = CS_OWNDC;
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

   parentInst = hThisInstance;

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


void MakeAboutWindow(HWND hwnd) {
   char *text = "2º Projeto de Estrutura de Dados.\n\nDesenvolvido por:\n- Mateus Tavares.\n- Ronily Gomes.\n\nProfessor:\n- Alex Sandro.";
   MessageBox(hwnd, text, "Sobre", MB_ICONINFORMATION | MB_OK);
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
      SendMessage(parentHwnd, (UINT)WM_COMMAND, (WPARAM)APP_REDRAW, (LPARAM)NULL);
   }
}

void CreateItem(){
   /**
    * Destroy a child window.
    */
   if( childHwnd != NULL )
      DestroyWindow(childHwnd);

   /**
    * Create the child window.
    */
   childHwnd = CreateWindowEx( // Criação da janela
      0,
      childWndClass, // Indicação da classe da janela
      "Criar Novo Item", // Nome da janela
      WS_SYSMENU | WS_CAPTION | WS_VISIBLE | WS_EX_MDICHILD, // Estilo da janela: Desabilitado resize - maximize
      CHD_X, // x em relação ao desktop
      CHD_Y, // y em relação ao desktop
      CHD_WIDTH, // largura da janela
      CHD_HEIGHT, // altura da janela
      parentHwnd,
      NULL,
      NULL,
      NULL
   );

   CreateWindowEx (
      0,
      "STATIC",
      "0",
      WS_CHILD | WS_VISIBLE,
      0, 0, 0, 0,
      childHwnd,
      (HMENU)ID_OPR,
      GetModuleHandle(NULL),
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
      CBS_DROPDOWNLIST | CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
      90, 10, 195, 80,
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
      10, 45, 70, 20,
      childHwnd,
      NULL,
      GetModuleHandle(NULL),
      NULL
   );
   wndImpressao.usuario = CreateWindow (
      "EDIT",
      "",
      WS_VISIBLE|WS_CHILD|WS_BORDER,
      90, 45, 195, 20,
      childHwnd,
      (HMENU)ID_EDIT_USR,
      GetModuleHandle(NULL),
      NULL
   );

   CreateWindowEx (
      0,
      "STATIC",
      "Documento:",
      WS_CHILD | WS_VISIBLE,
      10, 75, 85, 20,
      childHwnd,
      NULL,
      GetModuleHandle(NULL),
      NULL
   );
   wndImpressao.documento = CreateWindow (
      "EDIT",
      "",
      WS_VISIBLE|WS_CHILD|WS_BORDER,
      90, 75, 195, 20,
      childHwnd,
      (HMENU)ID_EDIT_DOC,
      GetModuleHandle(NULL),
      NULL
   );

   CreateWindowEx (
      0,
      "STATIC",
      "Páginas:",
      WS_CHILD | WS_VISIBLE,
      10, 105, 70, 20,
      childHwnd,
      NULL,
      GetModuleHandle(NULL),
      NULL
   );
   wndImpressao.paginas = CreateWindow (
      "EDIT",
      "",
      WS_VISIBLE|WS_CHILD|WS_BORDER|ES_NUMBER,
      90, 105, 195, 20,
      childHwnd,
      (HMENU)ID_EDIT_PAG,
      GetModuleHandle(NULL),
      NULL
   );

   CreateWindowEx (
      0,
      "BUTTON",
      "OK",
      WS_VISIBLE|WS_CHILD,
      110, 160, 60, 30,
      childHwnd,
      (HMENU)APP_BTN_OK,
      NULL,
      NULL
   );
}

void UpdatePriority(){
   /**
    * Destroy a child window.
    */
   if( childHwnd != NULL )
      DestroyWindow(childHwnd);

   /**
    * Create the child window.
    */
   childHwnd = CreateWindowEx( // Criação da janela
      0,
      childWndClass, // Indicação da classe da janela
      "Atualizar Prioridade", // Nome da janela
      WS_SYSMENU | WS_CAPTION | WS_VISIBLE | WS_EX_MDICHILD, // Estilo da janela: Desabilitado resize - maximize
      CHD_X, // x em relação ao desktop
      CHD_Y, // y em relação ao desktop
      CHD_WIDTH, // largura da janela
      CHD_HEIGHT, // altura da janela
      parentHwnd,
      NULL,
      NULL,
      NULL
   );

   CreateWindowEx (
      0,
      "STATIC",
      "1",
      WS_CHILD | WS_VISIBLE,
      0, 0, 0, 0,
      childHwnd,
      (HMENU)ID_OPR,
      GetModuleHandle(NULL),
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
      CBS_DROPDOWNLIST | CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
      90, 10, 195, 80,
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
      "ID Item:",
      WS_CHILD | WS_VISIBLE,
      10, 45, 70, 20,
      childHwnd,
      NULL,
      GetModuleHandle(NULL),
      NULL
   );
   CreateWindow (
      "EDIT",
      "",
      WS_VISIBLE|WS_CHILD|WS_BORDER|ES_NUMBER,
      90, 45, 195, 20,
      childHwnd,
      (HMENU)ID_EDIT_NUM,
      GetModuleHandle(NULL),
      NULL
   );

   CreateWindowEx (
      0,
      "BUTTON",
      "OK",
      WS_VISIBLE|WS_CHILD,
      110, 160, 60, 30,
      childHwnd,
      (HMENU)APP_BTN_OK,
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
   AppendMenu(hSubMenu, MF_STRING, APP_KEY_PPRX, "Imprimir &Próximo");
   AppendMenu(hSubMenu, MF_STRING, APP_KEY_EMPTY, "&Limpar Lista");
   AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hSubMenu, "&Impressões");

   AppendMenu(hMenu, MF_STRING, APP_KEY_PPRX, "Imprimir &Próximo");

   // Temporarios
   AppendMenu(hMenu, MF_STRING, APP_KEY_UPDATE, "Atualizar P&rioridade");
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
      hwnd, (HMENU) APP_STAT_ID, GetModuleHandle(NULL), NULL);

   SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths) / sizeof(int), (LPARAM) statwidths);

   char total[50];
   sprintf(total, "Total de Itens: %d", tamanho(lst));
   SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM) total);

   int pendentes = (tamanho(lst) == 0) ? 0 : tamanho(lst) - 1;
   sprintf(total, "Pendentes: %d", pendentes);
   SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM) total);
}

void DrawAppList(HWND hwnd){
   no *aux = lst.inicio;

   LVITEM item;
   item.mask = LVIF_TEXT;
   item.cchTextMax = 25;
   char buf[25];
   int index;

   if( !vazia(lst) ){
      for(index = 0; aux != NULL; index++, aux = aux->prox){

         item.iItem = index;

         sprintf(buf, "%d", index + 1);
         item.iSubItem = 0;
         item.pszText = buf;
         ListView_InsertItem(listViewHwnd, &item);

         sprintf(buf, "%d", aux->dados.prioridade);
         item.iSubItem = 1; // zero based index of column
         item.pszText = buf;
         ListView_SetItem(listViewHwnd, &item);

         item.iSubItem = 2; // zero based index of column
         item.pszText = aux->dados.documento;
         ListView_SetItem(listViewHwnd, &item);

         sprintf(buf, "%d", aux->dados.paginas);
         item.iSubItem = 3; // zero based index of column
         item.pszText = buf;
         ListView_SetItem(listViewHwnd, &item);

         item.iSubItem = 4; // zero based index of column
         item.pszText = aux->dados.usuario;
         ListView_SetItem(listViewHwnd, &item);

         if( index == 0 )
            sprintf(buf, "Imprimindo");
         else
            sprintf(buf, "Em Espera");

         item.iSubItem = 5; // zero based index of column
         item.pszText = buf;
         ListView_SetItem(listViewHwnd, &item);
      }
   }
}

void DrawComponents(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
   meinChild = CreateMainChild( hwnd );

   listViewHwnd = CreateListView( meinChild );

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

         MessageBox(hwnd, "Pressione ALT + P para imprimir\no próximo item da lista.", "Atenção!", MB_OK);
      }
      break;
   case WM_COMMAND: {
         switch (LOWORD(wParam)) {
            case APP_KEY_CREATE:
               CreateItem();
               break;
            case APP_KEY_POVOAR:
               povoar(&lst);
               SendMessage(parentHwnd, (UINT)WM_COMMAND, (WPARAM)APP_REDRAW, (LPARAM)NULL);
               break;
            case APP_KEY_EXIT:
               confirmExit();
               break;
            case APP_KEY_UPDATE:
               UpdatePriority();
               break;
            case APP_KEY_ABOUT:
               MakeAboutWindow(hwnd);
               break;
            case APP_KEY_EMPTY:
               EmptyList();
               break;
            case APP_KEY_PPRX:
               PrintNext(&lst);
            case APP_REDRAW:
               // Atualiza dados da Janela
               EnumChildWindows(hwnd, EnumChildProc, 0);
               DrawComponents(hwnd, message, wParam, lParam);
               InvalidateRect(hwnd, NULL, TRUE);
               UpdateWindow(parentHwnd);
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
   case WM_CREATE:
      break;
   case WM_COMMAND:
      if( HIWORD(wParam) == BN_CLICKED ){
         impressao novo;
         char opr[2];
         char pri[2];
         char buf[25];
         int  code;

         /// GET OPERATION
         GetDlgItemText(hwnd, ID_OPR, opr, 2);

         /// GET PRIORITY
         GetDlgItemText(hwnd, ID_EDIT_PRT, pri, 2);
         if( strcmp(pri, "") != 0 )
            novo.prioridade = atoi(pri);
         else
            novo.prioridade = 1;

         /// Editando
         if( strcmp(opr, "1") == 0 ){
            /// Alerta se lista estiver vazia
            if( vazia(lst) ){
               MessageBox(hwnd, "A lista está vazia!", "Erro!", MB_ICONEXCLAMATION | MB_OK);
               return FALSE;
            }

            /// GET PRIORITY
            GetDlgItemText(hwnd, ID_EDIT_NUM, buf, 25);
            code = atoi(buf);

            /// Verifica se o valor é diferente do tamanho
            if( code < 1 || code > tamanho(lst) ){
               MessageBox(hwnd, "O item não existe!", "Erro!", MB_ICONEXCLAMATION | MB_OK);
               return FALSE;
            }

            if( atualizar(&lst, code, novo.prioridade) )
               MessageBox(hwnd, "Atualizado com sucesso!", "Sucesso!", MB_OK);
         }
         /// Cadastrando
         else if( strcmp(opr, "0") == 0 ){
            GetDlgItemText(hwnd, ID_EDIT_USR, novo.usuario, 25);
            GetDlgItemText(hwnd, ID_EDIT_DOC, novo.documento, 25);
            GetDlgItemText(hwnd, ID_EDIT_PAG, buf, 25);
            novo.paginas = atoi(buf);
            if( inserir(&lst, novo) )
               MessageBox(hwnd, "Inserido com sucesso!", "Sucesso!", MB_OK);
         }

         DestroyWindow(childHwnd);
         SetFocus(parentHwnd);
         SendMessage(parentHwnd, (UINT)WM_COMMAND, (WPARAM)APP_REDRAW, (LPARAM)NULL);
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

HWND CreateListView(HWND pHwnd){
   HWND hWndList;      // Handle to the list view window
   RECT rcl;           // Rectangle for setting the size of the window
   int index;          // Index used in for loops
   LV_COLUMN lvC;      // List View Column structure

   // Get the size and position of the parent window
   GetClientRect(pHwnd, &rcl);

   // Create the list view window that starts out in report view
    // and allows label editing.
   hWndList = CreateWindowEx( 0L,
      WC_LISTVIEW,                // list view class
      "",                         // no default text
      WS_VISIBLE | WS_CHILD | LVS_REPORT |
          LVS_EDITLABELS | WS_EX_CLIENTEDGE,
      0, 0,
      rcl.right - rcl.left, rcl.bottom - rcl.top,
      pHwnd,
      (HMENU) IDC_LISTVIEW,
      parentInst,
      NULL );

   if (hWndList == NULL )
      return NULL;


   // Now initialize the columns we will need
   // Initialize the LV_COLUMN structure
   // the mask specifies that the .fmt, .ex, width, and .subitem members 
   // of the structure are valid,
   lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
   lvC.fmt = LVCFMT_CENTER;  // left align the column

   // Add columns
   lvC.cx = 40;            // width of the column, in pixels
   lvC.pszText = "#";
   lvC.iSubItem = 1;
   if (ListView_InsertColumn(hWndList, 1, &lvC) == -1)
      return NULL;

   lvC.cx = 80;            // width of the column, in pixels
   lvC.pszText = "Prioridade";
   lvC.iSubItem = 2;
   if (ListView_InsertColumn(hWndList, 2, &lvC) == -1)
      return NULL;

   lvC.cx = 200;            // width of the column, in pixels
   lvC.pszText = "Documento";
   lvC.iSubItem = 3;
   if (ListView_InsertColumn(hWndList, 3, &lvC) == -1)
      return NULL;

   lvC.cx = 80;            // width of the column, in pixels
   lvC.pszText = "Páginas";
   lvC.iSubItem = 4;
   if (ListView_InsertColumn(hWndList, 4, &lvC) == -1)
      return NULL;

   lvC.cx = 200;            // width of the column, in pixels
   lvC.pszText = "Usuário";
   lvC.iSubItem = 5;
   if (ListView_InsertColumn(hWndList, 5, &lvC) == -1)
      return NULL;

   lvC.cx = 80;            // width of the column, in pixels
   lvC.pszText = "Status";
   lvC.iSubItem = 6;
   if (ListView_InsertColumn(hWndList, 6, &lvC) == -1)
      return NULL;

   return (hWndList);

}

HWND CreateMainChild(HWND pHwnd){
   RECT rcl;
   GetClientRect(pHwnd, &rcl);

   HWND hwnd = CreateWindowEx( // Criação da janela
      0,
      "STATIC", // Indicação da classe da janela
      NULL, // Nome da janela
      WS_VISIBLE | WS_CHILD, // Estilo da janela: Desabilitado resize - maximize
      0, 0,
      rcl.right - rcl.left, rcl.bottom - 20,
      pHwnd,
      NULL,
      parentInst,
      NULL
   );

   return hwnd;
}