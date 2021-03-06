#ifndef _GOOGLE_H_
#define _GOOGLE_H_

#include "runtime.h"

struct _HttpResponse;

extern RuntimeType RUNTIME;

extern unsigned int PORT;

extern unsigned int CERVER_RECEIVE_BUFFER_SIZE;
extern unsigned int CERVER_TH_THREADS;
extern unsigned int CERVER_CONNECTION_QUEUE;

// inits google main values
extern unsigned int google_init (void);

// ends google main values
extern unsigned int google_end (void);

#endif