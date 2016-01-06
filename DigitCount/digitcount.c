/*

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2016 github.com/atlesn

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define NUM_MAX 10

const char *num_chars = "0123456789";
const int num_chars_count = sizeof(*num_chars) - 1;

struct num_sum {
	int sum;
};

void num_sum_dump(struct num_sum *source) {
	for (int i = 0; i < NUM_MAX; i++) {
		printf("Number %i: %i\n", i, source[i].sum);
	}
}

void num_sum_fill(struct num_sum *target, const char *input) {
	memset (target, 0, sizeof(struct num_sum) * NUM_MAX);

	int i = 0;
	while (input[i] != '\0') {
		target[input[i] - '0'].sum++;
		i++;
	}
}

bool num_sum_validate(struct num_sum *sums, char *test) {
	int i = 0;
	while (test[i] != '\0') {
		int value = test[i] - '0';
		//printf ("- Check %i: %i<=>%i\n", i, sums[i].sum, value);
		if (sums[i].sum != value) {
			return false;
		}
		i++;
	}
	return true;
}

int main (int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: 10digits {MIN} {MAX}\n");
		exit(1);
	}

	unsigned long long begin = strtoull(argv[1], NULL, 10);
	unsigned long long end = strtoull(argv[2], NULL, 10);

	char string[128];
	struct num_sum sums[NUM_MAX];

	long long unsigned parts = (NUM_MAX + 1) / 4;

	for (long long unsigned i = begin; i <= end; i++) {
		sprintf(string, "%llu", i);
		if (i % 1000000 == 0) {
			printf("Number %llu:\n", i);
		}
		num_sum_fill(sums, string);
		if (num_sum_validate(sums, string)) {
			printf("Number %llu:\n", i);
			num_sum_dump(sums);
			printf("DONE\n");
			break;
		}
	}

	exit (0);
}
