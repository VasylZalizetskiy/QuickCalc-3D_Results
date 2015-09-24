// MFCLibrary1.cpp: ���������� ��������� ������������� ��� DLL.
//

#include "stdafx.h"
#include "MFCLibrary1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ���� ��� ���������� DLL ����������� ������� � ������������ DLL MFC,
//		��� �������, ���������������� �� ������ DLL-����������, ������� ��������� ������ �
//		MFC, ������ ��������� ������ AFX_MANAGE_STATE �
//		����� ������ �������.
//
//		��������:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// ���� ���������� �������
//		}
//
//		�����, ����� ������ ������ ��� ����������� � ������
//		������� �� ������ MFC. ��� ��������, ���
//		�� ������ ���� ������ ���������� 
//		������� � �������������� ���� ����� ����������� ���������� �������,
//		��������� �� ������������ ����� ��������� ������ � MFC
//		DLL.
//
//		� ����������� ��������� MFC 33 � 58 ���������� �����
//		��������� ��������.
//

// CMFCLibrary1App

BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()


// �������� CMFCLibrary1App

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ CMFCLibrary1App

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

// ������������� CMFCLibrary1App

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
