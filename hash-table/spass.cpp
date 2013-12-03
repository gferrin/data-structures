#include <iostream>
#include <termios.h>
#include <stdio.h>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

int getch();


int main( int argc, char *argv[] )
{
	unsigned int x; 
	char input;
	const char *correct_password="null";
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
				password = getpass("Enter password: ");
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
				password=getpass("Enter password: ");
				new_password = getpass("\nEnter new password: ");
				temp_pair.first = name;
				temp_pair.second = password;
				table.change_password( temp_pair, new_password );
				break;
			case 'f':
				cout << "Enter username: ";
				cin >> name;
				password=getpass("Enter password: ");
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

int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}


string getpass(const char *prompt, bool show_asterisk=false)
{
  const char BACKSPACE=127;
  const char RETURN=10;

  string password;
  unsigned char ch=0;

  cout <<prompt<<endl;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}