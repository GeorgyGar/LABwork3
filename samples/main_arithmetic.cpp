// реализация пользовательского приложения
#include <arithmetic.h>
int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "=== Калькулятор ===" << endl << endl;
	int N = 1;
	string Primer;
	while (N == 1)
	{
		cout << "Введите задачу: ";
		getline(cin, Primer, '\n');
		cout << endl;
		arithmetic arith(Primer);
		arith.Check();
		arith.BreakLexemes();
		arith.PolishLexemes();
		arith.PolishLexemesSolution();
		cout << "1. Остаться;" << endl;
		cout << "2. Выйти;" << endl;
		cin >> N;
		std::cin.ignore();
		cout << "---------------------------------" << endl << endl;
		Primer.clear();
	}


}
