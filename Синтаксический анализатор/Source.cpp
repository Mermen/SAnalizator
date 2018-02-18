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

void fgl(Lexeme lexeme)
{
	if (!fin.eof())
	{
		fin >> lexeme.lex;
		fin >> lexeme.type;
		fin >> lexeme.str;
	}
	else
	{
		cout << "File is empty.";
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
}
void oper()
{
	if (lexeme.lex == "cinout") // Оператор ввода-вывода
	{
		cinout();
	}
	else if (lexeme.lex == "double" || lexeme.lex == "bool" || lexeme.lex == "int") //Описание
	{
		description();
	}
	else if (lexeme.lex == "for")//Спец. оператор cfor/pfor
	{

	}
	else if (lexeme.lex == "do")//Спец. оператор dowhile
	{
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
	}
}
void expression()
{
	if (lexeme.type != 2)
		expression1();
	else
	{
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

}
void dowhile()
{

}
void cinout()
{

}

int main()
{
	fgl(lexeme);
	program();
}
