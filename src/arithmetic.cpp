// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <sstream>



Lexema::Lexema(string V)
{
	Val = V;
	int i = Val.size();
	if (i != 1)
	{
		Num = std::stod(Val); //Если число;
		type = 1;
	}
	else
	{
		if (isalpha(Val[0])) // Если переменная;
		{
			type = 3;
			Num = 0;
		}
		else
		{
			if (isdigit(Val[0]))//Если число;
			{
				type = 1;
				Num = std::stod(Val);
			}
			else
			{
				switch (Val[0])//Если оператор;
				{
				case '(':
					Priority = 0;
					type = -1;
					Num = 0;
					break;
				case ')':
					Priority = 0;
					type = 0;
					Num = 0;
					break;
				case '+':
					Priority = 1;
					type = 2;
					Num = 0;
					break;
				case '-':
					Priority = 1;
					type = 2;
					Num = 0;
					break;
				case '*':
					Priority = 2;
					type = 2;
					Num = 0;
					break;
				case '/':
					Priority = 2;
					type = 2;
					Num = 0;
					break;
				default:
					cout << "Лексема не распознана" << endl;
					throw "Error";
					break;
				}
			}
		}
	}
}

Lexema::Lexema(const Lexema& Lex)
{
	Val = Lex.Val;
	Priority = Lex.Priority;
	Num = Lex.Num;
	type = Lex.type;
}

int Lexema::operator==(const char& v) const
{
	if (Val[0] == v)
		return 1;
	else
		return 0;
}

int Lexema::operator!=(const char& v) const
{
	if (Val[0] == v)
		return 0;
	else
		return 1;
}

arithmetic::arithmetic(string str)
{
	Input = str;
	Size = 0;
	Polish = str;
	Res = 0.0;
	for (int i = 0; i < Input.size(); i++) //колечество лексем ;
	{
		if (Input[i] != ' ')
			Size++;
		if (Input[i] == '.')
			Input[i] = ',';
	}
	LexInput = new Lexema[Size];
	LexPolish = new Lexema[Size];
}


void arithmetic::BreakLexemes()//Разбить на Лексемы;
{
	int reg = 0;
	string Copystr;
	//LexInput = new Lexema[Size];


	for (int i = 0; i < Input.size(); i++)//заполнение массива Лексем;
	{
		if (isalpha(Input[i]))
		{
			string per;
			cout << "Введите значение переменной " << Input[i] << ": ";
			cin >> per;
			for (int i = 0; i < per.size(); i++) //колечество лексем ;
			{
				if (per[i] == '.')
					per[i] = ',';
			}
			Copystr = Input[i];
			LexInput[reg] = Lexema(Copystr);
			LexInput[reg].type = 1;
			LexInput[reg].Num = stod(per);
			LexInput[reg].Val = 'a';
			Copystr.clear();
			reg++;
		}
		else
		{
			if (Input[i] != ' ')
			{
				if (isdigit(Input[i]))
				{
					int index = i + 1;
					while (isdigit(Input[index]) || Input[index] == '.' || Input[index] == ',')//Конец числа;
					{
						if (Input[index] != '/0')
							index++;
					}
					Copystr.insert(0, Input, i, index - i);
					//cout << Copystr;
					LexInput[reg] = Lexema(Copystr);
					Copystr.clear();
					reg++;
					i = index - 1;
				}
				else
				{
					Copystr = Input[i];
					LexInput[reg] = Lexema(Copystr);
					Copystr.clear();
					reg++;
				}
			}
		}
	}
	Size = reg;

	int ind = 0;
	Lexema* CopyLexInput = new Lexema[Size];
	for (int k = 0; k < Size; k++)
		CopyLexInput[k] = LexInput[k];
	for (int i = 0; i < Size; i++)
	{
		if ((LexInput[ind] == '-') && ((LexInput[ind - 1]).type != 1) && LexInput[ind - 1] != ')')//выделяет отрицательные числа, как одну лексему;
		{
			CopyLexInput[i].Num = (-1) * CopyLexInput[i + 1].Num;
			CopyLexInput[i].Val = '-' + CopyLexInput[i + 1].Val;
			CopyLexInput[i].type = 1;
			for (int j = i; j < Size; j++)
			{
				if (j + 2 < Size)
					CopyLexInput[j + 1] = CopyLexInput[j + 2];
			}
			Size--;
			ind++;
		}
		if ((LexInput[ind] == '+') && (LexInput[ind - 1]).type != 1 && LexInput[ind - 1] != ')')
		{
			CopyLexInput[i].Val = CopyLexInput[i + 1].Val;
			CopyLexInput[i].type = 1;
			CopyLexInput[i].Num = CopyLexInput[i + 1].Num;
			for (int j = i; j < Size; j++)
			{
				if (j + 2 < Size)
					CopyLexInput[j + 1] = CopyLexInput[j + 2];
			}
			Size--;
			ind++;
		}
		ind++;
	}

	for (int k = 0; k < Size; k++)
		LexInput[k] = CopyLexInput[k];

	cout << endl << " Массив лексем: " << endl;
	for (int i = 0; i < Size; i++)
	{
		std::cout << "|" << LexInput[i] << "|" << "   ";
	}
}

