#include "template.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#pragma warning(disable:4996)

/*
模板特化：为了解决通用模板不能处理的特殊类型
1. 函数模板特化
	a. 必须有基础函数模板
	b. 特化版本泛型参数位置（template<>)为空
	c. 函数名后面加入具体的特化类型（函数名<具体类型>)
注意: 特化的类型格式必须和基础模板的格式完全相同， 否则匹配不到特化版本
建议：对于不能处理的特殊类型，直接定义一个普通函数
2. 类模板特化
	a. 遵循基本原则: 必须要有一个通用的挤出来模板
	全特化: template<> 类型<具体类型>

	偏特化:
		1. 部分特化: template<泛型参数> 类名<泛型参数,具体类型>
		2. 对模板参数做进一步的限制, template<泛型参数>类型<进行限制的泛型参数>
	模板特化的应用: 类型萃取

模板编译:
	不支持分离编译, 模板按需实例化, 如果在定义模板的地方, 没有实际需要执行的代码,就不会进行实例化, 
	解决分离编译:
		1. 声明和定义写在一起, 一般是存放在".h"或者".hpp", 建议使用这种
		2. 在定义的地方使用一次, 

*/

template <class T>
T Add(T& a, T& b)
{
	return a + b;
}

//通用函数模板不能正确执行的类型，可以定义一个模板的特化版本
//特化版本
//template <>
//char* Add<char*>(char*& a, char*& b)
//{
//	strcat(a, b);
//	return a;
//}

//或者定义一个普通函数，一般选择定义一个普通函数即可
//普通函数
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

//全特化
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


//偏特化：
//1. 部分特化： 只特化部分参数
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

//偏特化
//2. 对模板参数做进一步的限制
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
	//C++： cout, cin 不需要指定数据格式：对于不同类型的数据，调用的为不同的重载函数
	cout << a << endl;
	cout.operator<<(a) << endl;
	char c = 'a';
	cout << c << endl;
	cout.operator<<(c) << endl;   //ostream 成员函数 operator<<(int): 不存在char数据溢出的风险
	operator<<(cout, c) << endl;  //全局函数operator<<(ostream, char)
	//cout, cerr, clog使用方式，现代编译器下， 功能相同
	cerr << a << endl;
	clog << a << endl;

	cin >> a;
	cin.operator>>(a);
	cin >> c;
	operator>>(cin, c);  ////全局函数operator>>(istream, char)
	//cin.operator>>(c);  

	//C语言需要指定数据格式： 对于不同类型的数据，调用的为同一个函数
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
	//二进制： 效率高， 可读性差
	//二进制：字节流文件IO
	// read, write

	Person p;
	p._age = 18;
	strcpy(p.name, "张三");
	//二进制打开文件
	ofstream fout("person.txt", ofstream::binary);
	fout.write((char*)&p, sizeof(p));
	fout.close();

	Person pin;
	cout << "二进制读之前" << endl;
	cout << pin._age << pin.name << endl;
	ifstream fin("person.txt", ifstream::binary);
	fin.read((char*)&pin, sizeof(pin));
	cout << "二进制读之后" << endl;
	cout << pin._age << pin.name << endl;

}

void test7()
{
	//文本：效率低， 可读性好
	//文本读写： 字符流文件IO
	Person p;
	p._age = 18;
	strcpy(p.name, "张三");
	//文本形式打开文件
	ofstream fout("person2.txt");
	fout << p._age << endl;
	fout << p.name << endl;
	fout.close();

	Person pin;
	cout << "文本之前" << endl;
	cout << pin._age << pin.name << endl;
	ifstream fin("person2.txt");
	fin >> pin._age >> pin.name;
	cout << "文本之后" << endl;
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

	//整数a转成对应的字符串形式
	ss << a;
	string ret = ss.str();
	ss.str("");
	ss.operator<<(a);

	ss >> ret;
	ss.clear();  //清空IO状态位
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
	//clear: 清空状态位
	ss.clear();
	//str(字符串): 把stringstream对象中的内容置为指定的字符串 
	ss.str("");
	ss << f;
	//str(): 获取stringstream对象中的内容
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