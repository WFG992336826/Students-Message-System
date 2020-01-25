// Database.h: ͷ�ļ�

#pragma once

//����һ�����ݽṹ
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
		_ConnectionPtr m_pConnection;                   //����access���ݿ�����Ӷ���
		_RecordsetPtr m_pRecordset;                     //���������
	public:
		void OnInitADOConn();                           //��ʼ�����Ӷ��� 
		void ExitConn();								//�ر����ݿ�����
		_RecordsetPtr GetRecordSet(_bstr_t bstrSQL);	//��ȡ��¼��
		_RecordsetPtr ExecuteSQL(_bstr_t bstrSQL);				//ִ�����ݿ����
		bool readMessage();                             //��ȡ��Ϣ
		bool addMessage(StudentInfor student_infor);    //�����Ϣ
		bool rewriteMessage(StudentInfor student_infor);//�޸���Ϣ
		bool deleMessage(StudentInfor student_infor);   //ɾ����Ϣ
		bool findMessage(StudentInfor student_infor);	//������Ϣ
		int loginVerify(CString account, CString password);  //��¼�����֤

};

