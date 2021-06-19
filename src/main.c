#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <signal.h>

#include <cerver/version.h>
#include <cerver/cerver.h>

#include <cerver/http/http.h>
#include <cerver/http/route.h>

#include <cerver/utils/log.h>
#include <cerver/utils/utils.h>

#include "google.h"
#include "version.h"

#include "routes/service.h"

static Cerver *google_api = NULL;

void end (int dummy) {
	
	if (google_api) {
		cerver_stats_print (google_api, false, false);
		cerver_log_msg ("\nHTTP Cerver stats:\n");
		http_cerver_all_stats_print ((HttpCerver *) google_api->cerver_data);
		cerver_log_line_break ();
		cerver_teardown (google_api);
	}

	(void) google_end ();

	cerver_end ();

	exit (0);

}

static void google_set_google_routes (HttpCerver *http_cerver) {

	/* register top level route */
	// GET /api/status
	HttpRoute *google_route = http_route_create (REQUEST_METHOD_GET, "api/status", google_handler);
	http_cerver_route_register (http_cerver, google_route);

	/* register google children routes */
	// GET api/status/version
	HttpRoute *google_version_route = http_route_create (REQUEST_METHOD_GET, "version", google_version_handler);
	http_route_child_add (google_route, google_version_route);

}

static void start (void) {

	google_api = cerver_create (
		CERVER_TYPE_WEB,
		"google-api",
		PORT,
		PROTOCOL_TCP,
		false,
		CERVER_CONNECTION_QUEUE
	);

	if (google_api) {
		/*** cerver configuration ***/
		cerver_set_receive_buffer_size (google_api, CERVER_RECEIVE_BUFFER_SIZE);
		cerver_set_thpool_n_threads (google_api, CERVER_TH_THREADS);
		cerver_set_handler_type (google_api, CERVER_HANDLER_TYPE_THREADS);

		/*** web cerver configuration ***/
		HttpCerver *http_cerver = (HttpCerver *) google_api->cerver_data;

		google_set_google_routes (http_cerver);

		// add a catch all route
		http_cerver_set_catch_all_route (http_cerver, google_catch_all_handler);

		if (cerver_start (google_api)) {
			cerver_log_error (
				"Failed to start %s!",
				google_api->info->name->str
			);

			cerver_delete (google_api);
		}
	}

	else {
		cerver_log_error ("Failed to create cerver!");

		cerver_delete (google_api);
	}

}

int main (int argc, char const **argv) {

	srand (time (NULL));

	// register to the quit signal
	(void) signal (SIGINT, end);
	(void) signal (SIGTERM, end);

	// to prevent SIGPIPE when writting to socket
	(void) signal (SIGPIPE, SIG_IGN);

	cerver_init ();

	cerver_version_print_full ();

	google_version_print_full ();

	if (!google_init ()) {
		start ();
	}

	else {
		cerver_log_error ("Failed to init google!");
	}

	(void) google_end ();

	cerver_end ();

	return 0;

}