*This project has been created as part of the 42 curriculum by jhcosta-.*

# get_next_line

## Description

`get_next_line` is a 42 project whose goal is to implement a function that reads
and returns, one call at a time, a single line from a file descriptor, no
matter if the descriptor points to a regular file, a pipe, or the standard
input. The returned line always keeps its trailing `\n`, except when the end
of the file is reached and the file does not end with one.

The main challenge of the project is that the file must be read in fixed-size
chunks (`BUFFER_SIZE`), so the function has to keep, between calls, whatever
was read past the current line's `\n`. This is done with a `static` variable,
which is the central concept the project teaches.

This repository contains only the **mandatory part** of the subject (single
file descriptor, no `_bonus` files).

## Instructions

### Compilation

The project is compiled as a static library (with and without the `-D BUFFER_SIZE` flag):

```bash
make                     # BUFFER_SIZE defaults to 42
make BUFFER_SIZE=5       # custom buffer size
```

This produces `libgnl.a`. Other rules available: `clean`, `fclean`, `re`.

You can also compile the sources directly:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c -o test
```

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("some_file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

`get_next_line` returns `NULL` when there is nothing left to read or when an
error occurs (invalid fd, `read`/`malloc` failure).

## How it works (algorithm)

A `static char *saved` variable persists the leftover data between calls,
per the following loop:

1. **`read_to_saved`**: keep calling `read()` in chunks of `BUFFER_SIZE`
   bytes, appending each chunk to `saved` (via `gnl_strjoin`), until either a
   `\n` is found inside `saved` or `read()` returns `0` (EOF) / `-1` (error).
   This guarantees the file is never read further than necessary.
2. Once the loop stops, `saved` holds at least one full line (or the final
   leftover bytes at EOF, or is an error).
3. **`gnl_extract_line`** copies everything up to and including the first
   `\n` (or up to the end of the string if there is none) into a new buffer:
   this is the line returned to the caller.
4. **`gnl_get_remainder`** copies whatever comes after that `\n` into a new
   `saved` buffer (or returns `NULL` if there was no `\n`, i.e. end of file),
   freeing the old one.

This design was chosen because it is the simplest approach that respects all
the constraints of the subject: it never reads more than necessary, it never
uses `lseek`, it uses no global variables (only one `static` local variable),
and it naturally supports any `BUFFER_SIZE` value, including `1` or values
much larger than a line.

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- 42 Norm (norminette) documentation
- General articles on C `static` variables and their scope/lifetime
- Subject "get_next_line.pdf"

### AI usage

- AI tools were used to support the study of C concepts.
- AI tools were used to review the implementation.
- AI tools were used to suggest test cases and edge cases.
- AI tools were used to assist with the documentation.
