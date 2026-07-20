#include <conio.h>  //For _getch

#include <chrono>  //For stopping programe
#include <ctime>   // For date fetching
#include <fstream>
#include <iomanip>  //For formatting
#include <iostream>
#include <thread>  //For stopping programe
using namespace std;

// Register User
bool is_strong_password(const char* password);
bool username_exists(const char* username);
bool is_all_lowercase(const char* str);
int strlength(const char* str);
void regrowx(char*& array, int& capacity);
void read(char*& input, int& len);
void upper_case(char* str);
void register_user();

// User login
void get_passwordx(char* password, int size);
bool compare_arraysx(const char a[], const char b[]);
void trim_new_line(char* str);
void user_login();

// Display available products
void regrow_2dx(char**& array, int& capacity, const int cols);
void load_csvx(const char* filename, char**& array, int& count, int& capacity, const int cols);
void display_tablex(char** array, int count, const int cols, const char* headers[]);
void display_all_productx();

// Add to cart
void add_to_cart(const char* username);

// View cart
int to_int(const char* str);
float to_float(const char* str);
void print_float(float num);
void view_cart(const char* username);

// Edit cart
void edit_cart(const char* username);
void str_copyx(char* dest, const char* src);

// Place Order
void print_float_to_file(ofstream& file, float num);
void get_current_date_day(char* date, char* day);
int extract_order_id(char* line);
void place_order(const char* username);

// Cancel Order
void cancel_order(const char* username);

// View Status
void view_order_status(const char* username);

// Main Flow
void User() {
	char currentUser[50];
	int choice;
	do {
		system("cls");
		cout << "=== Welcome to S&M Shopping Cart ===" << endl << "1. Register" << endl << "2. Login" << endl << "3. Exit" << endl << "Enter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
			case 1:
				register_user();
				break;
			case 2:
				user_login();
				break;
			case 3:
				cout << "Thank you for visiting. Goodbye!" << endl;
				return;
			default:
				cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
		}
	} while (true);
}

// Register User
bool is_strong_password(const char* password) {
	int length = 0;
	bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

	for (int i = 0; password[i] != '\0'; ++i) {
		char ch = password[i];
		length++;

		if (ch >= 'A' && ch <= 'Z')
			hasUpper = true;
		else if (ch >= 'a' && ch <= 'z')
			hasLower = true;
		else if (ch >= '0' && ch <= '9')
			hasDigit = true;
		else if (ch >= 33 && ch <= 47 || ch >= 58 && ch <= 64 || ch >= 91 && ch <= 96 || ch >= 123 && ch <= 126)
			hasSpecial = true;
	}

	return length >= 8 && hasUpper && hasLower && hasDigit && hasSpecial;
}
bool username_exists(const char* username) {
	ifstream read("users.csv");
	if (!read) return false;

	char line[200];
	while (read.getline(line, 200)) {
		int i = 0;
		while (line[i] != ',' && line[i] != '\0') {
			if (line[i] != username[i]) break;
			i++;
		}
		if (line[i] == ',' && username[i] == '\0') {
			read.close();
			return true;
		}
	}
	read.close();
	return false;
}
bool is_all_lowercase(const char* str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			return false;
		}
	}
	return true;
}
int strlength(const char* str) {
	int len = 0;
	while (str[len] != '\0') ++len;
	return len;
}
void regrowx(char*& array, int& capacity) {
	int newcapicity = capacity * 2;
	char* temp = new char[newcapicity];
	for (int i = 0; i < capacity; ++i) temp[i] = array[i];
	delete[] array;
	array = temp;
	capacity = newcapicity;
}
void read(char*& input, int& len) {
	int cap = 50;
	input = new char[cap];
	len = 0;
	char ch;

	while (true) {
		len = 0;
		while ((ch = cin.get()) != '\n') {
			if (len >= cap - 1) regrowx(input, cap);
			input[len++] = ch;
		}
		input[len] = '\0';

		if (strlength(input) == 0) {
			cout << "Input cannot be empty. Please enter again." << endl;
		} else {
			break;
		}
	}
}
void upper_case(char* str) {
	for (int i = 0; str[i] != '\0'; ++i)
		if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
}
void register_user() {
	cin.ignore();

	int len;
	system("cls");
	cout << "Register:" << endl;
	char* name;
	cout << "Name: ";
	read(name, len);
	upper_case(name);

	bool exists;
	char* username = nullptr;
	do {
		if (username != nullptr) {
			delete[] username;
			username = nullptr;
		}

		cout << "Username (lowercase only): ";
		read(username, len);

		if (!is_all_lowercase(username)) {
			cout << "Username must contain only lowercase letters. Try again.\n";
			continue;
		}

		exists = username_exists(username);
		if (exists) {
			cout << "Username already exists. Please choose another.\n";
		}

	} while (!is_all_lowercase(username) || exists);

	bool valid;
	char* password;
	do {
		cout << "Password: ";
		read(password, len);
		valid = is_strong_password(password);

		if (!valid) {
			cout << "Password must be at least 8 characters and include: " << endl;
			cout << "   - One uppercase letter" << endl;
			cout << "   - One lowercase letter" << endl;
			cout << "   - One number" << endl;
			cout << "   - One special symbol (!, @, #, etc.)" << endl << endl;
			delete[] password;
		}
	} while (!valid);

	ofstream write("users.csv", ios::app);
	if (!write) {
		cout << "Error opening file!" << endl;
		return;
	}

	write << username << "," << password << "," << name << endl;
	write.close();

	cout << "Registration successful!" << endl;
	cout << "Press any key...";
	_getch();
	delete[] name;
	delete[] username;
	delete[] password;
}

