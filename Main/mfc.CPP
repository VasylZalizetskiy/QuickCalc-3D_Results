#include <afxcmn.h>
#include <afxext.h>
#include <afxwin.h>
#include "resource.h"
#include <math.h>
#include <windows.h>
#include <gL/gl.h>
#include <gL/glu.h>
#include "glaux.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

int L,N,J,Y;
int* M =new int[N*N];
CString tmp;
int WindCounter=0; 
class CMyDialog : public CDialog
{
public:
	CMyDialog(CWnd* pParent = NULL);  
		enum { IDD = IDD_DIALOG1 };
	CEdit  masiv;
	CEdit  stovpec;
	CSliderCtrl bytes;
	CSliderCtrl rozmir;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

BOOL CMyDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	masiv.SetWindowText("10 11 12 13 14\r\n15 16 17 18 19\r\n20 21 22 23 24\r\n25 26 27 28 29\r\n30 31 32 33 34");
	stovpec.SetWindowText("1");
	bytes.SetRange(2,4);
	bytes.SetPos(2);
	rozmir.SetRange(2,9);
	rozmir.SetPos(5);
	return TRUE;
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, masiv);
	DDX_Control(pDX, IDC_EDIT2, stovpec);
	DDX_Control(pDX, IDC_SLIDER1, bytes);
	DDX_Control(pDX, IDC_SLIDER2, rozmir);
}

BEGIN_MESSAGE_MAP(CMyDialog,CDialog)
ON_COMMAND(IDOK,OnOK)
ON_COMMAND(IDCANCEL,OnCancel)
END_MESSAGE_MAP()

CMyDialog::CMyDialog(CWnd *pParent)
:CDialog(CMyDialog::IDD,pParent)
{

}

void CMyDialog::OnOK() 
{	
	char str[80];
	tmp="";
	N=rozmir.GetPos();
	L=bytes.GetPos();
	stovpec.GetWindowText(str,80);
	J=atoi(str);
	masiv.GetWindowText(str,80);

	int index=0;
	for(int i = 0; i < N*N; i++)
	{
			if(str[index]=='\r' || str[index]=='\n')
				index+=2;
			if(str[index]==' ')
				index+=1;

			tmp+=str[index];
			if (str[index+1]!=' ' || str[index+1]!='\r' || str[index+1]!='\n')
			tmp+=str[index+=1];

			M[i] = atoi(tmp);
			tmp="";
			index++;
	}
	CDialog::OnOK();
	MessageBox("Данні введено успішно!","Обробка...",MB_OK|MB_ICONINFORMATION);
} 

void CMyDialog::OnCancel()
{
	CDialog::OnCancel();
}

class Editor:public CDialog
{
public:
	Editor(char *s, CWnd *pParent = NULL)
		: CDialog(IDD_DIALOG2, pParent)
	{
		this->s = s;
	}
	CEdit Edit1;
protected:
	char *s;
	virtual BOOL OnInitDialog()
	{
			CDialog::OnInitDialog();	
			Edit1.SetWindowText(s);

			return TRUE;
	}
	virtual void DoDataExchange(CDataExchange *pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX,IDC_EDIT1,Edit1);
	}
};

class CMyFrameWnd:public CFrameWnd
{
	public :
		CMyFrameWnd();
	protected :
		CStatusBar m_wndStatusBar;
		CToolBar m_wndToolBar;
		afx_msg int OnCreate(LPCREATESTRUCT IpCreateStruct);
		afx_msg void OnInput();
		afx_msg void OnRun();
		afx_msg void OnResult();
		afx_msg void OnInfo();
		afx_msg void OnOpen();
		afx_msg void OnSave();
		afx_msg void OnRename();
		afx_msg void OnQuit();
		afx_msg void OnHelp();
		DECLARE_MESSAGE_MAP();         
  };

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	 ON_WM_CREATE()
	 ON_COMMAND(ID_INPUT,OnInput)
	 ON_COMMAND(ID_RUN,OnRun)
	 ON_COMMAND(ID_RESULT,OnResult)
	 ON_COMMAND(ID_INFO,OnInfo)
	 ON_COMMAND(ID_OPEN,OnOpen)
	 ON_COMMAND(ID_SAVE,OnSave)
	 ON_COMMAND(ID_RENAME,OnRename)
     ON_COMMAND(ID_QUIT,OnQuit)
	 ON_COMMAND(ID_HELP,OnHelp)
END_MESSAGE_MAP();

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMyFrameWnd::CMyFrameWnd()
{
	Create(NULL,"MFC project", 
	WS_OVERLAPPEDWINDOW,rectDefault,NULL,MAKEINTRESOURCE(IDR_MENU1));
};

