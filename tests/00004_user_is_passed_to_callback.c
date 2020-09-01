#include <assert.h>

#include "../callfull.h"

static int sentinel = 0xDEADBEEF;

static int called = 0;

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
	assert(user == &sentinel);

	called +=1;
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 2,

		.user = &sentinel
	});

	const char first[2] = { 0, 1 };
	callfull_feed(callfull, first, sizeof(first));

	assert(called == 1);

	return 0;
}