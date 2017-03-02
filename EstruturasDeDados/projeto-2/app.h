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

/**
 * SCRW: Screen Width
 * SCRH: Screen Height
 */
#define SCRW GetSystemMetrics(SM_CXSCREEN)
#define SCRH GetSystemMetrics(SM_CYSCREEN)

/**
 * Dados da Aplicação
 */
#define APP_WIDTH  800
#define APP_HEIGHT 600
#define APP_X ( (SCRW - APP_WIDTH) / 2 )
#define APP_Y ( (SCRH - APP_HEIGHT) / 2 )
#define APP_TITLE "Fila de Impressão"

/**
 * Dados da janela filha.
 */
#define CHD_WIDTH  300
#define CHD_HEIGHT 300
#define CHD_X ( (SCRW - CHD_WIDTH) / 2 )
#define CHD_Y ( (SCRH - CHD_HEIGHT) / 2 )

/**
 * Códigos da Aplicação
 */
#define APP_BTN_OK  8000
#define APP_BTN_CLS 8001

#define APP_MENU_ID    9000
#define APP_KEY_EXIT   9001
#define APP_KEY_ABOUT  9002
#define APP_KEY_POVOAR 9003
#define APP_KEY_CREATE 9004
#define APP_KEY_EMPTY  9005
#define APP_KEY_UPDATE 9006
#define APP_STAT_ID    9007
#define APP_REDRAW     9008
#define APP_KEY_PPRX   9009

#define IDC_LISTVIEW 1000

/**
 * ID's dos Elementos de formulários.
 */
#define ID_EDIT_PRT 500
#define ID_EDIT_USR 501
#define ID_EDIT_DOC 502
#define ID_EDIT_PAG 503
#define ID_EDIT_NUM 504
#define ID_OPR      599

HWND parentHwnd = NULL;
char parentWndClass[] = "WindowMainAppl";

HWND childHwnd = NULL;
char childWndClass[] = "WindowChildAppl";

HWND meinChild = NULL;
HWND listViewHwnd = NULL;

HINSTANCE parentInst = NULL;

typedef struct {
   HWND prioridade;
   HWND usuario;
   HWND paginas;
   HWND documento;
} hwndImpressao;

void MakeAboutWindow(HWND hwnd);
void confirmExit();
void EmptyList();
void CreateItem();
void UpdatePriority();
void DrawAppMenuBar(HWND hwnd);
void DrawAppStatusBar(HWND hwnd);
void DrawAppList(HWND hwnd);
void DrawComponents(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowChildProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateListView(HWND pHwnd);
HWND CreateMainChild(HWND pHwnd);