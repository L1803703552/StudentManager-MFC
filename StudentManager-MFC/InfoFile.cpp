#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
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

	ofs << name << endl; // nameд���ļ�
	ofs << pwd << endl;	// pwdд���ļ�

	ofs.close();	//�ر��ļ�
}

//��ȡ��Ʒ��Ϣ
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	num = 0;	//��ʼ����Ʒ��ĿΪ0
	ls.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��
		num++;	//��Ʒ��Ŀ��һ

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

//��Ʒд���ļ�
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//�����ʽ���ļ�

	if (ls.size() > 0)	//��Ʒ���������ݲ�ִ��
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

//�������Ʒ
//name:��Ʒ���ƣ�num����棬price���۸�
void CInfoFile::Addline(CString id, CString name, int sub1, int sub2)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//ѧ�š�������������Ч
		if (!name.IsEmpty() && num > 0 && !id.IsEmpty())
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
		num++;
	}
}
