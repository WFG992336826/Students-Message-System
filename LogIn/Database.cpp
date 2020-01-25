// Database.cpp: 实现文件

#include "pch.h"
#include "Database.h"

//初始化连接对象
void Database::OnInitADOConn()
{
	//初始化OLE/COM环境
	HRESULT hr;
	::CoInitialize(NULL);
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");  //创建连接对象实例
		if (SUCCEEDED(hr))
		{
			_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=stdudentInfor.accdb;";//连接字符串
			hr = m_pConnection->Open(strConnect, "", "", adModeUnknown); //打开数据库
		}
		
	}
	catch (_com_error e)
	{
		//显示错误信息
		AfxMessageBox(e.Description());
	}

}

//返回数据库列表结果集
_RecordsetPtr Database::GetRecordSet(_bstr_t bstrSQL)
{
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	try
	{
		if (m_pConnection == NULL)                        //判断Connection对象是否为空
			OnInitADOConn();                              //如果为空则重新连接数据库

		m_pRecordset->Open(bstrSQL,      // 查询DemoTable表中所有字段"SELECT * FROM students"
			m_pConnection.GetInterfacePtr(),              // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
	}

	return m_pRecordset;
}

//执行SQL语句查询数据库
_RecordsetPtr Database::ExecuteSQL(_bstr_t bstrSQL)
{
	//执行SQL语句
	_CommandPtr  m_pCommand;
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection = m_pConnection;  // 将库连接赋于它
	m_pCommand->CommandText = bstrSQL;  // SQL语句
	m_pRecordset = m_pCommand->Execute(NULL, NULL, adCmdText); // 执行SQL语句，返回记录集
	m_pCommand = NULL;

	return m_pRecordset;
}

bool Database::readMessage()
{
	_variant_t var;
	CString strName, strAge;
	try
	{

		if (!m_pRecordset->BOF)
		{
			m_pRecordset->MoveFirst();
		}
		else
		{
			AfxMessageBox(_T("表内数据为空"));
			return m_pRecordset;
		}

		// 读入库中各字段并加入列表框中
		while (!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("学号");
			var = m_pRecordset->GetCollect("姓名");
			var = m_pRecordset->GetCollect("班级");
			var = m_pRecordset->GetCollect("性别");
			var = m_pRecordset->GetCollect("年龄");
			var = m_pRecordset->GetCollect("入学日期");

			m_pRecordset->MoveNext();
		}

	}
	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false;
	}

	return true;
}

//添加信息
bool Database::addMessage(StudentInfor student_infor)
{
	//检查插入的学生信息是否重复
	try
	{

		if (!m_pRecordset->BOF)
		{
			m_pRecordset->MoveFirst();
		}

		//检测学号是否相同 不同则可以插入信息
		while (!m_pRecordset->adoEOF)
		{
			if (student_infor.student_number == m_pRecordset->GetCollect("学号"))
			{
				AfxMessageBox(_T("插入失败，已存在相同学号的学生"));
				return false;
			}

			m_pRecordset->MoveNext();
		}

	}
	catch (_com_error * e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false;
	}

	// 写入数据库学生信息
	try
	{
		
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("姓名", _variant_t(student_infor.student_name));
		m_pRecordset->PutCollect("学号", _variant_t(student_infor.student_number));
		m_pRecordset->PutCollect("班级", _variant_t(student_infor.student_class));
		m_pRecordset->PutCollect("性别", _variant_t(student_infor.student_gender));
		m_pRecordset->PutCollect("年龄", _variant_t(student_infor.student_age));
		m_pRecordset->PutCollect("入学日期", _variant_t(student_infor.student_startTime));
		m_pRecordset->Update();

		AfxMessageBox(_T("插入成功!"));
	}
	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false;
	}

	return true;
}

//修改信息
bool Database::rewriteMessage(StudentInfor student_infor)
{
	//检查修改的学生信息
	if (!m_pRecordset->BOF)
	{
		m_pRecordset->MoveFirst();
	}

	//检测学号是否相同 不同则可以插入信息
	while (!m_pRecordset->adoEOF)
	{
		if (student_infor.student_number == m_pRecordset->GetCollect("学号") &&
			student_infor.ID == m_pRecordset->GetCollect("ID"))
		{
			m_pRecordset->PutCollect("姓名", _variant_t(student_infor.student_name));
			m_pRecordset->PutCollect("学号", _variant_t(student_infor.student_number));
			m_pRecordset->PutCollect("班级", _variant_t(student_infor.student_class));
			m_pRecordset->PutCollect("性别", _variant_t(student_infor.student_gender));
			m_pRecordset->PutCollect("年龄", _variant_t(student_infor.student_age));
			m_pRecordset->PutCollect("入学日期", _variant_t(student_infor.student_startTime));
			m_pRecordset->Update();

			AfxMessageBox(_T("修改成功"));
			return true;
		}

		m_pRecordset->MoveNext();
	}

	AfxMessageBox(_T("学号信息不可更改！！"));

	return false;
}

//删除信息
bool Database::deleMessage(StudentInfor student_infor)
{
	//检查修改的学生信息
	if (!m_pRecordset->BOF)
	{
		m_pRecordset->MoveFirst();
	}

	//检测学号是否相同 不同则可以插入信息
	while (!m_pRecordset->adoEOF)
	{
		if (student_infor.student_number == m_pRecordset->GetCollect("学号") &&
			student_infor.ID == m_pRecordset->GetCollect("ID"))
		{
			m_pRecordset->Delete(adAffectCurrent);  // 参数adAffectCurrent为删除当前记录
			m_pRecordset->Update();

			AfxMessageBox(_T("删除成功!"));
			return true;
		}

		m_pRecordset->MoveNext();
	}

	AfxMessageBox(_T("没有该学生相关信息，无法删除!"));
	return false;
}

bool Database::findMessage(StudentInfor student_infor)
{

	return false;
}

//20200101 此功能未经验证
//返回值 0-表示账号密码错误 1-表示登陆成功权限是管理员 2-表示登陆成功权限是学生
int Database::loginVerify(CString account, CString password)
{
	_variant_t var_account, var_password;
	CString str_user;
	// 读入库中各字段并加入列表框中
	while (!m_pRecordset->adoEOF)
	{
		var_account = m_pRecordset->GetCollect("账号");
		var_password = m_pRecordset->GetCollect("密码");
		str_user = m_pRecordset->GetCollect("权限");
		if (var_account.vt != VT_NULL)
		{
			if (var_account == account && var_password == password)
			{
				if (str_user == _T("管理员"))
				{
					return 1;
				}
				else if(str_user == _T("学生"))
				{
					return 2;
				}
			}
		}

		m_pRecordset->MoveNext();
	}
	//将指针移向表格第一行
	m_pRecordset->MoveFirst();
	return 0;
}

//关闭连接
void Database::ExitConn()
{
	if (m_pRecordset != NULL)
	{
		m_pRecordset->Close();
	}
	m_pConnection->Close();
	//释放环境
	::CoUninitialize();
}
