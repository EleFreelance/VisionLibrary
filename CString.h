#ifndef _CSTRING_H_
#define _CSTRING_H_


class CString
{
public:
	CString();
	~CString();
	CString(const char* ch);
	CString(int n,const char ch);
	CString(const CString& str);

	//��ͷ�ļ��У����д��룬�����Զ���ΪInline��������
	int Getlength(){return m_length;}
	operator const char*(){return m_phead;}
	char operator[](int index) const{return *(m_phead+index);}

	//1.���string��ĺ������أ�������ΪCString&�Լ�char*����
	//=����������˸�ֵ���ʼ��������
	CString& operator=(const CString& str);
	CString& operator=(const char* ch);

	CString& operator+=(const CString& str);
	CString& operator+=(const char* ch);

	//friend CString operator+(const CString&str1,const CString& str2);

	CString& operator+(const CString& str) const;
	CString operator+(const char* ch) const;

private:
	char * m_phead;
	int m_length;
};

CString::CString()
{
	m_phead=new char(0);
	m_length=0;
}

CString::~CString()
{
	if (m_phead!=nullptr)
	{
		delete[] m_phead;
	}
}
//const����ָ���Ϊָ�볣���볣��ָ�룬ָ�볣����const���γ���������ֵ�޷����ı䣻
//������ָ�룬��const����ָ�룬�����޷�ͨ��ָ��ȥ�޸ı���ֵ��
CString::CString(const char* ch)
{
	m_length=strlen(ch);
	m_phead=new char[m_length+1];
	//����ָ���޷���ֵ�ǳ���ָ�룬������ȡֵ�����ֵ
	//strcpy(m_phead,ch);
	char *rect=m_phead;
	//�ַ����ĸ�ֵ��������뽫��/0��λ��ֵ����һ���ַ���
	while (*rect=*ch)
	{rect++;ch++;};
}

CString::CString(const CString& str)
{
	m_length=str.m_length;
	m_phead=new char[m_length+1];
	//m_phead=str.m_phead;
	strcpy(m_phead,str.m_phead);
}


CString& CString::operator+=(const char * ch)
{
	m_length+=strlen(ch);
	//2.�ַ�����ʵ�ʴ洢�ؼ�Ӧ��Ϊm_length+1����������\0��
	char* pNew=new char[m_length+1];
	//strcpy(pNew,m_phead);
	//strcat(pNew,ch);
	//3.��ָ���ȡ��ʱ��������Ϊ�˷���ָ������ͬʱ�����ı�ԭָ��
	char* new_temp=pNew;
	char* old_temp=m_phead;
	while (*new_temp=*old_temp)
	{new_temp++;old_temp++;}
	while (*new_temp=*ch)
	{new_temp++;ch++;}
	delete[] m_phead;
	m_phead=pNew;
	return *this;
}

CString& CString::operator+=(const CString& str)
{
	//4.��ָ���������ʱ����Ҫ���Ǹ�ָ��֮ǰ�Ƿ�������ݣ���Ҫ��պ��ٸ�ֵ
	m_length+=str.m_length;
	char* pNew=new char[m_length+1];
	strcpy(pNew,m_phead);
	strcat(pNew,str.m_phead);
	delete[] m_phead;
	m_phead=pNew;
	return *this;
}

//���
CString& CString::operator=(const char* ch)
{
	m_length=strlen(ch);
	char* pNew=new char[m_length+1];
	strcpy(pNew,ch);
	delete[] m_phead;
	m_phead=pNew;
	return *this;
}

CString& CString::operator=(const CString& str)
{
	m_length=str.m_length;	
	char* pNew=new char[m_length+1];
	//pNew=str.m_phead;
	strcpy(pNew,str.m_phead);
	delete[] m_phead;
	m_phead=pNew;
	return *this;
}


CString& CString::operator+(const CString& str) const
{
	//5.��ʱ������Ϊ����ֵʱ���ᷢ���������裺1.�ڱ����У������������죻2.�������١�
	//��������к���ָ��������򿽱��������Ϊ���
	static CString t1;
	t1.m_length=m_length+str.m_length;
	char *pNew=new char[t1.m_length+1];
	strcpy(pNew,m_phead);
	strcat(pNew,str.m_phead);
	delete[] t1.m_phead;
	t1.m_phead=pNew;
	return t1;
}


CString CString::operator+(const char* ch) const
{
	CString t;
	t.m_length=this->m_length+strlen(ch);
	char* pNew=new char[t.m_length+1];
	strcpy(pNew,this->m_phead);
	strcat(pNew,ch);
	delete[] t.m_phead;
	t.m_phead=pNew;
	return t;
}
#endif