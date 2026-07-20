#include <conio.h>  //For _getch

#include <chrono>  //For stopping programe
#include <ctime>   // For date fetching
#include <fstream>
#include <iomanip>  //For formatting
#include <iostream>
#include <thread>  //For stopping programe
using namespace std;

// Admin Login Validity
bool admin_login();
void get_password(char* password, int size);
bool compare_arrays(const char a[], const char b[]);

// Display all products
void regrow_2d(char**& array, int& capacity, const int cols);
void load_csv(const char* filename, char**& array, int& count, int& capacity, const int cols);
void display_table(char** array, int count, const int cols, const char* headers[]);
void display_all_products();

// Display products by catagory
void upper_casex(char* str);
void trim(char* str);
void display_products_by_category();

// Display low stock
int to_intx(const char* str);
void display_low_stock_products();

// Insert new Product
void upper_case(char*& ch);
int strlenx(const char* str);
int count_products(const char* filename);
void regrow(char*& array, int& capacity);
void insert_new_product();

// Delete a product
int get_id();
bool confirm_delete(int id);
void perform_delete(int id);
void delete_product();

// Update product
int find_product(char** products, int count, int cols, int id);
void updated_fields(char*& name, char*& price, char*& quantity, char*& category);
void save_products(const char* filename, char** products, int count, int cols);
void update_product();

// View all users
void view_users();

// View all Orders
void view_orders();

// View Pending order
void pending_orders();

// View Completed order
void completed_orders();

// Dispatch Order
void str_copy(char* dest, const char* src);
void get_current_date_dayx(char* date, char* day);
void dispatch_orders();

// Main Flow
void Admin() {
	int login = 0;
	const int max = 3;
	bool success = false;

	do {
		system("cls");
		if (admin_login()) {
			success = true;
			break;
		} else {
			login++;
			if (login < max) {
				cout << endl << "Invalid login. Try again." << endl;
				cout << "Press any key to try again...";
				_getch();
			} else {
				cout << endl << "Too many failed attempts. Please wait 30 seconds..." << endl;
				this_thread::sleep_for(chrono::seconds(30));

				char choice;
				cout << endl << "Press 'T' to try again or 'M' to return to the main menu: ";
				cin >> choice;

				if (choice == 'M' || choice == 'm') {
					cout << endl << "Returning to main menu..." << endl;
					return;
				} else {
					login = 0;
				}
			}
		}
	} while (true);
	cout << endl << "Login successful. Welcome, Admin!" << endl << endl;

	int choice;
	do {
		system("cls");
		cout << "==================== Admin Menu ====================" << endl;
		cout << "1.  Display all products" << endl;
		cout << "2.  Display products by category" << endl;
		cout << "3.  Display low stock products" << endl;
		cout << "4.  Insert new product" << endl;
		cout << "5.  Delete a product" << endl;
		cout << "6.  Update product information" << endl;
		cout << "7.  View all orders" << endl;
		cout << "8.  View pending orders" << endl;
		cout << "9.  View completed orders" << endl;
		cout << "10. Dispatch an order" << endl;
		cout << "11. View registered users" << endl;
		cout << "12. Logout" << endl;
		cout << "====================================================" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
			case 1:
				display_all_products();
				break;
			case 2:
				display_products_by_category();
				break;
			case 3:
				display_low_stock_products();
				break;
			case 4:
				insert_new_product();
				break;
			case 5:
				delete_product();
				break;
			case 6:
				update_product();
				break;
			case 7:
				view_orders();
				break;
			case 8:
				pending_orders();
				break;
			case 9:
				completed_orders();
				break;
			case 10:
				dispatch_orders();
				break;
			case 11:
				view_users();
				break;
			case 12:
				cout << "Logged out successfully." << endl << endl;
				break;
			default:
				cout << "Invalid choice. Please try again." << endl << endl;
		}

	} while (choice != 12);
}

