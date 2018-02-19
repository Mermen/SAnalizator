#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

ifstream fin("base.txt");

ifstream pin("prog.txt");

ofstream rout("return.txt");

bool if_off(string a)
{
	fin.clear();
	fin.seekg(0, ios_base::beg);

	string b;
	char m;
	for (int i = 0; i < 3; i++)
	{
		fin >> b;
	}
	int flag = 0;
	while (flag != 18)
	{

		fin >> b;
		if (a == b)
		{
			return 1;
		}
		flag++;
	}
	return 0;
}

bool if_punctuation(char a)
{
	if (a == 44 || a == 46 || a == 59 || a == 39 || a == 34 || a == 58 || a == 123 || a == 125 || a == 40 || a == 41)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool if_operation(string a)
{
	fin.clear();
	fin.seekg(0, ios_base::beg);
	string c = "12";
	char b;
	while (c != "operations")
	{
		fin >> c;
	}
	b = fin.get();
	b = fin.get();
	int d = 0;

	while (d != 24)
	{

		fin >> c;
		if (a == c)
		{
			return 1;
		}
		b = fin.get();
		d++;
	}
	return 0;
}

enum States
{
	start,
	A,
	B,
	C,
	D
};


int main()
{
	string word;
	char a;
	int str = 1;
	States  state = start;
	while (pin.peek() != EOF)
	{
		switch (state)
		{
		case start:
			a = pin.get();
			word = a;
			if (isalpha(a) || a == '_')
			{
				state = A;
				if (pin.peek() == EOF)
				{
					if (if_off(word))
					{
						rout << str << " 1 " << word << "\n";
						state = start;
						break;
					}
					else
					{
						rout << str << " 2 " << word << "\n";
						state = start;
						break;
					}
				}
			}
			else if (isdigit(a))
			{
				state = B;
				if (pin.peek() == EOF)
				{
					rout << str << " 3 " << word << "\n";
					state = start;
					break;
				}
			}
			else if (a == 34 || a == 39)
			{
				rout << str << " 5 " << a << "\n";

				state = C;
			}
			else if (if_punctuation(a) && pin.peek() != '=')
			{
				rout << str << " 5 " << a << "\n";
			}
			else if (a == ' ' || a == '	' || a == '\n')
			{
				if (a == '\n')
				{
					str++;
				}
			}
			else if (a == '/'&&pin.peek() == '/')
			{
				while (pin.peek() != '\n'&&pin.peek() != EOF)
				{
					pin >> a;
				}
				a = pin.get();
			}
			else if (a == '/'&&pin.peek() == '*')
			{
				while (a != '*' || pin.peek() != '/')
				{
					a = pin.get();
				}
				a = pin.get();
			}
			else
				if (if_operation(word) || word == ":")
				{
					if (pin.peek() == EOF)
					{
						rout << str << " 4 " << word << "\n";
					}
					state = D;
				}
				else if (true)
				{
					rout << str << " 6 " << word << "\n";
				}
			break;
		case A:
			if (true)
			{
				if (isalnum(pin.peek()) || pin.peek() == '_')
				{
					pin >> a;
					word = word + a;
					if (pin.peek() == EOF)
					{
						if (if_off(word))
						{
							rout << str << " 1 " << word << "\n";
							state = start;
							break;
						}
						else
						{
							if (word == "div")
							{
								rout << str << " 4 " << word << "\n";
								state = start;
							}
							else
							{
								rout << str << " 2 " << word << "\n";
								state = start;
							}
							break;
						}
					}
				}
				else if (if_off(word))
				{
					rout << str << " 1 " << word << "\n";
					state = start;
					break;
				}
				else
				{
					if (word == "div")
					{
						rout << str << " 4 " << word << "\n";
						state = start;
					}
					else
					{
						rout << str << " 2 " << word << "\n";
						state = start;
					}
					break;
				}
			}
			break;
		case B:
			if (true)
			{
				if (isdigit(pin.peek()))
				{
					a = pin.get();
					word = word + a;
					if (pin.peek() == EOF)
					{
						rout << str << " 3 " << word << "\n";
						state = start;
						break;
					}
				}
				else if (isalpha(pin.peek()))
				{
					cout << "error";
					return 1;
				}
				else
				{
					rout << str << " 3 " << word << "\n";
					state = start;
					break;
				}
			}
			break;
		case C:
			if (true)
			{
				string word;
				while (pin.peek() != 34 && pin.peek() != 39)
				{
					a = pin.get();
					word = word + a;
				}
				rout << str << " 7 " << word << "\n";
				pin >> a;
				rout << str << " 5 " << a << "\n";
				state = start;
			}
			break;
		case D:
			if (true)
			{
				string q = word;
				a = pin.peek();
				word = word + a;
				if (if_operation(word))
				{
					a = pin.get();
					rout << str << " 4 " << word << "\n";
					state = start;
					break;
				}
				else
				{
					rout << str << " 4 " << word << "\n";
					state = start;
					break;
				}
			}
			break;
		}
	}

}