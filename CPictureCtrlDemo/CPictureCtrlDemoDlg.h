// CPictureCtrlDemoDlg.h : header file
//

#pragma once
#include "picturectrl.h"
#include "afxwin.h"


// CCPictureCtrlDemoDlg-Dialogfeld
class CCPictureCtrlDemoDlg : public CDialog
{
// Construction
public:
	CCPictureCtrlDemoDlg(CWnd* pParent = NULL);	// Standardkonstruktor

//Dialog Data
	enum { IDD = IDD_CPICTURECTRLDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	BOOL PreTranslateMessage(MSG *pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
// 	afx_msg void OnBnClickedButton4();
	CPictureCtrl m_picCtrl;
	CPictureCtrl m_my;
	CString m_filename;
	afx_msg void OnBnClickedButton4();
	CPictureCtrl m_smallpic;
	
	CButton button1;
	CButton button2;
	afx_msg void OnBnClickedButton5();
	};
