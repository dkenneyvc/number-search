#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

// Function to generate a random alphanumeric character
char random_char() {
    int r = rand() % 36;
    if (r < 10) {
        return '0' + r;  // '0' to '9'
    } else {
        return 'A' + (r - 10);  // 'A' to 'Z'
    }
}

// Function to generate a random line with at least one digit
void generate_line(char *line, int length) {
    int digit_pos = rand() % length;
    for (int i = 0; i < length; i++) {
        if (i == digit_pos) {
            line[i] = '0' + (rand() % 10);  // Ensure at least one digit
        } else {
            line[i] = random_char();  // Random alphanumeric character
        }
    }
    line[length] = '\0';  // Null-terminate the line
}

// Function to generate the file with the specified number of lines and max line length
void generate_file(const char *filename, int num_lines, int max_line_length) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_lines; i++) {
        int line_length = (rand() % max_line_length) + 1;  // Random length between 1 and max_line_length
        char line[MAX_LINE_LENGTH + 1];  // Extra space for null terminator

        generate_line(line, line_length);
        fprintf(file, "%s\n", line);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <filename> <num_lines> <max_line_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int num_lines = atoi(argv[2]);
    int max_line_length = atoi(argv[3]);

    if (num_lines <= 0 || max_line_length <= 0 || max_line_length > MAX_LINE_LENGTH) {
        fprintf(stderr, "Invalid number of lines or line length\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));
    generate_file(filename, num_lines, max_line_length);

    return EXIT_SUCCESS;
}
