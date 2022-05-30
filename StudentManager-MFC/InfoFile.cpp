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
	ofs << Sql_Host << endl;
	ofs << Sql_User << endl;
	ofs << Sql_Pwd << endl;
	ofs << Sql_DB << endl;
	ofs << Sql_Port << endl;
	ofs.close();	//�ر��ļ�
}

//��ȡѧ����Ϣ
void CInfoFile::ReadDocline()
{
	ifstream ifi(_F_INFO); //���뷽ʽ��ѧ����Ϣ
	ifstream ifs(_F_STOCK); //���뷽ʽ�򿪳ɼ���Ϣ

	char buf[1024] = { 0 };
	ls.clear();
	subName.clear();
	stuInfo.clear();
	//ȡ����ͷ
	/*--------------ȡ��Ϣ�ֶ�-------------*/
	ifi.getline(buf, sizeof(buf));
	char* head = strtok(buf, ",");
	stuInfo.push_back(CString(head));
	while (head != NULL)
	{
		head = strtok(NULL, ",");
		if (head == NULL)
			break;
		stuInfo.push_back(CString(head));
	}
	/*--------------ȡѧ���ֶ�-------------*/
	ifs.getline(buf, sizeof(buf));
	head = strtok(buf, ",");
	subName.push_back(CString(head));
	while (head != NULL)
	{
		head = strtok(NULL, ",");
		if (head == NULL)
			break;
		subName.push_back(CString(head));
	}
	/*--------------ȡ����-------------*/
	while (!ifi.eof())
	{
		msg tmp;
		ifi.getline(buf, sizeof(buf));// ��ȡһ��ѧ����Ϣ
		char* sst = strtok(buf, ",");
		if (sst == NULL)
			tmp.info.push_back("#NULL");
		else
			tmp.info.push_back(sst);
		for (int i = 0; i < stuInfo.size() - 1; i++)//��ȡÿ���ֶ�
		{
			sst = strtok(NULL, ",");
			if (sst == NULL)
				tmp.info.push_back("#NULL");
			else
				tmp.info.push_back(sst);
		}
		ifs.getline(buf, sizeof(buf));// ��ȡһ��ѧ���ɼ�
		sst = strtok(buf, ","); 
		if (sst == NULL)
			tmp.sub.push_back(0);
		else
			tmp.sub.push_back(atoi(sst));
		for (int i = 0; i < subName.size() - 1; i++)//��ȡÿ��ѧ�Ƴɼ�
		{
			sst = strtok(NULL, ",");
			if (sst == NULL)
				tmp.sub.push_back(0);
			else
				tmp.sub.push_back(atoi(sst));
		}

		ls.push_back(tmp); //��������ĺ���
	}
	ls.pop_back();
	ifi.close();
	ifs.close(); //�ر��ļ�
}

//д���ļ�
void CInfoFile::WirteDocline()
{
	ofstream ofi(_F_INFO);
	ofstream ofs(_F_STOCK);//�����ʽ���ļ�
	//if (ls.size() > 0)	//ѧ�����������ݲ�ִ��
	//{
		/*--------------д���ͷ-------------*/
		ofi << CStringA(stuInfo.at(0));
		for (vector<CString>::iterator it = stuInfo.begin() + 1; it != stuInfo.end(); it++)
		{
			ofi << "," << CStringA(*it);
		}
		ofi << endl;

		ofs << CStringA(subName.at(0));
		for (vector<CString>::iterator it = subName.begin() + 1; it != subName.end(); it++)
		{
			ofs << "," << CStringA(*it);
		}
		ofs << endl;
		/*--------------д������-------------*/
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			// д��ѧ���ֶ���Ϣ
			ofi << it->info.at(0);
			for (vector<string>::iterator its = it->info.begin() + 1; its != it->info.end(); its++)
			{
				ofi << "," << *its;
			}
			ofi << endl;
			// д��ѧ���ɼ���Ϣ
			ofs << it->sub.at(0);
			for (vector<int>::iterator its = it->sub.begin() + 1; its != it->sub.end(); its++)
			{
				ofs << "," << *its;
			}
			ofs << endl;
		}
	//}

	ofi.close();
	ofs.close();//�ر��ļ�
}

