#ifndef _GOOGLE_ROUTES_SERVICE_H_
#define _GOOGLE_ROUTES_SERVICE_H_

struct _HttpReceive;
struct _HttpRequest;

// GET /api/google
extern void google_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET /api/google/version
extern void google_version_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET *
extern void google_catch_all_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

#endif