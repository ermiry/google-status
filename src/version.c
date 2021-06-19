#include <cerver/utils/log.h>

#include "version.h"

// print full google version information
void google_version_print_full (void) {

	cerver_log_msg ("\nGoogle Status Version: %s\n", GOOGLE_VERSION_NAME);
	cerver_log_msg ("Release Date & time: %s - %s\n", GOOGLE_VERSION_DATE, GOOGLE_VERSION_TIME);
	cerver_log_msg ("Author: %s\n", GOOGLE_VERSION_AUTHOR);

}

// print the version id
void google_version_print_version_id (void) {

	cerver_log_msg ("\nGoogle Status Version ID: %s\n", GOOGLE_VERSION);

}

// print the version name
void google_version_print_version_name (void) {

	cerver_log_msg ("\nGoogle Status Version: %s\n", GOOGLE_VERSION_NAME);

}