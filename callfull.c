// Callfull release 1
//
// copyright (c) 2020 Daniel Araujo
//
// permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "software"), to deal
// in the software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the software, and to permit persons to whom the software is
// furnished to do so, subject to the following conditions:
//
// the above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the software.
//
// the software shall be used for Good, not Evil. the original author of the
// software retains the sole and exclusive right to determine which uses are
// Good and which uses are Evil.
//
// the software is provided "as is", without warranty of any kind, express or
// implied, including but not limited to the warranties of merchantability,
// fitness for a particular purpose and noninfringement. in no event shall the
// authors or copyright holders be liable for any claim, damages or other
// liability, whether in an action of contract, tort or otherwise, arising from,
// out of or in connection with the software or the use or other dealings in the
// software.

#include <stdlib.h>
#include <string.h>

#include "callfull.h"

// A handle is just a pointer to this structure.
struct callfull_handle
{
	// Threshold for calling callback.
	size_t threshold;

	// Function that will be called when threshold is hit.
	callfull_callback_t callback;

	// Callback user data. This will always get passed to callback.
	void *user;

	// How many times callback has been called.
	size_t times;

	// How much data has been accumulated in the buffer thus far. This will
	// never be greater than threshold.
	size_t accumulated;

	// Holds data until threshold is hit.
	char buffer[];
};

struct callfull_handle *callfull_create(struct callfull_opts *opts)
{
	if (opts->threshold == 0) {
		return NULL;
	}

	callfull_t handle = malloc(sizeof(struct callfull_handle) + opts->threshold);

	if (handle == NULL) {
		return NULL;
	}

	handle->threshold = opts->threshold;
	handle->callback = opts->callback;
	handle->user = opts->user;
	handle->accumulated = 0;
	handle->times = 0;

	return handle;
}

enum callfull_error callfull_error(struct callfull_handle *handle)
{
	if (handle == NULL) {
		return CALLFULL_ERROR_OUT_OF_MEMORY;
	} else {
		return CALLFULL_ERROR_NONE;
	}
}

void callfull_destroy(struct callfull_handle *handle)
{
	if (handle == NULL) {
		// Must have failed to create.
		return;
	}

	// To detect use after free.
	handle->threshold = -1;

	free(handle);
}

void callfull_feed(struct callfull_handle *handle, const char *data, size_t size)
{
	// Offset into current data.
	size_t offset = 0;

	while (size > 0) {
		// How much space is left in the buffer.
		size_t remaining = handle->threshold - handle->accumulated;

		if (size >= remaining) {
			// Threshold will be hit.
			memcpy(handle->buffer + handle->accumulated, data + offset, remaining);

			if (handle->callback != NULL) {
				handle->callback(handle->buffer, handle->threshold, handle->times, handle->user);
				handle->times += 1;
			}

			// Reset.
			handle->accumulated = 0;

			offset += remaining;
			size -= remaining;
		} else {
			// Buffer will be partially filled up.
			memcpy(handle->buffer + handle->accumulated, data + offset, size);

			handle->accumulated += size;

			offset += size;
			size -= size;
		}
	}
}

size_t callfull_times(struct callfull_handle *handle)
{
	return handle->times;
}

const char *callfull_buffer(struct callfull_handle *handle)
{
	return handle->buffer;
}

size_t callfull_size(struct callfull_handle *handle)
{
	return handle->accumulated;
}

size_t callfull_reset(callfull_t handle)
{
	handle->accumulated = 0;
	handle->times = 0;
}