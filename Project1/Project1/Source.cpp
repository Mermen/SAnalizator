#define _CRT_SECURE_NO_WARNINGS

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


struct Lexeme
{
	int type = 0, str = 0;
	char lex[10000];
} lexeme, lexeme1;

struct TID
{
	char name[10000];
	int type = 0; // 1 - int, 2 - double, 3 - bool
	TID *next = NULL;
} *r = NULL, *s= NULL;

struct L_TID
{
	L_TID *next = NULL;
	TID *head = NULL;
} *L = new L_TID, *p = NULL, *q = NULL;

int depth = 1; 
int type = 0;
char name[10000];

void add_id()
{
	p = L;
	for (int i = depth; i > 0; --i)
	{
		if (p->head != NULL) r = p->head;
		else r = NULL;
		if (r != NULL)
		{
			while (true)
			{
				if (!strcmp(name, r->name))
				{
					cout << "String " << lexeme.str << ". Double description!" << endl;
					system("pause");
					exit(1);
				}
				if (r->next != NULL)
					r = r->next;
				else
					break;
			}
		}
		if (i != 1)
			p = p->next;
	}
	if (p->head == NULL)
	{
		p->head = new TID;
		r = p->head;
	}
	else
	{
		r->next = new TID;
		r = r->next;
	}
	r->type = type;
	strcpy(r->name, name);
}

int check_id()
{
	p = L;
	for (int i = depth; i > 0; --i)
	{
		if (p->head != NULL) r = p->head;
		else r = NULL;
		if (r != NULL)
		{
			while (true)
			{
				if (!strcmp(name, r->name))
					return r->type;
				if (r->next != NULL)
					r = r->next;
				else
					break;
			}
		}
		if (i != 1)
			p = p->next;
	}
	cout << "String " << lexeme.str << ". Using undescribed variable!" << endl;
	system("pause");
	exit(1);
}

void addDepth()
{
	p = L;
	for (int i = depth; i > 1; i--)
		p = p->next;
	p->next = new L_TID;
}

void deleteDepth()
{
	p = L;
	for (int i = depth; i > 1; i--)
		p = p->next;
	q = p->next;
	p->next = NULL;
	r = q->head;
	delete q;
	while (r != NULL)
	{
		s = r->next;
		delete r;
		r = s;
	}
}

struct stack
{
	int type = 0; // 1 - int, 2 - double, 3 - bool, 4 - operation
	char oper[3];
	stack *next;
} *H = NULL, *m = NULL;

