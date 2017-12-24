#include "Init.h"
#include "Thread.h"
#include "my.h"
#include "Scheduler.h"
#include <unistd.h>
#include <stdio.h>
static pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
int RunScheduler(void)
{


	int i = 0;
	while (1)
	{
		pthread_mutex_lock(&run_lock);
		while (sign != 0)
			pthread_cond_wait(&run_wait, &run_lock);


		// //레디큐가 비었는지 먼저 확인
		// if (NULL == ReadyQHead && NULL == ReadyQTail)
		// {

		// 	sleep(TIMESLICE);
		// 	continue;
		// }

		// if (i == 0)
		// {
		// 	sleep(TIMESLICE);
		// 	__thread_wakeup(ReadyQHead);//깨우고
		// 	ReadyQHead->status = THREAD_STATUS_RUN;

		// 	sleep(TIMESLICE);

		// 	i++;
		// }
		

		// ReadyQHead->bRunnable = 0;
		// if (ReadyQHead != ReadyQTail)
		// 	Ready_dequeue();//자리를 바꿈

							
		if(ReadyQHead!=NULL)
		__ContextSwitch(Running_Thread,Ready_peek());
		//if(ReadyQTail->status==THREAD_STATUS_ZOMBIE)
		//Ready_remove_element(ReadyQTail);



		//Running_Thread->tid=Ready_peek()->tid;
		//__thread_wakeup(Running_Thread);

		sleep(TIMESLICE);

		pthread_mutex_unlock(&run_lock);

		//pthread_kill(rp->tid, SIGUSR1);

	}
}
void __ContextSwitch(Thread* pCurThread, Thread* pNewThread){
	if(pCurThread!=NULL && pCurThread->status != THREAD_STATUS_BLOCKED){
		Running_Thread->bRunnable = 0;
		if(Running_Thread->status != THREAD_STATUS_ZOMBIE)
			Running_Thread->status = THREAD_STATUS_READY;
		//Ready_enqueue(Running_Thread);
		if(ReadyQHead==NULL)
		{
			ReadyQHead=Running_Thread;
		}
		else{
			ReadyQTail->pNext=Running_Thread;
			Running_Thread->pPrev=ReadyQTail;
		}
		ReadyQTail=Running_Thread;
		pthread_kill(Running_Thread->tid, SIGUSR1);
		//usleep(10);
	}

	Running_Thread = pNewThread;
	__thread_wakeup(Running_Thread);
}

// void __ContextSwitch(Thread* pCurThread, Thread* pNewThread)
// {    //pCurThread->bRunnable=THREAD_STATUS_RUN;
// 	if (pCurThread == NULL || pNewThread == NULL)
// 	{
// 		// pthread_kill(pCurThread->tid, SIGUSR2);

// 		sleep(2);

// 		return;
// 	}

// 	//pNewThread->bRunnable=THREAD_STATUS_READY;

// 	// if (pCurThread->status == THREAD_STATUS_BLOCKED)
// 	// {

// 	// 	Ready_remove_element(pCurThread);
// 	// 	//pCurThread->pPrev->pNext=NULL;

// 	// }


// 		__thread_wakeup(pNewThread);
// 		if (pCurThread == NULL || pNewThread == NULL)
// 		{
// 			// pthread_kill(pCurThread->tid, SIGUSR2);

// 			sleep(2);

// 			return;
// 		}

// 		pthread_kill(pCurThread->tid, SIGUSR1);
// 		pNewThread->status = THREAD_STATUS_RUN;
// 		// if (pCurThread->status == THREAD_STATUS_RUN)

// 		// 	if (pCurThread->status == THREAD_STATUS_RUN)
// 				pCurThread->status = THREAD_STATUS_READY;
	
// 	//pNewThread->bRunnable=THREAD_STATUS_RUN;


// }