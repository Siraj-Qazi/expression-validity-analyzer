#pragma once
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
	int _size;
	int _index;
	char _stackTop;

	Stack() : _index(-1), _size(0)
	{
		start();
	}

	void start()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n\n STACK-BASED ALGEBRAIC EXPRESSION ANALYZER\n";
		std::cout << "              VERSION 2.0\n";
		std::cout << "\n @SQ\n";
		std::cout << "\n Press 1 - 3: \n"
			<< "\n 1 - Stack Operations"
			<< "\n 2 - Expression validity check & Postfix Conversion"
			<< "\n 3 - Exit\n ";

		char choice = _getch();
		switch (choice)
		{
		case '1':
			createStack();
			break;

		case '2':
			expressionValidityCheck();
			break;

		case '3':
			exit(0);

		default:
			std::cout << "\n Press 1-3 Only. <PRESS ANY KEY> ";
			_getch();
			start();

		}
	}

	void createStack()
	{
		delete _stack;
		_index = -1;
		system("cls");
		std::cout << "\n\n STACK IMPLEMENTATION \n";
		std::cout << "     VERSION 2.0\n";
		std::cout << "\n @SQ\n";
		system("color 0a");
		std::cout << "\n Enter your desired stack size: ";
		std::cin >> _size;
		_stack = new char[_size];
		stackFunctions();
	}

	void stackFunctions()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n\n STACK IMPLEMENTATION\n";
		std::cout << "      VERSION 2.0\n";
		std::cout << "\n @SQ\n";
		std::cout << "\n Press 1 - 5: \n"
			<< "\n 1 - Push an element onto the stack"
			<< "\n 2 - Pop an element from the stack"
			<< "\n 3 - Create new stack"
			<< "\n 4 - Return to Main Menu"
			<< "\n 5 - Exit\n ";

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
			createStack();
			break;

		case '4':
			start();
			break;

		case '5':
			exit(0);

		default:
			std::cout << "\n Please press 1-5 only. <PRESS ANY KEY> ";
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

		_stackTop = _stack[++_index] = x;
		std::cout << "\n '" << x << "' pushed to stack. ";
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
		_stack[_index--] = '0';
		_stackTop = _stack[_index];
		std::cout << "\n '" << popped << "' popped from stack.";
		return popped;
	}

	char peek()
	{
		return _stackTop;
	}

	void expressionValidityCheck()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n\n ALEBRAIC EXPRESSION VALIDITY ANALYZER \n";
		std::cout << "              VERSION 2.0\n";
		std::cout << "\n @SQ\n";
		/*	std::cin.clear();
		std::string expression;*/

		char* expression = new char[100];
		std::cout << "\n Enter the expression to test:\n ";
		/*std::getline(std::cin, expression);*/

		// #The _getch() input loop
		int i = 0;
		char c = _getch();
		while (c != 13)
		{
			if (c == 8)  // Allow Backspace for erasing characters
			{
				if (i == 0);  // Do nothing
				else
				{
					expression[--i] = '\0';
					std::cout << "\b \b";
				}
			}
			else
			{
				expression[i++] = c;
				std::cout << c;
			}
			c = _getch();
		}
		expression[i] = '\0';

		delete _stack;
		_index = -1;
		_size = i;
		_stack = new char[_size];

		for (int i = 0; i < _size; ++i)
		{
			if (!(isdigit(expression[i]) or isOpeningBrace(expression[i]) or isClosingBrace(expression[i]) or isValid(expression[i])))
			{
				std::cout << "\n\n Entered expression was: \n " << expression;
				std::cout << "\n\n Invalid Expression! <Contains an invalid character>\n";
				_getch();
				start();
			}
		}

		for (int i = 0; i < _size; ++i)
		{
			if (isOpeningBrace(expression[i]))
				push(expression[i]);

			else if (isClosingBrace(expression[i]) and !isEmpty())
			{
				if (!isCorrespondingOpeningBrace(expression[i], _stack[_index]))
				{
					std::cout << "\n\n Entered expression was: \n " << expression;
					std::cout << "\n\n Invalid Expression! <Not corresponding brackets>\n";
					_getch();
					start();
				}
				else
					pop();
			}

			else if (isClosingBrace(expression[i]) and isEmpty())
			{
				std::cout << "\n\n Entered expression was: \n " << expression;
				std::cout << "\n\n Invalid Expression! <Unequal number of brackets>\n";
				_getch();
				start();
			}

		}

		std::cout << "\n\n Entered expression was: \n " << expression;

		if (isEmpty())
		{
		time:
			std::cout << "\n\n ### This is a valid expression. ###\n\n";
			std::cout << "\n Press 1-2: \n"
				<< "\n 1 - Proceed to convert this expression to postfix notation"
				<< "\n 2 - Go to Main Menu\n\n";
			char choice = _getch();
			switch (choice)
			{
			case '1':
				convertToPostFix(expression, _size);
				break;

			case '2':
				start();
				break;

			default:
				std::cout << "\n Press 1-2 Only! ";
				Sleep(1000);
				goto time;
			}

			start();
		}
		else
		{
			std::cout << "\n Invalid Expression! \n";
			_getch();
			start();
		}
		_getch();
	}

	void convertToPostFix(char* expression, int size)
	{
		system("cls");
		system("color 0a");
		std::cout << "\n\n Convert Infix to PostFix Notation - C++ \n";
		std::cout << "\n @SQ\n";
		std::cout << "\n";

		// Delete any current stack in memory
		delete _stack;
		_index = -1;
		_size = size;
		_stack = new char[_size];
		char* postFix = new char[_size];

		// The beautiful part
		int j = 0;
		for (int i = 0; i < _size; ++i)
		{
			if (isOpeningBrace(expression[i]))
				push(expression[i]);

			else if (isalnum(expression[i]))
				postFix[j++] = expression[i];

			else if (isOperator(expression[i]))
			{
				while (precedenceOf(_stackTop) >= precedenceOf(expression[i]) and !isEmpty())
					if (!isOpeningBrace(_stackTop))
						postFix[j++] = pop();
					else
						pop();

				push(expression[i]);
			}

			else if (isClosingBrace(expression[i]) and !isEmpty())
			{
				while (_stackTop != correspondingOpeningBracket(expression[i]) and !isEmpty())
					postFix[j++] = pop();
				pop();         // Pop the last opening bracket from the _stack
			}
		}

		while (!isEmpty())
			postFix[j++] = pop();       // append any remaining operators/literals to the postFix

		postFix[j] = '\0';             // Null-Terminate the postFix char* array
		int postFixSize = j;

		std::cout << "\n\n Entered expression was: \n\n " << expression;
		std::cout << "\n\n Post Fix Expression:\n\n ";

		for (int i = 0; i < postFixSize + 2; ++i)
			std::cout << "-";

		std::cout << "\n " << postFix << "\n ";

		for (int i = 0; i < postFixSize + 2; ++i)
			std::cout << "-";

	time2:
		std::cout << "\n\n Press 1-2: \n"
			<< "\n 1 - Evaluate this postfix expression"
			<< "\n 2 - Go to Main Menu\n\n";
		char choice = _getch();
		switch (choice)
		{
		case '1':
			evaluatePostFix(postFix, postFixSize);
			break;

		case '2':
			start();
			break;

		default:
			std::cout << "\n Press 1-2 Only! ";
			Sleep(1000);
			goto time2;
		}
	}

	void evaluatePostFix(char* postFixExpression, int size)
	{
		// Delete any current stack in memory
		delete _stack;
		_index = -1;
		_size = size;
		_stack = new char[_size];
		int tempVal = 0;

		for (int i = 0; i < _size; ++i)
		{
			if (isdigit(postFixExpression[i]))
				push(postFixExpression[i]);

			else if (isOperator(postFixExpression[i]))
			{
				char oprnd1;
				char oprnd2;
				if (!isEmpty())
				{
					oprnd2 = pop();
					oprnd1 = pop();
					tempVal = evaluate(postFixExpression[i], oprnd1, oprnd2);
					push(intToChar(tempVal));
				}
			}
		}

		tempVal = charToInt(pop());
		if (isEmpty())
			std::cout << "\n Going Fine";
		else
			std::cout << "\n Something messedup";

		std::cout << "\n\n The result of this postfix expression is " << tempVal;
		_getch();
	}

	int evaluate(char oprtr, char oprnd1, char oprnd2)
	{
		switch (oprtr)
		{
		case '+':
			return charToInt(oprnd1) + charToInt(oprnd2);

		case '-':
			return charToInt(oprnd1) - charToInt(oprnd2);

		case '*':
			return charToInt(oprnd1) * charToInt(oprnd2);

		case '/':
			if (charToInt(oprnd2) != 0)
				return charToInt(oprnd1) / charToInt(oprnd2);
			else
			{
				std::cout << "\n\n !!! MATH ERROR !!!\n";
				_getch();
				expressionValidityCheck();
			}
			break;

		default:
			std::cout << "\n Invalid Operator: " << oprtr;
			_getch();
		}
	}

	int charToInt(char x)
	{
		return x - 48;
	}

	char intToChar(int x)
	{
		return x + 48;
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

	static bool isOperator(char x)
	{
		return x == '+' or x == '-' or x == '*' or x == '/';
	}

	static bool isValid(char x)
	{
		return isalpha(x) or x == '+' or x == '-' or x == '*' or x == '/'; // or x == '!' or x == '<' or x == '>' or x == '.';
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

	static int precedenceOf(char op)
	{
		switch (op)
		{
		case '(':
		case '[':
		case '{':
			return 0;
			break;

		case '+':
		case '-':
			return 1;
			break;

		case '*':
		case '/':
			return 2;
			break;

		default:
			//std::cout << "\n Invalid Operator: "<<op<<std::endl;
			/*_getch();*/
			return -1;
			break;
		}
	}

	static char correspondingOpeningBracket(char closingBracket)
	{
		switch (closingBracket)
		{
		case ')':
			return '(';

		case '}':
			return '{';

		case ']':
			return '[';
		}
	}
};
