#include <iostream>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

int main( int argc, char *argv[] )
{
	unsigned int x; 
	char input;
	string filename, name, password, new_password;
	pair < string, string > temp_pair;

	cout << "Enter preferred hash table capacity: ";
	cin >> x;
	HashTable table( x );

	while( input != 'x' ){
		cout << "\n\nl - Load From File\na - Add User\nr - Remove User\nf - Find User\n";
		cout << "d - Dump HashTable\ns - HashTable Size\nw - Write to Password File\n";
		cout << "x - Exit program\n\nEnter choice : ";

		cin >> input; 
		switch( input )
		{
			case 'l':
				cout << "Enter password file name to load from: ";
				cin >> filename;
				table.read_from_file( filename );
				break;
			case 'a':
				cout << "Enter username: ";
				cin >> name;
				cout << "Enter password: ";
				cin >> password;
				temp_pair.first = name;
				temp_pair.second = password;
				table.add_user( temp_pair );
				cout << "\nUser " << name << " added.";
				break;
			case 'r':
				cout << "Enter username: ";
				cin >> name;
				if( table.remove_user( name ) ){
					cout << "User " << name << " deleted.\n";
				} else {
					cout << "*****Error: User not found.  Could not delete user\n";
				}
				break;
			case 'c':
				cout << "Enter username: ";
				cin >> name;
				cout << "Enter password: ";
				cin >> password;
				cout << "\nEnter new password: ";
				cin >> new_password;
				temp_pair.first = name;
				temp_pair.second = password;
				table.change_password( temp_pair, new_password );
				break;
			case 'f':
				cout << "Enter username: ";
				cin >> name;
				cout << "Enter password: ";
				cin >> password;
				temp_pair.first = name;
				temp_pair.second = password;
				if( table.find_user( temp_pair ) ){
					cout << "User \'" << name << "\' found.\n";
				} else {
					cout << "User \'" << name << "\' not found.\n";
				}
				break;
			case 'd':
				table.print_table();
				break;
			case 's':
				cout << "Size of hashtable: " << table.size() << endl;
				break;
			case 'w':
				cout << "Enter password file name to write to: ";
				cin >> filename;
				table.write_to_file( filename );
				break;
			case 'x':
				break;
			default:
				cout << "*****Error: Invalid entry.  Try again.\n";
		}
	} 



	return 0;
}