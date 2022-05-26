#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
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

	ofs << name << endl; // name写入文件
	ofs << pwd << endl;	// pwd写入文件

	ofs.close();	//关闭文件
}

//读取学生信息
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //输入方式打开文件

	char buf[1024] = { 0 };
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		// AfxMessageBox(CString(buf));
		char *sst = strtok(buf, ","); //以“,”切割
		if (sst != NULL)
		{
			tmp.id = sst; //学号
		}
		else
		{
			break;
		}

		sst = strtok(NULL, ",");
		tmp.name = sst;	//姓名

		sst = strtok(NULL, ",");
		tmp.sub1 = atoi(sst);	//学科1

		sst = strtok(NULL, ",");
		tmp.sub2 = atoi(sst);	//学科2

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//输出方式打开文件

	if (ls.size() > 0)	//学生链表有内容才执行
	{
		ofs << "学号,姓名,学科1,学科2" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“,”分隔，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << ",";		
			ofs << it->name << ",";
			ofs << it->sub1 << ",";
			ofs << it->sub2 << endl;
		}
	}

	ofs.close();//关闭文件
}

// 添加学生
// id:学号，name:姓名，sub1:成绩1，sub2:成绩2
void CInfoFile::Addline(CString id, CString name, int sub1, int sub2)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//学号、姓名、数量有效
		if (!name.IsEmpty() && !id.IsEmpty())
		{
			CStringA str;
			str = id;
			tmp.id = str.GetBuffer();
			str = name;	//CString转CStirngA
			tmp.name = str.GetBuffer(); //CStirngA转char *，姓名
			tmp.sub1 = sub1;	//学科1
			tmp.sub2 = sub2;	//学科2

			ls.push_back(tmp);	//放在链表的后面
		}
	}
}

BOOL CInfoFile::ConnectDB(CString strIP, CString strSqlUser, CString strSqlPassworld, CString strDataBase, int sqlPoint)
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, CT2A(strIP), CT2A(strSqlUser), CT2A(strSqlPassworld),CT2A(strDataBase), sqlPoint, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		return FALSE;
	}
	else
	{
		AfxMessageBox(_T("访问数据库成功!"));
		return TRUE;
	}
}

BOOL CInfoFile::DisconnectDB()
{
	mysql_close(&m_sqlCon);//关闭Mysql连接  
	return TRUE;
}
