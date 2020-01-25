// StudentInforDlg.cpp: 实现文件
#include "pch.h"
#include "LogIn.h"
#include "StudentInforDlg.h"
#include "afxdialogex.h"

//数据库表头数目 初始化ListCtrl控件的表头
#define list_head_num 7

// StudentInforDlg 对话框
StudentInforDlg::StudentInforDlg() : CDialogEx(IDD_STUDENTINFOR_DIALOG)
{
}

void StudentInforDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_EDIT_NAME, m_name);
	DDX_Control(pDX, IDC_EDIT_STUNUM, m_stuNum);
	DDX_Control(pDX, IDC_EDIT_CLASS, m_class);
	DDX_Control(pDX, IDC_EDIT_GENDER, m_gender);
	DDX_Control(pDX, IDC_EDIT_AGE, m_age);
	DDX_Control(pDX, IDC_EDIT_STARTTIME, m_startTime);
	DDX_Control(pDX, IDC_LIST_STUMES, m_showMess);
}


BEGIN_MESSAGE_MAP(StudentInforDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &StudentInforDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_READMES, &StudentInforDlg::OnBnClickedButtonReadMes)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &StudentInforDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &StudentInforDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &StudentInforDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &StudentInforDlg::OnBnClickedButtonClearEdit)
	ON_BN_CLICKED(IDC_BUTTON_FUZZYFIND, &StudentInforDlg::OnBnClickedButtonFuzzyFind)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &StudentInforDlg::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &StudentInforDlg::OnBnClickedButtonLast)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STUMES, &StudentInforDlg::OnLvnItemchangedListctrlInfor)
	ON_MESSAGE(WM_CLOSE, OnClose)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// StudentInforDlg 消息处理程序
BOOL StudentInforDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码

	//初始化数据库连接
	DBConn.OnInitADOConn();
	_bstr_t strConnect = "SELECT * FROM students";//连接字符串students
	DBConn.m_pRecordset = DBConn.GetRecordSet(strConnect);

	//添加背景图片
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP4);
	m_brBk.CreatePatternBrush(&bmp);

	return TRUE;
}

//获取编辑框输入的信息
StudentInfor StudentInforDlg::GetEditText()
{
	CString strText;
	m_name.GetWindowTextW(strText);
	student_infor.student_name = strText;

	m_stuNum.GetWindowTextW(strText);
	student_infor.student_number = strText;

	m_class.GetWindowTextW(strText);
	student_infor.student_class = strText;

	m_gender.GetWindowTextW(strText);
	student_infor.student_gender = strText;

	m_age.GetWindowTextW(strText);
	student_infor.student_age = strText;

	m_startTime.GetWindowTextW(strText);
	student_infor.student_startTime = strText;

	return student_infor;
}

//设置编辑框输入的信息
void StudentInforDlg::SetEditText(StudentInfor student_infor)
{
	m_name.SetWindowTextW(student_infor.student_name);
	m_stuNum.SetWindowTextW(student_infor.student_number);
	m_class.SetWindowTextW(student_infor.student_class);
	m_gender.SetWindowTextW(student_infor.student_gender);
	m_age.SetWindowTextW(student_infor.student_age);
	m_startTime.SetWindowTextW(student_infor.student_startTime);
}

//清空编辑框的文字信息
void StudentInforDlg::DeleteEditText()
{
	m_name.SetWindowTextW(_T(""));
	m_stuNum.SetWindowTextW(_T(""));
	m_class.SetWindowTextW(_T(""));
	m_gender.SetWindowTextW(_T(""));
	m_age.SetWindowTextW(_T(""));
	m_startTime.SetWindowTextW(_T(""));
}

//将编辑框用鼠标选中的信息显示到编辑框中
StudentInfor StudentInforDlg::GetListSelectInfor()
{
	CString strText;
	POSITION pos = m_showMess.GetFirstSelectedItemPosition(); //pos选中的首行位置
	if (pos != NULL)
	{
		while (pos)   //如果你选择多行
		{
			int nIdx = -1;
			nIdx = m_showMess.GetNextSelectedItem(pos);

			if (nIdx >= 0 && nIdx < m_showMess.GetItemCount())
			{
				student_infor.ID = m_showMess.GetItemText(nIdx, 0);
				student_infor.student_name = m_showMess.GetItemText(nIdx, 1);
				student_infor.student_number = m_showMess.GetItemText(nIdx, 2);
				student_infor.student_class = m_showMess.GetItemText(nIdx, 3);
				student_infor.student_gender = m_showMess.GetItemText(nIdx, 4);
				student_infor.student_age = m_showMess.GetItemText(nIdx, 5);
				student_infor.student_startTime = m_showMess.GetItemText(nIdx, 6);
				
				SetEditText(student_infor);
			}
		}
	}
	return student_infor;
}

