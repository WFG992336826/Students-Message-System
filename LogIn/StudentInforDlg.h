// StudentInforDlg.h: 头文件

#pragma once
// StudentInforDlg 对话框
#include "Database.h"
class StudentInforDlg : public CDialogEx
{
public:
	StudentInforDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTINFOR_DIALOG };
#endif

protected:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Database DBConn;
	StudentInfor student_infor;
	CEdit m_name;
	CEdit m_stuNum;
	CEdit m_class;
	CEdit m_gender;
	CEdit m_age;
	CEdit m_startTime;
	CListCtrl m_showMess;
	CBrush m_brBk;//背景图片设置


	afx_msg void OnBnClickedButtonInsert();//插入信息
	afx_msg void OnBnClickedButtonChange();//修改信息
	afx_msg void OnBnClickedButtonDelete();//删除信息
	afx_msg void OnBnClickedButtonFind();//精确查找
	afx_msg void OnBnClickedButtonClearEdit();//清空编辑框
	afx_msg void OnBnClickedButtonReadMes(); //读取信息
	afx_msg void OnBnClickedButtonFuzzyFind();//模糊查询
	afx_msg void OnBnClickedButtonFirst();//首项显示
	afx_msg void OnBnClickedButtonLast();//尾项显示
	afx_msg LRESULT OnClose(WPARAM wPara, LPARAM lPara);

	void InitListCtrl(); //list control 控件初始化
	StudentInfor GetEditText();//获取编辑框的文字信息
	void SetEditText(StudentInfor student_infor);//设置编辑框文字
	void DeleteEditText();//清空编辑框的文字信息
	StudentInfor GetListSelectInfor();//将编辑框用鼠标选中的信息显示到编辑框中
	void ShowMessToList(_RecordsetPtr m_pRecordset, int showPost = 0);//将数据库信息显示到ListCtrl（列表）控件中

	afx_msg void OnLvnItemchangedListctrlInfor(NMHDR* pNMHDR, LRESULT* pResult);//ListCtrl控件发生改变是执行的函数

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
