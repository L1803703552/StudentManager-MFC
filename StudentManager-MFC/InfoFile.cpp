#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_LOGIN); //���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //��ȡһ������
	ifs.getline(buf, sizeof(buf)); // �ٶ�ȡһ�У����������û�������
	ifs.getline(buf, sizeof(buf));
	Sql_Host = buf;// ������ַ
	ifs.getline(buf, sizeof(buf));
	Sql_User = buf;// �û���
	ifs.getline(buf, sizeof(buf));
	Sql_Pwd = buf;// ����
	ifs.getline(buf, sizeof(buf));
	Sql_DB = buf;// ���ݿ���
	ifs.getline(buf, sizeof(buf));
	Sql_Port = atoi(buf);// �˿ں�
	ifs.close(); //�ر��ļ�
}


CInfoFile::~CInfoFile()
{
}

//��ȡ��½��Ϣ
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_LOGIN); //���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //��ȡһ������
	name = CString(buf);			 //char *ת��ΪCString
	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);
	ifs.close(); //�ر��ļ�
}

//�޸�����
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //�����ļ��������
	ofs.open(_F_LOGIN); //���ļ�

	ofs << name << endl;
	ofs << pwd << endl;

	ofs.close();	//�ر��ļ�
}

//��ȡѧ����Ϣ
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	ls.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		// AfxMessageBox(CString(buf));
		char *sst = strtok(buf, ","); //�ԡ�,���и�
		if (sst != NULL)
		{
			tmp.id = sst; //ѧ��
		}
		else
		{
			break;
		}

		sst = strtok(NULL, ",");
		tmp.name = sst;	//����

		sst = strtok(NULL, ",");
		tmp.sub1 = atoi(sst);	//ѧ��1

		sst = strtok(NULL, ",");
		tmp.sub2 = atoi(sst);	//ѧ��2

		ls.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//д���ļ�
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//�����ʽ���ļ�

	if (ls.size() > 0)	//ѧ�����������ݲ�ִ��
	{
		ofs << "ѧ��,����,ѧ��1,ѧ��2" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�,���ָ�����β�ӻ���
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << ",";		
			ofs << it->name << ",";
			ofs << it->sub1 << ",";
			ofs << it->sub2 << endl;
		}
	}

	ofs.close();//�ر��ļ�
}

// ���ѧ��
// id:ѧ�ţ�name:������sub1:�ɼ�1��sub2:�ɼ�2
void CInfoFile::Addline(CString id, CString name, int sub1, int sub2)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//ѧ�š�������������Ч
		if (!name.IsEmpty() && !id.IsEmpty())
		{
			CStringA str;
			str = id;
			tmp.id = str.GetBuffer();
			str = name;	//CStringתCStirngA
			tmp.name = str.GetBuffer(); //CStirngAתchar *������
			tmp.sub1 = sub1;	//ѧ��1
			tmp.sub2 = sub2;	//ѧ��2

			ls.push_back(tmp);	//��������ĺ���
		}
	}
}

BOOL CInfoFile::ConnectDB()
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&m_sqlCon);
	//�����ַ�����
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB18030");
	if (!mysql_real_connect(&m_sqlCon, Sql_Host.c_str(), Sql_User.c_str(), Sql_Pwd.c_str(), Sql_DB.c_str(), Sql_Port, NULL, 0))
	{
		AfxMessageBox(_T("�������ݿ�ʧ��!"));
		return FALSE;
	}
	else
	{
		AfxMessageBox(_T("�������ݿ�ɹ�!"));
		return TRUE;
	}
}

BOOL CInfoFile::DisconnectDB()
{
	mysql_close(&m_sqlCon);//�ر�Mysql����  
	return TRUE;
}

void CInfoFile::GetDBInfo(CString& host, CString& user, CString& pwd, CString& db, int& port)
{
	host = (CString)Sql_Host.c_str();
	user = (CString)Sql_User.c_str();
	pwd = (CString)Sql_Pwd.c_str();
	db = (CString)Sql_DB.c_str();
	port = Sql_Port;
}

void CInfoFile::WriteDBInfo(char* host, char* user, char* pwd, char* db, int port)
{
	ifstream ifs;
	string user_name, user_pwd;
	ifs.open(_F_LOGIN);
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));
	user_name = buf;
	ifs.getline(buf, sizeof(buf));
	user_pwd = buf;
	ifs.close(); //�ر��ļ�

	ofstream ofs;
	ofs.open(_F_LOGIN);
	ofs << user_name << endl;
	ofs << user_pwd << endl;
	ofs << host << endl;
	ofs << user << endl;
	ofs << pwd << endl;
	ofs << db << endl;
	ofs << port << endl;

	ofs.close();	//�ر��ļ�
}

BOOL CInfoFile::ReadDB()
{
	mysql_query(&m_sqlCon, "select * from stumanager;");
	result = mysql_store_result(&m_sqlCon);
	if (!result)
		return FALSE;
	msg tmp;
	while (row = mysql_fetch_row(result))
	{
		tmp.id = row[0];
		tmp.name = row[1];
		tmp.sub1 = atoi(row[2]);
		tmp.sub2 = atoi(row[3]);
		ls.push_back(tmp);
	}
	return TRUE;
}

BOOL CInfoFile::WriteDB()
{
	return TRUE;
}
