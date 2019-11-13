/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-09-2019					                                  */
/******************************************************************************/

#include <stdexcept>		//	invalid_argument
#include <cstring>			//	memcpy

#include "storage.hpp"		//	Header file	

namespace ilrd
{

void Storage::Read(char *out_, uint64_t blockIndex_)
{
    // memcpy(out_, m_dataBlocksContainer[blockIndex_].m_data, DATA_BLOCK_SIZE);

    memcpy(out_, m_map[blockIndex_].m_data, DATA_BLOCK_SIZE);
}

void Storage::Write(const char *from_, uint64_t blockIndex_)
{
    // if (static_cast<size_t>(m_dataBlocksContainer.size()) <= blockIndex_)
    // {
    //     m_dataBlocksContainer.resize(blockIndex_ + 1);
    // }

    // memcpy(m_dataBlocksContainer[blockIndex_].m_data, from_, DATA_BLOCK_SIZE);

    DataBlock dataBlock;
    memcpy(dataBlock.m_data, from_, DATA_BLOCK_SIZE);

    m_map[blockIndex_] = dataBlock;
}

Storage::DataBlock &Storage::DataBlock::operator=(const DataBlock &other_)
{
    memcpy(m_data, other_.m_data, DATA_BLOCK_SIZE);

    return *this;
}


}//namespace ilrd

