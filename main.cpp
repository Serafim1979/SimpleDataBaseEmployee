// File input/output of employee objects
// Support for objects of different sizes
#include<fstream>
#include<iostream>
#include<typeinfo>
using namespace std;
#include<process.h>

const int LEN = 32; //The maximum length of names
const int MAXEM = 100; //Maximum number of employees

enum employee_type{tmanager, tscienist, tlaborer};
//////////////////////////////////////////////////////
class Employee
{
private:
	char name[LEN];
	unsigned long number;
	static int n;
	static Employee* arrap[];
public:
	virtual void getdata()
	{
		cin.ignore(10, '\n');
		cout << " Enter last name: ";
		cin >> name;
		cout << " Enter the number: ";
		cin >> number;
	}
	virtual void putdata()
	{
		cout << "\n Name: " << name;
		cout << "\n Number: " << number;
	}
	virtual employee_type get_type();
	static void add();
	static void display();
	static void read();
	static void write();
};
//------------------------------------------------------
int Employee::n;
Employee* Employee::arrap[MAXEM];
////////////////////////////////////////////////////////
class Manager : public Employee
{
private:
	char title[LEN];
	double dues;
public:
	void getdata()
	{
		Employee::getdata();
		cout << " Enter the title: ";
		cin >> title;
		cout << " Enter taxes: ";
		cin >> dues;
	}
	void putdata()
	{
		Employee::putdata();
		cout << "\n Title: " << title;
		cout << "\n Golf club taxes: " << dues;
	}
};
/////////////////////////////////////////////////////////
class Scienist : public Employee
{
private:
	int pubs;
public:
	void getdata()
	{
		Employee::getdata();
		cout << " Enter the number of publications: ";
		cin >> pubs;
	}
	void putdata()
	{
		Employee::putdata();
		cout << "\n Number of publications: " << pubs;
	}
};
////////////////////////////////////////////////////////////
class laborer : public Employee
{
};
////////////////////////////////////////////////////////////
void Employee::add()
{
	char ch;
	cout << "'m' to add a Manager"
		"\n's' to add a Scientist"
		"\n'l' to add a worker"
		"\nYour choice: ";
	cin >> ch;
	switch (ch)
	{
	case 'm': arrap[n] = new Manager;
		break;
	case 's': arrap[n] = new Scienist;
		break;
	case 'l': arrap[n] = new laborer;
		break;
	default:
		cout << "\nUnknown employee type\n";
		return;
	}
	arrap[n++]->getdata();
}
//--------------------------------------------------
void Employee::display()
{
	for (int j = 0; j < n; j++)
	{
		cout << (j + 1);
		switch (arrap[j]->get_type())
		{
		case tmanager: cout << ". Type: Manager";
			break;
		case tscienist: cout << ". Type: Scienist";
			break;
		case tlaborer: cout << ". Type: Laborer";
			break;
		default:
			cout << ". Unknown type";
		}
		arrap[j]->putdata();
		cout << endl;
	}
}
//-----------------------------------------------------
employee_type Employee::get_type()
{
	if (typeid(*this) == typeid(Manager))
		return tmanager;
	else if (typeid(*this) == typeid(Scienist))
		return tscienist;
	else if (typeid(*this) == typeid(laborer))
		return tlaborer;
	else
	{
		cerr << "\nWrong employee type";
		exit(1);
	}
	return tmanager;
}
//--------------------------------------------------------
void Employee::write()
{
	int size;
	cout << "Recording in progress " << n << " workers.\n";
	ofstream ouf;
	employee_type etype;

	ouf.open("EMPLOY.DAT", ios::trunc | ios::binary);
	if (!ouf)
	{
		cout << "\nUnable to open file\n";
		return;
	}
	for (int j = 0; j < n; j++)
	{
		etype = arrap[j]->get_type();
		ouf.write((char*)&etype, sizeof(etype));

		switch (etype)
		{
		case tmanager: size = sizeof(Manager);
			break;
		case tscienist: size = sizeof(Scienist);
			break;
		case tlaborer: size = sizeof(laborer);
			break;
		}
		ouf.write((char*)(arrap[j]), size);
		if (!ouf)
		{
			cout << "\nCannot write to file\n";
			return;
		}
	}
}
//--------------------------------------------------------
void Employee::read()
{
	int size;
	employee_type etype;
	ifstream inf;
	inf.open("EMPLOY.DAT", ios::binary);
	if (!inf)
	{
		cout << "\nUnable to open file\n";
		return;
	}
	n = 0;
	while (true)
	{
		inf.read((char*)&etype, sizeof(etype));
		if (inf.eof())
			break;
		if (!inf)
		{
			cout << "\nCould not read the type\n";
			return;
		}
		switch (etype)
		{
		case tmanager:
			arrap[n] = new Manager;
			size = sizeof(Manager);
			break;
		case tscienist:
			arrap[n] = new Scienist;
			size = sizeof(Scienist);
			break;
		case tlaborer:
			arrap[n] = new laborer;
			size = sizeof(laborer);
			break;
		default:
			cout << "\nUnknown file type\n";
			return;
		}
		inf.read((char*)arrap[n], size);
		if (!inf)
		{
			cout << "\nCannot read data from file\n";
			return;
		}
		n++;
	}
	cout << "Reading in progress " << n << " workers\n";
}
///////////////////////////////////////////////////////////////
int main()
{
	char ch;

	while (true)
	{
		cout << "'a' - add information about the employee"
			"\n'd' - display information about all employees"
			"\n'w' - write all data to file"
			"\n'r' - read all data from file"
			"\n'x' - exit"
			"\nYour choise: ";
		cin >> ch;

		switch (ch)
		{
		case 'a':
			Employee::add();
			break;
		case 'd':
			Employee::display();
			break;
		case 'w':
			Employee::write();
			break;
		case 'r':
			Employee::read();
			break;
		case 'x':
			exit(0);
		default:
			cout << "\nUnknown command";
		}
	}
	system("pause");
	return 0;
}