// Check and Validate admin login
bool admin_login() {
	char ousername[] = "admin";
	char opassword[] = "12345678";

	char username[20];

	cout << "Admin Login" << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	int size = 9;
	char* password = new char[size];
	get_password(password, size);

	bool result = compare_arrays(username, ousername) && compare_arrays(password, opassword);
	delete[] password;
	return result;
}
void get_password(char* password, int size) {
	char ch;
	int i = 0;

	while (true) {
		ch = _getch();
		if (ch == 13) {
			break;
		}

		else if (ch == 8 && i > 0) {
			cout << "\b \b";
			i--;
		} else if (ch >= 32 && ch <= 126 && i < size - 1) {
			*(password + i) = ch;
			cout << '*';
			i++;
		}
	}
	password[i] = '\0';
}
bool compare_arrays(const char a[], const char b[]) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) return false;
		i++;
	}
	return a[i] == b[i];
}

// Display all products in store
void regrow_2d(char**& array, int& capacity, const int cols) {
	int newcapacity = capacity * 2;
	char** temp = new char*[newcapacity * cols];
	for (int i = 0; i < capacity * cols; ++i) {
		temp[i] = array[i];
	}
	delete[] array;
	array = temp;
	capacity = newcapacity;
}
void load_csv(const char* filename, char**& array, int& count, int& capacity, const int cols) {
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
			regrow_2d(array, capacity, cols);
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
void display_table(char** array, int count, const int cols, const char* headers[]) {
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

	cout << setfill('-') << setw(30 * cols) << "-" << setfill(' ') << endl;
}
void display_all_products() {
	system("cls");
	const int productCols = 5;
	char** products;
	int productCount, productCap;

	const char* productHeaders[] = {"ID", "Name", "Price", "Quantity", "Category"};

	load_csv("products.csv", products, productCount, productCap, productCols);
	cout << endl << "========== Admin Product View ==========" << endl;
	display_table(products, productCount, productCols, productHeaders);
	cout << "Press any key..." << endl;
	_getch();
	for (int i = 0; i < productCount * productCols; ++i) delete[] products[i];
	delete[] products;
}

// Display products by catagory
void upper_casex(char* str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
	}
}
void trim(char* str) {
	int len = 0;
	while (str[len] != '\0') len++;
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r')) str[--len] = '\0';

	int start = 0;
	while (str[start] == ' ') start++;
	if (start > 0) {
		int i = 0;
		while (str[start + i] != '\0') {
			str[i] = str[start + i];
			i++;
		}
		str[i] = '\0';
	}
}
void display_products_by_category() {
	system("cls");
	const int cols = 5;
	char** products;
	int count, capacity;

	load_csv("products.csv", products, count, capacity, cols);

	char category[50];
	cout << "Enter category to filter by: ";
	cin.ignore();
	cin.getline(category, 50);
	upper_casex(category);
	trim(category);

	const char* headers[] = {"ID", "Name", "Price", "Quantity", "Category"};
	cout << endl << "=== Products in Category: " << category << " ===" << endl;
	for (int h = 0; h < cols; ++h) cout << left << setw(30) << headers[h];
	cout << endl << setfill('-') << setw(30 * cols) << "-" << setfill(' ') << endl;

	bool found = false;
	for (int i = 0; i < count; ++i) {
		int base = i * cols;
		trim(products[base + 4]);
		if (compare_arrays(products[base + 4], category)) {
			found = true;
			for (int j = 0; j < cols; ++j) cout << left << setw(20) << products[base + j];
			cout << endl;
		}
	}
	if (!found) {
		cout << "No products found in this category." << endl;
	}
	cout << setfill('-') << setw(30 * cols) << "-" << setfill(' ') << endl << endl;
	cout << "Press any key...";
	_getch();
	for (int i = 0; i < count * cols; ++i) delete[] products[i];
	delete[] products;
}