// User login
void get_passwordx(char* password, int size) {
	char ch;
	int i = 0;

	while (true) {
		ch = _getch();
		if (ch == 13)
			break;
		else if (ch == 8 && i > 0) {
			cout << "\b \b";
			i--;
		} else if (ch >= 32 && ch <= 126 && i < size - 1) {
			password[i++] = ch;
			cout << '*';
		}
	}
	password[i] = '\0';
}
bool compare_arraysx(const char a[], const char b[]) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) return false;
		i++;
	}
	return a[i] == b[i];
}
void trim_new_line(char* str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\n' || str[i] == '\r') {
			str[i] = '\0';
			break;
		}
	}
}
void user_login() {
	const int size = 50;
	char* enteredUser = new char[size];
	char* enteredPass = new char[size];

	int attempts = 0;
	bool found = false;

	while (true) {
		while (attempts < 3 && !found) {
			system("cls");
			cout << "***User Login***" << endl;
			cout << "Username: ";
			cin.ignore();
			cin.getline(enteredUser, size);

			cout << "Password: ";
			get_passwordx(enteredPass, size);
			cout << endl;

			ifstream read("users.csv");
			if (!read) {
				cout << "Error opening users.csv file." << endl;
				delete[] enteredUser;
				delete[] enteredPass;
				return;
			}

			char* fileLine = new char[150];

			while (read.getline(fileLine, 150)) {
				int ucap = 50, pcap = 50, ncap = 50;
				char* fileUser = new char[ucap];
				char* filePass = new char[pcap];
				char* name = new char[ncap];
				int col = 0, j = 0;

				for (int k = 0; fileLine[k] != '\0'; ++k) {
					if (fileLine[k] == ',') {
						if (col == 0)
							fileUser[j] = '\0';
						else if (col == 1)
							filePass[j] = '\0';
						col++;
						j = 0;
						continue;
					}
					if (col == 0)
						fileUser[j++] = fileLine[k];
					else if (col == 1)
						filePass[j++] = fileLine[k];
					else if (col == 2)
						name[j++] = fileLine[k];
				}
				name[j] = '\0';

				trim_new_line(fileUser);
				trim_new_line(filePass);
				trim_new_line(name);

				if (compare_arraysx(enteredUser, fileUser) && compare_arraysx(enteredPass, filePass)) {
					system("cls");
					cout << "Logged in as " << name << "." << endl;
					cout << "Press any key...";
					_getch();
					found = true;

					int choice;
					do {
						system("cls");
						cout << "==================== User Menu ====================" << endl;
						cout << "1.  Display all products" << endl;
						cout << "2.  Add product to cart" << endl;
						cout << "3.  View cart" << endl;
						cout << "4.  Edit cart" << endl;
						cout << "5.  Place order" << endl;
						cout << "6.  Cancel order" << endl;
						cout << "7.  View order status" << endl;
						cout << "8.  Logout" << endl;
						cout << "===================================================" << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						cout << endl;

						switch (choice) {
							case 1:
								display_all_productx();
								break;
							case 2:
								add_to_cart(enteredUser);
								break;
							case 3:
								view_cart(enteredUser);
								break;
							case 4:
								edit_cart(enteredUser);
								break;
							case 5:
								place_order(enteredUser);
								break;
							case 6:
								cancel_order(enteredUser);
								break;
							case 7:
								view_order_status(enteredUser);
								break;
							case 8:
								cout << "Logged out successfully." << endl << endl;
								break;
							default:
								cout << "Invalid choice. Please try again." << endl << endl;
						}
					} while (choice != 8);

					delete[] fileUser;
					delete[] filePass;
					delete[] name;
					break;
				}

				delete[] fileUser;
				delete[] filePass;
				delete[] name;
			}

			read.close();
			delete[] fileLine;

			if (!found) {
				attempts++;
				if (attempts < 3) cout << "Invalid username or password. Please try again." << endl;
				cout << "Press any key...";
				_getch();
			}
		}
		if (found) break;
		cout << endl << "3 unsuccessful login attempts. Please wait 30 seconds..." << endl;
		std::this_thread::sleep_for(std::chrono::seconds(30));

		char choice;
		cout << endl << "Press 'T' to try again or 'M' to return to the main menu: ";
		cin >> choice;

		if (choice == 'M' || choice == 'm') {
			cout << endl << "Returning to main menu..." << endl;
			break;
		} else {
			attempts = 0;
		}
	}
	delete[] enteredUser;
	delete[] enteredPass;
}

