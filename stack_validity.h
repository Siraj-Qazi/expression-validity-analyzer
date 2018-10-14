#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#define and &&
#define or ||

class Stack
{
public:
	int _size;
	bool _hasVariables;

	// Character Stack
	char* _stack;
	int _index;
	char _stackTop;
	
	// Integer Stack
	long long int* _intStack;
	int _intIndex;
	long long int _stackTopInt;

	Stack() :
		_stack(NULL),
		_intStack(NULL),
		_index(-1), 
		_intIndex(-1), 
		_size(0), 
		_hasVariables(false)
	{
		system("cls");
		std::cout << "\n Please set your command-window font size to 30 for best experience."
			<< "\n\n Click Window Icon > Properties > Font > 32 > OK"
			<< "\n Maximize window to Full Screen afterwards."
			<< "\n\n Press any key once you're done. ";
		_getch();
		start();
	}

	void start()
	{
		system("cls");
		system("color 0b");
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^ EVA - Expression Validity Analyzer ^^^^^^^^^^^^^^^^^^^^^^^^^";
		std::cout << "\n                                       Version 3.3X\n";
		std::cout << "                                          @sqazi";
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
		std::cout << "\n Press 1 - 3: \n"
			<< "\n 1 - Expression Validity Check & Postfix Conversion & Evaluation"
			<< "\n 2 - Evaluate a post-fix expression"
			<< "\n 3 - Exit\n ";

		char choice = _getch();
		switch (choice)
		{
		case '1':
			receiveInfix();
			break;

		case '2':
			receivePostFix();
			break;

		case '3':
			exit(0);

		default:
			std::cout << "\n Press 1-2 Only. <PRESS ANY KEY> ";
			_getch();
			start();
		}
	}

	void push(char x)
	{
		if (isFull())
		{
			std::cout << "\n Error! The stack is full. \n";
			_getch();
			start();
		}
		_stackTop = _stack[++_index] = x;
		std::cout << "\n '" << x << "'     pushed to stack. ";
	}

	char pop()
	{
		if (isEmpty())
		{
			std::cout << "\n Error! The stack is Empty. \n";
			_getch();
			start();
		}
		char popped = _stack[_index];
		_stack[_index--] = '0';
		_stackTop = _stack[_index];
		std::cout << "\n '" << popped << "'     popped from stack.";
		return popped;
	}

	void pushInt(long long int x)
	{
		if (!isFullInt())
		{
			_stackTopInt = _intStack[++_intIndex] = x;
			std::cout << "\n '" << x << "'     pushed to stack. ";
		}
		else
		{
			std::cout << "\n Error! The stack is Full. \n";
			_getch();
			start();
		}
	}

	long long int popInt()
	{
		if (!isEmptyInt())
		{
			long long int popped = _intStack[_intIndex];
			_intStack[_intIndex--] = 0;
			std::cout << "\n '" << popped << "'     popped from stack.";
			return popped;
		}
		else
		{
			std::cout << "\n Error! The stack is Empty. \n";
			_getch();
			start();
		}
	}

