#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	// Delcare variables
	const int hrPaySize = 2; const int size = 8;	// hrPaySize must be 1/4th of size
	float hourlyPay[hrPaySize][hrPaySize][hrPaySize]; string employeeName[size];
	float grossPay[size]; float netPay[size]; float taxRate[size]; float hoursWorked[size];float taxesPaid[size];
	int regionCtr = 0; int facilityCtr = 0; int employeeCtr = 0; int arrayCtr = 0;
	float totalHPExpenses = 0; int width = 12; // For setw
	
	// Get user input for employee name and hourly pay
	for (int i = 0; i < size; i++) {
		cout << "Enter the name of employee " << i + 1 << ": ";
		getline(cin, employeeName[i]);
		cout << "Enter the hourly pay of employee " << i + 1 << ": ";
		cin >> hourlyPay[regionCtr][facilityCtr][employeeCtr];
		cin.ignore();
		
		// increase hourlyPay array counters
		if (employeeCtr > hrPaySize - 1) {
			facilityCtr++;
			employeeCtr = 0;
			if (facilityCtr > hrPaySize - 1) {
				regionCtr++;
				facilityCtr = 0;
				if (regionCtr > hrPaySize - 1) {
					cout << "hrPaySize out of bounds"; return 1;
				}
			}
		}
		employeeCtr++;
	}
	
	// Get user input for hours worked by each employee
	for (int i = 0; i < size; i++) {
		cout << "Enter the hours worked by " << employeeName[i] << ": ";
		cin >> hoursWorked[i];
	}
	
	// Calculate gross pay, determine tax rate
	regionCtr = 0; facilityCtr = 0; employeeCtr = 0;	// Reset counters
	
	for (int i = 0; i < size; i++) {
		// If over 40 hours worked, add overtime (1.5x hourly rate for each hour of overtime)
		if (hoursWorked[i] > 40) { grossPay[i] = hoursWorked[i] * hourlyPay[regionCtr][facilityCtr][employeeCtr]
					+ ((hoursWorked[i] - 40) * hourlyPay[regionCtr][facilityCtr][employeeCtr] * 0.5); }
		else { grossPay[i] = hoursWorked[i] * hourlyPay[regionCtr][facilityCtr][employeeCtr]; }
		
		// Determine tax rate
		if (grossPay[i] <= 100) { taxRate[i] = 0; }
		else if (grossPay[i] > 100 && grossPay [i] <= 200) { taxRate[i] = 0.1; }
		else if (grossPay[i] > 200 && grossPay [i] <= 300) { taxRate[i] = 0.2; }
		else if (grossPay[i] > 300 && grossPay [i] <= 400) { taxRate[i] = 0.3; }
		else if (grossPay[i] > 400 && grossPay [i] <= 500) { taxRate[i] = 0.4; }
		else { taxRate[i] = 0.65; }
		
		// Determine taxes paid, net pay, and total expenses
		totalHPExpenses += grossPay[i];
		taxesPaid[i] = grossPay[i] * taxRate[i];
		netPay[i] = grossPay[i] - (taxesPaid[i]);
		
		// increase hourlyPay array counters
		if (employeeCtr > hrPaySize - 1) {
		facilityCtr++;
		employeeCtr = 0;
			if (facilityCtr > hrPaySize - 1) {
				regionCtr++;
				facilityCtr = 0;
				if (regionCtr > hrPaySize - 1) {
					cout << "hrPaySize out of bounds"; return 1;
					}
			}
		}
		employeeCtr++;
	}
	
	// Output headings
	cout << "\n"	<< "      S L A T E    R O C K    &    G R A V E L    C O .";
	cout << "\n"	<< "         W E E K L Y    P A Y R O L L    R E P O R T";
	cout << "\n\n"	<< "    Employee Name           Gross Pay   Taxes Paid   Net Pay";
	cout <<	"\n"	<< "------------------------------------------------------------";
	
	// Output region, facility, employee name, and the employees' gross pay, taxes paid, and net pay
	for (int regionCtr = 0; regionCtr < hrPaySize; regionCtr++) {
		if (regionCtr > 0) { cout << "\n"; }
		cout << "\nRegion # " << regionCtr + 1;
		for (facilityCtr = 0; facilityCtr < hrPaySize; facilityCtr++) {
			cout << "\nFacility # " << facilityCtr + 1;
			for (employeeCtr = 0; employeeCtr < hrPaySize; employeeCtr++) {
				cout << "\n  " << left << setw((width * 2) - 2) << employeeName[arrayCtr]
				<< right << setw(width) << fixed << setprecision(2) << grossPay[arrayCtr]
				<< setw(width) << taxesPaid[arrayCtr] << setw(width) << netPay[arrayCtr];
				arrayCtr++;
			}
		}
	}
	cout << "\n\nThe total hourly pay expenses for the Slate Rock & Gravel Co. this week are \n$"
		 << totalHPExpenses << "\n";
	return 0;
}
