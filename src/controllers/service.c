#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cerver/http/response.h>

#include <cerver/utils/utils.h>

#include "version.h"

HttpResponse *google_works = NULL;
HttpResponse *current_version = NULL;

HttpResponse *catch_all = NULL;

unsigned int google_service_init (void) {

	unsigned int retval = 1;

	google_works = http_response_json_key_value (
		(http_status) 200, "msg", "Google status works!"
	);

	char *status = c_string_create (
		"%s - %s",
		GOOGLE_VERSION_NAME, GOOGLE_VERSION_DATE
	);

	if (status) {
		current_version = http_response_json_key_value (
			(http_status) 200, "version", status
		);

		free (status);
	}

	catch_all = http_response_json_key_value (
		(http_status) 200, "msg", "Google status service!"
	);

	if (
		catch_all
		&& google_works && current_version
	) retval = 0;

	return retval;

}

void google_service_end (void) {

	http_response_delete (google_works);
	http_response_delete (current_version);

	http_response_delete (catch_all);

}