	void expressionValidityCheck(char* expression, int size)
	{
		system("cls");
		system("color 0a");
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^ EVA - Expression Validity Analyzer ^^^^^^^^^^^^^^^^^^^^^^^^^";
		std::cout << "\n                                       Version 3.3X\n";
		std::cout << "                                          @sqazi";
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";

		if (_stack)
		{
			delete _stack;
			_stack = NULL;
			_hasVariables = false;
		}
			
		_index = -1;
		_size = size;
		_stack = new char[_size];

		// Say invalid if the first or last character is an operator
		if (isOperator(expression[0]) || isOperator(expression[_size - 1]))
		{
			std::cout << "\n\n Entered expression was: \n " << expression;
			std::cout << "\n\n Invalid Expression! <Incorrectly written expression>\n";
			_getch();
			start();
		}

		for (int i = 0; i < _size; ++i)
		{
			if (!(isdigit(expression[i]) or isOpeningBrace(expression[i]) or isClosingBrace(expression[i]) or isValid(expression[i])))
			{
				std::cout << "\n\n Entered expression was: \n " << expression;
				std::cout << "\n\n Invalid Expression! <Contains an invalid character: '"<<expression[i]<<"' >\n";
				_getch();
				start();
			}

			if (isalnum(expression[i]) && isOpeningBrace(expression[i + 1]))
			{
				std::cout << "\n\n Entered expression was: \n " << expression;
				std::cout << "\n\nInvalid! <Please use x * (y) instead of x(y) >\n";
				_getch();
				start();
			}

			else if (isClosingBrace(expression[i]) && isalnum(expression[i+1]))
			{
				std::cout << "\n\n Entered expression was: \n " << expression;
				std::cout << "\n\n Invalid! <Please use (x) * y instead of (x)y >\n";
				_getch();
				start();
			}

			if (isalpha(expression[i]))
				_hasVariables = true;
		}

		for (int i = 0; i < _size; ++i)
		{
			if (isOpeningBrace(expression[i]))
			{
				if (isOperator(expression[i + 1]))
				{
					std::cout << "\n\n Entered expression was: \n " << expression;
					std::cout << "\n\n Invalid Expression! <Incorrect use of operators with brackets>\n";
					_getch();
					start();
				}

				else if (isClosingBrace(expression[i + 1]))
				{
					std::cout << "\n\n Entered expression was: \n " << expression;
					std::cout << "\n\n Invalid Expression! <Empty brackets>\n";
					_getch();
					start();
				}

				else
					push(expression[i]);
			}
				
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

			if (isOperator(expression[i]))
			{
				if (isOperator(expression[i + 1]) || isClosingBrace(expression[i + 1]))
				{
					std::cout << "\n\n Entered expression was: \n " << expression;
					std::cout << "\n\n Invalid Expression! <Incorrect use of operators with/without brackets>\n";
					_getch();
					start();
				}
			}
		}

		std::cout << "\n\n Entered expression was: \n " << expression;
		
		if (isEmpty())
		{
			std::cout << "\n\n ### This is a valid expression. ###\n\n";
		time:
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
			std::cout << "\n\n Invalid Expression! \n";
			_getch();
			start();
		}
		_getch();
	}

	void convertToPostFix(char* expression, int size)
	{
		system("color 0a");
		std::cout << "\n\n EVA - Convert Infix to PostFix Notation\n";
		std::cout << "\n @SQ\n";
		std::cout << "\n";

		// Delete any current stack in memory
		if (_stack)
		{
			delete _stack;
			_stack = NULL;
		}

		_index = -1;
		_size = size;
		_stack = new char[_size];
		char* postFix = new char[_size*2];

		// The beautiful part
		int j = 0;
		for (int i = 0; i < _size; ++i)
		{
			if (isOpeningBrace(expression[i]))
				push(expression[i]);

			else if (isalnum(expression[i]))
			{
				char* multiDigit = new char[100];
				int k = 0;
				while (isalnum(expression[i]))
					multiDigit[k++] = expression[i++];

				for (int z = 0; z < k; ++z)
					postFix[j++] = multiDigit[z];

				postFix[j++] = ' ';

				free(multiDigit);  // free multidigit

				--i;    // Decrement i so that the main for-loop's ++i sets it right again
			}
				
			else if (isOperator(expression[i]))
			{
				while (precedenceOf(_stackTop) >= precedenceOf(expression[i]) and !isEmpty())
					if (!isOpeningBrace(_stackTop))
					{
						postFix[j++] = pop();
						postFix[j++] = ' ';
					}
					else
						pop();

				push(expression[i]);
			}

			else if (isClosingBrace(expression[i]) and !isEmpty())
			{
				while (_stackTop != correspondingOpeningBracket(expression[i]) and !isEmpty())
				{
					postFix[j++] = pop();
					postFix[j++] = ' ';
				}
				pop();         // Pop the last opening bracket from the _stack
			}
		}

		while (!isEmpty())  // append any remaining operators/literals to the postFix
		{
			postFix[j++] = pop(); 
			postFix[j++] = ' ';
		}
			       
		postFix[j] = '\0';             // Null-Terminate the postFix char* array
		int postFixSize = j;

		std::cout << "\n\n Entered expression was: \n\n " << expression;
		std::cout << "\n\n Post Fix Expression:\n\n ";

		for (int i = 0; i < postFixSize + 2; ++i)
			std::cout << "-";

		std::cout << "\n " << postFix << "\n ";

		for (int i = 0; i < postFixSize + 2; ++i)
			std::cout << "-";
		
		if (_hasVariables)
		{
			std::cout << "\n This expression contains variables and thus cannot be evaluated.\n ";
			_getch();
			_hasVariables = false;
			start();
		}

		if (_stack)
		{
			delete _stack;  // Release memory
			_stack = NULL;
		}

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
		system("color 0a");
		std::cout << "\n\n EVA - Convert Infix to PostFix Notation\n";
		std::cout << "\n @SQ\n";
		std::cout << "\n";

		// Delete any current stack in memory
		if (_intStack)
		{
			delete _intStack;
			_intStack = NULL;
		}
		
		_intIndex = -1;
		_size = size;
		_intStack = new long long int[_size];

		long long int tempVal = 0;

		for (int i = 0; i < _size; ++i)
		{
			if (isdigit(postFixExpression[i]))
			{
				char* multiDigit = new char[100];
				int k = 0;
				while (isdigit(postFixExpression[i]))
					multiDigit[k++] = postFixExpression[i++];
	
				long long int tempVal = atoll(multiDigit);
				pushInt(tempVal);
			}
				
			else if (isOperator(postFixExpression[i]))
			{
				long long int oprnd1;
				long long int oprnd2;
				if (!isEmptyInt())
				{
					oprnd2 = popInt();
					oprnd1 = popInt();

					std::cout << "\n Operator Applied: " << postFixExpression[i] << std::endl;

					tempVal = evaluate(postFixExpression[i], oprnd1, oprnd2);
					pushInt(tempVal);
				}
			}
		}

		tempVal = popInt();

		if (isEmptyInt())
		{
			std::cout << "\n Going Fine";
			std::cout << "\n\n The result of this postfix expression is " << tempVal << " ";
		}
		else
			std::cout << "\n\n Something messed up!\n Are you sure you separated each postFix entry with a space?\n";
			
		if (_intStack)
		{
			delete _intStack;
			_intStack = NULL;
		}
		_getch();
	}