// Display low stock
int to_intx(const char* str) {
	int result = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		if (str[i] >= '0' && str[i] <= '9') result = result * 10 + (str[i] - '0');
	return result;
}
void display_low_stock_products() {
	system("cls");
	const int cols = 5;
	char** products;
	int count, capacity;

	load_csv("products.csv", products, count, capacity, cols);

	cout << "*** Low-Stock Products (Quantity < 10) ***" << endl << endl;
	const char* headers[] = {"ID", "Name", "Price", "Quantity", "Category"};
	for (int i = 0; i < cols; ++i) cout << left << setw(15) << headers[i];
	cout << endl;
	cout << setfill('-') << setw(15 * cols) << "-" << setfill(' ') << endl;

	bool any = false;
	for (int i = 0; i < count; ++i) {
		int base = i * cols;
		int qty = to_intx(products[base + 3]);
		if (qty < 10) {
			any = true;
			for (int j = 0; j < cols; ++j) cout << left << setw(15) << products[base + j];
			cout << endl;
		}
	}
	if (!any) {
		cout << "All products have sufficient stock." << endl;
	}

	cout << setfill('-') << setw(15 * cols) << "-" << setfill(' ') << endl;
	cout << endl;
	cout << "Press any key...";
	_getch();
	for (int i = 0; i < count * cols; ++i) delete[] products[i];
	delete[] products;
}

// Insert new Product
void upper_case(char*& ch) {
	for (int i = 0; ch[i] != '\0'; ++i)
		if (ch[i] >= 'a' && ch[i] <= 'z') ch[i] -= 32;
}
int strlenx(const char* str) {
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}
int count_products(const char* filename) {
	ifstream read(filename);
	if (!read) return 0;
	int count = 0;
	char temp[200];
	while (read.getline(temp, 256)) count++;
	read.close();
	return count;
}
void regrow(char*& array, int& capacity) {
	int newcapicity = capacity * 2;
	char* temp = new char[newcapicity];
	for (int i = 0; i < capacity; ++i) temp[i] = array[i];
	delete[] array;
	array = temp;
	capacity = newcapicity;
}
void insert_new_product() {
	const char* filename = "products.csv";

	char choice;
	do {
		system("cls");
		ofstream write(filename, ios::app);
		if (!write) {
			cout << "Error opening file for writing." << endl;
			return;
		}

		int id = count_products(filename) + 1;

		char* name = new char[20];
		char* price = new char[10];
		char* quantity = new char[10];
		char* category = new char[20];

		int ncapacity = 20, nlength = 0;
		int pcapacity = 10, plength = 0;
		int qcapacity = 10, qlength = 0;
		int ccapacity = 20, clength = 0;

		char ch;

		cout << "Insert new product:" << endl;
		cin.ignore();
		do {
			nlength = 0;
			cout << "Product name: ";
			while ((ch = cin.get()) != '\n') {
				if (nlength >= ncapacity - 1) regrow(name, ncapacity);
				name[nlength++] = ch;
			}
			name[nlength] = '\0';

			if (strlenx(name) == 0) {
				cout << "Name cannot be empty. Please enter again." << endl;
			}
		} while (strlenx(name) == 0);

		do {
			plength = 0;
			cout << "Price: ";
			while ((ch = cin.get()) != '\n') {
				if (plength >= pcapacity - 1) regrow(price, pcapacity);
				price[plength++] = ch;
			}
			price[plength] = '\0';

			if (strlenx(price) == 0) {
				cout << "Price cannot be empty. Please enter again." << endl;
			}
		} while (strlenx(price) == 0);

		do {
			qlength = 0;
			cout << "Quantity: ";
			while ((ch = cin.get()) != '\n') {
				if (qlength >= qcapacity - 1) regrow(quantity, qcapacity);
				quantity[qlength++] = ch;
			}
			quantity[qlength] = '\0';

			if (strlenx(quantity) == 0) {
				cout << "Quantity cannot be empty. Please enter again." << endl;
			}
		} while (strlenx(quantity) == 0);

		do {
			clength = 0;
			cout << "Category: ";
			while ((ch = cin.get()) != '\n') {
				if (clength >= ccapacity - 1) regrow(category, ccapacity);
				category[clength++] = ch;
			}
			category[clength] = '\0';

			if (strlenx(category) == 0) {
				cout << "Category cannot be empty. Please enter again." << endl;
			}
		} while (strlenx(category) == 0);

		upper_case(name);
		upper_case(category);

		write << endl << id << "," << name << "," << price << "," << quantity << "," << category;
		write.close();

		cout << "Product added successfully!" << endl;

		delete[] name;
		delete[] price;
		delete[] quantity;
		delete[] category;

		cout << endl << "do you want to add another product? (y/n): ";
		cin >> choice;
		cin.ignore();
		cout << "Press any key...";
		_getch();
	} while (choice == 'Y' || choice == 'y');
}

