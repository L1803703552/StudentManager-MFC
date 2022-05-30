#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf)); //读取一行内容
	ifs.getline(buf, sizeof(buf)); // 再读取一行，跳过本地用户名密码
	ifs.getline(buf, sizeof(buf));
	Sql_Host = buf;// 主机地址
	ifs.getline(buf, sizeof(buf));
	Sql_User = buf;// 用户名
	ifs.getline(buf, sizeof(buf));
	Sql_Pwd = buf;// 密码
	ifs.getline(buf, sizeof(buf));
	Sql_DB = buf;// 数据库名
	ifs.getline(buf, sizeof(buf));
	Sql_Port = atoi(buf);// 端口号
	ifs.close(); //关闭文件
}


CInfoFile::~CInfoFile()
{
}

//读取登陆信息
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	name = CString(buf);			 //char *转换为CString
	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);
	ifs.close(); //关闭文件
}

//修改密码
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件

	ofs << name << endl;
	ofs << pwd << endl;
	ofs << Sql_Host << endl;
	ofs << Sql_User << endl;
	ofs << Sql_Pwd << endl;
	ofs << Sql_DB << endl;
	ofs << Sql_Port << endl;
	ofs.close();	//关闭文件
}

//读取学生信息
void CInfoFile::ReadDocline()
{
	ifstream ifi(_F_INFO); //输入方式打开学生信息
	ifstream ifs(_F_STOCK); //输入方式打开成绩信息

	char buf[1024] = { 0 };
	ls.clear();
	subName.clear();
	stuInfo.clear();
	//取出表头
	/*--------------取信息字段-------------*/
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
	/*--------------取学科字段-------------*/
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
	/*--------------取内容-------------*/
	while (!ifi.eof())
	{
		msg tmp;
		ifi.getline(buf, sizeof(buf));// 读取一行学生信息
		char* sst = strtok(buf, ",");
		if (sst == NULL)
			tmp.info.push_back("#NULL");
		else
			tmp.info.push_back(sst);
		for (int i = 0; i < stuInfo.size() - 1; i++)//读取每个字段
		{
			sst = strtok(NULL, ",");
			if (sst == NULL)
				tmp.info.push_back("#NULL");
			else
				tmp.info.push_back(sst);
		}
		ifs.getline(buf, sizeof(buf));// 读取一行学生成绩
		sst = strtok(buf, ","); 
		if (sst == NULL)
			tmp.sub.push_back(0);
		else
			tmp.sub.push_back(atoi(sst));
		for (int i = 0; i < subName.size() - 1; i++)//读取每个学科成绩
		{
			sst = strtok(NULL, ",");
			if (sst == NULL)
				tmp.sub.push_back(0);
			else
				tmp.sub.push_back(atoi(sst));
		}

		ls.push_back(tmp); //放在链表的后面
	}
	ls.pop_back();
	ifi.close();
	ifs.close(); //关闭文件
}

//写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofi(_F_INFO);
	ofstream ofs(_F_STOCK);//输出方式打开文件
	//if (ls.size() > 0)	//学生链表有内容才执行
	//{
		/*--------------写入表头-------------*/
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
		/*--------------写入数据-------------*/
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			// 写入学生字段信息
			ofi << it->info.at(0);
			for (vector<string>::iterator its = it->info.begin() + 1; its != it->info.end(); its++)
			{
				ofi << "," << *its;
			}
			ofi << endl;
			// 写入学生成绩信息
			ofs << it->sub.at(0);
			for (vector<int>::iterator its = it->sub.begin() + 1; its != it->sub.end(); its++)
			{
				ofs << "," << *its;
			}
			ofs << endl;
		}
	//}

	ofi.close();
	ofs.close();//关闭文件
}

// 连接数据库
BOOL CInfoFile::ConnectDB()
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&m_sqlCon);
	//设置字符编码
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

// 关闭连接
BOOL CInfoFile::DisconnectDB()
{
	mysql_close(&m_sqlCon);//关闭Mysql连接  
	return TRUE;
}

