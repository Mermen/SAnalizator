#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

ifstream fin("C:\\Users\\User\\Documents\\Visual Studio 2017\\Projects\\Лексическиий анализатор\\Лексическиий анализатор\\return.txt");


struct Lexeme
{
	int type = 0, str = 0;
	char lex[10000];
} lexeme, lexeme1;
int str = 0;
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
	if (!fin.eof())
	{
		str = lexeme.str;
		fin >> lexeme.str;
		fin >> lexeme.type;
		fin.get();
		fin.getline(lexeme.lex, 10000);		
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
	cout << "There is a FATAL ERROR in string "<< str <<"!!! The unexpected lexeme \""<< lexeme.lex <<"\" was entered." << endl;
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
	} while (!strcmp(lexeme.lex, "}"));
	fgl(lexeme);
}
void oper()
{
	if (!strcmp(lexeme.lex, "cinout")) // Оператор ввода-вывода
	{
		fgl(lexeme);
		cinout();
	}
	else if (!strcmp(lexeme.lex, "double") || !strcmp(lexeme.lex, "bool") || !strcmp(lexeme.lex, "int")) //Описание
	{
		description();
	}
	else if (!strcmp(lexeme.lex, "for"))//Спец. оператор cfor/pfor
	{
		fgl(lexeme);
		operfor();
	}
	else if (!strcmp(lexeme.lex, "do"))//Спец. оператор dowhile
	{
		fgl(lexeme);
		dowhile();
	}
	else if (!strcmp(lexeme.lex, "{"))//Составной оператор
	{
		compositeoper();
	}
	else if (lexeme.type == 2 ||
		lexeme.type == 3 || !strcmp(lexeme.lex, "+") || !strcmp(lexeme.lex, "-") ||
		!strcmp(lexeme.lex, "!") || !strcmp(lexeme.lex, "(") ||
		!strcmp(lexeme.lex, "true") || !strcmp(lexeme.lex, "false"))//Оператор выражения
	{
		expression();
		if (!strcmp(lexeme.lex, ";")) error();
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
		else if (!strcmp(lexeme.lex, "\""))
		{
			fgl(lexeme);
			if (lexeme.type != 7) error();
			fgl(lexeme);
			if (strcmp(lexeme.lex, "\"")) error();
			fgl(lexeme);
		}
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
	fgl(lexeme);
	program();
}