// Delete a product
int get_id() {
	int id;
	cout << "Enter the Product ID: ";
	cin >> id;
	return id;
}
bool confirm_delete(int id) {
	char confirm;
	cout << "Are you sure you want to delete Product ID " << id << "? (Y/N): ";
	cin >> confirm;
	return (confirm == 'Y' || confirm == 'y');
}
void perform_delete(int id) {
	const char* filename = "products.csv";
	const int cols = 5;

	char** products;
	int count, capacity;
	load_csv(filename, products, count, capacity, cols);

	bool found = false;
	int indexToDelete = -1;

	for (int i = 0; i < count; ++i) {
		int base = i * cols;
		int currentId = 0;
		for (int j = 0; products[base][j] != '\0'; ++j) currentId = currentId * 10 + (products[base][j] - '0');

		if (currentId == id) {
			found = true;
			indexToDelete = i;
			break;
		}
	}

	if (!found) {
		cout << "Product ID not found." << endl;
	} else {
		ofstream read(filename);
		int newId = 1;
		int totalToWrite = count - 1;
		int written = 0;

		for (int i = 0; i < count; ++i) {
			if (i == indexToDelete) continue;
			int base = i * cols;

			read << newId++;
			for (int j = 1; j < cols; ++j) read << "," << products[base + j];

			written++;
			if (written < totalToWrite) read << endl;
		}

		read.close();
		cout << "Product deleted successfully!" << endl;
	}

	for (int i = 0; i < count * cols; ++i) delete[] products[i];
	delete[] products;
}
void delete_product() {
	char choice;
	do {
		system("cls");
		display_all_products();
		int id = get_id();

		if (confirm_delete(id)) {
			perform_delete(id);
		} else {
			cout << "Deletion cancelled." << endl;
		}

		cout << endl << "Do you want to delete another product? (Y/N): ";
		cin >> choice;
		cin.ignore();

	} while (choice == 'Y' || choice == 'y');
}

