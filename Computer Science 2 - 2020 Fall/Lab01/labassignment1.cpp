#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Employee {
	int id;
	string name;
};

struct Customer {
	int id;
	string name;
	float balance;
};

int main() {
	Customer CustomerArray [50];
	Employee EmployeeArray [50];
	
	ifstream fileInputStream;
	ofstream fileOutputStream;
	
	fileInputStream.open("transactiondata");
	cout << "123456789012345678901234567890123456789012345678901234567890" << endl;
	
	while(!(fileInputStream.eof() || fileInputStream.bad() || fileInputStream.fail())) {
		int id;
		string name;
		float balance;
		float transaction;
		
		char firstChar;
		string temp;
		stringstream strStream;
		
		getline(fileInputStream, temp);
		strStream << temp;
		
		strStream >> firstChar;
		firstChar = temp[0];
				
		if( firstChar != 't') {
			if( firstChar == 'e') {
				strStream >> id >> name;
				
				EmployeeArray[id-1].name = name;
				EmployeeArray[id-1].id = id;
			}
			else if ( firstChar == 'c') {
				strStream >> id >> name >> balance;
				
				CustomerArray[id-1].id = id;
				CustomerArray[id-1].name = name;
				CustomerArray[id-1].balance = balance;
			} 
		}
		else {
			int customerID;
			int employeeID;
			char action;
			float amount;
			strStream >> customerID >> employeeID >> action >> amount;
			printf("%15s ",&CustomerArray[customerID-1].name[0]);
			printf("%15s ",&EmployeeArray[employeeID-1].name[0]);
			if(action == 'w') {
				CustomerArray[customerID-1].balance -= amount;
				printf("-$%7.2f ",amount);
			} else {
				CustomerArray[customerID-1].balance += amount;
				printf("+$%7.2f ",amount);
			}
			printf("$%9.2f\n",CustomerArray[customerID-1].balance);
			
			
			
		}
	}
	
	return 0;
}
