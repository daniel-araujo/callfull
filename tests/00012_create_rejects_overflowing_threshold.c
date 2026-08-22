#include <assert.h>
#include <stdint.h>

#include "../callfull.h"

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
}

int main(int argc, char *argv[])
{
	// A threshold this large would overflow the internal allocation size
	// computation, which must be rejected instead of wrapping around to a
	// small allocation.
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = SIZE_MAX
	});

	assert(callfull == NULL);

	assert(callfull_error(callfull) == CALLFULL_ERROR_OUT_OF_MEMORY);

	return 0;
}
