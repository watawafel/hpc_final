#include "bzlib.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

using std::cin;
using std::cout;

int partition_range(int size){
	cout <<" size "<< size;
}

int main(){

	int numThreads, blockSize, inputSize;
	int destLen, sourceLen;	

	numThreads = 4;	
	blockSize = 900;
	inputSize = numThreads * blockSize;
	
	std::vector <char> in_buffer(inputSize);
	std::vector <char> out_buffer(inputSize);

	std::fstream fin("dummy.txt");

	if ( !fin ) {std::cerr << "Unable to open file";}
 
	else {

	   do {
		fin.read( &in_buffer[0], in_buffer.size() );

		//int result = BZ2_bzBuffToBuffCompress();

	     } while( !fin.eof());

	   }
	
	for (std::vector<char>::iterator it = in_buffer.begin(); it != in_buffer.end(); ++it)
    		std::cout  << *it;
  		std::cout << '\n';

	cout << "BUFFER SIZE " << partition_range(in_buffer.size());	
	//cout <<"BUFFFFER" << &buffer[1];	

   return 0;
}

