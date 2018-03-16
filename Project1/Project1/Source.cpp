
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>


using namespace std;

ifstream fin("base.txt");

ifstream pin("prog.txt");

ofstream rout("return.txt");

ifstream git;

struct TID
{
	char lex[10000];
	TID *next = NULL;

};

struct L_TID
{
	TID *a=NULL;
	L_TID *next=NULL;
};
L_TID *L_L=NULL;
struct Lexeme
{
	int type = 0, str = 0;
	char lex[10000];
} lexeme, lexeme1;

void add_id()
{
	if (L_L == NULL)
	{
		L_TID *R = new L_TID;
		R->a = new TID;
	}
	else
	{

	}
	R->a->lex = lexeme.lex;
}

bool if_off(string a)
{
	fin.clear();
	fin.seekg(0, ios_base::beg);

	string b;
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


char enter;

void fgl(Lexeme &lexeme);
void error();
void program();
void description();
void compositeoper();
void oper();
void expression();
void expression1();
void simpleexpression();
void term();
void atom1();
void atom();
void specialatom();
void constant();
void dowhile();
void cinout();
void element();
void operfor();
void cfor1();
void cfor2();
void pfor();

void fgl(Lexeme &lexeme)
{
	if (!git.eof())
	{
		git >> lexeme.str;
		git >> lexeme.type;
		if (lexeme.type != 7)
		{
			git.get();
			git.getline(lexeme.lex, 10000);
		}
		else
		{
			git.get();
			git.get();
			git.getline(lexeme.lex, 10000, '\"');
			git.get();
		}
	}
	else
	{
		cout << "Error! File is empty." << endl;
		system("pause");
		exit(1);
	}
}
void error()
{
	cout << "There is a FATAL ERROR in string " << lexeme.str << "!!! The unexpected lexeme \"" << lexeme.lex << "\" was entered." << endl;
	system("pause");
	exit(1);
}
void program()
{
	while (strcmp(lexeme.lex, "("))
		description();
	fgl(lexeme);
	if (strcmp(lexeme.lex, ")")) error();
	fgl(lexeme);
				compositeoper();
	cout << "There are no errors. The code is correct." << endl;
	system("pause");
}
void description()
{
	if (!strcmp(lexeme.lex, "double") || !strcmp(lexeme.lex, "bool") || !strcmp(lexeme.lex, "int"))
	{

		fgl(lexeme);

		if (!strcmp(lexeme.lex, "main"))
		{
			fgl(lexeme);
			if (!strcmp(lexeme.lex, "("))
				return;
			else goto mark47;
		}
		if (lexeme.type != 2) error();
		fgl(lexeme);
		mark47:
		if (!strcmp(lexeme.lex, "="))
		{
			fgl(lexeme);
			expression();
		}
		while (!strcmp(lexeme.lex, ","))
		{
			fgl(lexeme);
			if (lexeme.type != 2) error();
			fgl(lexeme);
			if (!strcmp(lexeme.lex, "="))
			{
				fgl(lexeme);
				expression();
			}
		}
		if (strcmp(lexeme.lex, ";")) error();
		fgl(lexeme);
		return;
	}
	else error();
}
void compositeoper()
{
	if (strcmp(lexeme.lex, "{")) error();
	fgl(lexeme);
	do
	{
		oper();
	} while (strcmp(lexeme.lex, "}"));
	fgl(lexeme);
}
void oper()
{
	if (!strcmp(lexeme.lex, "cinout")) // Îïåðàòîð ââîäà-âûâîäà
	{
		fgl(lexeme);
		cinout();
	}
	else if (!strcmp(lexeme.lex, "double") || !strcmp(lexeme.lex, "bool") || !strcmp(lexeme.lex, "int")) //Îïèñàíèå
	{
		description();
	}
	else if (!strcmp(lexeme.lex, "for"))//Ñïåö. îïåðàòîð cfor/pfor
	{
		fgl(lexeme);
		operfor();
	}
	else if (!strcmp(lexeme.lex, "do"))//Ñïåö. îïåðàòîð dowhile
	{
		fgl(lexeme);
		dowhile();
	}
	else if (!strcmp(lexeme.lex, "{"))//Ñîñòàâíîé îïåðàòîð
	{
		compositeoper();
	}
	else if (lexeme.type == 2 ||
		lexeme.type == 3 || !strcmp(lexeme.lex, "+") || !strcmp(lexeme.lex, "-") ||
		!strcmp(lexeme.lex, "!") || !strcmp(lexeme.lex, "(") ||
		!strcmp(lexeme.lex, "true") || !strcmp(lexeme.lex, "false"))//Îïåðàòîð âûðàæåíèÿ
	{
		expression();
		if (strcmp(lexeme.lex, ";")) error();
		fgl(lexeme);
	}
	else error();
}
void expression()
{
	if (lexeme.type != 2)
		expression1();
	else
	{
		if (lexeme1.type == 0)
			fgl(lexeme1);
		if (!strcmp(lexeme1.lex, "="))
		{
			lexeme1.type = 0;
			fgl(lexeme);
			expression();
		}
		else expression1();
	}
}
void expression1()
{
	simpleexpression();
	while (!strcmp(lexeme.lex, ">") || !strcmp(lexeme.lex, "<") || !strcmp(lexeme.lex, "!=") || !strcmp(lexeme.lex, ">=") || !strcmp(lexeme.lex, "<+") || !strcmp(lexeme.lex, "=="))
	{
		fgl(lexeme);
		simpleexpression();
	}
}
void simpleexpression()
{
	term();
	while (!strcmp(lexeme.lex, "+") || !strcmp(lexeme.lex, "-") || !strcmp(lexeme.lex, "||"))
	{
		fgl(lexeme);
		term();
	}
}
void term()
{
	atom1();
	while (!strcmp(lexeme.lex, "*") || !strcmp(lexeme.lex, "/") || !strcmp(lexeme.lex, "&&") || !strcmp(lexeme.lex, "div") || !strcmp(lexeme.lex, "%"))
	{
		fgl(lexeme);
		atom1();
	}
}
void atom1()
{
	atom();
	if (!strcmp(lexeme.lex, "^"))
	{
		fgl(lexeme);
		atom();
	}
	if (!strcmp(lexeme.lex, "++") || !strcmp(lexeme.lex, "--"))
		fgl(lexeme);
}
void atom()
{
	if (!strcmp(lexeme.lex, "("))
	{
		fgl(lexeme);
		expression();
		if (lexeme.lex != ")") error();
		fgl(lexeme);
	}
	else if (lexeme.type == 2)
	{
		if (lexeme1.type != 0)
		{
			lexeme = lexeme1;
			lexeme1.type = 0;
		}
		else fgl(lexeme);
	}
	else specialatom();
}
void specialatom()
{
	if (!strcmp(lexeme.lex, "!"))
	{
		fgl(lexeme);
		atom();
		return;
	}
	else if (!strcmp(lexeme.lex, "true") || !strcmp(lexeme.lex, "false"))
	{
		fgl(lexeme);
		return;
	}
	else constant();
}
void constant()
{
	if (!strcmp(lexeme.lex, "+") || !strcmp(lexeme.lex, "-"))
	{
		fgl(lexeme);
		if (lexeme.type != 3) error();
		fgl(lexeme);
		return;
	}
	else if (lexeme.type == 3)
	{
		fgl(lexeme);
		if (!strcmp(lexeme.lex, "."))
		{
			fgl(lexeme);
			if (lexeme.type != 3) error();
			fgl(lexeme);
			return;
		}
	}
	else error();
}
void dowhile()
{
	oper();
	if (strcmp(lexeme.lex, "while")) error();
	fgl(lexeme);
	if (strcmp(lexeme.lex, "(")) error();
	fgl(lexeme);
	expression();
	if (strcmp(lexeme.lex, ")")) error();
	fgl(lexeme);
	if (strcmp(lexeme.lex, ";")) error();
	fgl(lexeme);
}
void cinout()
{
	do {
		element();
	} while (!strcmp(lexeme.lex, "<<") || !strcmp(lexeme.lex, ">>"));
	if (strcmp(lexeme.lex, ";")) error();
	fgl(lexeme);
}
void element()
{
	if (!strcmp(lexeme.lex, ">>"))
	{
		fgl(lexeme);
		if (lexeme.type != 2) error();
		fgl(lexeme);
	}
	else if (!strcmp(lexeme.lex, "<<"))
	{
		fgl(lexeme);
		if (!strcmp(lexeme.lex, "endl"))
			fgl(lexeme);
		else if (lexeme.type == 7)
			fgl(lexeme);
		else expression();
	}
	else error();
}
void operfor()
{
	if (strcmp(lexeme.lex, "(")) error();
	fgl(lexeme);
	if (!strcmp(lexeme.lex, "int") || !strcmp(lexeme.lex, "double") || !strcmp(lexeme.lex, "bool"))
		cfor1();
	else if (lexeme.type == 2)
	{
		fgl(lexeme1);
		if (!strcmp(lexeme1.lex, ":="))
		{
			lexeme1.type = 0;
			fgl(lexeme);
			pfor();
		}
		else cfor2();
	}
	else cfor2();
	if (strcmp(lexeme.lex, ")")) error();
	fgl(lexeme);
	oper();
	if (!strcmp(lexeme.lex, "else"))
	{
		fgl(lexeme);
		oper();
	}
}
void cfor1()
{
	description();
	expression();
	if (strcmp(lexeme.lex, ";")) error();
	fgl(lexeme);
	expression();
}
void cfor2()
{
	expression();
	if (strcmp(lexeme.lex, ";")) error();
	fgl(lexeme);
	expression();
	if (strcmp(lexeme.lex, ";")) error();
	fgl(lexeme);
	expression();
}
void pfor()
{
	expression();
	if (strcmp(lexeme.lex, "to") && strcmp(lexeme.lex, "downto")) error();
	fgl(lexeme);
	expression();
}

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
				rout << str << " 7 " << a;

				state = C;
			}
			else if (if_punctuation(a) && pin.peek() != '=')
			{
				rout << str << " 5 " << a << '\n';
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
					if (a == '\n')
					{
						str++;
					}
				}
				rout << word;
				pin >> a;
				rout << a << "\n";
				state = start;
			}
			break;
		case D:
			if (true)
			{
				string q = word;
				a = pin.peek();
				if (!isspace(a)) word = word + a;
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
	rout.close();
	git.open("return.txt");
	fgl(lexeme);
	program();
}
