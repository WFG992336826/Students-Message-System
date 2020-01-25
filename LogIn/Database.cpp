// Database.cpp: ʵ���ļ�

#include "pch.h"
#include "Database.h"

//��ʼ�����Ӷ���
void Database::OnInitADOConn()
{
	//��ʼ��OLE/COM����
	HRESULT hr;
	::CoInitialize(NULL);
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");  //�������Ӷ���ʵ��
		if (SUCCEEDED(hr))
		{
			_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=stdudentInfor.accdb;";//�����ַ���
			hr = m_pConnection->Open(strConnect, "", "", adModeUnknown); //�����ݿ�
		}
		
	}
	catch (_com_error e)
	{
		//��ʾ������Ϣ
		AfxMessageBox(e.Description());
	}

}

//�������ݿ��б�����
_RecordsetPtr Database::GetRecordSet(_bstr_t bstrSQL)
{
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	try
	{
		if (m_pConnection == NULL)                        //�ж�Connection�����Ƿ�Ϊ��
			OnInitADOConn();                              //���Ϊ���������������ݿ�

		m_pRecordset->Open(bstrSQL,      // ��ѯDemoTable���������ֶ�"SELECT * FROM students"
			m_pConnection.GetInterfacePtr(),              // ��ȡ��ӿ��IDispatchָ��
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

//ִ��SQL����ѯ���ݿ�
_RecordsetPtr Database::ExecuteSQL(_bstr_t bstrSQL)
{
	//ִ��SQL���
	_CommandPtr  m_pCommand;
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection = m_pConnection;  // �������Ӹ�����
	m_pCommand->CommandText = bstrSQL;  // SQL���
	m_pRecordset = m_pCommand->Execute(NULL, NULL, adCmdText); // ִ��SQL��䣬���ؼ�¼��
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
			AfxMessageBox(_T("��������Ϊ��"));
			return m_pRecordset;
		}

		// ������и��ֶβ������б����
		while (!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("ѧ��");
			var = m_pRecordset->GetCollect("����");
			var = m_pRecordset->GetCollect("�༶");
			var = m_pRecordset->GetCollect("�Ա�");
			var = m_pRecordset->GetCollect("����");
			var = m_pRecordset->GetCollect("��ѧ����");

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

//�����Ϣ
bool Database::addMessage(StudentInfor student_infor)
{
	//�������ѧ����Ϣ�Ƿ��ظ�
	try
	{

		if (!m_pRecordset->BOF)
		{
			m_pRecordset->MoveFirst();
		}

		//���ѧ���Ƿ���ͬ ��ͬ����Բ�����Ϣ
		while (!m_pRecordset->adoEOF)
		{
			if (student_infor.student_number == m_pRecordset->GetCollect("ѧ��"))
			{
				AfxMessageBox(_T("����ʧ�ܣ��Ѵ�����ͬѧ�ŵ�ѧ��"));
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

	// д�����ݿ�ѧ����Ϣ
	try
	{
		
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("����", _variant_t(student_infor.student_name));
		m_pRecordset->PutCollect("ѧ��", _variant_t(student_infor.student_number));
		m_pRecordset->PutCollect("�༶", _variant_t(student_infor.student_class));
		m_pRecordset->PutCollect("�Ա�", _variant_t(student_infor.student_gender));
		m_pRecordset->PutCollect("����", _variant_t(student_infor.student_age));
		m_pRecordset->PutCollect("��ѧ����", _variant_t(student_infor.student_startTime));
		m_pRecordset->Update();

		AfxMessageBox(_T("����ɹ�!"));
	}
	catch (_com_error* e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false;
	}

	return true;
}

//�޸���Ϣ
bool Database::rewriteMessage(StudentInfor student_infor)
{
	//����޸ĵ�ѧ����Ϣ
	if (!m_pRecordset->BOF)
	{
		m_pRecordset->MoveFirst();
	}

	//���ѧ���Ƿ���ͬ ��ͬ����Բ�����Ϣ
	while (!m_pRecordset->adoEOF)
	{
		if (student_infor.student_number == m_pRecordset->GetCollect("ѧ��") &&
			student_infor.ID == m_pRecordset->GetCollect("ID"))
		{
			m_pRecordset->PutCollect("����", _variant_t(student_infor.student_name));
			m_pRecordset->PutCollect("ѧ��", _variant_t(student_infor.student_number));
			m_pRecordset->PutCollect("�༶", _variant_t(student_infor.student_class));
			m_pRecordset->PutCollect("�Ա�", _variant_t(student_infor.student_gender));
			m_pRecordset->PutCollect("����", _variant_t(student_infor.student_age));
			m_pRecordset->PutCollect("��ѧ����", _variant_t(student_infor.student_startTime));
			m_pRecordset->Update();

			AfxMessageBox(_T("�޸ĳɹ�"));
			return true;
		}

		m_pRecordset->MoveNext();
	}

	AfxMessageBox(_T("ѧ����Ϣ���ɸ��ģ���"));

	return false;
}

//ɾ����Ϣ
bool Database::deleMessage(StudentInfor student_infor)
{
	//����޸ĵ�ѧ����Ϣ
	if (!m_pRecordset->BOF)
	{
		m_pRecordset->MoveFirst();
	}

	//���ѧ���Ƿ���ͬ ��ͬ����Բ�����Ϣ
	while (!m_pRecordset->adoEOF)
	{
		if (student_infor.student_number == m_pRecordset->GetCollect("ѧ��") &&
			student_infor.ID == m_pRecordset->GetCollect("ID"))
		{
			m_pRecordset->Delete(adAffectCurrent);  // ����adAffectCurrentΪɾ����ǰ��¼
			m_pRecordset->Update();

			AfxMessageBox(_T("ɾ���ɹ�!"));
			return true;
		}

		m_pRecordset->MoveNext();
	}

	AfxMessageBox(_T("û�и�ѧ�������Ϣ���޷�ɾ��!"));
	return false;
}

bool Database::findMessage(StudentInfor student_infor)
{

	return false;
}

//20200101 �˹���δ����֤
//����ֵ 0-��ʾ�˺�������� 1-��ʾ��½�ɹ�Ȩ���ǹ���Ա 2-��ʾ��½�ɹ�Ȩ����ѧ��
int Database::loginVerify(CString account, CString password)
{
	_variant_t var_account, var_password;
	CString str_user;
	// ������и��ֶβ������б����
	while (!m_pRecordset->adoEOF)
	{
		var_account = m_pRecordset->GetCollect("�˺�");
		var_password = m_pRecordset->GetCollect("����");
		str_user = m_pRecordset->GetCollect("Ȩ��");
		if (var_account.vt != VT_NULL)
		{
			if (var_account == account && var_password == password)
			{
				if (str_user == _T("����Ա"))
				{
					return 1;
				}
				else if(str_user == _T("ѧ��"))
				{
					return 2;
				}
			}
		}

		m_pRecordset->MoveNext();
	}
	//��ָ���������һ��
	m_pRecordset->MoveFirst();
	return 0;
}

//�ر�����
void Database::ExitConn()
{
	if (m_pRecordset != NULL)
	{
		m_pRecordset->Close();
	}
	m_pConnection->Close();
	//�ͷŻ���
	::CoUninitialize();
}
