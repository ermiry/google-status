#ifndef _GOOGLE_SERVICE_H_
#define _GOOGLE_SERVICE_H_

struct _HttpResponse;

extern struct _HttpResponse *google_works;
extern struct _HttpResponse *current_version;

extern struct _HttpResponse *catch_all;

extern unsigned int google_service_init (void);

extern void google_service_end (void);

#endif