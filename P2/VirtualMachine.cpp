#include "VirtualMachine.h"
#include "Machine.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <vector>
#include<list>
//for testing 
#include <iostream> 
#include <cstdlib> 
using namespace std;
//VirtualMachineUtils.c functions made to work in C++
extern "C"{
	TVMMainEntry VMLoadModule(const char *module);
	TVMStatus VMFilePrint(int filedescriptor, const char *format, ...);
	TVMStatus VMThreadSleep(TVMTick tick);
	void MachineInitialize(int timeout);
	void MachineRequestAlarm(useconds_t usec, TMachineAlarmCallback callback, void *calldata);
	void MachineEnableSignals(void);

}
class tcb{
	public: 
	TVMThreadPriority priority; 
	TVMThreadID id; 
	TVMThreadState state;	
	TVMTick ticks;
	uint8_t base; // stack pointer base 
	TVMMemorySize memsize;
	TVMMutexID mid;
	TVMThreadEntry entry; //entry function need to make a skeleton wrapper for it 
	
};
tcb *current; // ptr to the current thread
tcb primary; //thread priority is normal 
tcb idle;
vector<*tcb> all;
//multiple ready queues one for each priority, thread state declares what goes first 
//goes into the ready queue when thread is activated
list<*tcb> high;
list<*tcb> normal;
list<*tcb> low;
//sleeping thread queue
list<*tcb> sleep;
//mutex thread queue


// The scheduler is responsible for determining what is the highest priority and therefore what should be running
int volatile gtick;


void AlarmCallback(void *params);
void scheduler(void);

TVMStatus VMStart(int tickms, int machinetickms, int argc, char *argv[])
{


	MachineInitialize(machinetickms);
	MachineRequestAlarm(machinetickms, AlarmCallback, NULL); //arguments? and alarmCallback being called?	
	MachineEnableSignals();


	TVMMainEntry vmmain; //creates a function pointer
	vmmain = VMLoadModule(argv[0]); //set function pointer to point to this function
	if(vmmain == NULL)//check if vmmain is pointing to the address of VMLoadModule 
		cerr << "is  null!" << endl;
	else
		vmmain(argc, argv);//run the function it points to, in a way it derefences it

  	return(VM_STATUS_SUCCESS);

}

void AlarmCallback(void *param){
	if(gtick > 0)
		gtick--;

}

TVMStatus VMThreadSleep(TVMTick tick){
	gtick = tick*1000;
	while(gtick > 0){


	}
	return(VM_STATUS_SUCCESS);
}


TVMStatus VMFileWrite(int filedescriptor, void *data, int *length){
	write(filedescriptor, data, *length);
	return(VM_STATUS_SUCCESS);
}
//check flow chart
TVMStatus VMThreadCreate(TVMThreadEntry entry, void *param, TVMMemorySize memsize, TVMThreadPriority prio, TVMThreadIDRef tid){
	TMachineSignalState oldstate;
	MachineSuspendSignals(&oldstate);

	
	return VM_STATUS_SUCCESS;
	
}

TVMStatus VMThreadActivate(TVMThreadID thread){
	TMachineSignalState oldstate;
	MachineSuspendSignals(&oldstate);
	
	
	
	return VM_STATUS_SUCCESS;

}