//将数据库信息显示到ListCtrl（列表）控件中 m_pRecordset - 数据库列表返回指针 showPost - 显示在list中的行数
void StudentInforDlg::ShowMessToList(_RecordsetPtr m_pRecordset, int showPost)
{
	student_infor.ID = m_pRecordset->GetCollect("ID");
	student_infor.student_name = m_pRecordset->GetCollect("姓名");
	student_infor.student_number = m_pRecordset->GetCollect("学号");
	student_infor.student_class = m_pRecordset->GetCollect("班级");
	student_infor.student_gender = m_pRecordset->GetCollect("性别");
	student_infor.student_age = m_pRecordset->GetCollect("年龄");
	student_infor.student_startTime = m_pRecordset->GetCollect("入学日期");

	m_showMess.InsertItem(showPost, student_infor.ID);
	m_showMess.SetItemText(showPost, 1, student_infor.student_name);
	m_showMess.SetItemText(showPost, 2, student_infor.student_number);
	m_showMess.SetItemText(showPost, 3, student_infor.student_class);
	m_showMess.SetItemText(showPost, 4, student_infor.student_gender);
	m_showMess.SetItemText(showPost, 5, student_infor.student_age);
	m_showMess.SetItemText(showPost, 6, student_infor.student_startTime);
}

//ListCtrl控件发生改变是执行的函数
void StudentInforDlg::OnLvnItemchangedListctrlInfor(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	GetListSelectInfor();
}

//插入信息按钮处理函数
void StudentInforDlg::OnBnClickedButtonInsert()
{
	student_infor = GetEditText();
	if (student_infor.student_name == "" ||
		student_infor.student_number == "" ||
		student_infor.student_class == "" ||
		student_infor.student_gender == "" ||
		student_infor.student_age == "" ||
		student_infor.student_startTime == ""
		)
	{
		MessageBox(_T("所有信息不能为空！请补全信息"));
	}
	else
	{
		//插入数据库信息
		DBConn.addMessage(student_infor);
	}
	
}

//修改信息按钮处理函数
void StudentInforDlg::OnBnClickedButtonChange()
{
	//修改学生信息
	StudentInfor stu_infor;
	stu_infor = GetEditText();
	DBConn.rewriteMessage(stu_infor);
}

//删除信息按钮处理函数
void StudentInforDlg::OnBnClickedButtonDelete()
{
	//删除学生信息
	StudentInfor stu_infor;
	stu_infor = GetListSelectInfor();
	DBConn.deleMessage(stu_infor);
}

//查找学生信息按钮处理函数
void StudentInforDlg::OnBnClickedButtonFind()
{
	int showPost = 0;
	StudentInfor stu_infor;
	//清空listCtrl控件中的信息
	m_showMess.DeleteAllItems();
	stu_infor = GetEditText();

	//判断数据表是否为空，不为空将指针m_pRecordset移向表头位置
	if (!DBConn.m_pRecordset->BOF)
	{
		DBConn.m_pRecordset->MoveFirst();
	}
	else
	{
		AfxMessageBox(_T("表内数据为空"));
	}

	
	//判断查找学生信息，并显示在listCtrl控件中
	while (!DBConn.m_pRecordset->adoEOF)
	{
		if (stu_infor.student_name == DBConn.m_pRecordset->GetCollect("姓名") ||
			stu_infor.student_number == DBConn.m_pRecordset->GetCollect("学号") ||
			stu_infor.student_class == DBConn.m_pRecordset->GetCollect("班级") ||
			stu_infor.student_gender == DBConn.m_pRecordset->GetCollect("性别") ||
			stu_infor.student_age == DBConn.m_pRecordset->GetCollect("年龄") ||
			stu_infor.student_startTime == DBConn.m_pRecordset->GetCollect("入学日期"))
		{
			
			ShowMessToList(DBConn.m_pRecordset, showPost);
			showPost++;
		}

		DBConn.m_pRecordset->MoveNext();
	}

}

//清除所有编辑框中的文字按钮处理函数
void StudentInforDlg::OnBnClickedButtonClearEdit()
{
	DeleteEditText();
}

