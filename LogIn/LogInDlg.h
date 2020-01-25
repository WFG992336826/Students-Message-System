
// LogInDlg.h: 头文件
//

#pragma once
#include "StudentInforDlg.h"
#include "Database.h"
// CLogInDlg 对话框
class CLogInDlg : public CDialogEx
{
// 构造
public:
	CLogInDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//自定义变量及函数
public:
	StudentInforDlg studentInforDlg;
	Database databaseConn;

 	BOOL userType; //TRUE - 管理员, FALSE - 学生
	
	CStatic m_hidetime;
	CEdit m_account;
	CEdit m_password;
	CBrush m_brBk;//背景图片设置
	bool flag_showbmp = true;
	int CloseBMPtime = 20;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonExit();

	afx_msg LRESULT OnClose(WPARAM wPara, LPARAM lPara);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
