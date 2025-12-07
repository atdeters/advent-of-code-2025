/*=========================================================

	This main function can take the puzzle input by
	command-line argument or by redirecting/piping it
	into the program.

//=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main( int ac, char **av ) {

	int fd = 0;
	char ch;

	if (ac > 2) {
		fprintf(stderr, "Usage: ./day <puzzle-input>\n");
		return 1;
	}
	else if (ac == 2) {
		fd = open(av[1], O_RDONLY);
		if (fd == -1) {
			fprintf(stderr, "Could not open file: %s\n", av[1]);
			return 1;
		}
	}

	size_t buff_len = 2;
	size_t len = 0;
	size_t lines = 0;

	char *input = calloc(sizeof(char), buff_len + 1);
	while(read(fd, &ch, sizeof(char))) {
		// === IF BUFFER FULL -> ALLOCATE NEW QUADRATICALLY ===
		if (len == buff_len) {
			buff_len *= 2;
			char *tmp = calloc(sizeof(char), buff_len + 1);
			if (!tmp) {
				fprintf(stderr, "Memory allocation failed\n");
				if (fd) {
					close(fd);
				}
				free(input);
				return 1;
			}
			memcpy(tmp, input, len);
			free(input);
			input = tmp;
		}
		if (ch == '\n') {
			lines++;
			input[len] = 0;
		}
		else {
			input[len] = ch;
		}
		len++;
	}
	if (fd) {
		close(fd);
	}

// ===== WORKING WTIH A C VERSION OF SLICES ====
	char **arr = calloc(lines + 1, sizeof(char **));
	if (!arr) {
		fprintf(stderr, "Memory allocation failed\n");
		free(input);
		return (1);
	}

	arr[0] = input;
	size_t curr_line = 0;
	for (size_t i = 0; i < len; i++) {
		if (input[i] == '\0' && curr_line < lines - 1 ) {
			curr_line++;
			i++;
			arr[curr_line] = &input[i];
		}
	}

	long splits = 0;
	for (size_t i = 1; i < lines; i++) {
		for (size_t j = 0; j < strlen(arr[i]); j++) {
			if (arr[i-1][j] == 'S') {
				arr[i][j] = '|';
			}
			else if (arr[i-1][j] == '|' && arr[i][j] == '^') {
				if (j > 0) {
					arr[i][j-1] = '|';
				}
				if (j < strlen(arr[i]) - 1) {
					arr[i][j+1] = '|';
				}
				splits++;
			}
			else if (arr[i-1][j] == '|') {
				arr[i][j] = '|';
			}
		}
		// printf("%s\n", arr[i]); // Uncomment to print updated line
	}
	printf("The beam was split %s%li%s times\n", "\e[1m", splits, "\e[0m");

// ===== CODE ENDS HERE ====
	free(arr);
	free(input);
	return 0;
}
