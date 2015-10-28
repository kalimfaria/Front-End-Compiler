#include <minmax.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
struct symbol
{
	string value;
	string type;
};
vector <symbol> SymbolTable;
bool isFloat(string myString) {
	stringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}
unsigned int levenshtein_distance(string s1, string s2) {
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);

	for (unsigned int i = 0; i < prevCol.size(); i++)
		prevCol[i] = i;
	for (unsigned int i = 0; i < len1; i++) {
		col[0] = i + 1;
		for (unsigned int j = 0; j < len2; j++)
			col[j + 1] = min(min(1 + col[j], 1 + prevCol[1 + j]),
			prevCol[j] + (s1[i] == s2[j] ? 0 : 1));
		col.swap(prevCol);
	}
	return prevCol[len2];
}
struct macros
{
	int pos;
	string value;
	string name;
};
string readFile(string filename)								//Reading file in a string
{
	string line;
	string file;
	string text;
	ifstream myfile;
	myfile.open(filename.c_str());
	if (!myfile)
	{
		cout << "Error opening file\n";
		getchar();
		exit(0);
	}
	else
	{
		while (getline(myfile, line, '\0'))
		{
			file += line;
		}
	}
	return file;
}
void removeComments(string &file)								//Removing Comments
{
	for (int k = 0; k < file.length(); k++)
	{
		if (file[k] == '/')
		{
			if (file[k + 1] == '/')
			{
				unsigned pos = file.find("\n", k);
				file.erase(file.begin() + k, file.begin() + pos);
			}
			else if (file[k + 1] == '*')
			{
				unsigned pos = file.find("*/", k);
				int counter = 0;
				for (int i = k; i< pos; i++)
				{
					if (file[i] == '\n')
						counter++;
				}
				for (int i = 0; i < counter; i++)
					file.insert(pos + 3, "\n");
				//cout << file << endl;
				file.erase(file.begin() + k, file.begin() + pos + 2);
			}
		}
	}
}
void removeSpaces(string &file)						//Removing Spaces
{
	for (int i = 0; i < file.length() - 1; i++)
	{
		while (isspace(file[i]) && file[i] != '\n')
		{
			file.erase(file.begin() + i);			//Removing all whitespaces
			if (!(isspace(file[i]) && file[i] != '\n'))
			{
				file.insert(file.begin() + i, ' ');	//Inserting a single space
				i++;
			}
		}
	}
	for (int i = 0; i < file.length() - 1; i++)
	{
		if (file[i] == '#')

		while (isspace(file[i + 1]))
			file.erase(file.begin() + i + 1);			//Removing all whitespaces
	}

}
void addSeparators(string &file)
{
	const char *brackets = "{}[]();,?:\"";
	const char *singleOperators = "!+-*/><=%";
	const char *doubleOperators = "&|";

	for (int i = 1; i < file.length() - 1; i++)
	{
		char *c = &file[i];
		if (strchr(brackets, *c))
		{
			if (!isspace(file[i - 1]))
			{

				file.insert(i, string(" "));
				i++;
				c++;
			}
			if (!isspace(file[i + 1]))
			{
				file.insert(i + 1, string(" "));
				i++;
				c++;
			}
		}
		if (strchr(singleOperators, *c))
		{
			if (!isspace(file[i - 1]))
			{
				file.insert(i, string(" "));
				i++;
				c++;
			}
			if (file[i] == file[i + 1])
			{
				file.insert(i + 2, string(" "));
				i++; c++; c++; i++;
			}
			else if (file[i + 1] == '=')
			{
				file.insert(i + 2, string(" "));
				i++; c++;
			}
			else
			{
				file.insert(i + 1, string(" "));
				i++;
				c++;
			}
		}
		if (strchr(doubleOperators, *c))
		{
			if (file[i] == file[i + 1])
			{
				file.insert(i, string(" "));
				i++;
				c++;
			}
			if (!isspace(file[i + 1]))
			{
				file.insert(i + 2, string(" "));
				i++;
				c++;
			}
		}

	}
}
void replaceMacros(string &file)
{
	int i = 1;
	vector <macros> mVec;
	while (i > 0)
	{
		int pos = file.find("#define ", i); // syntax is hard coded
		if (pos > 0) {
			i = pos + 1; // to find the next character
			macros One;
			One.pos = pos;
			int space = file.find(" ", pos);
			int space2 = file.find(" ", space + 1);
			One.name = file.substr(space + 1, space2 - space - 1);
			One.value = file.substr(space2 + 1, file.find("\n", space2) - space2 - 1);
			mVec.push_back(One);
		}
		else
			break;
	}
	for (int i = 0; i < mVec.size(); i++)
	{
		for (int j = 0; j < SymbolTable.size(); j++)
		if (mVec[i].name.compare(SymbolTable[j].value) == 0)
			SymbolTable[j].value = mVec[i].value;
	}
}
void findErrors(string &file)
{
	string keywords[] = { "const", "continue", "default", "double", "break", "extern", "enum", "goto", "return", "short", "long", "struct", "for", "if", "#include", "#define", "do", "while", "else", "else if", "bool", "int", "float", "string", "char", "main", "printf", "scanf", "void", "switch", "case", "malloc", "free" }; //33
	vector<string> result;
	const char * str = file.c_str();
	do
	{
		const char *begin = str;
		while ((*str != ' ' && *str != '\n' && *str != '\t') && *str)
			str++;
		if (*str == '\n') result.push_back("ANOTHER LINE");
		result.push_back(string(begin, str));
	} while (0 != *str++);

	int line = 1;
	for (int i = 0; i < result.size(); i++) {
		if (result[i].size() > 0 && result[i].compare("ANOTHER LINE") == 0)
		{
			line++; i++;
		}

		for (int k = 0; k < 33; k++)
		{
			if (levenshtein_distance(result[i], keywords[k]) == 1 && keywords[k].compare(result[i]) != 0)
				cout << line << " Warning: " << result[i] << " should be " << keywords[k] << endl;
		}
	}

}
void Tokenise(string &file)
{
	string datatype[] = { "int", "float", "string", "char", "bool", "double", "long", "short" }; //8
	string op[] = { "+", "-", "=", "++", "--", "+=", "-=", "*", "/", "/=", "*=" };//11
	string rel[] = { ">", "<", "<=", ">=", "!=", "!", "==" }; // 7
	string log[] = { "&&", "||" }; // 2
	string braces[] = { "{", "}" }; // 2
	string sqbrackets[] = {"[","]"};//2
	string parantheses[] = { "(", ")" }; // 2
	string separator = ";"; // 1
	string keywords[] = {  "#define","if", "else" , "main", "#include", "return", "printf", "scanf", "const", "continue", "default", "break", "extern", "enum", "goto", "struct" }; //15
	string comma = ",";
	string returntype = "void";
	vector <string> result;
	int check;
	const char * str = file.c_str();
	do
	{
		const char *begin = str;
		while ((*str != ' ' && *str != '\n' && *str != '\t') && *str)
			str++;
		result.push_back(string(begin, str));
		if (*str == '\n')
			result.push_back("\nNEWLINE");
	} while (0 != *str++); // tokens in str
	for (int i = 0; i < result.size(); i++) {
		bool found = false; symbol n;
		n.type = "identifier/literal";
		n.value = result[i];
		check = 1;
		if (!found && result[i].compare("\nNEWLINE") == 0) {
			found = true;
			n.type = "newline";
		}
		if (n.value.size()> 0 && n.value[0] == '\'' && n.value[2] == '\'')
		{			
			n.type = "char";
			found = true;
		}		
		if (n.value == "\"")
		{
			n.value = "";
			while (i < result.size() && check == 1)
			{
				i++;
				if (result[i] == "\"")
					check = 0;
				else
					n.value = n.value + " " + result[i];
			}
			n.type = "string";
			n.value.erase(0, 1);
			n.value = "\"" + n.value + "\"";
			found = true;
		}
		for (int j = 0; j < 8 && !found; j++)
		if (result[i].compare(datatype[j]) == 0)
		{
			found = true;
			n.type = "datatype";
		}
		if (!found) {
			for (int j = 0; j < 11 && !found; j++)
			if (result[i].compare(op[j]) == 0)
			{
				found = true;
				n.type = "operator";
			}
		}
		if (!found) {
			for (int j = 0; j < 7 && !found; j++)
			if (result[i].compare(rel[j]) == 0)
			{
				found = true;
				n.type = "relational_operator";
			}
		}
		if (!found) {
			for (int j = 0; j < 2; j++)
			if (result[i].compare(log[j]) == 0)
			{
				found = true;
				n.type = "logical_operator";
				break;
			}
		}
		if (!found) {
			for (int j = 0; j < 2; j++)
			if (result[i].compare(braces[j]) == 0)
			{
				found = true;
				n.type = "brace";
				break;
			}
		}
		if (!found) {
			for (int j = 0; j < 2; j++)
			if (result[i].compare(sqbrackets[j]) == 0)
			{
				found = true;
				n.type = "square brackets";
				break;
			}
		}
		if (!found) {
			for (int j = 0; j < 2 && !found; j++)
			if (result[i].compare(parantheses[j]) == 0)
			{
				found = true;
				n.type = "paranthesis";
			}
		}
		if (!found) {
			for (int j = 0; j < 15 && !found; j++)
			if (result[i].compare(keywords[j]) == 0)
			{
				found = true;
				n.type = "keywords";
			}
		}
		if (!found) {
			if (result[i].compare(separator) == 0)
			{
				found = true;
				n.type = "separator";
			}
		}
		if (!found) {
			if (result[i].compare(comma) == 0)
			{
				found = true;
				n.type = "comma";
			}
		}
		if (!found)
		{
			int isSpace = 0;
			for (int k = 0; k < result[i].length(); k++) {
				if (isspace(result[i][k]) == 8)
					isSpace += 0;
				else
					isSpace += 1;
			}
			if (isSpace == 0)
			{
				found = true;
				n.type = "space";
			}
		}
		if (!found)
		{
			if (n.value == returntype)
			{
				n.type = "returntype";
				found = true;
			}
		}
		if (!found)
		{
			for (int k = 0; k < result[i].length(); k++)
			{
				if (isdigit(result[i][k]))
					found = true;
				else
				{
					found = false;
					k = result[i].length() + 1;
				}
			}
			if (found)
				n.type = "number";
			if (!found)
			{
				if (isFloat(result[i]))
				{
					n.type = "float";
					found = true;
				}
			}

			if (!found) // if it is identifier
			{
				if ((result[i][0] >= 'A' && result[i][0] <= 'Z') || (result[i][0] >= 'a' && result[i][0] <= 'z'))
				{
					for (int k = 0; k < result[i].length(); k++)
					if (!((result[i][k] >= '0' && result[i][k] <= '9') || (result[i][k] >= 'A' && result[i][k] <= 'Z') || (result[i][k] >= 'a' && result[i][k] <= 'z')))
					{
						int count = 1;
						for (int j = 0; j < i; j++)
						if (result[j].compare("\nNEWLINE") == 0)
							count++;
						cout << count << " Incorrect identifier syntax: " << result[i] << endl;
					}
				}
				else
				{
					int count = 1;
					// counting the line number
					for (int j = 0; j < i; j++)
					if (result[j].compare("\nNEWLINE") == 0)
						count++;
					cout << count << " Incorrect identifier syntax: " << result[i] << endl;
				}
			}
		}
		SymbolTable.push_back(n);

	
	}
	ofstream tokens;
	tokens.open("Tokens.txt");
	const int width = 15;
	int linenum = 1;
	for (int i = 0; i < SymbolTable.size(); i++)
	{
		if (SymbolTable[i].type == "newline")
			linenum++;
		if (!(SymbolTable[i].type == "space" || SymbolTable[i].type == "newline"))
				tokens << linenum << " " << SymbolTable[i].type << " " << SymbolTable[i].value << endl;
	}
	tokens.close();
}
int main(int argc, char* argv[])
{
	string file;
	string filename = "Source.txt ";					//File Name
	file = readFile(filename);
	removeComments(file);							//Removing Comments
	removeSpaces(file);
	addSeparators(file);
	findErrors(file);
	Tokenise(file);
	replaceMacros(file);
	ofstream myfile;
	myfile.open("Output.cpp");
	int linenum = 1;
	for (int i = 0; i < SymbolTable.size(); i++)
	{
		if (SymbolTable[i].value.compare("NEWLINE") == 0)
		{
			myfile << "\n";
			i++;
		}
		else
			myfile << SymbolTable[i].value;
		myfile << ' ';
	}
	myfile.close();
	cout << "Program is ending." << endl;
	getchar();
	return 0;
}