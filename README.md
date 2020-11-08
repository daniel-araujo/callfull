# Callfull

Need to accumulate data to process in bulk? This drop-in C implementation for a
byte buffer will call your function once the buffer has been filled with your
desired threshold.

The following example shows you how to accumulate variable chunks of data over
time to do some processing:

Code:

```c
// Error handling omitted for simplicity.
#include <stdio.h>
#include "callfull.h"

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
    // The total is passed as a pointer.
    int *total = user;

    printf("Process %zu/%d (%zu bytes)\n", i + 1, *total, size);

    // Do processing here.
}

int main(int argc, char *argv[])
{
    const int samples_per_sec = 8000;
    const int bytes_per_sample = 2;

    // We will read up to 4 seconds.
    size_t total = 4;

    // Create buffer.
    callfull_t callfull = callfull_create(&(struct callfull_opts) {
        // The function that will be called when the threshold is reached.
        .callback = callback,

        // A pointer to anything. Will be passed to callback.
        .user = &total,

        // In this case we will process 1 second of audio at a time.
        .threshold = samples_per_sec * bytes_per_sample
    });

    while (callfull_times(callfull) < total) {
        char intermediate[5000];

        // Remember fread may not entirely fill your buffer.
        size_t actually_read = fread(intermediate, 1, sizeof(intermediate), stdin);

        callfull_feed(callfull, intermediate, actually_read);
    }

    // Done with it. Release buffer.
    callfull_destroy(callfull);

    return 0;
}
```

Output:

```
Processing 1/4 (16000 bytes)
Processing 2/4 (16000 bytes)
Processing 3/4 (16000 bytes)
Processing 4/4 (16000 bytes)
```


## How to use

Just copy `callfull.c` and `callfull.h` into your project and compile.

You can safely include the header file in your C++ code.


## Documentation

Read `callfull.h`. The comments will explain everything.


## License

Fuck around and find out. Read LICENSE file for details.
