/*=========================================================

	This main function can take the puzzle input by
	command-line argument or by redirecting/piping it
	into the program.

//=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

void free_llarr(long **arr) {
	size_t i = 0;
	while (arr && arr[i]) {
		free(arr[i]);
		i++;
	}
	free(arr);
}

long count_timelines(char **arr, size_t arr_idx, char *prev, long **visits) {

	long nb_timelines = 0;
	char *line = arr[arr_idx];


	if (arr[arr_idx] == NULL) {
		return 1;
	}

	size_t linelen = strlen(arr[arr_idx]);

	char tmp_line[linelen + 1];
	for (size_t i = 0; i < linelen; i++) {
		tmp_line[i] = line[i];
	}
	tmp_line[linelen] = 0;


	for (size_t i = 0; i < strlen(line); i++) {

		if (prev[i] == 'S' || prev[i] == '|') {
			if (line[i] == '.') {
				tmp_line[i] = '|';
				// printf("s: idx: %lu tmp: %s\n",arr_idx, &tmp_line[0]);
				if (visits[arr_idx][i] == 0) {
					visits[arr_idx][i] = count_timelines(arr, arr_idx+1, tmp_line, visits);
				}
				nb_timelines += visits[arr_idx][i];
			}
			else if (line[i] == '^') {
				if (i > 0) {
					tmp_line[i-1] = '|';
					// printf("l: idx: %lu tmp: %s\n",arr_idx, &tmp_line[0]);
					if (visits[arr_idx][i] == 0) {
						visits[arr_idx][i] = count_timelines(arr, arr_idx+1, tmp_line, visits);
					}
					nb_timelines += visits[arr_idx][i];
					tmp_line[i-1] = '.';
				}
				if (i < linelen + 1) {
					tmp_line[i+1] = '|';
					// printf("r: idx: %lu tmp: %s\n",arr_idx, &tmp_line[0]);
					nb_timelines += count_timelines(arr, arr_idx+1, tmp_line, visits);
				}
			}
		}
	}
	return nb_timelines;
}

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

	long **visits = calloc(lines + 1, sizeof(long **));
	if (!visits) {
		fprintf(stderr, "Memory allocation failed\n");
		free(arr);
		free(input);
		return 1;
	}
	for (size_t i = 0; i < lines; i++) {
		visits[i] = calloc(strlen(arr[0])+1, sizeof(long*));
		if (!visits[i]) {
			fprintf(stderr, "Memory allocation failed\n");
			free_llarr(visits);
			free(arr);
			free(input);
			return 1;
		}
	}

	long timelines = count_timelines(arr, 1, arr[0], visits);
	printf("The tachyon particle ended up on  %s%li%s timelines\n", "\e[1m", timelines, "\e[0m");

// ===== CODE ENDS HERE ====
	free_llarr(visits);
	free(arr);
	free(input);
	return 0;
}
