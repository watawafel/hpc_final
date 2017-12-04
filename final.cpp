#include "bzlib.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using std::cin;
using std::cout;

unsigned int numThreads = 4;
unsigned int start, end;
static std::vector<int> partition_start (numThreads);
static std::vector<int> partition_end (numThreads);

int partition_range(int size, int numThreads, int threadID){
	
	if ( threadID == 0){
		partition_start[threadID] = 0;
		partition_end[threadID] = size / numThreads;
	}	
	else {
		partition_start[threadID] = ((size / numThreads) * threadID ) + 1;
		partition_end[threadID] =  ((size / numThreads) * (threadID + 1));
	
	}
//	cout << partition_start[threadID] << partition_end[threadID];
//	cout << "SIZE "<< size <<" THREAD " << threadID <<" start "<< start << " end " << end;
}


void print_buffer( std::vector<char>& in_buffer){
	for (std::vector<char>::iterator it = in_buffer.begin(); it != in_buffer.end(); ++it)
                std::cout  << *it;
                std::cout << '\n';
}


int main(){

	unsigned int blockSize, inputSize;
	unsigned int destLen, sourceLen, threadID;	
		
	
//	numThreads = 4;	
	blockSize = 900;
	inputSize = numThreads * blockSize;
	
	std::vector <char> in_buffer(inputSize);
	std::vector< std::vector <char> > out_buffers(inputSize);
		

	std::fstream fin("test.txt");

	if ( !fin ) {std::cerr << "Unable to open file";}
 
	else {

	   do {

		
		fin.read( &in_buffer[0], in_buffer.size());	
		int actualReadSize = fin.gcount();	
		cout << actualReadSize;							
//		if(fin.eof())
//		{	int actualReadSize = fin.gcount();	
//			
//			cout << "READ NOT FULL" << actualReadSize;
//		}


		for (int threadID = 0; threadID < numThreads; ++threadID){

			unsigned int outputSize = (600 + (actualReadSize * 1.2));

			partition_range(actualReadSize, numThreads, threadID);			

			out_buffers[threadID].resize( outputSize );

			BZ2_bzBuffToBuffCompress( reinterpret_cast<char*> (&out_buffers[threadID]), &outputSize, reinterpret_cast<char*> (&in_buffer), actualReadSize, 9, 0, 0);

		}	
		
		
	     } while( !fin.eof());

	   }
/*	
	for (std::vector<char>::iterator it = in_buffer.begin(); it != in_buffer.end(); ++it)
    		std::cout  << *it;
  		std::cout << '\n';
*/

//	cout << "BUFFER SIZE " << partition_range(0, in_buffer.size(), 4, 0);	
	//cout <<"BUFFER" << &in_buffer[1];	

   return 0;
}

