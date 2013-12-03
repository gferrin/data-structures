#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstring>

using namespace std;

namespace cop4530
{

static const unsigned int max_prime = 64997;

class HashTable {
  public:
  	HashTable();
  	HashTable( unsigned int n );
  	~HashTable();

  	void add_user( pair <string, string> , bool encrypted = false );
  	bool remove_user( const string & );
    bool find_user( pair <string, string> );
  	void change_password( pair <string, string>, const string &, bool encrypted = false );
  	void print_table();
    void read_from_file( const string & );
  	void write_to_file( const string & );
  	int size();


  private:
    unsigned int Index (const string &);
    unsigned int hash_function(const string& );
    unsigned int prime_below(unsigned int);
    void setPrimes(vector<unsigned int> &);
    vector < list < pair <string, string> > > bucketVector;

};

#include "hashtable.cpp"

}

#endif
