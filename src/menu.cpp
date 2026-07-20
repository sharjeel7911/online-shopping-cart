#include <conio.h>  //For _getch

#include <iostream>
using namespace std;

bool is_single_digit_input(const char* input);

void Admin();
void User();

bool is_single_digit_input(const char* input) { return ((input[0] == '1' || input[0] == '2' || input[0] == '3') && input[1] == '\0'); }
int main() {
	char input[10];

	while (true) {
		system("cls");
		cout << "Welcome to S&M Online Shopping Cart" << endl;
		cout << "*** Main Menu ***" << endl;
		cout << "1. Admin" << endl;
		cout << "2. User" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> input;

		if (!is_single_digit_input(input)) {
			cout << "Invalid input! Please enter only 1, 2, or 3." << endl;
			cout << "Press any key to try again...";
			_getch();
			continue;
		}
		char choice = input[0];
		if (choice == '1') {
			Admin();
		} else if (choice == '2') {
			User();
		} else if (choice == '3') {
			cout << "Thank you for using Online Shopping Cart!" << endl;
			cout << "Press any key...";
			_getch();
			break;
		}
		cout << "Press Enter to return to Main Menu...";
		cin.ignore();
		cin.get();
	}
	return 0;
}