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

#pragma once

// For size_t.
#include <stdlib.h>

// Callback function type.
typedef void (*callfull_callback_t)(const char *, size_t, size_t, void *);

// Options for creating a callfull handle.
struct callfull_opts
{
	// How many bytes are needed for callback to be called and the buffer to
	// be emptied.
	size_t threshold;

	// The function that will be called when threshold is reached.
	callfull_callback_t callback;

	// Callback user data. This will always get passed to callback.
	void *user;
};

enum callfull_error
{
	CALLFULL_ERROR_NONE = 0,
	CALLFULL_ERROR_OUT_OF_MEMORY = 1,
};

// A pointer to an opaque structure.
typedef struct callfull_handle *callfull_t;

/*
 * Creates buffer. See options struct for more details.
 *
 * You must call callfull_error to check if the handle was successfully
 * created. if the handle failed to be created correctly then you can only
 * pass it to callfull_error and callfull_destroy. Any other functions will
 * result in undefined behavior.
 */
callfull_t callfull_create(struct callfull_opts *opts);

/*
 * Disposes resources. The handle can no longer be used after calling this method.
 */
void callfull_destroy(callfull_t handle);

/*
 * Checks if handle is still usable. If this returns a value other than
 * CALLFULL_ERROR_NONE then you should destroy the handle.
 */
enum callfull_error callfull_error(callfull_t handle);

/*
 * Adds data to the buffer. This calls the callback function if the buffer
 * gets filled. It can call callback multiple times if data overflows threshold.
 */
void callfull_feed(callfull_t handle, const char *data, size_t size);

/*
 * How many times callback has been called.
 */
size_t callfull_times(callfull_t handle);

/*
 * Direct reference to buffer.
 */
const char *callfull_buffer(callfull_t handle);

/*
 * How much data is accumulated in the buffer.
 */
size_t callfull_size(callfull_t handle);

/*
 * Discards current contents in buffer and resets counter. It's as if no
 * data has ever been fed.
 */
size_t callfull_reset(callfull_t handle);
