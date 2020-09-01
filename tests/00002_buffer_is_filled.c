#include <assert.h>

#include "../callfull.h"

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.threshold = 3
	});

	// Writing first character.
	const char first[1] = { 1 };
	callfull_feed(callfull, first, sizeof(first));

	assert(callfull_size(callfull) == 1);
	assert(callfull_buffer(callfull)[0] == 1);

	// Writing second character. Should come after the first one in the
	// buffer.
	const char second[1] = { 2 };
	callfull_feed(callfull, second, sizeof(second));

	assert(callfull_size(callfull) == 2);
	assert(callfull_buffer(callfull)[0] == 1);
	assert(callfull_buffer(callfull)[1] == 2);

	// Third character should clear the buffer and cause callback to be
	// called.
	const char third[1] = { 3 };
	callfull_feed(callfull, third, sizeof(third));

	assert(callfull_size(callfull) == 0);

	// Writing multiple characters.
	const char fourth[2] = { 1, 2 };
	callfull_feed(callfull, fourth, sizeof(fourth));

	assert(callfull_size(callfull) == 2);
	assert(callfull_buffer(callfull)[0] == 1);
	assert(callfull_buffer(callfull)[1] == 2);

	// Writing multiple characters that fill current buffer and partially
	// fill next buffer.
	const char fifth[3] = { 1, 2, 3 };
	callfull_feed(callfull, fifth, sizeof(fifth));

	assert(callfull_size(callfull) == 2);
	assert(callfull_buffer(callfull)[0] == 2);
	assert(callfull_buffer(callfull)[1] == 3);

	return 0;
}