//显示信息到列表中按钮处理函数
void StudentInforDlg::OnBnClickedButtonReadMes()
{
	int showPost = 0;
	
	if (!DBConn.m_pRecordset->BOF)
	{
		DBConn.m_pRecordset->MoveFirst();
	}
	else
	{
		AfxMessageBox(_T("表内数据为空"));
	}
	//清空listCtrl控件中的信息
	m_showMess.DeleteAllItems();
	
	//读取数据库信息并把他们显示到listCtrl控件中
	while (!DBConn.m_pRecordset->adoEOF)
	{
		ShowMessToList(DBConn.m_pRecordset, showPost);
		showPost++;

		DBConn.m_pRecordset->MoveNext();
	}
}

//模糊查询按钮处理函数
void StudentInforDlg::OnBnClickedButtonFuzzyFind()
{
	int showPost = 0;
	_bstr_t bstrSQL;
	CString str_sql, strText;
	_RecordsetPtr m_pRecordset;
	m_name.GetWindowTextW(strText);
	str_sql = "select * from students where 姓名 like '%";
	str_sql = str_sql + strText + _T("%'");
	bstrSQL = str_sql;
	//bstrSQL = "select * from students where 姓名 like '%张%'";
	m_pRecordset = DBConn.ExecuteSQL(bstrSQL);

	if (!m_pRecordset->BOF)
	{
		m_pRecordset->MoveFirst();
	}
	else
	{
		AfxMessageBox(_T("表内数据为空"));
	}
	//清空listCtrl控件中的信息
	m_showMess.DeleteAllItems();

	//读取数据库信息并把他们显示到listCtrl控件中
	while (!m_pRecordset->adoEOF)
	{
		ShowMessToList(m_pRecordset, showPost);
		showPost++;

		m_pRecordset->MoveNext();
	}

}

//首项显示按钮处理函数
void StudentInforDlg::OnBnClickedButtonFirst()
{
	//清空listCtrl控件中的信息
	m_showMess.DeleteAllItems();

	DBConn.m_pRecordset->MoveFirst();
	ShowMessToList(DBConn.m_pRecordset);
}

//尾项显示按钮处理函数
void StudentInforDlg::OnBnClickedButtonLast()
{
	//清空listCtrl控件中的信息
	m_showMess.DeleteAllItems();

	//需要重新连接students表，当进行模糊查询之后会出现读取数据库数据的Bug
	_bstr_t strConnect = "SELECT * FROM students";//连接字符串students
	DBConn.m_pRecordset = DBConn.GetRecordSet(strConnect);

	
	DBConn.m_pRecordset->MoveLast();

	ShowMessToList(DBConn.m_pRecordset);
}

LRESULT StudentInforDlg::OnClose(WPARAM wPara, LPARAM lPara)
{
	if (IDNO == MessageBox(_T("请再次确认退出"), _T("提示"), MB_YESNO))
	{
		return 0;
	}
	else
	{
		DBConn.ExitConn();
		PostQuitMessage(0);
	}
	return 0;
}

//list control 控件初始化
void StudentInforDlg::InitListCtrl()
{
	//int num = 9;//表头数目
	//设置Listctrl为报表形式
	CListCtrl* pmyListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_STUMES);
	DWORD dwStyle = GetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE);
	SetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT);

	//设置listctrl可以整行选择和网格条纹
	DWORD styles = pmyListCtrl->GetExtendedStyle();
	pmyListCtrl->SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//给listctrl设置8个标题栏
	TCHAR rgtsz[list_head_num][100] = { _T("ID"), _T("姓名"), _T("学号"), _T("班级"), _T("性别"), _T("年龄"), _T("入学时间")};

	//修改数组大小，可以确定分栏数和没栏长度，如果修改下面的数据（蓝色部分）也要跟着改变
	LV_COLUMN lvcolumn;
	CRect rect;
	pmyListCtrl->GetWindowRect(&rect);
	for (int i = 0; i < list_head_num; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT
			| LVCF_WIDTH | LVCF_ORDER;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = rgtsz[i];
		lvcolumn.iSubItem = i;
		lvcolumn.iOrder = i;
		lvcolumn.cx = rect.Width() / list_head_num;
		pmyListCtrl->InsertColumn(i, &lvcolumn);
	}

}


HBRUSH StudentInforDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if (pWnd == this)
	{
		return m_brBk;
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		pDC->SetTextColor(RGB(0, 0, 0));//设置字体为黑色
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	return hbr;
}