// Update product
int find_product(char** products, int count, int cols, int id) {
	for (int i = 0; i < count; ++i) {
		int base = i * cols;
		int currentId = 0;
		for (int j = 0; products[base][j] != '\0'; ++j) currentId = currentId * 10 + (products[base][j] - '0');
		if (currentId == id) return i;
	}
	return -1;
}
void updated_fields(char*& name, char*& price, char*& quantity, char*& category) {
	int ncap = 50, pcap = 20, qcap = 20, ccap = 30;
	char ch;

	name = new char[ncap];
	price = new char[pcap];
	quantity = new char[qcap];
	category = new char[ccap];

	cin.ignore();
	cout << "Enter updated product information:" << endl;

	int nlen;
	do {
		nlen = 0;
		cout << "Product Name: ";
		while ((ch = cin.get()) != '\n') {
			if (nlen >= ncap - 1) regrow(name, ncap);
			name[nlen++] = ch;
		}
		name[nlen] = '\0';
		if (strlenx(name) == 0) cout << "Name cannot be empty." << endl;
	} while (strlenx(name) == 0);

	int plen;
	do {
		plen = 0;
		cout << "Price: ";
		while ((ch = cin.get()) != '\n') {
			if (plen >= pcap - 1) regrow(price, pcap);
			price[plen++] = ch;
		}
		price[plen] = '\0';
		if (strlenx(price) == 0) cout << "Price cannot be empty." << endl;
	} while (strlenx(price) == 0);

	int qlen;
	do {
		qlen = 0;
		cout << "Quantity: ";
		while ((ch = cin.get()) != '\n') {
			if (qlen >= qcap - 1) regrow(quantity, qcap);
			quantity[qlen++] = ch;
		}
		quantity[qlen] = '\0';
		if (strlenx(quantity) == 0) cout << "Quantity cannot be empty." << endl;
	} while (strlenx(quantity) == 0);

	int clen;
	do {
		clen = 0;
		cout << "Category: ";
		while ((ch = cin.get()) != '\n') {
			if (clen >= ccap - 1) regrow(category, ccap);
			category[clen++] = ch;
		}
		category[clen] = '\0';
		if (strlenx(category) == 0) cout << "Category cannot be empty." << endl;
	} while (strlenx(category) == 0);

	upper_case(name);
	upper_case(category);
}
void save_products(const char* filename, char** products, int count, int cols) {
	ofstream write(filename);
	for (int i = 0; i < count; ++i) {
		int base = i * cols;
		write << products[base];
		for (int j = 1; j < cols; ++j) write << "," << products[base + j];
		if (i < count - 1) write << endl;
	}
	write.close();
}
void update_product() {
	char choice;
	do {
		system("cls");
		int id = get_id();
		const char* filename = "products.csv";
		const int cols = 5;
		char** products;
		int count, capacity;

		load_csv(filename, products, count, capacity, cols);

		int index = find_product(products, count, cols, id);
		if (index == -1) {
			cout << "Product ID not found." << endl;
		} else {
			char* name;
			char* price;
			char* quantity;
			char* category;
			updated_fields(name, price, quantity, category);

			int base = index * cols;
			delete[] products[base + 1];
			delete[] products[base + 2];
			delete[] products[base + 3];
			delete[] products[base + 4];

			products[base + 1] = name;
			products[base + 2] = price;
			products[base + 3] = quantity;
			products[base + 4] = category;

			save_products(filename, products, count, cols);

			cout << "Product information updated successfully!" << endl;
		}

		for (int i = 0; i < count * cols; ++i) delete[] products[i];
		delete[] products;
		cout << endl << "Do you want to update another product? (Y/N): ";
		cin >> choice;

	} while (choice == 'Y' || choice == 'y');
}

// View all users
void view_users() {
	system("cls");
	const int cols = 3;
	char** users;
	int count, capacity;

	load_csv("users.csv", users, count, capacity, cols);

	cout << "*** Registered Users ***" << endl;
	cout << left << setw(20) << "Username" << left << setw(20) << "Password" << left << setw(20) << "Name" << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

	for (int i = 0; i < count; ++i) {
		int base = i * cols;

		cout << left << setw(20) << users[base] << left << setw(20) << users[base + 1] << left << setw(20) << users[base + 2] << endl;
	}
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl << endl;
	cout << "Press any key...";
	_getch();
	for (int i = 0; i < count * cols; ++i) delete[] users[i];
	delete[] users;
}

