#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <fstream> 
using namespace std;
void conditional_expression();
void while_loop();
void for_loop();
void printf_statement();
void expression();
void type_declaration_list();
void scanf_statement();
void closingBrace();
int i;
int type_i;
int Opening;
int Closing;
int for_open;
int for_close;
struct token
{
	int line;
	string name;
	string type;
};
vector <token> Token;
vector <token> Token1;
vector <token> SymbolTable;
vector <token> Used;
vector <token> typetable;
token a,b;
token l;
token r;
void type_statement_list();
struct table
{
	string name;
	string type;
};
int q = 0;
vector <table> var;
table d;
int max = 0;
int newq()
{
	max++;
	return max + 1;
}
void populateFunctionTable(int num)
{
	d.type = Token[i].name;
	i++;
	d.name = Token[i].name;
	i++;
	var.push_back(d);
	while (Token[i].name != ";")
	{
		if (Token[i].name == ",")
		{
			i++;
			d.name = Token[i].name;
			var.push_back(d);
			i++;
		}
	}
	if (Token[i].name == ";")
	{
		i++;
		return;
	}
}
void newfunctionTable()
{
	//var = new vector<table>;


}
void typecheck_old()
{
	while (i < Token.size())
	{
		if (Token[i].name == "{")
		{
			i++;
			q = newq();
			newfunctionTable();
			while (Token[i].type == "datatype")
			{
				populateFunctionTable(q);
			}
		}
		else if (Token[i].name == "}")
		{
			i++;
			q--;
		}
		i++;
	}
}
void readfile()
{
	string line;
	fstream myfile;
	myfile.open("Tokens.txt");
	if (!myfile)
	{
		cout << "Error opening file\n";
		getchar();
		exit(0);
	}
	else
	{
		int test1;
		getline(myfile, line, ' ');
		while (!myfile.eof())
		{
			token myToken;
			if (line == "" || line == "\n")
				cout << "silly\n";
			myToken.line = stoi(line);
			getline(myfile, line, ' ');//
			myToken.type = line;
			getline(myfile, line, '\n');//
			myToken.name = line;
			if (myToken.name[0] == ' ')
				myToken.name.erase(myToken.name.begin());
			Token1.push_back(myToken);
			Token.push_back(myToken);
			//myfile >> line;

			getline(myfile, line, ' ');

		}
	}
}
string findtype(string);
void panic_mode(){

	while (i < Token.size() && Token[i].type != "separator") i++;

	if (i == Token.size())
	{
		cout << "PANIC MODE: End of file reached. " << endl;
		system("pause");
		exit(0);
	}
	cout << "PANIC MODE: Separator found. Continuing thread of execution. " << endl;
	i++;
}
void CheckScope(int a, int b)
{
	int c = 0;
	for (int j = 0; j < SymbolTable.size(); j++)
	for (int k = 0; k < SymbolTable.size(); k++)
	if (SymbolTable[k].name == SymbolTable[j].name && (k != j))
		cout << "Variable redefined: Line number: " << SymbolTable[k].line << " " << SymbolTable[k].name << endl;
	for (int j = a; a < b; a++)
	{
		if (Token[a].type == "identifier/literal" && (!isdigit(Token[a].name[0])))
		{
			for (int k = 0; k < SymbolTable.size(); k++)
			{
				if (Token[a].name == SymbolTable[k].name)
					c++;
			}
			if (c == 0)
				cout << "Variable undefined: Line number: " << Token[a].line << " " << Token[a].name << endl;
			c = 0;
		}
	}
}
vector<token> typevec;
bool isnumber(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}
//string convert_to_number(string name)
//{
//	//CONVERT CHAR 'a' TO NUMBER  :/
//	
//}
void typeconversion()
{

	int cal_i = i;
	string prev_token = Token1[cal_i].type;
	while (Token1[cal_i].name != ";")
	{
		if (Token1[cal_i].type == "operator")
			cal_i++;
		else if (prev_token == Token1[cal_i].type)
		{
			//do nothing
		}
		else if ((prev_token == "int" && Token1[cal_i].type == "float") || (prev_token == "float" && Token1[cal_i].type == "int"))
		{
			Token1[cal_i - 1].type == "float"; Token1[cal_i].type == "float";
		}
		else if ((prev_token == "int" && Token1[cal_i].type == "char") || (prev_token == "char" && Token1[cal_i].type == "int"))
		{
			//!!!! OONVERT char if it is in 'a' form. else leave it as it is
			Token1[cal_i - 1].type == "int"; Token1[cal_i].type == "int";
		}
		else if ((prev_token == "char" && Token1[cal_i].type == "float") || (prev_token == "float" && Token1[cal_i].type == "char"))
		{
			//CONVERT char if it is in 'a' form, else leave it be
			Token1[cal_i - 1].type == "float"; Token1[cal_i].type == "float";
		}
		else if (prev_token == "bool" || Token1[cal_i].type == "bool")
		{
			cout << "Err: bool cannot be converted\n";
		}
		prev_token = Token1[cal_i].type;
		cal_i++;
		
	}
}
string righttype()
{
	string first = typevec[0].type;
	bool same = 1;
	for (int w = 0; w < typevec.size(); w++)
	{
		if (typevec[w].type != first)
		{
			same = 0;
			typeconversion();
			return "float";
		}
	}
	if (same == 1)
	{
		return first;
	}
}
string calculatetype()
{
	typevec.clear();
	int cal_i = i;
	while (Token1[cal_i].name != ";")
	{
		if (Token1[cal_i].type == "operator" || Token1[cal_i].type == "relational_operator")
			cal_i++;
		r.name = Token1[cal_i].name;
		r.type = findtype(r.name);
		if (r.type == " ")r.type = Token1[cal_i].type;
		typevec.push_back(r);

		cal_i++;
	}
	string a = righttype();
	return a;
}
string findtype(string n)
{
	for (int p = 0; p < typetable.size(); p++)
	{
		if (typetable[p].name == n)
			return typetable[p].type;
	}
	cout << "Type not found!!!\n";
	return " " ;
}
void typecheck_table (int ab)
{
	type_i = i;
	type_i++;
	int cont = 1;
	while (cont) //declaration
	{
		if (ab==1 && Token1[type_i].type == "datatype")
		{
			type_declaration_list();
			/*token a;
			a.type = Token[type_i].name;
			a.name = Token[type_i + 1].name;
			typetable.push_back(a);
			type_i++;*/
		}
		else if (Token1[type_i].type == "identifier/literal")
		{
			//type_statement_list();
		}
		//// if (Token[type_i].name == "}")
		cont = 0;
		
	}
	
}
bool balancedParanthesis(int a, int b)
{
	stack <token> opening;
	stack <token> closing;
	for (; a < b; a++)
	if (Token[a].name == "(")
		opening.push(Token[a]);
	else if (Token[a].name == ")")
		closing.push(Token[a]);
	if (opening.size() == closing.size())
		return true;
	else
		return false;
}
bool balancedBraces(int a, int b)
{
	stack <token> opening;
	stack <token> closing;
	for (; a < b; a++)
	{
		if (Token[a].name == "{")
			opening.push(Token[a]);
		else if (Token[a].name == "}")
			closing.push(Token[a]);
	}
	if (opening.size() == closing.size())
		return true;
	else
		return false;
}
void replace()
{
	int j = 0;
	for (; j < Token.size(); j++)
	{
		if (Token[j].type == "number" || Token[j].type == "float" || Token[j].type == "bool")
			Token[j].type = "identifier/literal";
	}
}
void replace1()
{
	int j = 0;
	for (; j < Token1.size(); j++)
	{
		if (Token1[j].type == "number")
			Token1[j].type = "int";
	}
}
int priority(string op)
{
	if (op == "+" || op == "-")
		return 1;
	else if (op == "/" || op == "*")
		return 2;
	else if (op == "=")
		return 0;
}
int priority_bool(string op)
{
	if (op == "<=" || op == ">=" || op == "<" || op == ">")
		return 0;
	else if (op == "==" || op == "!=")
		return 1;
	else if (op == "&&" || op == "||")
		return 2;

}
void return_type()
{
	if (!(Token[i].type == "returntype" || Token[i].type == "datatype"))
		cout << "Err: Line " << Token[i].line << ":Expecting a return type but saw " << Token[i].name << " of type " << Token[i].type << endl;
}
void identifier_name()
{
	if (!(Token[i].type == "identifier/literal"))
		cout << "Err: Line " << Token[i].line << ":Expecting an identifier/literal but saw " << Token[i].name << " of type " << Token[i].type << endl;
}
void openingParanthesis()
{
	if (!(Token[i].name == "(" && Token[i].type == "paranthesis")) {
		cout << "Err: Line " << Token[i].line << ":Expecting an opening paranthesis but saw " << Token[i].name << " of type " << Token[i].type << endl;
	}
}
void openingBrace()
{
	if (!(Token[i].name == "{" && Token[i].type == "brace"))
		cout << "Err: Line " << Token[i].line << ":Expecting an opening brace but saw " << Token[i].name << " of type " << Token[i].type << endl;
}
void statement_list()
{
	cout << "Message: Checkins statement list " << Token[i].name << endl;
	while (Token[i].name != "}")
	{
		if (Token[i].name == "if" && Token[i + 1].name == "(") // if conditional
		{
			cout << "Message: If statement: \nChecking expression: " << endl;
			conditional_expression();
			//    i++;
		}
		else if (Token[i].type == "identifier/literal" && Token[i + 1].type == "operator" && Token[i + 1].name == "=") // assignment
		{
			l.name = Token1[i].name;
			l.type = findtype(l.name);
			if (l.type == " ")l.type = Token1[i].type;
			cout << "Message: Assignment statement: \nChecking expression: " << endl;
			i += 2;
			expression();
			i++;
		}
		else if (Token[i].name == "break" && Token[i + 1].name == ";") // break statement
		{
			cout << "Message: Correct break statement!" << endl;
			i += 2;
		}
		else if (Token[i].name == "break" && Token[i + 1].name != ";") // break error :D
		{
			cout << "Err: Line " << Token[i].line << ":Expecting nothing after break except ; but saw " << Token[i].name << " of type " << Token[i].type << endl;
			while (i < Token.size() && Token[i].line < Token[i].line) i++;

			if (i == Token.size())
			{
				cout << "PANIC MODE for new line: End of file reached. " << endl;
				system("pause");
				exit(0);
			}
			cout << "PANIC MODE: New line. Continuing thread of execution. " << endl;
			i++;
		}
		else if (Token[i].type == "keywords") // printf or scanf or return
		{
			if (Token[i].name == "printf")
			{
				i++;
				printf_statement();
			}
			else if (Token[i].name == "scanf")
			{
				i++;
				scanf_statement();
			}
			else if (Token[i].name == "return")
			{
				i++;
				expression(); //function return type to be stored in l.type :/
				i++;
			}
			else if (Token[i].name == "while" && Token[i + 1].name == "(") // if conditional
			{
				cout << "Message: While statement: \nChecking expression: " << endl;
				while_loop();
				i++;
			}

			else if (Token[i].name == "for" && Token[i + 1].name == "(") // if conditional
			{
				cout << "Message: For Loop: \nChecking expression: " << endl;
				for_loop();
				i++;
			}
			else panic_mode();
		}

	}

}
//void type_statement_list()
//{
//	cout << "Message: Type Checking statement list " << Token[type_i].name << endl;
//	while (Token[type_i].name != "}")
//	{
//		if (Token[type_i].name == "if" && Token[type_i + 1].name == "(") // if conditional
//		{
//			cout << "Message: If statement: \nChecking expression: " << endl;
//			conditional_expression();
//			//   type_i++;
//		}
//		else if (Token[type_i].type == "identifier/literal" && Token[type_i + 1].type == "operator" && Token[type_i + 1].name == "=") // assignment
//		{
//			cout << "Message: Assignment statement: \nChecking expression: " << endl;
//			type_i += 2;
//			expression();
//			type_i++;
//		}
//		else if (Token[type_i].name == "break" && Token[type_i + 1].name == ";") // break statement
//		{
//			cout << "Message: Correct break statement!" << endl;
//			type_i += 2;
//		}
//		else if (Token[type_i].name == "break" && Token[type_i + 1].name != ";") // break error :D
//		{
//			cout << "Err: Line " << Token[type_i].line << ":Expecting nothing after break except ; but saw " << Token[type_i].name << " of type " << Token[type_i].type << endl;
//			while (type_i < Token.size() && Token[type_i].line < Token[type_i].line) type_i++;
//
//			if (type_i == Token.size())
//			{
//				cout << "PANIC MODE for new line: End of file reached. " << endl;
//				system("pause");
//				exit(0);
//			}
//			cout << "PANIC MODE: New line. Continuing thread of execution. " << endl;
//			type_i++;
//		}
//		else if (Token[type_i].type == "keywords") // printf or scanf or return
//		{
//			if (Token[type_i].name == "printf")
//			{
//				type_i++;
//				printf_statement();
//			}
//			else if (Token[type_i].name == "scanf")
//			{
//				type_i++;
//				scanf_statement();
//			}
//			else if (Token[type_i].name == "return")
//			{
//				type_i++;
//				expression();
//				type_i++;
//			}
//			else if (Token[type_i].name == "while" && Token[type_i + 1].name == "(") // if conditional
//			{
//				cout << "Message: While statement: \nType checking expression: " << endl;
//				while_loop();
//				type_i++;
//			}
//
//			else if (Token[type_i].name == "for" && Token[type_i + 1].name == "(") // if conditional
//			{
//				cout << "Message: For Loop: \nChecking expression: " << endl;
//				for_loop();
//				type_i++;
//			}
//			else panic_mode();
//		}
//
//	}
//
//}
void statement()
{
	if (Token[i].name == "if" && Token[i + 1].name == "(") // if conditional
	{
		cout << "Message : If statement: \nChecking expression: " << endl;
		conditional_expression();
		i++;
	}
	else if (Token[i].type == "identifier/literal" && Token[i + 1].type == "operator" && Token[i + 1].name == "=") // assignment
	{
		l.name = Token1[i].name;
		l.type = findtype(l.name);
		if (l.type == " ") l.type = Token1[i].type;
		cout << "Message : Assignment statement: \nChecking expression: " << endl;
		i += 2;
		expression();
		i++;
	}
	else if (Token[i].name == "break" && Token[i + 1].name == ";") // break statement
	{
		cout << "Message: Correct break statement!" << endl;
		i += 2;
	}
	else if (Token[i].name == "break" && Token[i + 1].name != ";") // break error :D
	{
		cout << "Warning: Line " << Token[i].line << ":Expecting nothing after break except ; but saw " << Token[i].name << " of type " << Token[i].type << endl;
		while (i < Token.size() && Token[i].line < Token[i].line) i++;

		if (i == Token.size())
		{
			cout << "PANIC MODE for new line: End of file reached. " << endl;
			system("pause");
			exit(0);
		}
		cout << "PANIC MODE: New line. Continuing thread of execution. " << endl;
		i++;
	}
	else if (Token[i].type == "keywords") // printf or scanf or return
	{
		if (Token[i].name == "printf")
		{
			i++;
			printf_statement();
		}
		else if (Token[i].name == "scanf")
		{
			i++;
			scanf_statement();
		}
		else if (Token[i].name == "return")
		{
			i++;
			expression();
			i++;
		}
	}
	cout << "Message: Statements list checked!" << Token[i].name << endl;
}
void parameter_list(int a)
{
	
	if (Token[i].type != "datatype" && Token[i + 1].type != "identifier/literal" && Token[i].name == ")" && a == 0)
		return; // list is empty
	else if (Token[i].type == "datatype" && Token[i + 1].type == "identifier/literal")
	{
		b.type = Token1[i].name;
		b.name = Token1[i+1].name;
		typetable.push_back(b);
		SymbolTable.push_back(Token[i + 1]);
		if (Token[i + 2].name == ")")
		{
			i += 2;
			return;
		}
		else if (Token[i + 2].type == "comma")
		{
			i = i + 3;
			parameter_list(1);
			return;
		}
	}
	else
		cout << "Err: Line " << Token[i].line << ":Expecting parameter list but saw " << Token[i].name << " of type " << Token[i].type << endl;
	i++;
}
void closingParanthesis()
{
	if (!(Token[i].name == ")" && Token[i].type == "paranthesis"))
		cout << "Err: Line " << Token[i].line << ":Expecting a closing paranthesis but saw " << Token[i].name << " of type " << Token[i].type << endl;
}
void closingBrace()
{
	if (i < Token.size()) {
		if (!(Token[i].name == "}" && Token[i].type == "brace"))
			cout << "Err: Line " << Token[i].line << ":Expecting a closing brace but saw " << Token[i].name << " of type " << Token[i].type << endl;
	}
}
void variable()
{
	if (Token[i].type == "datatype")
	{
		// it was datatype so we move to the next one  
		i++;
		if (Token[i].type == "identifier/literal")
		{
			SymbolTable.push_back(Token[i]);
		}

		if (Token[i].type != "identifier/literal")
		{
			cout << "Err: Line " << Token[i].line << ":Expecting an identifier/literal but saw " << Token[i].name << " of type " << Token[i].type << endl;
			panic_mode();
			variable();
			return;
		}
		i++; // now we are expecting a comma or a separator 
		if (Token[i].type == "separator")
		{
			i++;
			variable();
			return;
		}
		else if (Token[i].type == "comma"){
			i++;
			if (Token[i].type != "identifier/literal")
			{
				cout << "Err: Line " << Token[i].line << ":Expecting an identifier/literal but saw " << Token[i].name << " of type " << Token[i].type << endl;
				panic_mode();
				variable();
				return;
			}
			i++;
			while (Token[i].type != "separator" && Token[i].type == "comma")
			{
				i++;
				if (Token[i].type != "identifier/literal")
				{
					cout << "Err: Line " << Token[i].line << ":Expecting an identifier/literal but saw " << Token[i].name << " of type " << Token[i].type << endl;
					panic_mode();
					variable();
					return;
				}
				i++;
			}
			if (Token[i].type == "separator")
				variable();
			else if (Token[i].type != "separator" && Token[i].type != "comma")
			{
				cout << "Err: Line " << Token[i].line << ":Expecting a comma or separator but saw " << Token[i].name << " of type " << Token[i].type << endl;
				panic_mode();
				variable();
				return;
			}
		}
		else {
			// error condition
			cout << "Err: Line " << Token[i].line << ":Expecting a comma or a separator but saw " << Token[i].name << " of type " << Token[i].type << endl;
			panic_mode(); // CAUSES PROBLEMS WHEN YOU HAVE int blue }
		}
	}
	else // done for ending execution in variable and beginning statement list 
		// two cases
		// 1. code correct, and are expecting statement list
		// 2. variable but no datatype ->  should call panic_mode :/
	{
		cout << "Err: Line " << Token[i].line << ":Expecting a data type for variable declaration but saw " << Token[i].name << " of type " << Token[i].type << endl;
		if (Token[i].type == "separator") // automatic panic mode
		{
			i++;
			variable();
			return;
		}
	}
}
void variable_for()
{
	if (Token[i].name == ";")
		i++;
	else if (Token[i].type == "identifier/literal")
	{
		i++;
		if (Token[i].name == ",")
			variable_for();
		else if (Token[i].name == "=")
		{
			l.name = Token1[i - 1].name;
			l.type = findtype(l.name);
			if (l.type == " ")l.type = Token1[i - 1].type;
			i++;
			expression();
		}
	}
	else
		cout << "Line no: " << Token[i].line << "Expecting a variable or an initialisation but found " << Token[i].name << " of type: " << Token[i].type << endl;

}
void variable_list()
{
	if (Token[i].type == "datatype")
		variable();
	else if (Token[i].type != "datatype")
	{
		cout << "Err: Line " << Token[i].line << ":Expecting atleast one variable declaration but saw " << Token[i].name << " of type " << Token[i].type << endl;
		panic_mode();
		variable();
	}
}
void declaration_list()
{
	variable_list();
}
void type_variable()
{
	if (Token1[type_i].type == "datatype")
	{
		a.type = Token1[type_i].name;

		// it was datatype so we move to the next one  
		type_i++;
		if (Token1[type_i].type == "identifier/literal")
		{
			a.name = Token1[type_i].name;
			typetable.push_back(a);
		}

		if (Token1[type_i].type != "identifier/literal")
		{
			//cout << "Err: Line " << Token1[type_i].line << ":Expecting an identifier/literal but saw " << Token1[type_i].name << " of type " << Token1[type_i].type << endl;
			panic_mode();
			type_variable();
			return;
		}
		type_i++; // now we are expecting a comma or a separator 
		if (Token1[type_i].type == "separator")
		{
			type_i++;
			type_variable();
			return;
		}
		else if (Token1[type_i].type == "comma"){
			type_i++;
			if (Token1[type_i].type != "identifier/literal")
			{
				//cout << "Err: Line " << Token1[type_i].line << ":Expecting an identifier/literal but saw " << Token1[type_i].name << " of type " << Token1[type_i].type << endl;
				panic_mode();
				type_variable();
				return;
			}
			type_i++;
			while (Token1[type_i].type != "separator" && Token1[type_i].type == "comma")
			{
				type_i++;
				if (Token1[type_i].type != "identifier/literal")
				{
					//cout << "Err: Line " << Token1[type_i].line << ":Expecting an identifier/literal but saw " << Token1[type_i].name << " of type " << Token1[type_i].type << endl;
					panic_mode();
					type_variable();
					return;
				}
				type_i++;
			}
			if (Token1[type_i].type == "separator")
				type_variable();
			else if (Token1[type_i].type != "separator" && Token1[type_i].type != "comma")
			{
				//cout << "Err: Line " << Token1[type_i].line << ":Expecting a comma or separator but saw " << Token1[type_i].name << " of type " << Token1[type_i].type << endl;
				panic_mode();
				type_variable();
				return;
			}
		}
		else {
			// error condition
			//cout << "Err: Line " << Token1[type_i].line << ":Expecting a comma or a separator but saw " << Token1[type_i].name << " of type " << Token1[type_i].type << endl;
			panic_mode(); // CAUSES PROBLEMS WHEN YOU HAVE int blue }
		}
	}
	else // done for ending execution in variable and beginning statement list 
		// two cases
		// 1. code correct, and are expecting statement list
		// 2. variable but no datatype ->  should call panic_mode :/
	{
		//cout << "Err: Line " << Token1[type_i].line << ":Expecting a data type for variable declaration but saw " << Token1[type_i].name << " of type " << Token1[type_i].type << endl;
		if (Token1[type_i].type == "separator") // automatic panic mode
		{
			type_i++;
			type_variable();
			return;
		}
	}
}
void type_variable_list()
{
	if (Token1[type_i].type == "datatype")
		type_variable();
	else if (Token1[type_i].type != "datatype")
	{
		//cout << "Err: Line " << Token1[type_i].line << ":Expecting atleast one variable declaration but saw " << Token1[type_i].name << " of type " << Token1[type_i].type << endl;
		panic_mode();
		type_variable();
	}
}
void type_declaration_list()
{
	type_variable_list();
}
void separator()
{
	if (Token[i].type == "separator") // automatic panic mode
	{
		i++;
		return;
	}
}
void printf_identifiers()
{
	//checking identifiers/variables/literals in printf statement
	if (Token[i].type == "identifier/literal")
	{
		i++;
		if (Token[i].type == "comma")
		{
			i++;

			printf_identifiers();

			return;
		}
		else if (Token[i].name != ")")
			cout << "Err: Line " << Token[i].line << ":Expecting a comma but saw " << Token[i].name << " of the type " << Token[i].type << endl;
	}
	else
		cout << "Err: Line " << Token[i].line << ":Expecting an identifier but saw " << Token[i].name << " of the type " << Token[i].type << endl;
}
void printf_statement()
{
	openingParanthesis();
	i++;
	//checking string part ""
	if (Token[i].type == "string")
	{
		i++;
		if (Token[i].type == "comma")
		{
			i++;
			//checking variables/literals part
			if (Token[i].name == ")" && Token[i].type == "paranthesis")
			{
				cout << "Err: Line " << Token[i].line << ":Expecting an identifier list but saw " << Token[i].name << " of the type " << Token[i].type << endl;
			}
			else printf_identifiers();
		}
		else if (Token[i].name != ")")
		{
			cout << "Err: Line " << Token[i].line << ":Expecting a comma but saw " << Token[i].name << " of the type " << Token[i].type << endl;
			i++;
		}
	}
	else cout << "Err: Line " << Token[i].line << ":Expecting string in printf statement, but saw " << Token[i].name << " of type " << Token[i].type << "\n";
	closingParanthesis();
	i++;
	separator();
	//i++;
}
void scanf_identifiers()
{
	if (Token[i].type == "identifier/literal" && Token[i].name[0] == '&')
	{
		i++;
		if (Token[i].type == "comma")
		{
			i++;
			scanf_identifiers();
			return;
		}
		else if (Token[i].name != ")"){
			cout << "Err: Line " << Token[i].line << ":Expecting a comma but saw " << Token[i].name << " of the type " << Token[i].type << endl;
			panic_mode();
		}
	}
	else if (Token[i].type != "identifier/literal")
	{
		cout << "Err: Line " << Token[i].line << ":Expecting an identifier but saw " << Token[i].name << " of the type " << Token[i].type << endl;
		panic_mode();
	}
	else if (Token[i].name[0] != '&') {
		cout << "Err: Line " << Token[i].line << ":Expecting an address but saw identifier " << Token[i].name << endl;
		panic_mode();
	}
}
void scanf_statement()
{
	openingParanthesis();
	i++;
	if (Token[i].type == "string")
	{
		i++;
		if (Token[i].type == "comma")
		{
			i++;
			if (Token[i].name == ")" && Token[i].type == "paranthesis")
			{
				cout << "Err: Line " << Token[i].line << ":Expecting an identifier list but saw " << Token[i].name << " of the type " << Token[i].type << endl;
				panic_mode();
				return;
			}
			else {
				scanf_identifiers();
				if (Token[i - 1].name != ";")
				{
					closingParanthesis();
					i++;
					separator();
				}
			}
		}
		else if (Token[i].name != ")")
		{
			cout << "Err: Line " << Token[i].line << ":Expecting a comma but saw " << Token[i].name << " of the type " << Token[i].type << endl;
			i++;
			panic_mode();
		}
	}
	else {
		cout << "Err: Line " << Token[i].line << ":Expecting string in scanf statement, but saw " << Token[i].name << " of type " << Token[i].type << endl;
		panic_mode();
	}

}
string compare()
{
	if (l.type != r.type)
	{
		cout << "Type mismatch!!!\n";
		return (l.type);
		//"APPENDING TO THE SEMI COLON" wala part :D
		//check if int = float -> convert
		//check if float = int -> convert
		//check if int = char -> convert
		//check if char = int -> convert
		//check if bool = int -> convert // no error :)
		//check if int = bool -> convert // no error :)
		
	}
	else if (l.type == r.type)
	{
		cout << "Correct type !!!!!!!!!!!!!!!!!!\n";
	}
	return (r.type);
}
void expression()
{
	r.name = Token1[i].name;
	r.type = calculatetype();// findtype(r.name);
	string asdf = compare();
	Token1[i - 1].name = Token1[i - 1].name + asdf;
	stack <token>Temp;
	vector <token> RPN;
	int k = i;
	while (k < Token.size() && Token[k].type != "separator" && Token[k].line >= Token[k + 1].line) k++;
	if (Token[i].type == "identifier/literal" && (k - i) == 1)
	{
		cout << Token[i].type <<"\n";
		                   
		i += 1;                      
		return;                      
	}
	else if (Token[k].type != "identifier/literal" && (k - i) == 1)
	{
		cout << Token[k].line << " Expecting a single constant or variable but found " << Token[k].name << " of type " << Token[k].type << endl;
		panic_mode();
		return;
	}
	if (!balancedParanthesis(i, k))
	{
		cout << "Err: Line " << Token[i].line << ": Paranthesis are unbalanced in the expression \n";
		while (i < Token.size() && Token[i].line == Token[i + 1].line) i++;
	}
	else{
		for (i; i < k; i++)
		{
			if (Token[i].name == "(")
				Temp.push(Token[i]);
			else if (Token[i].name == ")")
			{
				for (int j = Temp.size(); j > 0 && Temp.top().name != "("; j--)
				{
					RPN.push_back(Temp.top());
					Temp.pop();
				}
				Temp.pop();
			}
			else if (Token[i].type == "identifier/literal")
				RPN.push_back(Token[i]);
			else if (Token[i].type == "operator")
			{
				if (Temp.size() == 0 || priority(Token[i].name) > priority(Temp.top().name) || Temp.top().type != "operator")
					Temp.push(Token[i]);
				else
				{
					RPN.push_back(Temp.top());
					Temp.pop();
					i--;
				}
			}
		}
		cout << "Message: Done!" << endl;
		for (; Temp.size() > 0;)
		{
			RPN.push_back(Temp.top());
			Temp.pop();
		}

		for (int k = 0; k < RPN.size(); k++)
		{
			cout << RPN[k].name << " ";
		}
		cout << endl;

		stack <token> NewStack; int p = 0;
		while (p < RPN.size())
		{
			token current = RPN[p];
			if (current.type == "operator")
			{
				if (NewStack.size() >= 2) {
					token op = current;
					token a = NewStack.top();
					NewStack.pop();
					token b = NewStack.top();
					NewStack.pop();
					p++;
					a.name = b.name + " " + op.name + " " + a.name;
					NewStack.push(a);
				}
				else {
					cout << "Err: Line " << Token[i].line << ":There are too few identifier/literals in the expression.\n";
					for (int j = 0; j < NewStack.size(); j++)
						NewStack.pop();
					break;
				}

			}
			else if (current.type == "identifier/literal")
			{
				NewStack.push(current); p++;
			}

		}
		if (NewStack.size() == 1)
			cout << "Message: Final value: " << NewStack.top().name << endl;
		else if (NewStack.size() >  1) {
			cout << "Err: Line " << Token[i].line << ":There are too many terms in the expression. Evaluates to:  ";
			for (int j = 0; j < NewStack.size(); j++)
			{
				cout << NewStack.top().name << " ";
				NewStack.pop();
			}
			cout << endl;
		}
		else if (NewStack.size() < 1)
			cout << "Err: Line " << Token[i].line << ":Incorrect expression. " << endl;
	}
}
void list() {

	declaration_list();
	statement_list();
}
void nested_block()
{
	openingBrace(); i++;
	
	typecheck_table(0);

	statement_list();
	
	closingBrace(); i++;
}
void block()
{
	//typetable.clear();
	openingBrace();
	typecheck_table(1);
	Opening = i;
	i++;
	list();
	closingBrace();
	Closing = i;
	i++;
}
void function()
{
	return_type(); i++;
	identifier_name();  i++;
	openingParanthesis(); i++;
	parameter_list(0);
	closingParanthesis(); i++;
	block();
}
void function_list()
{
	while (i < Token.size() - 1)
	{
		function();
		CheckScope(Opening, Closing);
		SymbolTable.clear();
		Used.clear();
		Opening = Closing = 0;
	}
}
void findMain()
{
	int count = 0;
	for (int k = 0; k < Token.size() - 2; k++)
	if ((Token[k].type == "returntype" || Token[k].type == "datatype") && Token[k + 1].name == "main" && Token[k + 2].name == "(")
		count++;

	if (count == 1)
		return;
	else if (count < 1)
		cout << "Error: No main function found." << endl;
	else if (count > 1)
		cout << "Error: Multiple main functions found." << endl;
}
void program()
{
	findMain();
	bool a = balancedParanthesis(0, Token.size());
	bool b = balancedBraces(0, Token.size());
	if (!a && !b)
		cout << "Err: Both braces and paranthesis are unbalanced." << endl;
	else if (!b)
		cout << "Err: Unbalanced Braces." << endl;
	else if (!a)
		cout << "Err: Unbalanced Parantheses." << endl;
	else
		function_list();

}
void findbooltype()
{
	int bool_i = i;
	l.name = Token1[bool_i].name;
	l.type = findtype(l.name);
	if (l.type == " ") l.type = Token1[bool_i].type;
	bool_i++;
	if (Token1[bool_i].type == "relational_operator")
		bool_i++;
	if (Token1[bool_i-1].type == "logical_operator")
	{
		r.name = l.name;
		r.type = l.type;
	}
	else
	{
		r.name = Token1[bool_i].name;
		r.type = findtype(r.name);
		if (r.type == " ") r.type = Token1[bool_i].type;
	}

	if (l.type != r.type)
		cout << "Line # " << Token1[bool_i].line << "Incorrect types in boolean expression" << endl;
	else 
		cout << "Correct type usage in boolean expression" << endl;
}
void boolean_expression()
{
	//r.name = Token[i].name;
	//r.type = calculatetype();// findtype(r.name);
	//compare();

	
	
	stack <token>Temp;
	vector <token> RPN;
	int k = i;

	while (k < Token.size() && !(Token[k].name == ")" && (Token[k].line < Token[k + 1].line))) k++; // that would be the last expected token
	// insert condition here that if ) not found then declare and skip to the end :D
	// CHECK FOR BALANCED BRACES FROM i to K FIRST :D AND YOU ARE DONE -> FOR BOTH IN EXP AND BOOLEAN EXP
	if (Token[i].type == "identifier/literal" && (k - i) == 1)
	{
		
		i += 1;
		return;
	}
	else if (Token[k].type != "identifier/literal" && (k - i) == 1)
	{
		//verify
		cout << Token[k].line << " Expecting a single boolean value but found " << Token[k].name << " of type " << Token[k].type << endl;
		i = k;
		return;
	}
	if (!balancedParanthesis(i, k))
	{
		cout << "Err: Line " << Token[i].line << ": Paranthesis are unbalanced in the expression  ";
		while (i < Token.size() && Token[i].line == Token[i + 1].line) i++;
	}
	else
	{
		bool firsttime = 1;
		
		//i++;
		//l.name = Token1[i-1].name;
		//l.type = findtype(l.name);
		//if (l.type == " ")l.type = Token1[i].type;
		//i++;
		//i++;
		//r.name = Token1[i].name;
		//r.type = calculatetype();// findtype(r.name);
		//string asdf = compare();
		//Token1[i - 1].name = Token1[i - 1].name + asdf;
		//i--;
		//i--;
		//i--;
		for (i; i < k; i++)
		{

			if (Token[i].name == "(")
				Temp.push(Token[i]);
			else if (Token[i].name == ")")
			{
				for (int j = Temp.size(); j > 0 && Temp.top().name != "("; j--)
				{
					RPN.push_back(Temp.top());
					Temp.pop();
				}
				Temp.pop();
			}
		

			else if (Token[i].type == "identifier/literal")
			{
				if (firsttime || (Token[i-1].type)=="logical_operator")
				{
					findbooltype();
					firsttime = 0;
				}
				RPN.push_back(Token[i]);
			}
			else if (Token[i].type == "relational_operator" || Token[i].type == "logical_operator")
			{
			/////////////////
				if (Temp.size() == 0 || priority_bool(Token[i].name) > priority_bool(Temp.top().name) || (Temp.top().type != "logical_operator" || Temp.top().type != "relational_operator"))
					Temp.push(Token[i]);
				else
				{
					RPN.push_back(Temp.top());
					Temp.pop();
					i--;
				}
			}
		}
		cout << "Message: Done!" << endl;
		for (; Temp.size() > 0;)
		{
			RPN.push_back(Temp.top());
			Temp.pop();
		}

		for (int k = 0; k < RPN.size(); k++)
		{
			cout << RPN[k].name << " ";
		}
		cout << endl;
		stack <token> NewStack; int p = 0;
		while (p < RPN.size())
		{
			token current = RPN[p];
			if (current.type == "relational_operator" || current.type == "logical_operator")
			{
				if (NewStack.size() >= 2) {
					token op = current;
					token a = NewStack.top();
					NewStack.pop();
					token b = NewStack.top();
					NewStack.pop();
					p++;
					a.name = b.name + " " + op.name + " " + a.name;
					NewStack.push(a);
				}
				else {
					cout << "Err: Line " << Token[i].line << ":There are too few identifier/literals in the expression.\n";
					for (int j = 0; j < NewStack.size(); j++)
						NewStack.pop();
					break;
				}
			}
			else if (current.type == "identifier/literal")
			{
				NewStack.push(current); p++;
			}
		}
		if (NewStack.size() == 1) 
			cout << "Final value: " << NewStack.top().name << endl;
		else if (NewStack.size() >  1) {
			cout << "Err: Line " << Token[i].line << ":There are too many terms in the expression. Evaluates to:  ";
			for (int j = 0; j < NewStack.size(); j++)
			{
				cout << NewStack.top().name << " ";
				NewStack.pop();
			}
			cout << endl;
		}
		else if (NewStack.size() < 1)
			cout << "Err: Line " << Token[i].line << ":Incorrect expression. " << endl;
	}
}
void conditional_expression()
{
	if (Token[i].name == "if" && Token[i + 1].name == "(") // if statement
	{
		i += 2;
		boolean_expression();
		if (Token[i].name == ")")
			i++; // for closing paranthesis
		else {
			cout << "Err: Line " << Token[i].line << ":Expecting an ) but saw " << Token[i].name << ".\n";
			while (i < Token.size() && Token[i].line == Token[i + 1].line) i++; // panic mode
			i++;
		}
	}// evaluation condition
	else if (Token[i].name == "if" && Token[i + 1].name != "(")
	{ // did not evaluate boolean expression
		// loop forward to the end of the line :D 
		cout << "Err: Line " << Token[i].line << ":Expecting an ( but saw " << Token[i].name << ".\n";
		while (i < Token.size() && Token[i].line == Token[i + 1].line) i++;
		i++; // for Token[i+1]/line
		if (i >= Token.size()) {
			cout << "PANIC MODE: End of file reached. " << endl;
			getchar();
			exit(0);
		}
		else
			cout << "PANIC MODE:Skipped to the next line in the block since if condition was wrong. " << endl;
	}
	if (Token[i].name == "{")
	{
		cout << "Message: calling nested block functiom" << endl;
		nested_block();
		//	/*DEBUG!*/i += 6;
	}
	else
	{
		cout << Token[i].name << "Message: calling statement function" << endl;
		statement();
		//	/*DEBUG!*/ i+= 4;
	}
	if (Token[i].name == "else" && Token[i + 1].name != "if")
	{
		if (Token[i + 1].name == "{")
		{
			i += 2;
			cout << Token[i].name << "Message: calling nested block function" << endl;
			nested_block();
			//	/*DEBUG!*/ i+= 6;
		}
		else
		{
			i++;
			cout << Token[i].line << "Message: calling statement function" << endl;
			statement();
			///*DEBUG!*/ i+= 4;
		}
	}
	else if (Token[i].name == "else" && Token[i + 1].name == "if")
	{
		i++; // consume the else
		conditional_expression();
	}
}
void boolean_expression_forloop()
{
	stack <token>Temp;
	vector <token> RPN;
	int k = i;

	while (k < Token.size() && !(Token[k].name == ";" && k>i)) k++; // that would be the last expected token
	// insert condition here that if ; not found then declare and skip to the end :D
	// CHECK FOR BALANCED BRACES FROM i to K FIRST :D AND YOU ARE DONE -> FOR BOTH IN EXP AND BOOLEAN EXP

	bool bo = balancedParanthesis(i, k);

	if (!bo)
	{
		cout << "Err: Line " << Token[i].line << ": Paranthesis are unbalanced in the expression bool ";
		while (i < Token.size() && Token[i].line == Token[i + 1].line) i++;
	}

	else
	{
		for (i; i < k; i++)
		{
			if (Token[i].name == "(")
				Temp.push(Token[i]);
			else if (Token[i].name == ";")
			{
				for (int j = Temp.size(); j > 0 && Temp.top().name != "("; j--)
				{
					RPN.push_back(Temp.top());
					Temp.pop();
				}
				//Temp.pop();
			}
			else if (Token[i].type == "identifier/literal")
				RPN.push_back(Token[i]);
			else if (Token[i].type == "logical_operator" || Token[i].type == "relational_operator")
			{
				if (Temp.size() == 0 || priority_bool(Token[i].name) > priority_bool(Temp.top().name) || Temp.top().type != "logical_operator" || Temp.top().type != "relational_operator")
					Temp.push(Token[i]);
				else
				{
					RPN.push_back(Temp.top());
					Temp.pop();
					i--;
				}
			}
		}
		cout << "Done!" << endl;
		for (; Temp.size() > 0;)
		{
			RPN.push_back(Temp.top());
			Temp.pop();
		}

		for (int k = 0; k < RPN.size(); k++)
		{
			cout << RPN[k].name << " ";
		}
		cout << endl;
		stack <token> NewStack; int p = 0;
		while (p < RPN.size())
		{
			token current = RPN[p];
			if (current.type == "logical_operator" || current.type == "relational_operator")
			{
				if (NewStack.size() >= 2) {
					token op = current;
					token a = NewStack.top();
					NewStack.pop();
					token b = NewStack.top();
					NewStack.pop();
					p++;
					a.name = b.name + " " + op.name + " " + a.name;
					NewStack.push(a);
				}
				else {
					cout << "Err: Line " << Token[i].line << ":There are too few identifier/literals in the expression.\n";
					for (int j = 0; j < NewStack.size(); j++)
						NewStack.pop();
					break;
				}
			}
			else if (current.type == "identifier/literal")
			{
				NewStack.push(current); p++;
			}
		}
		if (NewStack.size() == 1)
			cout << "Final value: " << NewStack.top().name << endl;
		else if (NewStack.size() > 1) {
			cout << "Err: Line " << Token[i].line << ":There are too many terms in the expression. Evaluates to:  ";
			for (int j = 0; j < NewStack.size(); j++)
			{
				cout << NewStack.top().name << " ";
				NewStack.pop();
			}
			cout << endl;
		}
		else if (NewStack.size() < 1)
			cout << "Err: Line " << Token[i].line << ":Incorrect expression. " << endl;
	}
}
void while_loop()
{
	if (Token[i].name == "while" && Token[i + 1].name == "(")
	{
		i += 2;
		boolean_expression();
		if (Token[i].name == ")")
			i++; // for closing paranthesis
		else {
			cout << "Err: Line " << Token[i].line << ":Expecting a ) but saw " << Token[i].name << ".\n";
			while (i < Token.size() && Token[i].line == Token[i + 1].line) i++; // panic mode
			i++;
		}
	}// evaluation condition
	else if (Token[i].name == "while" && Token[i + 1].name != "(")
	{ // did not evaluate boolean expression
		// loop forward to the end of the line :D 
		cout << "Err: Line " << Token[i].line << ":Expecting an ( but saw " << Token[i].name << ".\n";
		while (i < Token.size() && Token[i].line == Token[i + 1].line) i++;
		i++; // for Token[i+1]/line
		if (i >= Token.size()) {
			cout << "PANIC MODE: End of file reached. " << endl;
			getchar();
			exit(0);
		}
		else
			cout << "PANIC MODE:Skipped to the next line in the block since if condition was wrong. " << endl;
	}
	if (Token[i].name == ";" && Token[i + 1].name != "{"){ return; }
	else if (Token[i].name == ";" && Token[i + 1].name == "{"){
		cout << "Warning: Line " << Token[i].line << ":Expecting a ) but saw " << Token[i].name << endl;
	}
	if (Token[i].name == "{")
	{
		cout << "Message: Calling nested_block" << endl;
		nested_block();
	}
	else
	{
		cout << "Message: Calling statement function" << endl;
		statement();
	}
}
void expression_forloop()
{
	stack <token>Temp;
	vector <token> RPN;
	int k = i;
	while (k < Token.size() && !(Token[k].name == ")" && (Token[k].line < Token[k + 1].line))) k++; // that would be the last expected token

	if (Token[i].type == "identifier/literal" && (k - i) == 1)
	{
		i += 1;
		return;

	}
	else if (Token[k].type != "identifier/literal" && (k - i) == 1)
	{
		cout << Token[k].line << " Expecting a single constant or variable but found " << Token[k].name << " of type " << Token[k].type << endl;
		i = k;
		return;
	}

	if (!balancedParanthesis(i, k))
	{
		cout << "Err: Line " << Token[i].line << ": Paranthesis are unbalanced in the expression \n";
		while (i < Token.size() && Token[i].line == Token[i + 1].line) i++;
	}
	else{
		for (i; i < k; i++)
		{
			if (Token[i].name == "(")
				Temp.push(Token[i]);
			else if (Token[i].name == ")")
			{
				for (int j = Temp.size(); j > 0 && Temp.top().name != "("; j--)
				{
					RPN.push_back(Temp.top());
					Temp.pop();
				}
				Temp.pop();
			}
			else if (Token[i].type == "identifier/literal")
				RPN.push_back(Token[i]);
			else if (Token[i].type == "operator")
			{
				if (Temp.size() == 0 || priority(Token[i].name) > priority(Temp.top().name) || Temp.top().type != "operator")
					Temp.push(Token[i]);
				else
				{
					RPN.push_back(Temp.top());
					Temp.pop();
					i--;
				}
			}
		}
		cout << "Done!" << endl;
		for (; Temp.size() > 0;)
		{
			RPN.push_back(Temp.top());
			Temp.pop();
		}

		for (int k = 0; k < RPN.size(); k++)
		{
			cout << RPN[k].name << " ";
		}
		cout << endl;

		stack <token> NewStack; int p = 0;
		while (p < RPN.size())
		{
			token current = RPN[p];
			if (current.type == "operator")
			{
				if (NewStack.size() >= 2) {
					token op = current;
					token a = NewStack.top();
					NewStack.pop();
					token b = NewStack.top();
					NewStack.pop();
					p++;
					a.name = b.name + " " + op.name + " " + a.name;
					NewStack.push(a);
				}
				else {
					cout << "Err: Line " << Token[i].line << ":There are too few identifier/literals in the expression.\n";
					for (int j = 0; j < NewStack.size(); j++)
						NewStack.pop();
					break;
				}

			}
			else if (current.type == "identifier/literal")
			{
				NewStack.push(current); p++;
			}

		}
		if (NewStack.size() == 1)
			cout << "Final value: " << NewStack.top().name << endl;
		else if (NewStack.size() >  1) {
			cout << "Err: Line " << Token[i].line << ":There are too many terms in the expression. Evaluates to:  ";
			for (int j = 0; j < NewStack.size(); j++)
			{
				cout << NewStack.top().name << " ";
				NewStack.pop();
			}
			cout << endl;
		}
		else if (NewStack.size() < 1)
			cout << "Err: Line " << Token[i].line << ":Incorrect expression. " << endl;
	}
}
void for_loop()
{
	int scfound = 0;
	if (Token[i].name == "for" && Token[i + 1].name == "(")
	{
		i += 2;
		int i1 = i;

		while (i1 != 0 && scfound <4)
		{
			if (Token[i1].name == ";")
			{
				i1++;
				scfound++;
			}
			else if (Token[i1].name != ")")
			{
				i1++; //if i1 is too big???
			}
			else if (Token[i1].name == ")")
			{
				i1 = 0;
			}
		}
		if (scfound != 2)
		{
			cout << "Warning: Line " << Token[i].line << ":invalid use of for loop" << endl;
		}
	}
	if (scfound == 2)
	{
		cout << "Message: 2 x ; found in for loop \n checking declaration list now\n";
		variable_for();
		boolean_expression_forloop();
		cout << "Message: Checking expression list for for loop" << endl;
		//statement list for for loop
		i++;
		if (Token[i].type == "identifier/literal" && Token[i + 1].type == "operator" && Token[i + 1].name == "=") // assignment
		{
			cout << "Message: Assignment statement: \nChecking expression: " << endl;
			i += 2;
			expression_forloop();
			i++;
		}

		if (Token[i].name == "{")
		{
			cout << "Message: Calling nested_block" << endl;
			nested_block();
		}
		else if (Token[i].name != "{")
		{
			cout << "Message: Calling statement function" << endl;
			statement();
			i--;
			cout << "Message: returned from statement func" << endl;
		}

	}

}
int main()
{
	readfile();
	i = 0;
	replace();
	replace1();
	program();

	//typecheck();

	
	getchar();
	return 0;
}
