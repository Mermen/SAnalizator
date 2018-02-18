#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

ifstream fin("return.txt");

struct Lexeme
{
	int type, str;
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

int main()
{
	fgl(lexeme);
	program();
}