// View all Orders
void view_orders() {
	system("cls");
	const int summaryCols = 8;
	char** summaries;
	int summaryCount, summaryCap;

	load_csv("orders.csv", summaries, summaryCount, summaryCap, summaryCols);

	const int detailCols = 7;
	char** details;
	int detailCount, detailCap;

	load_csv("order-details.csv", details, detailCount, detailCap, detailCols);

	cout << "========== All Orders ==========" << endl << endl;
	for (int i = 0; i < summaryCount; ++i) {
		int sbase = i * summaryCols;
		char* status;
		if (summaries[sbase + 7][0] == 'P') {
			status = (char*)"Pending";
		} else if (summaries[sbase + 7][0] == 'C') {
			status = (char*)"Complete";
		} else {
			status = (char*)"Invalid Status";
		}

		cout << "Order ID: " << summaries[sbase + 0] << " | Date: " << summaries[sbase + 1] << " (" << summaries[sbase + 2] << ")" << " | User: " << summaries[sbase + 3] << " | Phone: " << summaries[sbase + 4] << " | Adress: " << summaries[sbase + 5] << " | Total: " << summaries[sbase + 6] << " | Status: " << status << endl << endl;

		cout << left << setw(20) << "ProdID" << setw(20) << "Qty" << setw(30) << "Name" << setw(20) << "Price" << setw(20) << "Stock" << setw(20) << "Category" << endl;
		cout << setfill('-') << setw(130) << "-" << setfill(' ') << endl;

		for (int j = 0; j < detailCount; ++j) {
			int dbase = j * detailCols;
			if (compare_arrays(summaries[sbase], details[dbase])) {
				cout << left << setw(20) << details[dbase + 1] << setw(20) << details[dbase + 2] << setw(30) << details[dbase + 3] << setw(20) << details[dbase + 4] << setw(20) << details[dbase + 5] << setw(20) << details[dbase + 6] << endl;
			}
		}
		cout << setfill('-') << setw(130) << "-" << setfill(' ') << endl << endl;
		cout << endl;
	}
	cout << "========== End of Orders ==========" << endl << endl;
	cout << "Press any key...";
	_getch();

	for (int i = 0; i < summaryCount * summaryCols; ++i) delete[] summaries[i];
	delete[] summaries;

	for (int i = 0; i < detailCount * detailCols; ++i) delete[] details[i];
	delete[] details;
}

// View Pending order
void pending_orders() {
	system("cls");
	const int summaryCols = 8;
	char** orders;
	int count, capacity;

	load_csv("orders.csv", orders, count, capacity, summaryCols);

	cout << "*** Pending Orders ***" << endl;
	cout << left << setw(20) << "OrderID" << setw(20) << "Date" << setw(20) << "Day" << setw(20) << "Username" << setw(20) << "Phone" << setw(20) << "Adress" << setw(20) << "Total" << setw(20) << "Status" << endl;
	cout << setfill('-') << setw(150) << "-" << setfill(' ') << endl;

	bool any = false;
	for (int i = 0; i < count; ++i) {
		int base = i * summaryCols;
		if (orders[base + 7][0] == 'P') {
			any = true;
			for (int j = 0; j < summaryCols; ++j) cout << left << setw(20) << orders[base + j];
			cout << endl;
		}
	}

	if (!any) cout << "No pending orders." << endl;
	cout << "Press any key...";
	_getch();
	for (int i = 0; i < count * summaryCols; ++i) delete[] orders[i];
	delete[] orders;

	cout << setfill('-') << setw(150) << "-" << setfill(' ') << endl << endl;
}

// View Completed order
void completed_orders() {
	system("cls");
	const int summaryCols = 8;
	char** orders;
	int count, capacity;

	load_csv("orders.csv", orders, count, capacity, summaryCols);

	cout << "*** Completed Orders ***" << endl;
	cout << left << setw(20) << "OrderID" << setw(20) << "Date" << setw(20) << "Day" << setw(20) << "Username" << setw(20) << "Phone" << setw(20) << "City" << setw(20) << "Total" << setw(20) << "Status" << endl;
	cout << setfill('-') << setw(150) << "-" << setfill(' ') << endl;

	bool any = false;
	for (int i = 0; i < count; ++i) {
		int base = i * summaryCols;
		if (orders[base + 7][0] == 'C') {
			any = true;
			for (int j = 0; j < summaryCols; ++j) cout << left << setw(20) << orders[base + j];
			cout << endl;
		}
	}

	if (!any) {
		cout << "No completed orders." << endl;
	}

	cout << setfill('-') << setw(150) << "-" << setfill(' ') << endl << endl;
	cout << "Press any key...";
	_getch();
	for (int i = 0; i < count * summaryCols; ++i) delete[] orders[i];
	delete[] orders;
}

