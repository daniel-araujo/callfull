#include "../callfull.h"

int main(int argc, char *argv[])
{
	struct callfull_opts opts = {
		.threshold = 2
	};

	// Making sure that the header marks functions with extern C otherwise this
	// results in a link error.
	callfull_t callfull = callfull_create(&opts);

	return 0;
}