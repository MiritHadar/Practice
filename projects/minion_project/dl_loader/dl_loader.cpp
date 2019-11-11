/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 31-10-2019					                                  */
/******************************************************************************/

#include "dl_loader.hpp"		//	Header file	

/*************************Helper functions*************************************/

/******************************************************************************/

namespace ilrd
{

SharedPtr<SharedObject> DlLoader::Open(const std::string &path_)
{
	if (m_sharedObjects.find(path_) == m_sharedObjects.end())
	{
		m_sharedObjects[path_] = SharedPtr<SharedObject> 
								(new SharedObject(path_));
	}

	return m_sharedObjects[path_];
}

}//namespace ilrd
