#include "stack.hpp"

using namespace std;

int main(){
  freopen("input_balanced.txt", "r", stdin);
  string s,r;
  int line_counter;
  while(cin >> r){
    cin>>s;
    Stack<char> stack;
    bool isBalanced = true;
    bool solution;
    if(r[0] == 'Y' || r[0] == 'y'){
      solution = true;
    }else{
      solution = false;
    }

    // The input file is in the format "expected_solution expression"
    // so variable solution tells you whether 'expression' is balanced or not

    for(int i=0; i<s.length(); ++i){ //Only push braces / parenthesis
	  switch(s[i]){
		case('['):
		case(']'):
		case('('):
		case(')'):
			stack.push(s[i]);
			break;
		default:
			break;
	  }
    }
	
	Stack<char> holdingStack; // Stack to maintain order of stack when skipping characters
	char workingChar; //Current character to pair

	while(stack.size() > 0) {
		workingChar = stack.pop(); //Select new working character.
		switch(workingChar){
			case(')'): //Matching () case
				while(true){
					if (stack.size() > 0) {
						if(stack.peek() == '('){ //If the next char on the stack is (, pair is found.
							stack.pop();
							workingChar = '\0'; //Set working char to null, signifying a pair has been found, or end of string if null terminated.
							while(holdingStack.size() > 0) {
								stack.push(holdingStack.pop()); //Push all skipped chars back to stack in same order, minus the matched pair.
							}
							break; //Break out of loop. Begin next character comparison.
						} else {
							holdingStack.push(stack.pop()); // Skip char, not a match.
						}
					} else {
						break; //Stack is empty.
					}
				}
				break;
			case(']'): //Matching [] case
				while(true){
					if (stack.size() > 0) {
						if(stack.peek() == '['){//If the next char on the stack is [, pair is found.
							stack.pop();
							workingChar = '\0';//Set working char to null, signifying a pair has been found, or end of string if null terminated.
							while(holdingStack.size() > 0) {
								stack.push(holdingStack.pop()); //Push all skipped chars back to stack in same order, minus the matched pair.
							}
							break; //Break out of loop. Begin next character comparison.
						} else {
							holdingStack.push(stack.pop()); // Skip char, not a match.
						}
					} else {
						break;
					}
				}
				break;
			default:
				if(workingChar != '\0') { //If the working character is not null, ), or ], it must be (, or [. This signifies an extra ( or [, thus it is not balanced.
					isBalanced = false;
				}
				break;
		}
		if(workingChar != '\0') { //If the working character comparison has exited from a loop and it is not null, the character must be ) or ] and have reached the end of the stack.
			isBalanced = false;   //Meaning there is an extra ) or ], and the equation is not balanced.
		}		
	}

    // checking if you stored in isBalanced the correct value
    if(isBalanced == solution){
      cout << "line " << line_counter << ": OK [" << solution << " " << isBalanced << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << isBalanced << "]" << endl;
    }
    line_counter++;
  }
}