// Display available products
void regrow_2dx(char**& array, int& capacity, const int cols) {
	int newcapacity = capacity * 2;
	char** temp = new char*[newcapacity * cols];
	for (int i = 0; i < capacity * cols; ++i) {
		temp[i] = array[i];
	}
	delete[] array;
	array = temp;
	capacity = newcapacity;
}
void load_csvx(const char* filename, char**& array, int& count, int& capacity, const int cols) {
	ifstream read(filename);
	if (!read) {
		cout << "Error: Cannot open " << filename << endl;
		return;
	}

	capacity = 4;
	count = 0;
	array = new char*[capacity * cols];

	char line[200];
	while (read.getline(line, 200)) {
		if (count == capacity) {
			regrow_2dx(array, capacity, cols);
		}

		int base = count * cols;
		for (int j = 0; j < cols; ++j) array[base + j] = new char[50];

		int i = 0, col = 0, ci = 0;
		while (line[i] != '\0') {
			if (line[i] == ',') {
				array[base + col][ci] = '\0';
				col++;
				ci = 0;
			} else {
				array[base + col][ci++] = line[i];
			}
			i++;
		}
		array[base + col][ci] = '\0';
		count++;
	}
	read.close();
}
void display_tablex(char** array, int count, const int cols, const char* headers[]) {
	for (int i = 0; i < cols; ++i) cout << left << setw(30) << headers[i];
	cout << endl;
	cout << setfill('-') << setw(30 * cols) << "-" << setfill(' ') << endl;

	for (int i = 0; i < count; ++i) {
		int base = i * cols;
		for (int j = 0; j < cols; ++j) {
			cout << left << setw(30) << array[base + j];
		}
		cout << endl;
	}
	cout << setfill('-') << setw(20 * cols) << "-" << setfill(' ') << endl;
}
void display_all_productx() {
	system("cls");
	const int productCols = 5;
	char** products;
	int productCount, productCap;

	const char* productHeaders[] = {"ID", "Name", "Price", "Quantity", "Category"};

	load_csvx("products.csv", products, productCount, productCap, productCols);
	cout << endl << "========== Products View ==========" << endl;
	display_tablex(products, productCount, productCols, productHeaders);
	cout << "Press any key..." << endl;
	_getch();
	for (int i = 0; i < productCount * productCols; ++i) delete[] products[i];
	delete[] products;
}