// Dispatch Order
void str_copy(char* dest, const char* src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
void get_current_date_dayx(char* date, char* day) {
	time_t now = time(0);
	tm localTime;

	localtime_s(&localTime, &now);

	sprintf_s(date, 20, "%02d-%02d-%04d", localTime.tm_mday, localTime.tm_mon + 1, localTime.tm_year + 1900);

	const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

	str_copy(day, days[localTime.tm_wday]);
}
void dispatch_orders() {
	system("cls");
	const int summaryCols = 8;
	char** summaries;
	int scount, scap;

	load_csv("orders.csv", summaries, scount, scap, summaryCols);

	cout << "Pending Orders:" << endl;

	bool foundx = false;
	for (int i = 0; i < scount; ++i) {
		int base = i * summaryCols;
		if (summaries[base + 7][0] == 'P') {
			cout << "Order ID: " << summaries[base + 0] << " | Date: " << summaries[base + 1] << " | User: " << summaries[base + 3] << " | Total: " << summaries[base + 6] << endl;
			foundx = true;
		}
	}

	if (!foundx) {
		cout << "No pending orders found." << endl;
		for (int i = 0; i < scount * summaryCols; ++i) delete[] summaries[i];
		delete[] summaries;

		cout << "Press any key to go back...";
		_getch();
		return;
	}

	char orderId[20];
	cout << endl << "Enter the Order ID to dispatch (or 0 to go back): ";
	cin >> orderId;

	if (orderId[0] == '0') {
		for (int i = 0; i < scount * summaryCols; ++i) delete[] summaries[i];
		delete[] summaries;
		cout << "Dispatch cancelled. Returning to menu..." << endl;
		_getch();
		return;
	}

	bool found = false;
	char date[20], day[20];
	get_current_date_dayx(date, day);
	for (int i = 0; i < scount; ++i) {
		int base = i * summaryCols;
		if (compare_arrays(summaries[base], orderId) && summaries[base + 7][0] == 'P') {
			delete[] summaries[base + 1];
			delete[] summaries[base + 2];

			summaries[base + 1] = new char[20];
			summaries[base + 2] = new char[20];

			str_copy(summaries[base + 1], date);
			str_copy(summaries[base + 2], day);

			summaries[base + 7][0] = 'C';
			summaries[base + 7][1] = '\0';
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "Order ID not found or already completed." << endl;
	} else {
		ofstream write("orders.csv");
		for (int i = 0; i < scount; ++i) {
			int base = i * summaryCols;

			bool skip = false;
			for (int j = 0; j < summaryCols; ++j) {
				if (summaries[base + j] == nullptr || summaries[base + j][0] == '\0') {
					skip = true;
					break;
				}
			}
			if (skip) continue;

			write << summaries[base];
			for (int j = 1; j < summaryCols; ++j) write << "," << summaries[base + j];
			if (i != scount - 1) write << endl;
		}
		write.close();
		cout << "Order " << orderId << " dispatched." << endl;
	}

	const int detailCols = 7;
	char** details;
	int dcount, dcap;

	load_csv("order-details.csv", details, dcount, dcap, detailCols);

	int validLines = 0;
	for (int i = 0; i < dcount; ++i) {
		if (!compare_arrays(details[i * detailCols], orderId)) {
			validLines++;
		}
	}

	int written = 0;
	ofstream writex("temp-order-details.csv");
	for (int i = 0; i < dcount; ++i) {
		int base = i * detailCols;
		if (!compare_arrays(details[base], orderId)) {
			writex << details[base];
			for (int j = 1; j < detailCols; ++j) writex << "," << details[base + j];
			writex << endl;
		}
	}

	writex.close();
	remove("order-details.csv");
	rename("temp-order-details.csv", "order-details.csv");

	cout << "Press any key...";
	_getch();
	for (int i = 0; i < scount * summaryCols; ++i) delete[] summaries[i];
	delete[] summaries;
	for (int i = 0; i < dcount * detailCols; ++i) delete[] details[i];
	delete[] details;
}