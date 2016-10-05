# Producer_consumer
This program has a circler array to work as a buffer. Two threads will run. One will fill the buffer and use a semaphore to insure that it is not overfilled. The other will remove items from the buffer using a semaphore to insure that it does not try to remove an item if it is empty. Context switching will toggle which thread is run