// Add to cart
void add_to_cart(const char* username) {
	const int cols = 5;
	char** products;
	int count, capacity;

	load_csvx("products.csv", products, count, capacity, cols);

	char choice;
	do {
		system("cls");
		display_all_productx();

		char idInput[10];
		char quantityInput[10];

		cout << "Enter Product ID: ";
		cin >> idInput;

		cout << "Enter Quantity: ";
		cin >> quantityInput;

		int foundIndex = -1;
		for (int i = 0; i < count; ++i) {
			int base = i * cols;
			if (compare_arraysx(idInput, products[base])) {
				foundIndex = i;
				break;
			}
		}

		if (foundIndex == -1) {
			cout << "Product ID not found." << endl;
		} else {
			int base = foundIndex * cols;
			int stock = to_int(products[base + 3]);
			int quantity = to_int(quantityInput);

			if (quantity > stock) {
				cout << "Requested quantity exceeds available stock (" << stock << ")." << endl;
			} else {
				ifstream read("carts.csv");
				ofstream temp("temp-cart.csv");
				bool updated = false;
				char line[256];

				while (read.getline(line, 256)) {
					char row[7][100];
					int col = 0, idx = 0;

					for (int i = 0; line[i] != '\0' && col < 7; ++i) {
						if (line[i] == ',') {
							row[col][idx] = '\0';
							col++;
							idx = 0;
						} else {
							row[col][idx++] = line[i];
						}
					}
					row[col][idx] = '\0';

					if (compare_arraysx(row[0], username) && compare_arraysx(row[1], idInput)) {
						int existingQty = to_int(row[2]);
						int newQty = existingQty + quantity;
						temp << username << "," << idInput << "," << newQty << "," << products[base + 1] << "," << products[base + 2] << "," << products[base + 3] << "," << products[base + 4] << endl;
						updated = true;
					} else {
						for (int i = 0; i < 7; ++i) {
							temp << row[i];
							if (i < 6) temp << ",";
						}
						temp << endl;
					}
				}
				read.close();

				if (!updated) {
					temp << username << "," << idInput << "," << quantity << "," << products[base + 1] << "," << products[base + 2] << "," << products[base + 3] << "," << products[base + 4] << endl;
				}

				temp.close();
				remove("carts.csv");
				rename("temp-cart.csv", "carts.csv");

				cout << "Product added to the cart successfully." << endl;
			}
		}
		cout << endl << "Do you want to add another item? (y/n): ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');

	for (int i = 0; i < count * cols; ++i) delete[] products[i];
	delete[] products;
}

// View cart
int to_int(const char* str) {
	int result = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		if (str[i] >= '0' && str[i] <= '9') result = result * 10 + (str[i] - '0');
	return result;
}
float to_float(const char* str) {
	float result = 0, decimalPart = 0;
	int i = 0, afterDecimal = 0, isDecimal = 0;

	while (str[i] != '\0') {
		if (str[i] == '.') {
			isDecimal = 1;
			i++;
			continue;
		}

		if (str[i] >= '0' && str[i] <= '9') {
			if (!isDecimal)
				result = result * 10 + (str[i] - '0');
			else {
				decimalPart = decimalPart * 10 + (str[i] - '0');
				afterDecimal++;
			}
		}
		i++;
	}

	while (afterDecimal--) decimalPart /= 10;

	return result + decimalPart;
}
void print_float(float num) {
	int intPart = (int)num;
	int decimal = (int)((num - intPart) * 100 + 0.5);

	cout << "Rs " << intPart << '.';
	if (decimal < 10) cout << '0';
	cout << decimal;
}
void view_cart(const char* username) {
	system("cls");
	const int cartCols = 7;
	char** cart;
	int cartCount, cartCap;

	const char* cartHeaders[] = {"Username", "ID", "Quantity", "Name", "Price", "Total in stock", "Category"};

	load_csvx("carts.csv", cart, cartCount, cartCap, cartCols);

	cout << endl << "========== Your Cart ==========" << endl << endl;
	for (int i = 0; i < cartCols; ++i) cout << setw(30) << left << cartHeaders[i];
	cout << endl;

	cout << setfill('-') << setw(30 * cartCols) << "-" << setfill(' ') << endl;

	bool empty = true;
	float totalAmount = 0;
	for (int i = 0; i < cartCount; ++i) {
		int base = i * cartCols;
		if (compare_arraysx(username, cart[base])) {
			for (int j = 0; j < cartCols; ++j) cout << setw(30) << left << cart[base + j];
			cout << endl;
			int quantity = to_int(cart[base + 2]);
			float price = to_float(cart[base + 4]);
			totalAmount += quantity * price;

			empty = false;
		}
	}
	cout << setfill('-') << setw(30 * cartCols) << "-" << setfill(' ') << endl;

	if (empty) {
		cout << "No items found in your cart." << endl;
	} else {
		cout << "Total Amount: ";
		print_float(totalAmount);
		cout << endl;
	}
	cout << "Press any key...";
	_getch();
	for (int i = 0; i < cartCount * cartCols; ++i) delete[] cart[i];
	delete[] cart;
}

// Edit cart
void str_copyx(char* dest, const char* src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
void edit_cart(const char* username) {
	system("cls");
	const int cartCols = 7;
	char** cart;
	int cartCount, cartCap;

	load_csvx("carts.csv", cart, cartCount, cartCap, cartCols);

	int choice;
	cout << "=== Edit Cart Menu ===" << endl;
	cout << "1. Edit/Remove specific products" << endl;
	cout << "2. Clear entire cart" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	if (choice == 2) {
		char confirm;
		cout << "Are you sure you want to remove all items from your cart? (y/n): ";
		cin >> confirm;
		if (confirm == 'y' || confirm == 'Y') {
			int newCount = 0;
			for (int i = 0; i < cartCount; ++i) {
				int base = i * cartCols;
				if (!compare_arraysx(cart[base], username)) {
					if (newCount != i) {
						for (int j = 0; j < cartCols; ++j) str_copyx(cart[newCount * cartCols + j], cart[base + j]);
					}
					newCount++;
				}
			}

			cartCount = newCount;
			cout << "All items cleared from your cart." << endl;
		} else {
			cout << "Cart clear cancelled." << endl;
		}
	} else if (choice == 1) {
		char ch;
		do {
			system("cls");
			cout << endl << "========= Edit Your Cart ==========" << endl;
			const char* headers[] = {"ID", "Quantity", "Name", "Price", "Stock", "Category"};

			cout << left << setw(10) << "ID";
			for (int i = 2; i < cartCols; ++i) cout << left << setw(20) << headers[i - 1];
			cout << endl;

			cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;

			for (int i = 0; i < cartCount; ++i) {
				int base = i * cartCols;
				if (compare_arraysx(cart[base], username)) {
					cout << setw(10) << cart[base + 1];
					for (int j = 2; j < cartCols; ++j) cout << setw(20) << cart[base + j];
					cout << endl;
				}
			}

			char idToEdit[10];
			cout << endl << "Enter the Product ID you want to edit: ";
			cin >> idToEdit;

			bool found = false;
			for (int i = 0; i < cartCount; ++i) {
				int base = i * cartCols;
				if (compare_arraysx(cart[base], username) && compare_arraysx(cart[base + 1], idToEdit)) {
					found = true;
					cout << "Current quantity: " << cart[base + 2] << endl;
					cout << "Enter new quantity (0 to remove): ";
					char newQty[10];
					cin >> newQty;

					if (to_int(newQty) == 0) {
						for (int j = base; j < (cartCount - 1) * cartCols; ++j) {
							str_copyx(cart[j], cart[j + cartCols]);
						}
						cartCount--;
						cout << "Item removed from cart." << endl;
					} else {
						str_copyx(cart[base + 2], newQty);
						cout << "Quantity updated." << endl;
					}
					break;
				}
			}

			if (!found) {
				cout << "Item not found in your cart." << endl;
			}
			cout << endl << "Do you want to edit another product? (y/n): ";
			cin >> ch;

		} while (ch == 'y' || ch == 'Y');
	} else {
		cout << "Invalid choice." << endl;
	}
	ofstream write("carts.csv");
	for (int i = 0; i < cartCount; ++i) {
		int base = i * cartCols;
		write << cart[base];
		for (int j = 1; j < cartCols; ++j) write << "," << cart[base + j];
		write << endl;
	}
	write.close();

	for (int i = 0; i < cartCount * cartCols; ++i) delete[] cart[i];
	delete[] cart;
}

// Place Order
void print_float_to_file(ofstream& write, float num) {
	int intPart = (int)num;
	int decimal = (int)((num - intPart) * 100 + 0.5);

	write << intPart << '.';
	if (decimal < 10) write << '0';
	write << decimal;
}
void get_current_date_day(char* date, char* day) {
	time_t now = time(0);
	tm localTime;

	localtime_s(&localTime, &now);

	sprintf_s(date, 20, "%02d-%02d-%04d", localTime.tm_mday, localTime.tm_mon + 1, localTime.tm_year + 1900);

	const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

	str_copyx(day, days[localTime.tm_wday]);
}
int extract_order_id(char* line) {
	int id = 0;
	int i = 0;
	while (line[i] != ',' && line[i] != '\0') {
		if (line[i] >= '0' && line[i] <= '9') {
			id = id * 10 + (line[i] - '0');
		}
		i++;
	}
	return id;
}
void place_order(const char* username) {
	system("cls");
	const int cartCols = 7;
	char** cart;
	int cartCount, cartCap;
	load_csvx("carts.csv", cart, cartCount, cartCap, cartCols);

	float totalAmount = 0;
	bool found = false;

	int lastOrderId = 100;
	ifstream read("orders.csv");
	if (read) {
		char line[300];
		while (read.getline(line, 300)) {
			int id = extract_order_id(line);
			if (id > lastOrderId) lastOrderId = id;
		}
		read.close();
	}
	int orderId = lastOrderId + 1;

	cout << endl << "Review Your Cart Before Ordering: " << endl;

	const char* cartHeaders[] = {"ID", "Quantity", "Name", "Price", "Stock", "Category"};
	for (int i = 0; i < 6; ++i) cout << setw(30) << left << cartHeaders[i];
	cout << endl;

	cout << setfill('-') << setw(30 * 6) << "-" << setfill(' ') << endl;

	float previewTotal = 0;
	for (int i = 0; i < cartCount; ++i) {
		int base = i * cartCols;
		if (compare_arraysx(cart[base], username)) {
			found = true;
			int quantity = to_int(cart[base + 2]);
			float price = to_float(cart[base + 4]);
			previewTotal += quantity * price;

			for (int j = 1; j < cartCols; ++j) cout << setw(30) << left << cart[base + j];
			cout << endl;
		}
	}

	cout << setfill('-') << setw(30 * 6) << "-" << setfill(' ') << endl;

	if (!found) {
		cout << "Your cart is empty. Cannot place an order." << endl;
		for (int i = 0; i < cartCount * cartCols; ++i) delete[] cart[i];
		delete[] cart;
		return;
	}

	cout << "Total Amount: ";
	print_float(previewTotal);
	cout << endl;

	char phone[30], address[100];
	cin.ignore();
	cout << "Enter your phone number: ";
	cin.getline(phone, 30);
	cout << "Enter your address: ";
	cin.getline(address, 100);

	char date[20], day[15];
	get_current_date_day(date, day);

	ofstream write("order-details.csv", ios::app);
	for (int i = 0; i < cartCount; ++i) {
		int base = i * cartCols;
		if (compare_arraysx(cart[base], username)) {
			write << orderId;
			for (int j = 1; j < cartCols; ++j) write << "," << cart[base + j];
			write << endl;

			int quantity = to_int(cart[base + 2]);
			float price = to_float(cart[base + 4]);
			totalAmount += quantity * price;
		}
	}
	write.close();

	ofstream writex("orders.csv", ios::app);
	writex << orderId << "," << date << "," << day << "," << username << "," << phone << "," << address << ",";
	print_float_to_file(writex, totalAmount);
	writex << ",P" << endl;
	writex.close();

	ofstream writey("temp-carts.csv");
	for (int i = 0; i < cartCount; ++i) {
		int base = i * cartCols;
		if (!compare_arraysx(cart[base], username)) {
			writey << cart[base];
			for (int j = 1; j < cartCols; ++j) writey << "," << cart[base + j];
			writey << endl;
		}
	}
	writey.close();
	remove("carts.csv");
	rename("temp-carts.csv", "carts.csv");

	cout << endl << "Order placed successfully. Your order ID is: " << orderId << endl;
	cout << "Press any key...";
	_getch();
	for (int i = 0; i < cartCount * cartCols; ++i) delete[] cart[i];
	delete[] cart;
}

// Cancel order
void cancel_order(const char* username) {
	system("cls");
	const int orderCols = 7;
	const int summaryCols = 8;
	char** details;
	int dcount, dcap;

	char** summaries;
	int scount, scap;

	load_csvx("order-details.csv", details, dcount, dcap, orderCols);

	load_csvx("orders.csv", summaries, scount, scap, summaryCols);

	bool hasOrder = false;
	cout << "=== Your Placed Orders ===" << endl;

	for (int i = 0; i < scount; ++i) {
		int base = i * summaryCols;
		if (compare_arraysx(summaries[base + 3], username)) {
			hasOrder = true;
			cout << "Order ID: " << summaries[base] << "\tDate: " << summaries[base + 1] << "\tAmount: " << summaries[base + 6] << endl;
		}
	}

	if (!hasOrder) {
		cout << "You have no orders to cancel." << endl;
		for (int i = 0; i < dcount * orderCols; ++i) delete[] details[i];
		delete[] details;
		for (int i = 0; i < scount * summaryCols; ++i) delete[] summaries[i];
		delete[] summaries;
		return;
	}

	char cancelId[10];
	cout << "Enter Order ID to cancel: ";
	cin >> cancelId;

	ofstream write("temp-order-details.csv");
	for (int i = 0; i < dcount; ++i) {
		int base = i * orderCols;
		if (!compare_arraysx(details[base], cancelId)) {
			write << details[base];
			for (int j = 1; j < orderCols; ++j) write << "," << details[base + j];
			write << endl;
		}
	}
	write.close();

	ofstream writex("temp-orders.csv");
	for (int i = 0; i < scount; ++i) {
		int base = i * summaryCols;
		if (!compare_arraysx(summaries[base], cancelId)) {
			writex << summaries[base];
			for (int j = 1; j < summaryCols; ++j) writex << "," << summaries[base + j];
			writex << endl;
		}
	}
	writex.close();

	remove("order-details.csv");
	rename("temp-order-details.csv", "order-details.csv");

	remove("orders.csv");
	rename("temp-orders.csv", "orders.csv");

	cout << "Order ID " << cancelId << " cancelled successfully!" << endl;
	cout << "Press any key...";
	_getch();

	for (int i = 0; i < dcount * orderCols; ++i) delete[] details[i];
	delete[] details;
	for (int i = 0; i < scount * summaryCols; ++i) delete[] summaries[i];
	delete[] summaries;
}

// View order status
void view_order_status(const char* username) {
	system("cls");
	const int cols = 8;
	char** orders;
	int count, capacity;

	load_csvx("orders.csv", orders, count, capacity, cols);

	bool found = false;
	int user_orders = 0;

	for (int i = 0; i < count; ++i) {
		int base = i * cols;

		if (compare_arraysx(orders[base + 3], username)) {
			user_orders++;

			if (orders[base + 7][0] == 'C') {
				if (!found) {
					cout << " *** Your Dispatched Orders ***" << endl;

					cout << left << setw(20) << "OrderID" << setw(20) << "Dispatching date" << setw(20) << "Dispatching day" << setw(20) << "Phone" << setw(20) << "Address" << setw(20) << "Total" << setw(20) << "Status" << endl;
					cout << setfill('-') << setw(130) << "-" << setfill(' ') << endl;
				}
				found = true;
				cout << left << setw(20) << orders[base + 0] << setw(20) << orders[base + 1] << setw(20) << orders[base + 2] << setw(20) << orders[base + 4] << setw(20) << orders[base + 5] << setw(20) << orders[base + 6] << setw(1) << orders[base + 7] << "ompleted" << endl;
				cout << setfill('-') << setw(130) << "-" << setfill(' ') << endl;
			}
		}
	}

	if (user_orders == 0) {
		cout << "You have not placed any orders yet." << endl;
	} else if (!found) {
		cout << "Your order is yet to be dispatched." << endl;
	}

	cout << "Press any key to continue...";
	_getch();
	for (int i = 0; i < count * cols; ++i) delete[] orders[i];
	delete[] orders;
}