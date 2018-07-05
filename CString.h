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

	//在头文件中，单行代码，程序自动归为Inline内联函数
	int Getlength(){return m_length;}
	operator const char*(){return m_phead;}
	char operator[](int index) const{return *(m_phead+index);}

	//1.针对string类的函数重载，变量分为CString&以及char*两类
	//=运算符体现了赋值与初始化的区别
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
//const修饰指针分为指针常量与常量指针，指针常量，const修饰常量，变量值无法被改变；
//而常量指针，则const修饰指针，仅仅无法通过指针去修改变量值。
CString::CString(const char* ch)
{
	m_length=strlen(ch);
	m_phead=new char[m_length+1];
	//常量指针无法赋值非常量指针，但可以取值逐个赋值
	//strcpy(m_phead,ch);
	char *rect=m_phead;
	//字符串的赋值运算符必须将‘/0’位赋值给另一个字符串
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
	//2.字符串的实际存储控件应该为m_length+1，结束符‘\0’
	char* pNew=new char[m_length+1];
	//strcpy(pNew,m_phead);
	//strcat(pNew,ch);
	//3.对指针存取临时变量，是为了访问指针数据同时，不改变原指针
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
	//4.在指针变量重置时，需要考虑该指针之前是否存有数据，需要清空后再赋值
	m_length+=str.m_length;
	char* pNew=new char[m_length+1];
	strcpy(pNew,m_phead);
	strcat(pNew,str.m_phead);
	delete[] m_phead;
	m_phead=pNew;
	return *this;
}

//深复制
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
	//5.临时变量作为返回值时，会发生两个步骤：1.在本类中，发生拷贝构造；2.变量销毁。
	//因此若类中含有指针变量，则拷贝构造必须为深拷贝
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