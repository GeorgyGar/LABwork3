// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память


#include <iostream>
using namespace std;

template <class ValType>
class Stack
{
private:
	ValType* stack;
	int Size;
	int StackIndex;
public:
	Stack(int s = 0);
	Stack(const Stack<ValType>& v);
	~Stack();

	void StackPush(const ValType i);
	ValType& StackGet();
	ValType& StackSee() const;
	bool  StackEmpty();
	int  StackNum();
	void  StacClean();
};

template <class ValType>
Stack<ValType>::Stack(int s)
{
	if (s >= 0)// max?
	{
		Size = s;
		StackIndex = -1;
		stack = new ValType[Size];
	}
	else
		throw "Error";
}


template <class ValType> //конструктор копирования;
Stack<ValType>::Stack(const Stack<ValType>& v)
{
	Size = v.Size;
	StackIndex = v.StackIndex;
	stack = new ValType[v.Size];
	for (int i = 0; i < Size; i++)
		stack[i] = v.stack[i];
}

template <class ValType>
Stack<ValType>::~Stack()
{
	delete[] stack;
}

template <class ValType>
void Stack<ValType>::StackPush(const ValType num)//вставить в Стек;
{
	if (StackIndex + 1 < Size)
	{
		StackIndex++;
		stack[StackIndex] = num;
	}
	else
	{
		Stack<ValType> Copy(*this);
		delete[] stack;
		Size = Size * 2;
		stack = new ValType[Size];
		for (int i = 0; i <= StackIndex; i++)
			stack[i] = Copy.stack[i];
		StackIndex++;
		stack[StackIndex] = num;
	}
}

template <class ValType>//извлечение элемента;
ValType& Stack<ValType>::StackGet()
{
	if (StackIndex != -1)
	{
		StackIndex--;
		return stack[StackIndex + 1];
	}
	else
		throw "Error";
}

template <class ValType>//просмотр верхнего элемента(без удаления);
ValType& Stack<ValType>::StackSee() const
{
	if (StackIndex != -1)
		return stack[StackIndex];
	else
		throw "Error";
}

template <class ValType>//проверка на пустоту;
bool  Stack<ValType>::StackEmpty()
{
	if (StackIndex == -1)
		return 1;
	else
		return 0;
}

template <class ValType>//получение количества элементов в стеке;
int Stack<ValType>::StackNum()
{
	return StackIndex + 1;
}

template <class ValType>//очистка стека;
void Stack<ValType>::StacClean()
{
	Size = 0;
} 