// �������ݿ�
BOOL CInfoFile::ConnectDB()
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&m_sqlCon);
	//�����ַ�����
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB18030");
	if (!mysql_real_connect(&m_sqlCon, Sql_Host.c_str(), Sql_User.c_str(), Sql_Pwd.c_str(), Sql_DB.c_str(), Sql_Port, NULL, 0))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

// �ر�����
BOOL CInfoFile::DisconnectDB()
{
	mysql_close(&m_sqlCon);//�ر�Mysql����  
	return TRUE;
}

// ��ȡ���ݿ�������Ϣ
void CInfoFile::GetDBInfo(CString& host, CString& user, CString& pwd, CString& db, int& port)
{
	host = (CString)Sql_Host.c_str();
	user = (CString)Sql_User.c_str();
	pwd = (CString)Sql_Pwd.c_str();
	db = (CString)Sql_DB.c_str();
	port = Sql_Port;
}

// �������ݿ�������Ϣ
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

// �����ݿ��ȡ��Ϣ
BOOL CInfoFile::ReadDB()
{
	ls.clear();
	stuInfo.clear();
	subName.clear();
	/*----------��ȡ��Ϣ�ֶ�----------*/
	mysql_query(&m_sqlCon, "show full fields from info");
	resInfo = mysql_store_result(&m_sqlCon);
	if (!resInfo)
		return FALSE;
	while (rowInfo = mysql_fetch_row(resInfo))
	{
		stuInfo.push_back(CString(rowInfo[0]));
	}
	/*----------��ȡѧ������----------*/
	mysql_query(&m_sqlCon, "show full fields from score");
	resSub = mysql_store_result(&m_sqlCon);
	if (!resSub)
		return FALSE;
	rowSub = mysql_fetch_row(resSub);// ������������š�
	while (rowSub = mysql_fetch_row(resSub))
	{
		subName.push_back(CString(rowSub[0]));
	}
	/*----------��ȡ��Ϣ����----------*/
	mysql_query(&m_sqlCon, "select * from info;");
	resInfo = mysql_store_result(&m_sqlCon);
	if (!resInfo)
		return FALSE;
	mysql_query(&m_sqlCon, "select * from score;");
	resSub = mysql_store_result(&m_sqlCon);
	if (!resSub)
		return FALSE;
	/*----------��ȡ����----------*/
	while (rowInfo = mysql_fetch_row(resInfo))
	{
		msg tmp;
		// ��ȡѧ����Ϣ
		int j = 0;
		for (vector<CString>::iterator it = stuInfo.begin(); it != stuInfo.end(); it++)
		{
			string str;
			str = rowInfo[j];
			if (str == "")
				tmp.info.push_back("#NULL");
			else
				tmp.info.push_back(str);
			j++;
		}
		// ��ȡѧ����Ϣ
		rowSub = mysql_fetch_row(resSub);
		j = 1;
		for (vector<CString>::iterator it = subName.begin(); it != subName.end(); it++)
		{
			string str;
			str = rowSub[j];
			if (str == "")
				tmp.sub.push_back(0);
			else
				tmp.sub.push_back(atoi(rowSub[j]));
			j++;
		}
		ls.push_back(tmp);
	}
	return TRUE;
}

