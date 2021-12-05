// объявление функций и классов для вычисления арифметических выражений
#include "stack.h"
#include <string>
#include <vector>

struct Lexema
{
	string Val;   //значение лексемы;
	int Priority; //приоритет лексемы;
	double Num;   //значение числа;
	int type;     //Тип лексемы: 0 - скобки;
				  //             1 - число;
				  //             2 - оператор;
				  //             3 - переменная.
	Lexema() {}
	Lexema(string V);
	Lexema(const Lexema& Lex);
	char ReVal() { return Val[0]; }
	//double ReNum() { return Num; }
	int operator==(const char& v) const;
	int operator!=(const char& v) const;
	friend ostream& operator<<(ostream& out, const Lexema& Lex)
	{
		out << Lex.Val;
		return out;
	}
	~Lexema() {}


};


class arithmetic 
{
private:
	string Input;
	string Polish;
	double Res;
	Lexema* LexInput;  //массив лексем;
	Lexema* LexPolish; //Массив лексем в польской записи;
	int Size;

public:
	arithmetic() {}
	arithmetic(string);
	void BreakLexemes();
	void PolishLexemes();
	double PolishLexemesSolution();
	void Check() const;
	~arithmetic() { 
		delete[] LexInput;
	delete[] LexPolish;
	}
};