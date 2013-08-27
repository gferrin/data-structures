#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP

#include "hashtable.h"

using namespace std;
using namespace cop4530;

static const unsigned int default_capacity = 11;
char salt[] = "$1$########";

HashTable::HashTable() : bucketVector( default_capacity ) {}

HashTable::HashTable( unsigned int n ) : bucketVector( prime_below( n )) {}

HashTable::~HashTable()
{
  bucketVector.clear();
}

void HashTable::add_user( pair <string , string> user, bool encrypted )
{
  char * password = new char [100];

  if( !encrypted ){
    strcpy ( password, crypt( user.second.c_str(), salt));
    for( int i = 12; i < 100; ++i ){  password[ i - 12 ] = password[ i ]; }
    user.second = password;
  }


  unsigned int hash_value = Index( user.first );

  if( bucketVector[ hash_value ].empty() ){
    bucketVector[ hash_value ].push_front( user );
  } else { // check to make sure the entry does not already exist
    
    list< pair <string, string> >::iterator itr;
    
    for( itr = bucketVector[ hash_value ].begin(); itr != bucketVector[ hash_value ].end(); itr++ ){
      if( itr->first == user.first ){
        cout << "attempting to add username which already exists" << endl;
        return;
      }
    }

    bucketVector[ hash_value ].push_front( user );
  }
}

bool HashTable::remove_user( const string & username )
{ 
  unsigned int hash_value = Index( username );
  if( bucketVector[ hash_value ].empty() ){
    return false;
  } else {
    list< pair <string, string> >::iterator itr;
    
    for( itr = bucketVector[ hash_value ].begin(); itr != bucketVector[ hash_value ].end(); itr++ ){
      if( itr->first == username ){
        bucketVector[ hash_value ].remove( *itr );
        return true;
      }
    }
    return false;
  }
}

bool HashTable::find_user( pair <string , string> user )
{
  char * password = new char [100];
  unsigned int hash_value = Index( user.first );
  strcpy ( password, crypt( user.second.c_str(), salt));
  for( int i = 12; i < 100; ++i ){ password[ i - 12 ] = password[ i ]; }
  user.second = password;

  if( bucketVector[ hash_value ].empty() ){
    return false;
  } else {
    list< pair <string, string> >::iterator itr;
    
    for( itr = bucketVector[ hash_value ].begin(); itr != bucketVector[ hash_value ].end(); itr++ ){
      if( itr->first == user.first && itr->second == user.second ){
        return true;
      }
    }
    return false;
  }
}

void HashTable::change_password( pair <string, string> user, const string & new_password, bool encrypted  )
{
  char * password = new char [100];

  if( !encrypted ){

    strcpy ( password, crypt( user.second.c_str(), salt));
    for( int i = 12; i < 100; ++i ){ password[ i - 12 ] = password[ i ]; }
    user.second = password;
    strcpy ( password, crypt( new_password.c_str(), salt));
    for( int i = 12; i < 100; ++i ){ password[ i - 12 ] = password[ i ]; }
  }

  unsigned int hash_value = Index( user.first );
  if( bucketVector[ hash_value ].empty() ){
    cout << "*****Error: User not found.  Could not change user password\n" << endl;
  } else {
    list< pair <string, string> >::iterator itr;
    
    for( itr = bucketVector[ hash_value ].begin(); itr != bucketVector[ hash_value ].end(); itr++ ){
      if( itr->first == user.first ){
        if( itr->second == user.second ){
          itr->second = password;
        } else {
          cout << "*****Error: Password incorrect.  Could not change user password\n";
        }
        return;
      }
    }
    cout << "*****Error: User not found.  Could not change user password\n" << endl;
  }
}

void HashTable::print_table()
{
  for( unsigned int i = 0; i < bucketVector.capacity(); ++i ){
    if( bucketVector[i].empty() ){
      cout << "V[" << i << "]:" << endl;
    } else if( bucketVector[i].size() == 1 ) {
      cout << "V[" << i << "]: " 
           << bucketVector[i].front().first << ":"
           << bucketVector[i].front().second << endl;
    } else {
      list< pair <string, string> >::iterator itr;

      cout << "V[" << i << "]: ";
      for( itr = bucketVector[i].begin(); itr != bucketVector[i].end(); itr++ ){
        cout << itr->first << ":" << itr->second << "\t";
      }
      cout << endl;
    }
  }
}

void HashTable::read_from_file( const string & filename )
{
  ifstream file( filename.c_str( ) );
  string line, token;

  vector<string> tokens; 

  while( getline( file, line ) ){
    istringstream stream( line );
    while( getline( stream, token, ':' )){
      tokens.push_back( token );
    }
  }
  if( tokens.size() % 2 == 0 ){
    string temp;
    for( unsigned int i = 0; i < tokens.size(); ++i ){
      if( i % 2 == 0 ){
        temp = tokens[ i ];
      } else {
        pair < string, string > temp_pair ( temp, tokens[i] );
        add_user( temp_pair, true );
      }
    }
  } else {
    cout << "Error in read from file" << endl;
  }

}

void HashTable::write_to_file( const string & filename )
{
  ofstream file( filename.c_str() );

  for( unsigned int i = 0; i < bucketVector.capacity(); ++i ){
    if( !bucketVector[i].empty() ){
      list< pair <string, string> >::iterator itr;
      for( itr = bucketVector[i].begin(); itr != bucketVector[i].end(); itr++ ){
        file << itr->first << ":" << itr->second << "\n";
      }
    }
  }

  file.close();
}

int HashTable::size()
{
  int size = 0;
  for( unsigned int i = 0; i < bucketVector.capacity(); ++i ){
    size += bucketVector[i].size();
  }
  return size;
}

  //Returns the bucket index where the pair should be inserted
  unsigned int HashTable::Index (const string & key)
  {
    return hash_function(key) % bucketVector.capacity();
  }
  
    //Returns the hashed index
    unsigned int HashTable::hash_function (const string & s)
    {
      unsigned int i;
      unsigned long bigval = s[0];
      for (i = 1; i < s.size(); ++i)
        bigval = ((bigval & 65535) * 18000) + (bigval >> 16) + s[i];
      bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
      return bigval & 65535;
      
    }
    
    // returns largest prime number <= n or zero if input is too large
    // This is likely to be more efficient than prime_above(), because
    // it only needs a vector of size n
    unsigned int HashTable::prime_below (unsigned int n)
    {
      if (n > max_prime)
        {
  	std::cerr << "** input too large for prime_below()\n";
  	return 0;
        }
      if (n == max_prime)
        {
  	return max_prime;
        }
      if (n <= 1)
        {
  	return 0;
        }
      
      // now: 2 <= n < max_prime
      vector <unsigned int> v (n + 1);
      setPrimes(v);
      while (n > 2)
        {
  	if (v[n] == 1)
  	  return n;
  	--n;
        }
      
      return 2;
    }
    
    //Sets all prime number indexes to 1. Called by method prime_below(n) 
    void HashTable::setPrimes(vector<unsigned int>& vprimes)
    {
      int i = 0;
      int j = 0;
      
      vprimes[0] = 0;
      vprimes[1] = 0;
      int n = vprimes.capacity();
      
      for (i = 2; i < n; ++i)
        vprimes[i] = 1;
      
      for( i = 2; i*i < n; ++i)
        {
  	if (vprimes[i] == 1)
  	  for(j = i + i ; j < n; j += i)
  	    vprimes[j] = 0;
        }
    }
    
#endif