// 获取数据库连接信息
void CInfoFile::GetDBInfo(CString& host, CString& user, CString& pwd, CString& db, int& port)
{
	host = (CString)Sql_Host.c_str();
	user = (CString)Sql_User.c_str();
	pwd = (CString)Sql_Pwd.c_str();
	db = (CString)Sql_DB.c_str();
	port = Sql_Port;
}

// 保存数据库连接信息
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
	ifs.close(); //关闭文件

	ofstream ofs;
	ofs.open(_F_LOGIN);
	ofs << user_name << endl;
	ofs << user_pwd << endl;
	ofs << host << endl;
	ofs << user << endl;
	ofs << pwd << endl;
	ofs << db << endl;
	ofs << port << endl;

	ofs.close();	//关闭文件
}

// 从数据库读取信息
BOOL CInfoFile::ReadDB()
{
	ls.clear();
	stuInfo.clear();
	subName.clear();
	/*----------读取信息字段----------*/
	mysql_query(&m_sqlCon, "show full fields from info");
	resInfo = mysql_store_result(&m_sqlCon);
	if (!resInfo)
		return FALSE;
	while (rowInfo = mysql_fetch_row(resInfo))
	{
		stuInfo.push_back(CString(rowInfo[0]));
	}
	/*----------读取学科名称----------*/
	mysql_query(&m_sqlCon, "show full fields from score");
	resSub = mysql_store_result(&m_sqlCon);
	if (!resSub)
		return FALSE;
	rowSub = mysql_fetch_row(resSub);// 跳过主键“序号”
	while (rowSub = mysql_fetch_row(resSub))
	{
		subName.push_back(CString(rowSub[0]));
	}
	/*----------读取信息内容----------*/
	mysql_query(&m_sqlCon, "select * from info;");
	resInfo = mysql_store_result(&m_sqlCon);
	if (!resInfo)
		return FALSE;
	mysql_query(&m_sqlCon, "select * from score;");
	resSub = mysql_store_result(&m_sqlCon);
	if (!resSub)
		return FALSE;
	/*----------读取数据----------*/
	while (rowInfo = mysql_fetch_row(resInfo))
	{
		msg tmp;
		// 读取学生信息
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
		// 读取学科信息
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

// 写入到数据库
BOOL CInfoFile::WriteDB()
{
	int flag=0;
	/*----------删除原记录----------*/
	flag = mysql_query(&m_sqlCon, "drop table info;");
	flag = mysql_query(&m_sqlCon, "drop table score;");
	/*----------创建学生信息字段----------*/
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
	/*----------创建学生成绩字段----------*/
	snprintf(sqlstr, 1024, "create table if not exists score (");
	snprintf(sqlstr, 1024, "%s `%s` int NOT NULL AUTO_INCREMENT", sqlstr, "序号");
	for (int i = 0; i < subName.size(); i++)
	{
		snprintf(sqlstr, 1024, "%s ,\n`%s` int NULL", sqlstr, CStringA(subName[i]));
	}
	snprintf(sqlstr, 1024, "%s ,\nPRIMARY KEY (`%s`));", sqlstr, "序号");
	flag = mysql_query(&m_sqlCon, sqlstr);
	if (flag)
	{
		AfxMessageBox(CString(mysql_error(&m_sqlCon)));
		return FALSE;
	}
	/*----------创建命令头----------*/
	// 学生信息命令头
	snprintf(sqlheadInfo, 1024, "insert into info (`%s`",CStringA(stuInfo[0]));
	for (int i = 1; i < stuInfo.size(); i++)
	{
		snprintf(sqlheadInfo, 1024, "%s ,`%s`", sqlheadInfo, CStringA(stuInfo[i]));
	}
	snprintf(sqlheadInfo, 1024, "%s) values(",sqlheadInfo);
	// 学生成绩命令头
	snprintf(sqlheadSub, 1024, "insert into score (`%s`", CStringA(subName[0]));
	for (int i = 1; i < subName.size(); i++)
	{
		snprintf(sqlheadSub, 1024, "%s ,`%s`", sqlheadSub, CStringA(subName[i]));
	}
	snprintf(sqlheadSub, 1024, "%s) values(", sqlheadSub);
	/*----------开始写入----------*/
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

