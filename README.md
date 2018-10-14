# expression-validity-analyzer
A Stack-based algebraic expression validity analyzer and infix to postfix converter in C++

EVA - Expression Validity Analyzer
By Siraj Qazi
-------------------------------------
Changelog Updated on Oct 13, 2018

Build 1.0:
Oct 9, 2018 8:21PM PST

   - Initial build
   - First stable version
   - Implemented all standard stack operations
   - Designed an interactive UI to ease usage of the Data Structure.
   - Expression Validity Analyzer - Enter an algebraic expression (with braces and
     operators to check its validity)
   - Conversion of the entered(infix) expression into postFix notation

Build 2.0:
Oct 10, 2018 2:49PM PST

   - [FEATURE UPDATE] Evaluation of a postFix expression - A postfix expression
     can now be evaluated to an arithematic value, if the postfix expression
     does not contain any variables.
   - Minor bug fixes

Build 2.2:
Oct 12, 2018 9:27PM PST
    
   - Made the expression validity check function more robust - Now it can detect
     incorrect use of brackets, operators or empty brackets.
   - [FEATURE UPDATE] Expressions with variables can now be converted to Postfix
   - Handled arrow keys at the input screen.

Build 3.0:
Oct 13, 2018 12:03PM PST

   - [FEATURE UPDATE] Multi-Digit Support: Now more-than-one digit numbers can be        entered and their correct postfix conversion and evaluation is supported.
   - Handled more incorrect inputs
   - Better Memory Management : Stacks are deleted after usage to free memory
   - Bug Fixes
   
Build 3.1:
Oct 13, 2018 2:04PM PST

   - Feature 'downdate'? Removed the stack operations function: Using basic
     stack functions has been removed.
   - Now purely an expression-validity-analyzer
   
Build 3.2:
Oct 13, 2018 11:06PM PST

   - Added Function receivePostFix( ) to directly input a post fix expression from user 
     and evaluate it

Build 3.3:
Oct 14, 2018 1:18PM PST

   - Added function receiveInfix( ) to take infix expression as input
   - Now a new function _getchInputLoop( ) is called to take all inputs in the application. 

