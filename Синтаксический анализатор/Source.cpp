#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

ifstream fin("return.txt");

struct Lexeme
{
	int type = 0, str;
	string lex;
} lexeme, lexeme1;

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
		fin >> lexeme.lex;
		fin >> lexeme.type;
		fin >> lexeme.str;
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
	cout << "There is a FATAL ERROR in string "<< lexeme.str <<"!!! Run away! There are 3 seconds before the exlosive. 2... 1..." << endl;
	system("pause");
	exit(1);
}
void program()
{
	while (lexeme.lex != "(")
		description();
	fgl(lexeme);
	if (lexeme.lex != ")") error();
	fgl(lexeme);
	compositeoper();
	cout << "There are no errors. The code is correct." << endl;
	system("pause");
}
void description()
{
	if (lexeme.lex == "double" || lexeme.lex == "bool" || lexeme.lex == "int")
	{
		fgl(lexeme);
		if (lexeme.lex == "main")
		{
			fgl(lexeme);
			if (lexeme.lex == "(")
				return;
			else goto mark47;
		}
		if (lexeme.type != 2) error();
		fgl(lexeme);
		mark47:
		if (lexeme.lex == "=")
		{
			fgl(lexeme);
			expression();
		}
		while (lexeme.lex == ",")
		{
			fgl(lexeme);
			if (lexeme.type != 2) error();
			fgl(lexeme);
			if (lexeme.lex == "=")
			{
				fgl(lexeme);
				expression();
			}
		}
		if (lexeme.lex != ";") error();
		fgl(lexeme);
		return;
	}
	else error();
}
void compositeoper()
{
	if (lexeme.lex != "{") error();
	fgl(lexeme);
	do
	{
		oper();
	} while (lexeme.lex != "}");
	fgl(lexeme);
}
void oper()
{
	if (lexeme.lex == "cinout") // Оператор ввода-вывода
	{
		fgl(lexeme);
		cinout();
	}
	else if (lexeme.lex == "double" || lexeme.lex == "bool" || lexeme.lex == "int") //Описание
	{
		description();
	}
	else if (lexeme.lex == "for")//Спец. оператор cfor/pfor
	{
		fgl(lexeme);
		operfor();
	}
	else if (lexeme.lex == "do")//Спец. оператор dowhile
	{
		fgl(lexeme);
		dowhile();
	}
	else if (lexeme.lex == "{")//Составной оператор
	{
		compositeoper();
	}
	else if (lexeme.type == 2 ||
		lexeme.type == 3 || lexeme.lex == "+" || lexeme.lex == "-" || 
		lexeme.lex == "!" || lexeme.lex == "(" ||
		lexeme.lex == "true" || lexeme.lex == "false")//Оператор выражения
	{
		expression();
		if (lexeme.lex != ";") error();
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
		if (lexeme1.lex == "=")
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
	while (lexeme.lex == ">" || lexeme.lex == "<" || lexeme.lex == "!=" || lexeme.lex == ">=" || lexeme.lex == "<+" || lexeme.lex == "==")
	{
		fgl(lexeme);
		simpleexpression();
	}
}
void simpleexpression()
{
	term();
	while (lexeme.lex == "+" || lexeme.lex == "-" || lexeme.lex == "||")
	{
		fgl(lexeme);
		term();
	}
}
void term()
{
	atom1();
	while (lexeme.lex == "*" || lexeme.lex == "/" || lexeme.lex == "&&" || lexeme.lex == "div" || lexeme.lex == "%")
	{
		fgl(lexeme);
		atom1();
	}
}
void atom1()
{
	atom();
	if (lexeme.lex == "^")
	{
		fgl(lexeme);
		atom();
	}
	if (lexeme.lex == "++" || lexeme.lex == "--")
		fgl(lexeme);	
}
void atom()
{
	if (lexeme.lex == "(")
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
	if (lexeme.lex == "!")
	{
		fgl(lexeme);
		atom();
		return;
	}
	else if (lexeme.lex == "true" || lexeme.lex == "false")
	{
		fgl(lexeme);
		return;
	}
	else constant();
}
void constant()
{
	if (lexeme.lex == "+" || lexeme.lex == "-")
	{
		fgl(lexeme);
		if (lexeme.type != 3) error();
		fgl(lexeme);
		return;
	}
	else if (lexeme.type == 3)
	{
		fgl(lexeme);
		if (lexeme.lex == ".")
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
	if (lexeme.lex != "while") error();
	fgl(lexeme);
	if (lexeme.lex != "(") error();
	fgl(lexeme);
	expression();
	if (lexeme.lex != ")") error();
	fgl(lexeme);
	if (lexeme.lex != ";") error();
	fgl(lexeme);
}
void cinout()
{
	do {
		element();
	} while (lexeme.lex == "<<" || lexeme.lex == ">>");
	if (lexeme.lex != ";") error();
	fgl(lexeme);
}
void element()
{
	if (lexeme.lex == ">>")
	{
		fgl(lexeme);
		if (lexeme.type != 2) error();
		fgl(lexeme);
	}
	else if (lexeme.lex == "<<")
	{
		fgl(lexeme);
		if (lexeme.lex == "endl")
			fgl(lexeme);
		else if (lexeme.lex == "\"")
		{
			fgl(lexeme);
			if (lexeme.type != 7) error();
			fgl(lexeme);
			if (lexeme.lex != "\"") error();
			fgl(lexeme);
		}
		else expression();
	}
	else error();
}
void operfor()
{
	if (lexeme.lex != "(") error();
	fgl(lexeme);
	if (lexeme.lex == "int" || lexeme.lex == "double" || lexeme.lex == "bool")
		cfor1();
	else if (lexeme.type == 2)
	{
		fgl(lexeme1);
		if (lexeme1.lex == ":=")
		{
			lexeme1.type = 0;
			fgl(lexeme);
			pfor();
		}
		else cfor2();
	}
	else cfor2();
	if (lexeme.lex != ")") error();
	fgl(lexeme);
	oper();
	if (lexeme.lex == "else")
	{
		fgl(lexeme);
		oper();
	}
}
void cfor1()
{
	description();
	expression();
	if (lexeme.lex != ";") error();
	fgl(lexeme);
	expression();
}
void cfor2()
{
	expression();
	if (lexeme.lex != ";") error();
	fgl(lexeme);
	expression(); 
	if (lexeme.lex != ";") error();
	fgl(lexeme);
	expression();
}
void pfor()
{
	expression();
	if (lexeme.lex != "to" && lexeme.lex != "downto") error();
	fgl(lexeme);
	expression();
}

int main()
{
	fgl(lexeme);
	program();
}
