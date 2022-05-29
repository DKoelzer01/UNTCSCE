/* 
Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
Date: January 30, 2020
Instructor: Joseph Helsing
Description: Homework 1. Calculate temperature difference required for a change in carnot efficiency of heat engines.
*/

#include <iostream>
using namespace std;

int main() {
	cout << "+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
	cout << "|        CSCE 1030 - Computer Science I        |" << endl;
	cout << "| Daniel Koelzer   dlk0138  dlk0138@my.unt.edu |" << endl;
	cout << "+----------------------------------------------+" << endl;
	cout << endl;
	
	/*
	Declare all variables. 3 to store user input (InitialEfficiency, FinalEfficiency, ColdTempC).
	ColdTempK is the variable that stores the cold reservoir temperature in Kelvin.
	DeltaTempK is the variable that stores the calculated temperature change required to get the desired efficiency.
	*/
	
	double InitialEfficiency,FinalEfficiency,ColdTempC,ColdTempK,DeltaTempK;
	cout << "Enter the original Carnot efficiency (0 < n1 < 1): ";
	cin >> InitialEfficiency;
	cout << "Enter the improved Carnot efficiency (0 < n2 < 1 and n1 < n2): ";
	cin >> FinalEfficiency;
	cout << "Enter the temperature of the cold reservoir in Celcius: ";
	cin >> ColdTempC;

	if(ColdTempC < -273.15) ColdTempC = -273.15; //Check if ColdTempC defies physics. If it does, force temp back into bounds.
	ColdTempK = ColdTempC + 273.15; //Convert Celcius to Kelvin.
	
	DeltaTempK = ((ColdTempK)/(1-FinalEfficiency))-((ColdTempK)/(1-InitialEfficiency)); // Calculate using formula provided.
	
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2); //Set output format to 2 decimal places for consistency and readability.
	
	cout << "The temperature of the hot reservoir must increase by " << DeltaTempK << " K." << endl;
	return (0);
}