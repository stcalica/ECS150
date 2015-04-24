#include "VirtualMachine.h"
#include "Machine.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//for testing 
#include <iostream> 
#include <cstdlib> 
using namespace std;
//VirtualMachineUtils.c functions made to work in C++
extern "C"{
	TVMMainEntry VMLoadModule(const char *module);
	TVMStatus VMFilePrint(int filedescriptor, const char *format, ...);
}

/*
*	Get VMStart to work, use MainEntry function pointer to load a module and then call it 
*/
TVMStatus VMStart(int tickms, int machinetickms, int argc, char *argv[])
{
	TVMMainEntry vmmain; //creates a function pointer
	vmmain = VMLoadModule(argv[0]); //set function pointer to point to this function
	if(vmmain != NULL)//check if vmmain is pointing to the address of VMLoadModule 
		cerr << "is not null!" << endl;
	else
		vmmain(argc, argv);//run the function it points to, in a way it derefences it

  	return(VM_STATUS_SUCCESS);

}



TVMStatus VMFileWrite(int filedescriptor, void *data, int *length){
	int w = write(filedescriptor, data, *length);
	if(w < 0) //error handling
		return(VM_STATUS_FAILURE);
	else
		return(VM_STATUS_SUCCESS);
}


TVMStatus VMThreadSleep(TVMTick tick){
	
		

		return(VM_STATUS_SUCCESS);
	
	
}
