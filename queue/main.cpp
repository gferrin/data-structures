#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Queue.h"

using namespace std;
using namespace cop4530;

void print( vector<string> &destinations, vector< vector<int> > &data );
void BFS( vector<string> &destinations, vector< vector<int> > &data );

int main( int argc, char *argv[] )
{
	// check for proper input
    if( argc != 2 ){
    	cout << "Usage: ./proj3.x airline_file\n";
    	return 0;
    }

    // variable declerations 
    ifstream input( argv[1] );
    string line;
    vector<string > destinations;
    vector< string > tempData;
    vector< int > tempIntData; 
    vector< vector<string> > stringData;
    vector< vector< int > > data;
    int numCitys = 0, cityCounter = 0, dataCounter = 0;

    // read in data
    if( input.is_open() ){
    	while( getline( input, line ) ){
    		if( numCitys == 0 ){
    			numCitys = atoi( line.c_str() );

    		} else if( cityCounter < numCitys ){
    			destinations.push_back( line );	
    			cityCounter++;
    		} else {

    			istringstream iss( line );
    			copy(istream_iterator<string>(iss),
         			istream_iterator<string>(),
         			back_inserter<vector<string> >( tempData ));

    			stringData.push_back( tempData );
    			tempData.clear();
    		}
    	}
    } else {
    	cout << "file not found " << endl;
    	return 0;
    }

    // close file 
    input.close();

    // change data from string to int
    for( int i = 0; i < numCitys; ++i ){
    	for( int j = 0; j < numCitys; ++j ){
    		tempIntData.push_back( atoi( stringData.at( i ).at( j ).c_str() ) );
    	}
    	data.push_back( tempIntData );
    	tempIntData.clear();
    }
    // print out info 
    print( destinations, data );

    string userInput= "y";
    // main program loop
    do{
    	while( userInput != "y" && userInput != "Y" ){
    		cout << "Search another route? (Y/N) ";
    		getline( cin, userInput );
    		if( userInput == "n" || userInput == "N" ){
    			return 0;
    		}
    	};
    	 
    	BFS( destinations, data ); 

    	cout << "Search another route? (Y/N) ";
    	getline( cin, userInput );

    } while( userInput != "n" && userInput != "N" ); 

    return 0;
} // end of main

void print( vector<string> &destinations, vector< vector<int> > &data)
{
	cout << destinations.size() << " cities: " << endl;
	
	for( int i = 0; i < destinations.size(); ++i ){
		cout << "\t" << destinations.at( i ) << endl;
	}

	cout << "\ndirect flights between cities\n-------------------------\n";

	for( int i = 0; i < destinations.size(); ++i ){
		cout << destinations.at( i ) << ":" << endl;
		for( int j = 0; j < destinations.size(); ++j ){
			int x = data.at(i).at(j);
			if( x != 0 && x != -1 ){
				cout << "\t" << destinations.at(j) << ", $" << x << endl;
			}
		}
	}

	cout << "------------------------\n\n";

}

void BFS( vector<string> &destinations, vector< vector<int> > &data )
{
	string source, destination;
	int numSource = -1, numDestination = -1;

	cout << "Source city : " ;
	getline( cin, source );
	cout << "Destination city : ";
	getline( cin, destination );
	cout << "finding min_hop route....\n";

	for( int i = 0; i < destinations.size(); ++i ){
		if( source == destinations.at(i) ){
			numSource = i;
		}
		if( destination == destinations.at(i) ){
			numDestination = i;
		}
	}
	if( numSource == -1 ){
		cout << "\tpath not found, source city, " << source << ", not on the map\n";
		return;
	} else if( numDestination == -1 ){
		cout << "\tpath not found, destination city, " << destination << ", not on the map\n";
		return;
	} else if ( numDestination == numSource ){
		cout << "\t" << source << ", $0\n";
		return; 
	}


	Queue< vector< int > > Q;
	vector< vector< int > > visited; // this is a 2d vector which holds the particualr location in its first adress 
									 // and its parent in the secound of each subvector. Both are with respect to destinations
	vector< int > temp;
	int index = numSource, tempCity;
	bool success = false, visit = false;

	temp.push_back( numSource );
	temp.push_back( -1 );
	Q.push( temp );
	temp.clear();

	while( !Q.empty() && !success ){

		visited.push_back( Q.front() );
		int tempCity = Q.front().at(0);
		// check all viable citys connected to tempCity
		for( int i = 0; i < destinations.size(); ++i ){
			int x = data.at( tempCity ).at( i );
			if( x != 0 && x != -1 ){
				// now make sure it hasnt already been visited
				visit = false;
				for( int j = 0; j < visited.size(); ++j ){
					if( visited.at(j).at(0) == i ){
						visit = true;
					}
				}
				if( !visit ){ // if this is met i is a new node
					temp.push_back( i );
					temp.push_back( tempCity );
					Q.push( temp );
					temp.clear();
					if( i == numDestination ){
						visited.push_back( Q.back() );
						success = true;
						break;
					} 
				}
			}
		}
		Q.pop();
	}
	// organize the visited vector into the string path vector with correct path
	if( success ){
		vector<string> path;
		int current = visited.back().at(0), cost = 0;
		path.push_back( destinations.at(current) );
		int parent = visited.back().at(1);
		while( parent != -1 ){
			path.push_back( destinations.at(parent) );
			// find the cost
			cost += data.at( parent ).at( current );
			for( int i = 0; i < visited.size(); ++i ){
				if( parent == visited.at(i).at(0) ){
					current = parent;
					parent = visited.at(i).at(1);
				}
			}
		}
		// output the shortest path 
		cout << "\t";
		for( int j = path.size() - 1; j >= 0 ; --j ){
			if( j != 0 ) {
				cout << path.at(j) << " --> ";
			} else {
				cout << path.at(j) << ", $" << cost << endl;
			}

		}

	} else {
		cout << "\tpath not found" << endl;
	}

}














