
// LogInDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LogIn.h"
#include "LogInDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLogInDlg 对话框
CLogInDlg::CLogInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_account);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Control(pDX, IDC_STATIC_HIDEBMP_TIME, m_hidetime);
}

BEGIN_MESSAGE_MAP(CLogInDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLogInDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CLogInDlg::OnBnClickedButtonExit)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLogInDlg 消息处理程序
BOOL CLogInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	studentInforDlg.Create(IDD_STUDENTINFOR_DIALOG, this);
	studentInforDlg.ShowWindow(SW_HIDE);
	//初始化listCtrl控件
	studentInforDlg.InitListCtrl();

	//添加背景图片
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP4);
	m_brBk.CreatePatternBrush(&bmp);

	//开启定时器
	SetTimer(1, 20000, NULL);
	SetTimer(2, 1000, NULL);

	m_hidetime.SetWindowTextW(_T("20"));

	//初始化数据库
	databaseConn.OnInitADOConn();

	_bstr_t strConnect = "SELECT * FROM account";//连接字符串students
	databaseConn.m_pRecordset = databaseConn.GetRecordSet(strConnect);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLogInDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLogInDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLogInDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLogInDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_account, str_password;
	int user;
	m_account.GetWindowTextW(str_account);
	m_password.GetWindowTextW(str_password);

	user = databaseConn.loginVerify(str_account, str_password);

	if (user == 1)
	{
		userType = TRUE;
		CLogInDlg::ShowWindow(SW_HIDE);
		databaseConn.ExitConn();

		studentInforDlg.ShowWindow(SW_SHOW);
	}
	else if (user == 2)
	{
		userType = FALSE;
		CLogInDlg::ShowWindow(SW_HIDE);
		databaseConn.ExitConn();
		studentInforDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		MessageBox(_T("账号或密码错误！！"));
	}

}

void CLogInDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDNO == MessageBox(_T("请再次确认退出"), _T("提示"), MB_YESNO))
	{
	}
	else
	{
		PostQuitMessage(0);
	}

}

afx_msg LRESULT CLogInDlg::OnClose(WPARAM wPara, LPARAM lPara)
{
	if (IDNO == MessageBox(_T("请再次确认退出"), _T("提示"), MB_YESNO))
	{
		return 0;
	}
	else
	{
		CDialog::OnClose();
	}
	return 0;
}

HBRUSH CLogInDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if (flag_showbmp == true)
	{

		if (pWnd == this)
		{
			return m_brBk;
		}
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		pDC->SetTextColor(RGB(0, 0, 0));//设置字体为黑色
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	return hbr;
}

void CLogInDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == 2)
	{
		CloseBMPtime = CloseBMPtime - 1;

		CLogInDlg::SetDlgItemInt(IDC_STATIC_HIDEBMP_TIME, CloseBMPtime);

		CLogInDlg::Invalidate(true);   //擦除窗口上的元素
		CLogInDlg::UpdateWindow();     //重绘界面
		/*m_hidetime.UpdateData(true);
		GetDlgItem(IDC_STATIC_HIDEBMP_TIME)->Invalidate(true);
		GetDlgItem(IDC_STATIC_HIDEBMP_TIME)->UpdateWindow();*/

		if (CloseBMPtime == 0)
		{
			KillTimer(2);
		}
	}

	else if (nIDEvent == 1)
	{
		flag_showbmp = false;
		CLogInDlg::Invalidate(true);   //擦除窗口上的元素
		CLogInDlg::UpdateWindow();     //重绘界面

		//关闭定时器
		KillTimer(1);
	}
}
