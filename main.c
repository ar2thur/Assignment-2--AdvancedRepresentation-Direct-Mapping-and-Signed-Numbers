#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int n, char *out);
void to_ones_complement(int n, char *out);
void to_twos_complement(int n, char *out);

int tests_passed = 0;
int tests_failed = 0;

void trim_whitespace(char *str) {
    int len = strlen(str);
    
    while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\t' || str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
    
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t') {
        start++;
    }
    
    if (start > 0) {
        memmove(str, str + start, len - start + 1);
    }
}

void run_test(const char *function_name, const char *input1, const char *expected) {
    char result[100];
    
    if (strcmp(function_name, "oct_to_bin") == 0) {
        oct_to_bin(input1, result);
    }
    else if (strcmp(function_name, "oct_to_hex") == 0) {
        oct_to_hex(input1, result);
    }
    else if (strcmp(function_name, "hex_to_bin") == 0) {
        hex_to_bin(input1, result);
    }
    else if (strcmp(function_name, "to_sign_magnitude") == 0) {
        int input_num = atoi(input1);
        to_sign_magnitude(input_num, result);
    }
    else if (strcmp(function_name, "to_ones_complement") == 0) {
        int input_num = atoi(input1);
        to_ones_complement(input_num, result);
    }
    else if (strcmp(function_name, "to_twos_complement") == 0) {
        int input_num = atoi(input1);
        to_twos_complement(input_num, result);
    }
    else {
        printf("Unknown function: %s\n", function_name);
        tests_failed++;
        return;
    }
    
    if (strcmp(result, expected) == 0) {
        tests_passed++;
        printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [PASS]\n", 
               tests_passed + tests_failed, function_name, input1, expected, result);
    } else {
        tests_failed++;
        printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", 
               tests_passed + tests_failed, function_name, input1, expected, result);
    }
}

void parse_test_line(char *line) {
    char function_name[50], input1[50], expected[100];
    
    int parsed = sscanf(line, "%s %s %s", function_name, input1, expected);
    
    if (parsed == 3) {
        run_test(function_name, input1, expected);
    }
}

int main() {
    FILE *file = fopen("a2_test.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open a2_test.txt\n");
        printf("Make sure the test file is in the same directory as your program.\n");
        return 1;
    }
    
    char line[256];
    
    while (fgets(line, sizeof(line), file)) {
        trim_whitespace(line);
        
        if (strlen(line) == 0 || line[0] == '#') {
            continue;
        }
        
        parse_test_line(line);
    }
    
    fclose(file);
    
    printf("\nSummary: %d/%d tests passed\n", tests_passed, tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        return 0;
    } else {
        return 1;
    }
}

//I decided to split everything up into nice functions this time, so I can modify file reading easier for the future!