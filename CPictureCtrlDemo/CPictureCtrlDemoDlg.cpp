// CPictureCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CPictureCtrlDemo.h"
#include "PictureCtrl.h"
#include "CPictureCtrlDemoDlg.h"
#include "EyeDetection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCPictureCtrlDemoDlg-Dialog




CCPictureCtrlDemoDlg::CCPictureCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCPictureCtrlDemoDlg::IDD, pParent)
	, m_filename(_T(""))
	{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCPictureCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
CDialog::DoDataExchange(pDX);
DDX_Control(pDX, IDC_STATIC_PICTURE, m_picCtrl);
DDX_Control(pDX, IDC_STATIC_PICTURE2, m_my);
DDX_Text(pDX, IDC_EDIT1, m_filename);
DDX_Control(pDX, IDC_STATIC_PICTURE3, m_smallpic);
DDX_Control(pDX, IDC_BUTTON1, button1);
DDX_Control(pDX, IDC_BUTTON2, button2);
	}

BEGIN_MESSAGE_MAP(CCPictureCtrlDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCPictureCtrlDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCPictureCtrlDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCPictureCtrlDemoDlg::OnBnClickedButton3)
/*	ON_BN_CLICKED(IDC_BUTTON4, &CCPictureCtrlDemoDlg::OnBnClickedButton4)*/
ON_BN_CLICKED(IDC_BUTTON4, &CCPictureCtrlDemoDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &CCPictureCtrlDemoDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CCPictureCtrlDemoDlg-message handlers

BOOL CCPictureCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	button2.EnableWindow(false);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCPictureCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCPictureCtrlDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon); 
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCPictureCtrlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//Globle variables
Eye aaa;
CWnd *pWnd;
bool flag=false;
CString loadedFace;

void CCPictureCtrlDemoDlg::OnBnClickedButton1()
{

	UpdateData(TRUE);
	pWnd = GetDlgItem(IDC_EDIT1);
	
	pWnd->GetWindowText(loadedFace);
	
	if(!m_picCtrl.Load(loadedFace))
	{
		MessageBox(L"Can not Find the File '"+loadedFace+L"'",L"Error",MB_OK);
		button2.EnableWindow(false);
	}
	else
	{
		flag=true;
		button1.EnableWindow(false);
		button2.EnableWindow(true);
	}

	UpdateData(FALSE);
}

void CCPictureCtrlDemoDlg::OnBnClickedButton2()
{

	UpdateData(TRUE);
	pWnd = GetDlgItem(IDC_EDIT1);
	CString str;
	pWnd->GetWindowText(str);
	CStringA ansiString(str);

	// Load image from data base
	IplImage* img = cvLoadImage(ansiString);
	
	if( img == 0 ) 
	{
		MessageBox(L"Can not Initiate the Image",L"Error",MB_OK);
		return ; 
	}
	aaa.detect_faces(img);
	aaa.detect_eyes(img);

	//save detected image states as gotface.jpg
	cvSaveImage("gotface.jpg",img);
	MessageBox(L"Apply Changes on Image...",MB_OK);
	cvWaitKey(1000); 

	if(!m_my.Load(CString(_T("gotface.jpg"))))
	{
		MessageBox(L"Can not Find the File \"gotface.jpg\"",L"Error",MB_OK);
		button2.EnableWindow(true);
	}
	else
		button2.EnableWindow(false);
		
	cvReleaseImage( &img );
	UpdateData(FALSE);
	
}

void CCPictureCtrlDemoDlg::OnBnClickedButton3()
{
	if(!flag)
	{
		MessageBox(L"Load an Image First",L"Error",MB_OK);
		return;
	}
		
	UpdateData(TRUE);

	//get text box values
	pWnd = GetDlgItem(IDC_EDIT2);
	CString str;
	pWnd->GetWindowText(str);
	CStringA ansiString1(str);
	CStringA ansiString2(loadedFace);
	pWnd=NULL;
	pWnd = GetDlgItem(IDC_EDIT3);
	CString str1;
	pWnd->GetWindowText(str1);
	double d= _tstof(str1);

	//load images
	IplImage* img1 = cvLoadImage(ansiString1);
	IplImage* img2 = cvLoadImage(ansiString2);

	if( img1 == 0 ) 
	{
		MessageBox(L"Can not Load the Template",L"Error",MB_OK);
		return ; 
	}

	if( img2 == 0 ) 
	{
		MessageBox(L"Can not Load the Image",L"Error",MB_OK);
		return ; 
	}

	int result=-1;			
	result=aaa.match_templates(img1,img2,d);

	//check match function status
	if(result==0)
		m_my.Load(CString(_T("success.jpg")));
	else
	{
		m_my.FreeData();
		m_my.CloseWindow();
		m_my.ShowWindow(1);
	}
	UpdateData(FALSE);
	
}


void CCPictureCtrlDemoDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	pWnd = GetDlgItem(IDC_EDIT2);
	CString str;
	pWnd->GetWindowText(str);
	
	if(!m_smallpic.Load(str))
	{
		MessageBox(L"Can not Find the File '"+str+L"'",L"Error",MB_OK);	
	}

	UpdateData(FALSE);
}

BOOL CCPictureCtrlDemoDlg::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE))
			pMsg->wParam = NULL;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CCPictureCtrlDemoDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	//this function will reset the GUI components 
	button1.EnableWindow(true);
	flag=false;
	m_picCtrl.FreeData();
	m_my.FreeData();
	m_smallpic.FreeData();
	m_picCtrl.CloseWindow();
	m_picCtrl.ShowWindow(1);
	m_my.CloseWindow();
	m_my.ShowWindow(1);
	m_smallpic.CloseWindow();
	m_smallpic.ShowWindow(1);
}
