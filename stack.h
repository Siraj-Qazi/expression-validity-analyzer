#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <cctype>
#define and &&
#define or ||

class Stack
{
public:
	char* _stack;
	// int* _indexArray;
	int _size;
	int _index;

	Stack() : _index(-1), _size(0)
	{
		launch();
	}

	void sizeControl()
	{
		delete _stack;
		_index = -1;
		system("cls");
		std::cout << "\n\n STACK IMPLEMENTATION - C++ \n";
		std::cout << "\n @SQ\n";
		system("color 0a");
		std::cout << "\n Enter your desired stack size: ";
		std::cin >> _size;
		_stack = new char[_size];
		stackFunctions();
	}

	void launch()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n\n EXPRESSION VALIDITY ANALYZER - C++ \n";
		std::cout << "\n @SQ\n";
		std::cout << "\n Press 1 - 3: \n"
			<< "\n 1 - Stack Operations"
			<< "\n 2 - Expression validity check"
			<< "\n 3 - Exit\n ";

		char choice = _getch();
		switch (choice)
		{
		case '1':
			sizeControl();
			break;

		case '2':
			expressionValidityCheck();
			break;

		case '3':
			exit(0);

		default:
			std::cout << "\n Press 1-3 Only. <PRESS ANY KEY> ";
			_getch();
			launch();

		}
	}

	void stackFunctions()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n\n STACK IMPLEMENTATION - C++ \n";
		std::cout << "\n @SQ\n";
		std::cout << "\n Press 1 - 4: \n"
			<< "\n 1 - Push an element onto the stack"
			<< "\n 2 - Pop an element from the stack"
			<< "\n 3 - Create new stack"
			<< "\n 4 - Exit\n ";

		char input;
		char popped;
		char choice = _getch();
		switch (choice)
		{
		case '1':
			std::cout << "\n\n Enter the value to push onto the stack: ";
			std::cin >> input;
			push(input);
			Sleep(1000);
			stackFunctions();
			break;

		case '2':
			popped = pop();
			Sleep(1000);
			stackFunctions();
			break;

		case '3':
			sizeControl();
			break;

		case '4':
			exit(0);

		default:
			std::cout << "\n Please press 1-3 only. <PRESS ANY KEY> ";
			_getch();
			stackFunctions();
		}
	}
	void push(char x)
	{
		if (isFull())
		{
			std::cout << "\n Error! The stack is full. \n";
			_getch();
			stackFunctions();
		}

		_stack[++_index] = x;
		std::cout << "\n '" << x << "'pushed to stack. ";
	}

	char pop()
	{
		if (isEmpty())
		{
			std::cout << "\n Error! The stack is Empty. \n";
			_getch();
			stackFunctions();
		}

		char popped = _stack[_index];
		_stack[_index--] = -1;

		std::cout << "\n '" << popped << "' popped from stack.";
		return popped;
	}

	void expressionValidityCheck()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n\n ALEBRAIC EXPRESSION VALIDITY ANALYSIS - C++ \n";
		std::cout << "\n @SQ\n";
		std::cin.clear();
		std::string expression;
		std::cout << "\n Enter the expression to test:\n ";
		std::getline(std::cin, expression);

		delete _stack;
		_index = -1;
		_size = expression.size();
		_stack = new char[_size];
		// _indexArray = new int[_size];

		for (int i = 0; i < _size; ++i)
		{
			if (!(isdigit(expression[i]) or isOpeningBrace(expression[i]) or isClosingBrace(expression[i]) or isValid(expression[i])))
			{
				std::cout << "\n\n Entered expression was: \n " << expression;
				std::cout << "\n\n Invalid Expression! <Contains an invalid character>\n";
				_getch();
				launch();
			}
		}

		for (int i = 0; i < _size; ++i)
		{
			if (isOpeningBrace(expression[i]))
				push(expression[i]);
				
			else if (isClosingBrace(expression[i]) and !isEmpty())
			{
				//if (!isCorrespondingOpeningBrace(expression[i], _stack[_indexArray[j]]))

				if (!isCorrespondingOpeningBrace(expression[i], _stack[_index]))
				{
					std::cout << "\n\n Entered expression was: \n " << expression;
					std::cout << "\n\n Invalid Expression! <Not corresponding brackets>\n";
					_getch();
					launch();
				}
				else
					pop();
			}
				
			else if (isClosingBrace(expression[i]) and isEmpty())
			{
				std::cout << "\n\n Entered expression was: \n " << expression;
				std::cout << "\n\n Invalid Expression! <Unequal number of brackets>\n";
				_getch();
				launch();
			}

		}

		std::cout << "\n\n Entered expression was: \n " << expression;

		if (isEmpty())
		{
			std::cout << "\n\n ### This is a valid expression. ###";
			_getch();
			launch();
		}
		else
		{
			std::cout << "\n Invalid Expression! \n";
			_getch();
			launch();
		}
		_getch();
	}

	bool isFull()
	{
		return _index == _size - 1;
	}

	bool isEmpty()
	{
		return _index == -1;
	}

	static bool isOpeningBrace(char x)
	{
		return x == '{' or x == '[' or x == '(';
	}

	static bool isClosingBrace(char x)
	{
		return x == '}' or x == ']' or x == ')';
	}

	static bool isValid(char x)
	{
		return isalpha(x) or x == '+' or x == '-' or x == '*' or x == '/' or x == '!' or x == '<' or x == '>' or x == '.';	
	}

	static bool isCorrespondingOpeningBrace(char test, char corresponding)
	{
		if (test == '}' and corresponding == '{')
			return true;
		else if (test == ')' and corresponding == '(')
			return true;
		else if (test == ']' and corresponding == '[')
			return true;
		else
			return false;
	}
};