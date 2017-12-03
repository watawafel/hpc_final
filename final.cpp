#include "bzlib.c"

#include <iostream>
using std::cin;
using std::cout;
//https://www.gamedev.net/forums/topic/464525-bzip2/

static void _Multiple_thread_compress( void* arg )

		{
#ifdef MANAGED_ENABLE_COMPRESSION
			CompressionCommandMT *cmd = static_cast<CompressionCommandMT*>(arg);
			thisType::CompressionHeap& ch = cmd->_this->compressedHeap;
			thisType::MemoryBlockIter mb = cmd->_this->memoryBlocks.begin();

			IterSeek< MemoryBlockContainer >( cmd->memoryBlockIndex, mb );

			unsigned int destLen	= ch.heapSize - ch.cur;
			unsigned int sourceLen	= mb->sizeBytes;
			char *dest	  = (char*) ch.heap + ch.cur;
			char *source  = (char*) mb->address;
	
			int result = BZ2_bzBuffToBuffCompress( dest, &destLen, source, sourceLen,
									  cmd->blockSize, 0, cmd->workFactor );

			switch (result)
			{
				case BZ_OK: 
					std::cout << mb->sizeBytes << " compressed to: " << destLen << std::endl;
					ch.memoryBlocks.back().address = ch.heap + ch.cur;
					ch.memoryBlocks.back().sizeBytes = destLen;
					ch.cur += destLen;
					break;
				case BZ_OUTBUFF_FULL: break;
				case BZ_MEM_ERROR: break;
			}
#endif		
		}

int main(int argc, char *argv[])
{
//	unsigned int destLen	= ch.heapSize - ch.cur;
//	unsigned int sourceLen	= mb->sizeBytes;
//	char *dest	  = (char*) ch.heap + ch.cur;
//	char *source  = (char*) mb->address;
    
char ch;
    unsigned m = 10;
    while (cin && m--) {
        cin.read(&ch, sizeof(ch));
	unsigned int destLen = sizeof(ch);
	unsigned int sourceLen = sizeof(ch);
	char *dest =  &ch;
	char *source = &ch;
        BZ2_bzBuffToBuffCompress(dest, &destLen, source, sourceLen, 0,0,0);	
	cout << ch;
	}
    return 0;
}