int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HICON hIcon= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon( hIcon, TRUE );

	if(CFrameWnd::OnCreate(lpCreateStruct)==-1)
		return -1;
	if(!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || !m_wndToolBar.LoadToolBar(IDR_MENU1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	if(!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar/n");
		return -1;
	}
}

void CMyFrameWnd::OnInput()
{
	CMyDialog dialog;		
    dialog.DoModal();
}

void CMyFrameWnd::OnRun()
  {
	if (N!=NULL)
	{
	int*pointer = &M[0];
	HINSTANCE hDll;
	hDll=::LoadLibrary("MFCLibrary1");
	if(hDll==NULL)
	MessageBox("Файл MFCLibrary1.dll не знайдено!","Помилка",MB_OK|MB_ICONERROR);
	else
	{
	typedef int (*FUN)(int*, int, int, int);
	FUN func;
	func=(FUN)::GetProcAddress(hDll, "count");
    Y=(*func)(pointer,pow(2.0,L),N,J);
	MessageBox("Функцію викликано!","Підключення бібліотеки...",MB_OK|MB_ICONINFORMATION);
	}
	::FreeLibrary(hDll);
	}
	else
	MessageBox("Спочатку Input!","Введіть дані!",MB_OK|MB_ICONERROR);
}

void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    

void CALLBACK display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	glClearColor(0.2,0.2,0.2,1);
	glRotated(0.03,0,1,0);
	glPushMatrix();

	glColor3d(1,1,1);
	auxSolidCube(3);//дім

	glPushMatrix();
	glTranslated(0,1.5,0);
	glRotated(-90,1,0,0);
	glColor3d(1,0,0);
	auxSolidCone(2.8,1);//дах
	glPopMatrix();

	glTranslated(0,-1,1.5);
	glColor3d(0.9,0.3,0);
	auxSolidBox(0.5,1,0.2);//двері

	//вікна
	
	glTranslated(-1,1,0);
	if (Y>=1)
		glColor3d(1,1,0);
	else
		glColor3d(0,0,1);
	auxSolidBox(0.7,0.5,0.1);

	glTranslated(0,1,0);
		if (Y>=2)
		glColor3d(1,1,0);
	else
		glColor3d(0,0,1);
	auxSolidBox(0.7,0.5,0.1);

	glTranslated(2,0,0);
		if (Y>=3)
		glColor3d(1,1,0);
	else
		glColor3d(0,0,1);
	auxSolidBox(0.7,0.5,0.1);

	glTranslated(0,-1,0);
		if (Y>=4)
		glColor3d(1,1,0);
	else
		glColor3d(0,0,1);
	auxSolidBox(0.7,0.5,0.1);

    glPopMatrix();
    auxSwapBuffers();
}

void CMyFrameWnd::OnResult()
{
	WindCounter++;
	char s[20]={0};
	sprintf(s," Результат %i", Y);
	MessageBox(s,"Calc",MB_OK|
		MB_ICONASTERISK);
	if (WindCounter>1)
	MessageBox("OpenGL реєструє лише один примірник вікна!","Графічний результат",MB_OK|
				MB_ICONEXCLAMATION);  
	else
//колірний режим, видалення невидимих ​​ліній і подвійна буферизація
	auxInitDisplayMode( AUX_RGBA | AUX_DEPTH | AUX_DOUBLE);
	auxInitPosition(50,10,400,400); //позиція і розміри вікна
	auxInitWindow("Графічний результат");//заголовок вікна
	auxReshapeFunc(resize);//реакція на зміну розмірів вікна
	glEnable(GL_ALPHA_TEST);//врахування прозорості
    glEnable(GL_DEPTH_TEST);//видалення невидимих ​​ліній
	glEnable(GL_COLOR_MATERIAL);//синхронне завдання кольору малювання і матеріалу
	glEnable(GL_BLEND);//дозвіл змішування кольорів
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHTING);//врахування освітлення
	glEnable(GL_LIGHT0);//включення нульового джерела світла
    //задання положення та напрямки нульового джерела світла
	float pos[4]={0,5,5,1};
	float dir[3]={0,-1,-1};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	auxIdleFunc(display);//задання анімації
	auxMainLoop(display);//перерисовка вікна
}

void CMyFrameWnd::OnInfo()
{
	  ::MessageBox(NULL,"Copyright by ZVV","Info",MB_OK|
				MB_ICONASTERISK);  
}

void CMyFrameWnd::OnOpen()
{
	char *s; 
	CString path;

	CFileDialog dlgOpen(TRUE,"txt","",OFN_HIDEREADONLY, "Data (*.txt)|*.txt|All Files(*.*)|*.*|",this);
	if(dlgOpen.DoModal()==IDOK)
	{ 
		CStdioFile File(dlgOpen.GetPathName(),
			 CFile::modeRead | CFile::typeBinary);
		
		int Len = File.GetLength();
		
		s = new char[Len + 1];

		File.Read(s, Len);
		s[Len] = 0;
		
		Editor FC(s);

		FC.DoModal();
		delete [] s;
	}
}

void CMyFrameWnd::OnSave()
{
	char s[50];
	sprintf(s,"Результат обчислень = %d", Y);
	CFileDialog dlgSave(FALSE,"txt","result",OFN_HIDEREADONLY,"Data (*.txt)|*.txt|All Files(*.*)|*.*|",this);
	if(dlgSave.DoModal()==IDOK)
	{ 
		CStdioFile File(dlgSave.GetPathName(),
			CFile::modeCreate | CFile::modeWrite);
		File.WriteString(LPCSTR(s));     
	}
}

void CMyFrameWnd::OnRename()
{
	char s[50];
	sprintf(s,"Результат обчислень = %d", Y);
	CFileDialog dlgSave(FALSE,"txt","result",OFN_HIDEREADONLY,"Data (*.txt)|*.txt|All Files(*.*)|*.*|",this);
	if(dlgSave.DoModal()==IDOK)
	{ 
		CStdioFile File(dlgSave.GetPathName(),
			CFile::modeCreate | CFile::modeWrite);
		File.WriteString(LPCSTR(s));     
	}
}

 void CMyFrameWnd::OnQuit()
{
    SendMessage(WM_CLOSE);
}

 void CMyFrameWnd::OnHelp()
{
	  ::MessageBox(NULL,"Help","Help",MB_OK|
		  MB_ICONQUESTION);  
}

class CMyApp:public CWinApp
{
  public:
	virtual BOOL InitInstance();
};
BOOL CMyApp::InitInstance()
{
	CMyFrameWnd *pMainWnd=new CMyFrameWnd;
	
	m_pMainWnd=pMainWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	    return TRUE;
};

CMyApp app;
