// MFCLibrary1.cpp: определяет процедуры инициализации для DLL.
//

#include "stdafx.h"
#include "MFCLibrary1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC. Это означает, что
//		он должен быть первым оператором 
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CMFCLibrary1App

BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()


// создание CMFCLibrary1App

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CMFCLibrary1App

CMFCLibrary1App theApp;
int count(int *ptr,int l, int n, int j)
{
	int result=0;
	int address = (int)ptr;
__asm{
		mov esi, address 
		mov eax, j
		sub eax, 1  
		imul eax,l 
		add esi,eax 
		xor eax,eax
		mov edi, n
		imul edi, l
		xor ebx,ebx
		mov ecx,n 
iter:	mov  eax, [esi]
		cmp eax, 9
		jnle els //Jump if not less or equal (signed) (X > Y)
		cmp eax, 0 
		jnge els //Jump if not greater or equal (signed) (X < Y)
    	inc ebx
els:	add esi, edi
		loop iter
		mov result, ebx
}
return result;
}

// инициализация CMFCLibrary1App

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
