#include "ALL_HEADER.h"

struct Ring_Queue_struct Ring_Queue;

char Ring_Queue_Check(struct Ring_Queue_struct *Q, short Queue_Position)
{
	if(Q->Queue[Queue_Position] == Queue_Full)
	{
		return Queue_Status_Full;
	}
	else if(Q->Queue[Queue_Position] == Queue_Empty)
	{
		return Queue_Empty;
	}
}

void Ring_Queue_Enqueue(struct Ring_Queue_struct *Q)
{
	short i;
	Ring_Queue_Check(Q, i);
}

void Ring_Queue_Dequeue(void)
{
	
}