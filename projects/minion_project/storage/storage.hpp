/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-09-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_STORAGE
#define ILRD_RD6768_STORAGE

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <vector>			//	vector
#include <map>				//	map
#include <stdint.h>			//	uint32_t

#include "uncopyable.hpp"	//	Disable copies

namespace ilrd
{
static const uint32_t DATA_BLOCK_SIZE = 4 * 1024;

class Storage /* : private Uncopyable */
{

struct DataBlock;

public:
    //Constructors
    // explicit Storage() = default;
    // Storage(const Storage other_) = default;
    // ~Storage() = default;
    
    //member functions
    void Read(char *out_, uint64_t blockIndex_);
    void Write(const char *from_, uint64_t blockIndex_);

private:

    //Member variables
    // std::vector<DataBlock> m_dataBlocksContainer;
    std::map<uint64_t, DataBlock> m_map;

struct DataBlock
{
    //Constructors
    // explicit DataBlock() = default;
    // DataBlock(const DataBlock other_) = default;
    // ~DataBlock() = default;

    DataBlock &operator=(const DataBlock &other_);

    //Member variables
    char m_data[DATA_BLOCK_SIZE];
};

};

}//namespace ilrd

#endif  //ILRD_RD6768_STORAGE