void push(int t)
{
	m = new stack;
	strcpy(m->oper, name);
	m->type = t;
	m->next = H;
	H = m;
}
void pop()
{
	*m = *H;
	H = H->next;
	m->next = NULL;
}
void peek()
{
	*m = *H;
	m->next = NULL;
}
void clear()
{
	while (H != NULL)
	{
		m = H;
		H = H->next;
		delete m;
	}
}
void check_op()
{
	int t1, t2, t, ret;
	char op[10];
	pop();
	t2 = m->type;
	pop();
	strcpy(op, m->oper);
	pop();
	t1 = m->type;
	if (!strcmp(op, "&&") || !strcmp(op, "||"))
	{
		t = 3;
		ret = 3;
	}
	else if (!strcmp(op, "%") || !strcmp(op, "div"))
	{
		t = 1;
		ret = 1;
	}
	else if (!strcmp(op, "+") || !strcmp(op, "-") || !strcmp(op, "*") || !strcmp(op, "/") || !strcmp(op, "^") || !strcmp(op, "="))
	{
		ret = t = t1;
	}
	else
	{
		ret = 3;
		if (t1 != t2)
		{
			cout << "String " << lexeme.str << ". Disperancy of operands." << endl;
			system("pause");
			exit(1);
		}
		else
			push(ret);
		return;
	}
	if (t1 == t2 && t1 == t)
		push(ret);
	else
	{
		cout << "String " << lexeme.str << ". Disperancy of operands and operation." << endl;
		system("pause");
		exit(1);
	}
}
void check_inc()
{
	int t;
	char op[10];
	pop();
	strcpy(op, m->oper);
	pop();
	t = m->type;
	if (t <= 2)
		push(t);
	else 
	{
		cout << "String " << lexeme.str << ". Disperancy of operand and operation." << endl;
		system("pause");
		exit(1);
	}
}
void check_not()
{
	int t;
	char op[10];
	pop();
	t = m->type;
	pop();
	strcpy(op, m->oper);
	if (t == 3)
		push(t);
	else
	{
		cout << "String " << lexeme.str << ". Disperancy of operand and operation." << endl;
		system("pause");
		exit(1);
	}
}
void eq_bool()
{
	int t;
	pop();
	t = m->type;
	if (t != 3)
	{
		cout << "String " << lexeme.str << ". There is no a boolean expression in the special operator." << endl;
		system("pause");
		exit(1);
	}
}
void eq_int()
{
	int t;
	pop();
	t = m->type;
	if (t != 1)
	{
		cout << "String " << lexeme.str << ". There is no a integer expression in the special operator pfor." << endl;
		system("pause");
		exit(1);
	}
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


void fgl(Lexeme &lexeme);
void synterror();
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
void synterror()
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
	if (strcmp(lexeme.lex, ")")) synterror();
	fgl(lexeme);
	compositeoper();
	cout << "There are no errors. The code is correct." << endl;
	system("pause");
}
void description()
{
	if (!strcmp(lexeme.lex, "double") || !strcmp(lexeme.lex, "bool") || !strcmp(lexeme.lex, "int"))
	{
		if (!strcmp(lexeme.lex, "int")) type = 1;
		else if (!strcmp(lexeme.lex, "double")) type = 2;
		else type = 3;
		fgl(lexeme);
		strcpy(name, lexeme.lex);
		if (!strcmp(lexeme.lex, "main"))
		{
			fgl(lexeme);
			if (!strcmp(lexeme.lex, "("))
				return;
			else goto mark47;
		}
		if (lexeme.type != 2) synterror();
		fgl(lexeme);
	mark47:
		if (!strcmp(lexeme.lex, "="))
		{
			push(type);
			fgl(lexeme);
			expression();
			check_op();
		}
		add_id();
		
		while (!strcmp(lexeme.lex, ","))
		{
			fgl(lexeme);
			strcpy(name, lexeme.lex);
			if (lexeme.type != 2) synterror();
			fgl(lexeme);
			if (!strcmp(lexeme.lex, "="))
			{
				fgl(lexeme);
				expression();
			}
			add_id();
		}
		if (strcmp(lexeme.lex, ";")) synterror();
		fgl(lexeme);
		return;
	}
	else synterror();
}
void compositeoper()
{
	if (strcmp(lexeme.lex, "{")) synterror();
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
		if (strcmp(lexeme.lex, ";")) synterror();
		fgl(lexeme);
	}
	else synterror();
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
			strcpy(name, lexeme.lex);
			push(check_id());
			strcpy(name, lexeme1.lex);
			push(4);
			lexeme1.type = 0;
			fgl(lexeme);
			expression();
			check_op();
		}
		else expression1();
	}
}
void expression1()
{
	simpleexpression();
	while (!strcmp(lexeme.lex, ">") || !strcmp(lexeme.lex, "<") || !strcmp(lexeme.lex, "!=") || !strcmp(lexeme.lex, ">=") || !strcmp(lexeme.lex, "<=") || !strcmp(lexeme.lex, "=="))
	{
		strcpy(name, lexeme.lex);
		push(4);
		fgl(lexeme);
		simpleexpression();
		check_op();
	}
}
void simpleexpression()
{
	term();
	while (!strcmp(lexeme.lex, "+") || !strcmp(lexeme.lex, "-") || !strcmp(lexeme.lex, "||"))
	{
		strcpy(name, lexeme.lex);
		push(4);
		fgl(lexeme);
		term();
		check_op();
	}
}
void term()
{
	atom1();
	while (!strcmp(lexeme.lex, "*") || !strcmp(lexeme.lex, "/") || !strcmp(lexeme.lex, "&&") || !strcmp(lexeme.lex, "div") || !strcmp(lexeme.lex, "%"))
	{
		strcpy(name, lexeme.lex);
		push(4);
		fgl(lexeme);
		atom1();
		check_op();
	}
}
void atom1()
{
	atom();
	if (!strcmp(lexeme.lex, "^"))
	{
		strcpy(name, lexeme.lex);
		push(4);
		fgl(lexeme);
		atom();
		check_op();
	}
	else if (!strcmp(lexeme.lex, "++") || !strcmp(lexeme.lex, "--"))
	{
		strcpy(name, lexeme.lex);
		push(4);
		check_inc();
		fgl(lexeme);
	}
}
void atom()
{
	if (!strcmp(lexeme.lex, "("))
	{
		fgl(lexeme);
		expression();
		if (lexeme.lex != ")") synterror();
		fgl(lexeme);
	}
	else if (lexeme.type == 2)
	{
		strcpy(name, lexeme.lex);
		push(check_id());
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
		strcpy(name, lexeme.lex);
		push(4);
		fgl(lexeme);
		atom();
		check_not();
		return;
	}
	else if (!strcmp(lexeme.lex, "true") || !strcmp(lexeme.lex, "false"))
	{
		push(3);
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
		if (lexeme.type != 3) synterror();
		push(1);
		fgl(lexeme);
		return;
	}
	else if (lexeme.type == 3)
	{
		fgl(lexeme);
		if (!strcmp(lexeme.lex, "."))
		{
			fgl(lexeme);
			if (lexeme.type != 3) synterror();
			push(2);
			fgl(lexeme);
			return;
		}
		push(1);
	}
	else synterror();
}
void dowhile()
{
	addDepth();
	depth++;
	oper();
	if (strcmp(lexeme.lex, "while")) synterror();
	fgl(lexeme);
	if (strcmp(lexeme.lex, "(")) synterror();
	fgl(lexeme);
	expression();
	if (strcmp(lexeme.lex, ")")) synterror();
	eq_bool();
	fgl(lexeme);
	if (strcmp(lexeme.lex, ";")) synterror();
	fgl(lexeme);
	depth--;
	deleteDepth();
}
void cinout()
{
	do {
		element();
	} while (!strcmp(lexeme.lex, "<<") || !strcmp(lexeme.lex, ">>"));
	if (strcmp(lexeme.lex, ";")) synterror();
	fgl(lexeme);
}
void element()
{
	if (!strcmp(lexeme.lex, ">>"))
	{
		fgl(lexeme);
		if (lexeme.type != 2) synterror();
		strcpy(name, lexeme.lex);
		check_id();
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
	else synterror();
}
void operfor()
{
	addDepth();
	depth++;
	if (strcmp(lexeme.lex, "(")) synterror();
	fgl(lexeme);
	if (!strcmp(lexeme.lex, "int") || !strcmp(lexeme.lex, "double") || !strcmp(lexeme.lex, "bool"))
		cfor1();
	else if (lexeme.type == 2)
	{
		fgl(lexeme1);
		if (!strcmp(lexeme1.lex, ":="))
		{
			strcpy(name, lexeme.lex);
			type = 1;
			add_id();
			lexeme1.type = 0;
			fgl(lexeme);
			pfor();
		}
		else cfor2();
	}
	else cfor2();
	if (strcmp(lexeme.lex, ")")) synterror();
	fgl(lexeme);
	oper();
	depth--;
	deleteDepth();
	if (!strcmp(lexeme.lex, "else"))
	{
		addDepth();
		depth++;
		fgl(lexeme);
		oper();
		depth--;
		deleteDepth();
	}
}
void cfor1()
{
	description();
	expression();
	if (strcmp(lexeme.lex, ";")) synterror();
	eq_bool();
	fgl(lexeme);
	expression();
}
void cfor2()
{
	expression();
	if (strcmp(lexeme.lex, ";")) synterror();
	fgl(lexeme);
	expression();
	if (strcmp(lexeme.lex, ";")) synterror();
	eq_bool();
	fgl(lexeme);
	expression();
}
void pfor()
{
	expression();
	eq_int();
	if (strcmp(lexeme.lex, "to") && strcmp(lexeme.lex, "downto")) synterror();
	fgl(lexeme);
	expression();
	eq_int();
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
