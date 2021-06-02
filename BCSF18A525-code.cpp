#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool isNotEq(char c)
{
	if (c == '!')
		return true;
	return false;
}
bool isBraces(char c)
{
	if (c == '}' || c == '{')
		return true;
	return false;
}
bool isBrackets(char c)
{
	if (c == ']' || c == '[')
		return true;
	return false;
}
bool isComma(char c)
{
	if (c == ',')
		return true;
	return false;
}
bool iscolon(char c)
{
	if (c == ';')
		return true;
	return false;
}
bool isparen(char c)
{
	if (c == '(' || c == ')')
		return true;
	return false;
}
bool isComment(string s)
{
	if ((int(s[0]) == 47 && int(s[s.length() - 1]) == 47) || (int(s[0]) == 47 && int(s[1]) == 47))
		return true;
	return false;
}
bool isColon(char c)
{
	if (c == ':')
		return true;
	return false;
}
bool isSpace(char c)
{
	if (c == ' ')
		return true;
	return false;
}
bool isKeyword(string s)
{
	if (s == "if" || s == "else" || s == "while" || s == "ret" || s == "write" || s == "read")
		return true;
	return false;
}
bool isDataType(string s)
{
	if (s == "int" || s == "char")
		return true;
	return false;
}
bool isArith(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}
bool isassign(string s)
{
	if (s == ":=")
		return true;
	return false;
}
bool isread(string s)
{
	if (s == ">>")
		return true;
	return false;
}
bool isrel(char c)
{
	if (c == '>' || c == '<' || c == '=')
		return true;
	return false;
}
bool isLetter(char c)
{
	for (int i = 65; i <= 122; i++)
	{
		if (int(c) == i)
		{
			return true;
		}
	}
	return false;
}
bool isNum(char c)
{
	for (int i = 48; i <= 57; i++)
	{
		if (int(c) == i)
		{
			return true;
		}
	}
	return false;
}
bool isid(string s)
{
	bool isIden = false;
	if (isLetter(s[0]))
		isIden = true;
	for (int i = 1; i < s.size(); i++)
	{
		if (isLetter(s[i]) || isNum(s[i]))
			isIden = true;
		else
			isIden = false;
	}
	return isIden;
}
bool isLiteralConst(string s)
{
	if (int(s[0]) == 39 && (isNum(s[1]) || isLetter(s[1])) && int(s[2]) == 39)
		return true;
	return false;
}
bool isSpecialOp(char c)
{
	if (isBraces(c) || isArith(c) || isComma(c) || isparen(c) || isBrackets(c) || isColon(c) || iscolon(c) || isrel(c) || isSpace(c))
		return true;
	return false;
}

