#include "bzlib.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

//g++ -o final final.cpp -lbz2 -L.

using std::cin;
using std::cout;

unsigned int numThreads = 4;

static std::vector<int> partition_start (numThreads);
static std::vector<int> partition_end (numThreads);


int partition_range (const int global_start, const int global_end,
		const int num_partitions, const int rank,
		int& local_start, int& local_end)
{
	// Total length of the iteration space.
	const int global_length = global_end - global_start;

	// Simple per-partition size ignoring remainder.
	const int chunk_size = global_length / num_partitions;

	// And now the remainder.
	const int remainder = global_length - chunk_size * num_partitions;

	// We want to spreader the remainder around evening to the 1st few ranks.
	// ... add one to the simple chunk size for all ranks < remainder.
	if (rank < remainder)
	{
		local_start = global_start + rank * chunk_size + rank;
		local_end   = local_start + chunk_size + 1;
	}
	else
	{
		local_start = global_start + rank * chunk_size + remainder;
		local_end   = local_start + chunk_size;
	}

	return 0;
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
	std::vector< std::vector <char> > out_buffers(numThreads);


	std::fstream fin("test.txt");

	if ( !fin ) {std::cerr << "Unable to open file";}

	else {

		while(!fin.eof()) {


			fin.read( &in_buffer[0], in_buffer.size());
			int actualReadSize = fin.gcount();
	//				cout << " ACTUAL READ SIZE " << actualReadSize;

			in_buffer.resize(actualReadSize);
			//		print_buffer(in_buffer);
	//		cout << "BUFFER SIZE " << in_buffer.size();
	//	std::vector< std::vector <char> > out_buffers(numThreads);
			for (int ID = 0; ID < numThreads; ++ID){
				
				//			unsigned int outputSize = (600 + (actualReadSize * 1.2));
				if( actualReadSize > 50 ){
				partition_range(0, actualReadSize, numThreads, ID, partition_start[ID], partition_end[ID]);
				//			cout << sizeof(std::vector<char>) + (sizeof(char) * in_buffer.size());	
				}
				else {
				
					partition_range(0, actualReadSize, 1, ID, partition_start[ID], partition_end[ID]);
					numThreads = 1;
					}

				out_buffers[ID].resize(((partition_end[ID] - partition_start[ID]) * 1.2) + 600);
				//			cout << "THREAD ID "<< threadID << "SIZE " << out_buffers[threadID].size();

				unsigned int destLen = out_buffers[ID].size();
				char *dest = (char*) &out_buffers[ID][0];
				char *source = (char*) (&in_buffer);
				inputSize = partition_end[ID] - partition_start[ID];
				//                      char* dest = reinterpret_cast<char*> (&out_buffers[ID]);
				//                      char * source = reinterpret_cast<char*> (&in_buffer);

				std::vector<char> temp ((in_buffer.begin() + partition_start[ID]), (in_buffer.begin() + partition_end[ID]));
				char*temp1 = (char*) (&temp[0]);		

//				cout << "THREAD ID " << ID << " ";
//				print_buffer(temp);		

				int result = BZ2_bzBuffToBuffCompress( dest, &destLen, temp1, inputSize, 9, 0, 0);
				//&in_buffer[partition_start[ID]]
				switch (result)

				{
					case BZ_OK: /*cout << "BZ_OK"*/; break;	
					case BZ_OUTBUFF_FULL:/* cout<< "FULL"*/; break;
					case BZ_MEM_ERROR: /*cout << "MEMERROR"*/; break;

				} 

				
			}  


		}

	}

	return 0;
}
