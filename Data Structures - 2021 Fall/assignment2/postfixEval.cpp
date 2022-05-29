#include "stack.hpp"

using namespace std;

int eval(char operation, int b, int a){
	switch(operation){
			case('+'):
				return (b + a);
			case('-'):
				return (b - a);
			case('/'):
				return (b / a);
			case('*'):
				return (b * a);
			default:
				cout<<"Invalid\n";
				return 0;
	  }
}

int main(){
  freopen("input_postfixEval.txt", "r", stdin);
  string s;
  int solution;
  int line_counter = 0;
  while(cin>>solution){
    cin>>s;
    Stack<int> stack;
    Stack<int> holdingStack;
    // The input file is in the format "expected_solution postfix_expression"

    // We assume that all operands in the input are one digit (so they range from 0 to 9)
	
	char oper = '\0';
	char workingChar = '\0';
	int arg1 = -1;
	int	arg2 = -1;
	int result = -1;
	
    for(int i=0; i<s.length(); ++i){
    // WRITE CODE HERE to evaluate the postfix expression in s
    // At the end of the loop, stack.pop() should contain the value of the postfix expression
		stack.push(s[i]);
		if(s.length() == stack.size()) {
		while(stack.size() > 0) {
			workingChar = stack.pop();
			switch(workingChar){
				case('+'):
				case('-'):
				case('/'):
				case('*'):
					if(oper == '\0') {
						oper = workingChar;
					}
					else {
						holdingStack.push(oper);
						oper = workingChar;
						if(arg2 != -1){
							holdingStack.push(arg2+48);
							arg2 = -1;
						}
						if(arg1 != -1){
							holdingStack.push(arg1+48);
							arg1 = -1;
						}
					}
				
					break;
				default:
					if(arg1 == -1)
						arg1 = workingChar-48;
					else
					if(arg2 == -1)
						arg2 = workingChar-48;
					break;
			}
			if((oper != '\0') && (arg1 != -1) && (arg2 != -1)) {
				result = eval(oper,arg2,arg1);
				stack.push(result+48);
				oper = '\0';
				arg1 = -1;
				arg2 = -1;
				while(holdingStack.size() > 0) {
					stack.push(holdingStack.pop());
				}
			}
			
		}  
		stack.push(result);
		}
    }

    // Checking whether the value you calculated is correct ...
    int value = stack.pop();

    if(solution == value){
      cout << "line " << line_counter << ": OK [" << solution << " " << value << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << value << "]" << endl;
    }
    line_counter++;
  }
}
