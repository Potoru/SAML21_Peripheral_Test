#ifndef _RING_QUEUE_TEST_H_
#define _RING_QUEUE_TEST_H_

#define Queue_Status_Full true
#define Queue_Status_Empty false
#define Queue_Empty 0
#define Queue_Full !Queue_Empty


#define Ring_Queue_Size 256

struct Ring_Queue_struct {
	short front, tail;
	char Queue[Ring_Queue_Size];
};

#endif