	void receiveInfix()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^ EVA - Expression Validity Analyzer ^^^^^^^^^^^^^^^^^^^^^^^^^";
		std::cout << "\n                                       Version 3.3X\n";
		std::cout << "                                          @sqazi";
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";

		char* expression = new char[100];
		std::cout << "\n Enter the (infix) expression here.\n";
		std::cout << "\n";

		int expSize = 0;
		_getchInputLoop(expression, &expSize);

		expressionValidityCheck(expression, expSize);
		start();
	}

	void receivePostFix()
	{
		system("cls");
		system("color 0a");
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^ EVA - Expression Validity Analyzer ^^^^^^^^^^^^^^^^^^^^^^^^^";
		std::cout << "\n                                       Version 3.3X\n";
		std::cout << "                                          @sqazi";
		std::cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";

		char* expression = new char[100];
		std::cout << "\n Enter the post-fix expression here.\n"
			<< " Note: Separate each entry with a space, e.g.\n"
			<< "\n 23 47 * 51 -\n";

		int expSize = 0;
		_getchInputLoop(expression, &expSize);
		
		std::cout << "\n";

		evaluatePostFix(expression, expSize);
		start();
	}

	void _getchInputLoop(char* expression, int* size)
	{
		std::cout << "\n Input Expression> ";

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

			// Ignore arrow keys 
			else if (c == -32 || c == 72 || c == 80 || c == 75 || c == 77)
				c = _getch();

			else
			{
				expression[i++] = c;
				std::cout << c;
			}
			c = _getch();
		}

		expression[i] = '\0';
		*size = i;
	}

	long long int evaluate(char oprtr, long long int oprnd1, long long int oprnd2)
	{
		switch (oprtr)
		{
		case '+':
			return oprnd1 + oprnd2;

		case '-':
			return oprnd1 - oprnd2;

		case '*':
			return oprnd1 * oprnd2;

		case '/':
			if (oprnd2 != 0)
				return oprnd1 / oprnd2;
			else
			{
				std::cout << "\n\n !!! MATH ERROR !!!\n";
				_getch();
				start();
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

	bool isEmptyInt()
	{
		return _intIndex == -1;
	}

	bool isFullInt()
	{
		return _intIndex == _size - 1;
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
		return isalpha(x) or isOperator(x); // or x == '!' or x == '<' or x == '>' or x == '.';
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