// д�뵽���ݿ�
BOOL CInfoFile::WriteDB()
{
	int flag=0;
	/*----------ɾ��ԭ��¼----------*/
	flag = mysql_query(&m_sqlCon, "drop table info;");
	flag = mysql_query(&m_sqlCon, "drop table score;");
	/*----------����ѧ����Ϣ�ֶ�----------*/
	char sqlheadInfo[1024] = { 0 }, sqlheadSub[1024] = { 0 }, sqlstr[1024] = { 0 };
	snprintf(sqlstr, 1024, "create table if not exists info (");
	snprintf(sqlstr, 1024, "%s `%s` varchar(255) NOT NULL DEFAULT ''", sqlstr, CStringA(stuInfo[0]));
	for (int i = 1; i < stuInfo.size(); i++)
	{
		snprintf(sqlstr, 1024, "%s ,`%s` varchar(255) NULL DEFAULT ''", sqlstr, CStringA(stuInfo[i]));
	}
	snprintf(sqlstr, 1024, "%s ,PRIMARY KEY (`%s`));", sqlstr, CStringA(stuInfo[0]));
	flag = mysql_query(&m_sqlCon, sqlstr);
	if (flag)
	{
		AfxMessageBox(CString(mysql_error(&m_sqlCon)));
		return FALSE;
	}
	/*----------����ѧ���ɼ��ֶ�----------*/
	snprintf(sqlstr, 1024, "create table if not exists score (");
	snprintf(sqlstr, 1024, "%s `%s` int NOT NULL AUTO_INCREMENT", sqlstr, "���");
	for (int i = 0; i < subName.size(); i++)
	{
		snprintf(sqlstr, 1024, "%s ,\n`%s` int NULL", sqlstr, CStringA(subName[i]));
	}
	snprintf(sqlstr, 1024, "%s ,\nPRIMARY KEY (`%s`));", sqlstr, "���");
	flag = mysql_query(&m_sqlCon, sqlstr);
	if (flag)
	{
		AfxMessageBox(CString(mysql_error(&m_sqlCon)));
		return FALSE;
	}
	/*----------��������ͷ----------*/
	// ѧ����Ϣ����ͷ
	snprintf(sqlheadInfo, 1024, "insert into info (`%s`",CStringA(stuInfo[0]));
	for (int i = 1; i < stuInfo.size(); i++)
	{
		snprintf(sqlheadInfo, 1024, "%s ,`%s`", sqlheadInfo, CStringA(stuInfo[i]));
	}
	snprintf(sqlheadInfo, 1024, "%s) values(",sqlheadInfo);
	// ѧ���ɼ�����ͷ
	snprintf(sqlheadSub, 1024, "insert into score (`%s`", CStringA(subName[0]));
	for (int i = 1; i < subName.size(); i++)
	{
		snprintf(sqlheadSub, 1024, "%s ,`%s`", sqlheadSub, CStringA(subName[i]));
	}
	snprintf(sqlheadSub, 1024, "%s) values(", sqlheadSub);
	/*----------��ʼд��----------*/
	for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
	{
		snprintf(sqlstr, 1024, "%s'%s'", sqlheadInfo,it->info[0].c_str());
		for (vector<string>::iterator its = it->info.begin() + 1; its != it->info.end(); its++)
		{
			if (*its == "")
			{
				snprintf(sqlstr, 1024, "%s ,'%s'", sqlstr,"#NULL");
			}
			else
				snprintf(sqlstr, 1024, "%s ,'%s'", sqlstr, its->c_str());
		}
		snprintf(sqlstr, 1024, "%s);", sqlstr);
		flag = mysql_real_query(&m_sqlCon, sqlstr, strlen(sqlstr));
		if (flag)
			return FALSE;
		snprintf(sqlstr, 1024, "%s%d", sqlheadSub, it->sub[0]);
		for (vector<int>::iterator its = it->sub.begin() + 1; its != it->sub.end(); its++)
		{
			snprintf(sqlstr, 1024, "%s ,%d", sqlstr, *its);
		}
		snprintf(sqlstr, 1024, "%s);", sqlstr);
		flag = mysql_real_query(&m_sqlCon, sqlstr, strlen(sqlstr));
		if (flag)
			return FALSE;
	}
	return TRUE;
}

