// Database.h: 头文件

#pragma once

//定义一个数据结构
typedef struct StudentInfor
{
	CString ID;
	CString student_name;
	CString student_number;
	CString student_class;
	CString student_gender;
	CString student_age;
	CString student_startTime;
}StudentInfor;


class Database
{
	public:
		_ConnectionPtr m_pConnection;                   //连接access数据库的链接对象
		_RecordsetPtr m_pRecordset;                     //结果集对象
	public:
		void OnInitADOConn();                           //初始化连接对象 
		void ExitConn();								//关闭数据库连接
		_RecordsetPtr GetRecordSet(_bstr_t bstrSQL);	//获取记录集
		_RecordsetPtr ExecuteSQL(_bstr_t bstrSQL);				//执行数据库语句
		bool readMessage();                             //读取信息
		bool addMessage(StudentInfor student_infor);    //添加信息
		bool rewriteMessage(StudentInfor student_infor);//修改信息
		bool deleMessage(StudentInfor student_infor);   //删除信息
		bool findMessage(StudentInfor student_infor);	//查找信息
		int loginVerify(CString account, CString password);  //登录身份验证

};

