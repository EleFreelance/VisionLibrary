#include<iostream>
#include"CString.h"
#include<string>

using namespace std;

int main(int agrc,char* agrv)
{
	/*string str_1="123";
	string str_2="456";
	string str_3="abc";

	str_3=str_1+str_2;*/

	CString str="128";
	CString str1="abc";
	CString str2="250";
	str2+="123";

	str=str2+str1;
	//str2=str+"abc";
	for (int i = 0; i < str2.Getlength(); i++)
	{
		cout<<str2[i]<<endl;
	}
	getchar();
	return 0;
}