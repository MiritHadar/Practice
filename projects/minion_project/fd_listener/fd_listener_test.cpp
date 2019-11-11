/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 20-10-2019					                                  */
/******************************************************************************/

#include <iostream>			//	cout 	

#include "fd_listener.hpp"		//	Header file		

using namespace ilrd;

int main()
{
	FDListener::FDVector fdVectorInput;
	fdVectorInput.push_back(FDListener::FDPair(0, FDListener::READ));
	fdVectorInput.push_back(FDListener::FDPair(1, FDListener::READ));
	fdVectorInput.push_back(FDListener::FDPair(2, FDListener::READ));

	FDListener listner;

	FDListener::FDVector fdVectorOutput = listner(fdVectorInput, 5);

    for(size_t i = 0; i < fdVectorOutput.size(); ++i)
    {
		if (fdVectorOutput[i].first != fdVectorInput[i].first)
		{
			std::cout << "ERROR in line: " << __LINE__ << std::endl;
		}
    }

	return 0;
}