void arithmetic::PolishLexemes()
{
	Stack<Lexema> stack(Size);
	int PolishIndex = 0;

	delete[] LexPolish;
	LexPolish = new Lexema[Size];

	for (int i = 0; i < Size; i++)
	{
		if (LexInput[i].type == 1)
		{
			LexPolish[PolishIndex] = LexInput[i];
			PolishIndex++;
		}
		if (LexInput[i].type == 2)
		{
			if (stack.StackEmpty() == true)
			{
				stack.StackPush(LexInput[i]);
			}
			else
			{
				if (stack.StackSee().Priority != 0)
				{

					while (LexInput[i].Priority <= stack.StackSee().Priority && stack.StackSee().Priority != 0)
					{
						if (stack.StackEmpty() == false)
						{
							LexPolish[PolishIndex] = stack.StackGet();
							PolishIndex++;
						}
						if (stack.StackNum() == 0)
							break;
					}

					stack.StackPush(LexInput[i]);
				}

				if (LexInput[i].Priority > stack.StackSee().Priority && stack.StackSee().Priority != 0)
				{
					stack.StackPush(LexInput[i]);

				}

				if (stack.StackSee().Priority == 0)
				{
					stack.StackPush(LexInput[i]);
				}
			}
		}
		if (LexInput[i].type == -1)
		{
			stack.StackPush(LexInput[i]);
		}
		if (LexInput[i].type == 0)
		{
			int index = stack.StackNum();
			for (int i = 0; i < index; i++)
			{
				if (stack.StackSee() != '(')
				{
					LexPolish[PolishIndex] = stack.StackGet();
					PolishIndex++;
				}
				else
				{
					stack.StackGet();
					index = i;
				}
			}
		}

	}

	if (stack.StackEmpty() == false)
	{
		int index2 = stack.StackNum();
		for (int i = Size - index2; i < Size; i++)
		{
			if (stack.StackSee() != '(' && stack.StackSee() != ')')
			{
				LexPolish[PolishIndex] = stack.StackGet();
				PolishIndex++;
			}
		}
	}
	cout << endl << " Массив лексем в польской записи: " << endl;
	for (int i = 0; i < PolishIndex; i++)
	{
		std::cout << "|" << LexPolish[i] << "|" << "   ";

	}
	Size = PolishIndex;
}

double arithmetic::PolishLexemesSolution()
{
	Stack<double> stack(Size);
	int index = 0;
	double res = 0;
	while (index < Size)
	{
		if (LexPolish[index].type == 1)
		{
			stack.StackPush(LexPolish[index].Num);
			//cout << endl << "вывожу число: " << LexPolish[index].Num << endl;
		}
		else
		{
			if (LexPolish[index] == '+')
			{
				double a = stack.StackGet();
				double b = stack.StackGet();
				stack.StackPush(b + a);
				res = a + b;
			}
			if (LexPolish[index] == '-')
			{
				double a = stack.StackGet();
				double b = stack.StackGet();
				stack.StackPush(b - a);
				res = b - a;
			}
			if (LexPolish[index] == '*')
			{
				double a = stack.StackGet();
				double b = stack.StackGet();
				stack.StackPush(b * a);
				res = b * a;
			}
			if (LexPolish[index] == '/')
			{
				double a = stack.StackGet();
				double b = stack.StackGet();
				stack.StackPush(b / a);
				res = b / a;
			}
		}
		index++;
		//cout << res << endl;
	}
	Res = stack.StackSee();
	cout << endl << " Ответ = " << Res << endl;
	return Res;
}


void arithmetic::Check() const
{
	int index = 0, SecIndex = 0;
	while (index < Input.size())
	{

		if (Input[index] == '(')
			SecIndex++;
		if (Input[index] == ')')
			SecIndex--;
		index++;
	}

	if (SecIndex != 0)
	{
		cout << "ошибка скобок" << endl;
		throw "Error";
	}

}
