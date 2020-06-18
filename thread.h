#ifndef __libcore_concurrency_thread__
#define __libcore_concurrency_thread__

#include <libcore-types/types.h>

typedef AbstractPointer ThreadInputData;
typedef AbstractPointer ThreadOutputData;
typedef ThreadOutputData (*ThreadCode)(ThreadInputData);
typedef void (*ThreadHook)(ThreadInputData);

typedef struct {
	ThreadHook ThreadOnSart;	// public, set by user, delegate to run when thread starts
	ThreadCode CodeToRun;		// public, set by user, points to what to run
	ThreadHook ThreadOnFinish;	// public, set by user, delegate to run when thread finishes

	AbstractPointer houseKeeping;  // private, implementation depenent, don't touch

} Thread;
typedef Thread* ThreadRef;
typedef ThreadRef* ThreadRefRef;

extern ThreadRef ThreadNew();											  // creates a new thread
extern void ThreadDelete(ThreadRefRef thread);							  // frees resources and resets the pointer to `nil`
extern void ThreadRun(ThreadRef thread, ThreadInputData inputData);		  // runs the thread, blocks until thread finishes
extern void ThreadRunAsync(ThreadRef thread, ThreadInputData inputData);  // runs the thread, returns immediately
extern void ThreadWaitForFinish(ThreadRef thread);						  // blocks until thread finishes

#endif