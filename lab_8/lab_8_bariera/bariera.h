#ifndef BARRIER_H
#define BARRIER_h

void bariera_init(int threads_count);
void bariera(void);                     // wywolanie bariery przez watek
void bariera_destroy(void);

#endif