int main()
{
	string path;
	cout << "Kindly Enter the path of test file with .cmm extension :";
	getline(cin, path);
	cout << '\n';
	fstream file(path, ios::in);
	if (!file.is_open())
	{
		cout << "Failed to open the file. Invalid path or file doesn't exist!\n";
		exit(0);
	}
	string* keywordArr = new string[50], * datatypeArr = new string[50], * idArr = new string[50], * assignArr = new string[50],
		* arithArr = new string[50], * readArr = new string[50], * relArr = new string[50], * cmtArr = new string[50];
	string* colonArr = new string[50], * bracesArr = new string[50], * parenArr = new string[50], * commaArr = new string[50],
		* bracketsArr = new string[50], * varDecOpArr = new string[50], * litConstArr = new string[50];
	int keywordCount = 0, datatypeCount = 0, idCount = 0, assignCount = 0, arithCount = 0, readCount = 0, relCount = 0, cmtCount = 0;
	int colonCount = 0, bracesCount = 0, parenCount = 0, commaCount = 0, bracketsCount = 0, varDecOpCount = 0, litConstCount = 0;
	char ch;
	char colonSlash = NULL;
	string lexeme = "";
	while (!file.eof())
	{
		ch = file.get();
		if (isColon(ch) || isNotEq(ch))
		{
			colonSlash = ch;
		}
		if (ch == '\n')
		{
			continue;
			lexeme = "";
		}
		if (!isSpecialOp(ch))
		{
			lexeme = lexeme + ch;
		}
		else if (isKeyword(lexeme))
		{
			keywordArr[keywordCount++] = lexeme;
			lexeme = "";
		}
		else if (isDataType(lexeme))
		{
			datatypeArr[datatypeCount++] = lexeme;
			lexeme = "";
		}
		else if (isid(lexeme))
		{
			idArr[idCount++] = lexeme;
			lexeme = "";
		}
		else if (isread(lexeme))
		{
			readArr[readCount++] = lexeme;
			lexeme = "";
		}
		else if (isLiteralConst(lexeme))
		{
			litConstArr[litConstCount++] = lexeme;
			lexeme = "";
		}
		else if (isComment(lexeme))
		{
			cmtArr[cmtCount++] = lexeme;
			lexeme = "";
		}

		if (isSpecialOp(ch))
		{
			if (colonSlash == ':' && ch == '=')
			{
				assignArr[assignCount++] = ":=";
				lexeme = "";
			}
			else if (isArith(ch))
			{
				arithArr[arithCount++] = ch;
				lexeme = "";
			}
			else if (isrel(ch))
			{
				relArr[relCount++] = ch;
				lexeme = "";
			}
			else if (colonSlash == '!' && ch == '=')
			{
				relArr[relCount++] = "!=";
				lexeme = "";
			}
			else if (isColon(ch))
			{
				varDecOpArr[varDecOpCount++] = ch;
				lexeme = "";
			}
			else if (isparen(ch))
			{
				parenArr[parenCount++] = ch;
				lexeme = "";
			}
			else if (isBraces(ch))
			{
				bracesArr[bracesCount++] = ch;
				lexeme = "";
			}
			else if (isBrackets(ch))
			{
				bracketsArr[bracketsCount++] = ch;
				lexeme = "";
			}
			else if (isComma(ch))
			{
				commaArr[commaCount++] = ch;
				lexeme = "";
			}
		}
	}

	file.close();

	file.open("words.txt", ios::out);
	for (int i = 0; i < 50; i++)
	{
		if (keywordArr[i] != "")
		{
			file << "< KEYWORD, " << keywordArr[i] << " >" << endl;
		}
		if (datatypeArr[i] != "")
		{
			file << "< DATATYPE, " << datatypeArr[i] << " >" << endl;
		}
		if (idArr[i] != "")
		{
			file << "< ID, " << idArr[i] << " >" << endl;
		}
		if (assignArr[i] != "")
		{
			file << "< ASSIGN_OP, " << assignArr[i] << " >" << endl;
		}
		if (arithArr[i] != "")
		{
			file << "< ARITHMETIC_OP, " << arithArr[i] << " >" << endl;
		}
		if (readArr[i] != "")
		{
			file << "< READ_OP, " << readArr[i] << " >" << endl;
		}
		if (relArr[i] != "")
		{
			file << "< REL_OP, " << relArr[i] << " >" << endl;
		}
		if (cmtArr[i] != "")
		{
			file << "< COMMENT, " << cmtArr[i] << " >" << endl;
		}
		if (colonArr[i] != "")
		{
			file << "< colon, " << colonArr[i] << " >" << endl;
		}
		if (bracesArr[i] != "")
		{
			file << "< BRACES, " << bracesArr[i] << " >" << endl;
		}
		if (parenArr[i] != "")
		{
			file << "< paren, " << parenArr[i] << " >" << endl;
		}
		if (commaArr[i] != "")
		{
			file << "< COMMA, " << commaArr[i] << " >" << endl;
		}
		if (bracketsArr[i] != "")
		{
			file << "< BRACKETS, " << bracketsArr[i] << " >" << endl;
		}
		if (varDecOpArr[i] != "")
		{
			file << "< VAR_DEV_OP, " << varDecOpArr[i] << " >" << endl;
		}
		if (litConstArr[i] != "")
		{
			file << "< LITERAL_CONST, " << litConstArr[i] << " >" << endl;
		}
	}
	file.close();

	file.open("symboltable.txt", ios::out);

	for (int i = 0; i < 50; i++)
	{
		if (idArr[i] != "")
		{
			file << idArr[i] << endl;
		}
	}
	file.close();
	cout << "Lexical Analysis complete successfully!\n";

	return 0;
}
