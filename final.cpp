#include "bzlib.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using std::cin;
using std::cout;

unsigned int numThreads =4;
unsigned int start, end;
static std::vector<int> partition_start (numThreads);
static std::vector<int> partition_end (numThreads);

int partition_range(int start, int end, int size, int numThreads, int threadID){
	
	if ( threadID == 0){
		partition_start[threadID] = 0;
		partition_end[threadID] = size / numThreads;
	}	
	else {
		partition_start[threadID] = ((size / numThreads) *threadID ) + 1;
		partition_end[threadID] =  ((size / numThreads) * (threadID + 1));
	
	}
//	cout << partition_start[threadID] << partition_end[threadID];
//	cout << "SIZE "<< size <<" THREAD " << threadID <<" start "<< start << " end " << end;
}

int main(){

	unsigned int blockSize, inputSize;
	unsigned int destLen, sourceLen, threadID;	
		
	
//	numThreads = 4;	
	blockSize = 900;
	inputSize = numThreads * blockSize;
	
	std::vector <char> in_buffer(inputSize);
	std::vector <char> out_buffer(inputSize);
		

	std::fstream fin("test.txt");

	if ( !fin ) {std::cerr << "Unable to open file";}
 
	else {

	   do {

		for (int threadID = 0; threadID < numThreads; ++threadID){

			partition_range(start, end, in_buffer.size(), numThreads, threadID);
			
	
			fin.read( &in_buffer[partition_start[threadID]], in_buffer[partition_end[threadID]]); //in_buffer.size());
//		cout<<"EXIT READ";
		for (int i = partition_start[threadID]; i < partition_end[threadID]; ++i){
			//std::cout << "GOT TO LOOP";
			std::cout  << *in_buffer[5];
                	std::cout << '\n';
			}				
					
			}		
		//	BZ2_bzBuffToBuffCompress(out_buffer.data(), &inputSize, in_buffer.data(), inputSize, 900, 0, 0);
//		std::copy(in_buffer.begin(), in_buffer.end(), out_buffer);
		//out_buffer[]i=&in_buffer[0];		

	     } while( !fin.eof());

	   }
	
	for (std::vector<char>::iterator it = in_buffer.begin(); it != in_buffer.end(); ++it)
    		std::cout  << *it;
  		std::cout << '\n';


//	cout << "BUFFER SIZE " << partition_range(0, in_buffer.size(), 4, 0);	
	//cout <<"BUFFER" << &in_buffer[1];	

   return 0;
}

