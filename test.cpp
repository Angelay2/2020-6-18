#include "template.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#pragma warning(disable:4996)

/*
ģ���ػ���Ϊ�˽��ͨ��ģ�岻�ܴ������������
1. ����ģ���ػ�
	a. �����л�������ģ��
	b. �ػ��汾���Ͳ���λ�ã�template<>)Ϊ��
	c. ������������������ػ����ͣ�������<��������>)
ע��: �ػ������͸�ʽ����ͻ���ģ��ĸ�ʽ��ȫ��ͬ�� ����ƥ�䲻���ػ��汾
���飺���ڲ��ܴ�����������ͣ�ֱ�Ӷ���һ����ͨ����
2. ��ģ���ػ�
	a. ��ѭ����ԭ��: ����Ҫ��һ��ͨ�õļ�����ģ��
	ȫ�ػ�: template<> ����<��������>

	ƫ�ػ�:
		1. �����ػ�: template<���Ͳ���> ����<���Ͳ���,��������>
		2. ��ģ���������һ��������, template<���Ͳ���>����<�������Ƶķ��Ͳ���>
	ģ���ػ���Ӧ��: ������ȡ

ģ�����:
	��֧�ַ������, ģ�尴��ʵ����, ����ڶ���ģ��ĵط�, û��ʵ����Ҫִ�еĴ���,�Ͳ������ʵ����, 
	����������:
		1. �����Ͷ���д��һ��, һ���Ǵ����".h"����".hpp", ����ʹ������
		2. �ڶ���ĵط�ʹ��һ��, 

*/

template <class T>
T Add(T& a, T& b)
{
	return a + b;
}

//ͨ�ú���ģ�岻����ȷִ�е����ͣ����Զ���һ��ģ����ػ��汾
//�ػ��汾
//template <>
//char* Add<char*>(char*& a, char*& b)
//{
//	strcat(a, b);
//	return a;
//}

//���߶���һ����ͨ������һ��ѡ����һ����ͨ��������
//��ͨ����
char* Add(char*& a, char*& b)
{
	strcat(a, b);
	return a;
}


void test()
{
	int a = 1;
	int b = 2;

	float c = 1.5;
	float d = 2.2;

	char* str1 = new char[10];
	char* str2 = new char[10];

	strcpy(str1, "123");
	strcpy(str2, "456");

	int ret = Add(a, b);
	float ret2 = Add(c, d);

	char* str3 = Add(str1, str2);
	cout << str3 << endl;
}


template <class T1, class T2>
class A
{
public:
	A()
	{
		cout << "A(T1, T2)" << endl;
	}
private:
	T1 _t1;
	T2 _t2;
};

//ȫ�ػ�
template <>
class A<int, char>
{
public:
	A()
	{
		cout << "A(int, char)" << endl;
	}
private:
	int _t1;
	char _t2;
};


//ƫ�ػ���
//1. �����ػ��� ֻ�ػ����ֲ���
template <class T1>
class A<T1, double>
{
public:
	A()
	{
		cout << "A(T1, double)" << endl;
	}
private:
	T1 _t1;
	double _t2;
};

//ƫ�ػ�
//2. ��ģ���������һ��������
template <class T1, class T2>
class A<T1*, T2*>
{
public:
	A()
	{
		cout << "A(T1*, T2*)" << endl;
	}
private:
	T1* _t1;
	T2* _t2;
};

void test2()
{
	A<float, int> a;
	A<int, char> b;
	A<int, double> c;
	A<double, int> d;
	A<int*, int*> e;
	A<float*, char*> f;
}

void test3()
{
	int a = 1, b = 2;
	char c = 'a', d = 'c';
	bool ret = isEqual(a, b);  // isEqual<int, int> ? 
	ret = isEqual(c, d);   // isEqual<char, char> ?
}

void test4()
{
	int a = 10;
	//C++�� cout, cin ����Ҫָ�����ݸ�ʽ�����ڲ�ͬ���͵����ݣ����õ�Ϊ��ͬ�����غ���
	cout << a << endl;
	cout.operator<<(a) << endl;
	char c = 'a';
	cout << c << endl;
	cout.operator<<(c) << endl;   //ostream ��Ա���� operator<<(int): ������char��������ķ���
	operator<<(cout, c) << endl;  //ȫ�ֺ���operator<<(ostream, char)
	//cout, cerr, clogʹ�÷�ʽ���ִ��������£� ������ͬ
	cerr << a << endl;
	clog << a << endl;

	cin >> a;
	cin.operator>>(a);
	cin >> c;
	operator>>(cin, c);  ////ȫ�ֺ���operator>>(istream, char)
	//cin.operator>>(c);  

	//C������Ҫָ�����ݸ�ʽ�� ���ڲ�ͬ���͵����ݣ����õ�Ϊͬһ������
	printf("%d\n", a);
	scanf("%d", &a);
}

void test5()
{
	ifstream fin("test.txt");
	char str[100] = { 0 };
	fin.getline(str, 100);
	cout << str << endl;
	fin.close();
}

struct Person
{
	int _age;
	char name[30];
};

void test6()
{
	//�����ƣ� Ч�ʸߣ� �ɶ��Բ�
	//�����ƣ��ֽ����ļ�IO
	// read, write

	Person p;
	p._age = 18;
	strcpy(p.name, "����");
	//�����ƴ��ļ�
	ofstream fout("person.txt", ofstream::binary);
	fout.write((char*)&p, sizeof(p));
	fout.close();

	Person pin;
	cout << "�����ƶ�֮ǰ" << endl;
	cout << pin._age << pin.name << endl;
	ifstream fin("person.txt", ifstream::binary);
	fin.read((char*)&pin, sizeof(pin));
	cout << "�����ƶ�֮��" << endl;
	cout << pin._age << pin.name << endl;

}

void test7()
{
	//�ı���Ч�ʵͣ� �ɶ��Ժ�
	//�ı���д�� �ַ����ļ�IO
	Person p;
	p._age = 18;
	strcpy(p.name, "����");
	//�ı���ʽ���ļ�
	ofstream fout("person2.txt");
	fout << p._age << endl;
	fout << p.name << endl;
	fout.close();

	Person pin;
	cout << "�ı�֮ǰ" << endl;
	cout << pin._age << pin.name << endl;
	ifstream fin("person2.txt");
	fin >> pin._age >> pin.name;
	cout << "�ı�֮��" << endl;
	cout << pin._age << pin.name << endl;

}

void test8()
{
	stringstream ss;
	int a = 10;
	char str[10];
	itoa(a, str, 10);
	char str2[10];
	sprintf(str2, "%d", a);

	//����aת�ɶ�Ӧ���ַ�����ʽ
	ss << a;
	string ret = ss.str();
	ss.str("");
	ss.operator<<(a);

	ss >> ret;
	ss.clear();  //���IO״̬λ
	float f = 0.1832;
	ss << f;
	ss >> ret;
}

void test9()
{
	int a = 1;
	float f = 0.12;
	stringstream ss;
	ss << a;
	//clear: ���״̬λ
	ss.clear();
	//str(�ַ���): ��stringstream�����е�������Ϊָ�����ַ��� 
	ss.str("");
	ss << f;
	//str(): ��ȡstringstream�����е�����
	cout << ss.str() << endl; // 0.12

	ss.clear();
	ss.str("");
	//ss << "123" << "456" << "789";// 123456789
	//ss.str("");
	ss << "101112";
	cout << ss.str() << endl;// 101112
}

int main()
{
	//test();
	//test2();
	test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();

	system("pause");
	return 0;
}