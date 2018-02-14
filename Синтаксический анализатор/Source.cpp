#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

ifstream fin("return.txt"); //файл из лексического анализатора

struct Lexeme
{
	int type;
	string lex;
} lexeme, lexeme1;

void fgl(Lexeme lexeme) //считывание лексемы из файла
{
	if (!fin.eof())
	{
		fin >> lexeme.lex;
		fin >> lexeme.type;
		fin >> lexeme.type;
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
	cout << "FATAL ERROR!!! Run away! There are 3 seconds before the exlosive. 2... 1..." << endl;
	system("pause");
	exit(1);
}

void program()
{
	while (lexeme.lex != "main")
		description();
	fgl(lexeme);
	if (lexeme.lex != "(") error();
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
			return;
		if (lexeme.type != 2) error();
		fgl(lexeme);
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
	if (lexeme.lex == "cinout")
	{

	}
	else if (lexeme.lex == "double" || lexeme.lex == "bool" || lexeme.lex == "int")
	{
		description();
	}
	else if (lexeme.lex == "for")
	{

	}
	else if (lexeme.lex == "do")
	{

	}
	else if (lexeme.lex == "{")
	{

	}
	else if (/*expression*/true)
	{

	}
}
void expression()
{

}
/*void logicValue()
{
	if (lexeme.type == 1 && (lexeme.lex == "true" || lexeme.lex == "false")) 
	{
		fgl(lexeme); 
		return; 
	}
	error();
}
void increment()
{
	if (lexeme.type == 4 && (lexeme.lex == "++" || lexeme.lex == "--"))
	{
		fgl(lexeme);
		return;
	}
	error();
}
void assignment()
{
	if (lexeme.type == 4 && lexeme.lex == "=")
	{
		fgl(lexeme);
		return;
	}
	error();
}
void multiplication()
{
	if (lexeme.type == 4 && (lexeme.lex == "*" || lexeme.lex == "/" || lexeme.lex == "%" || lexeme.lex == "&&")) //сюда нужно засунуть div
	{
		fgl(lexeme);
		return;
	}
	error();
}
void addition()
{
	if (lexeme.type == 4 && (lexeme.lex == "+" || lexeme.lex == "-" || lexeme.lex == "||"))
	{
		fgl(lexeme);
		return;
	}
	error();
}
void type()
{
	if (lexeme.type == 2 && (lexeme.lex == "int" || lexeme.lex == "bool" || lexeme.lex == "double"))
	{
		fgl(lexeme);
		return;
	}
	error();
}
void name()
{
	if (lexeme.type == 2)
	{
		fgl(lexeme);
		return;
	}
	error();
}
void direction()
{
	if (lexeme.type == 1 && (lexeme.lex == "to" || lexeme.lex == "downto"))
	{
		fgl(lexeme);
		return;
	}
	error();
}
void exponentiation()
{
	if (lexeme.type == 4 && lexeme.lex == "^")
	{
		fgl(lexeme);
		return;
	}
	error();
}
*/


int main()
{
	fgl(lexeme);
	program();
}
