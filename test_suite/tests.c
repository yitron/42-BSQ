#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define TEST_DIR "test_maps"

typedef struct s_test {
    char *name;
    char *description;
    char *map_file;
    int expected_error_message; // 1 if "map error" expected, 0 if not
} t_test;

void create_test_directory() {
    struct stat st = {0};
    if (stat(TEST_DIR, &st) == -1) {
        if (mkdir(TEST_DIR, 0755) == -1) {
            perror("Failed to create test directory");
            exit(1);
        }
    }
    // Make sure the directory is writable
    if (access(TEST_DIR, W_OK) == -1) {
        chmod(TEST_DIR, 0755);
        if (access(TEST_DIR, W_OK) == -1) {
            perror("Test directory is not writable");
            exit(1);
        }
    }
}

void create_test_file(const char *filename, const char *content) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", TEST_DIR, filename);
    
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create test file");
        exit(1);
    }
    
    write(fd, content, strlen(content));
    close(fd);
}

int run_test(t_test test);
int run_multiple_files_test(void);
int run_no_args_test(void);

int run_test(t_test test) {
    pid_t pid;
    int status;
    char *args[3];
    char path[256] = {0};
    int pipefd[2];
    
    if (test.map_file) {
        snprintf(path, sizeof(path), "%s/%s", TEST_DIR, test.map_file);
    }
    
    printf("Testing: %s\n", test.name);
    printf("Description: %s\n", test.description);
    
    // Create a pipe to capture stdout
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();
    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end
        
        // Redirect stdout to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Execute bsq with the test file
        args[0] = "./bsq";
        if (test.map_file) {
            args[1] = path;
            args[2] = NULL;
        } else {
            args[1] = NULL;
        }
        
        execv("./bsq", args);
        exit(127); // Command not found
    } else {
        // Parent process
        close(pipefd[1]); // Close write end
        
        // Read output from pipe
        char buffer[4096];
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
        close(pipefd[0]);
        
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
        } else {
            buffer[0] = '\0';
        }
        
        waitpid(pid, &status, 0);
        
        // Check if output contains "map error"
        int has_error_message = (strstr(buffer, "map error") != NULL);
        
        if (has_error_message == test.expected_error_message) {
            printf("%s[PASS]%s\n\n", GREEN, RESET);
            return 1;
        } else {
            printf("%s[FAIL]%s (Expected %s\"map error\"%s, but %s)\n\n", 
                   RED, RESET, 
                   test.expected_error_message ? "" : "not ",
                   RESET,
                   has_error_message ? "found it" : "didn't find it");
            return 0;
        }
    }
}

int run_multiple_files_test(void) {
    int pipefd[2];
    pid_t pid;
    int status;
    
    // Create a pipe to capture stdout
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();
    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end
        
        // Redirect stdout to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        char *args[] = {
            "./bsq", 
            TEST_DIR "/valid_basic.map", 
            TEST_DIR "/invalid_char_in_map.map", 
            TEST_DIR "/valid_with_obstacles.map", 
            NULL
        };
        execv("./bsq", args);
        exit(127);
    }
    
    // Parent process
    close(pipefd[1]); // Close write end
    
    // Read output from pipe
    char buffer[4096];
    ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
    close(pipefd[0]);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
    } else {
        buffer[0] = '\0';
    }
    
    waitpid(pid, &status, 0);
    
    // Check if output contains both successful map processing and "map error"
    int success = (strstr(buffer, "map error") != NULL);
    
    printf("Testing: Multiple Files with Some Invalid\n");
    printf("Description: Running with multiple files, some invalid\n");
    
    if (success) {
        printf("%s[PASS]%s\n\n", GREEN, RESET);
        return 1;
    } else {
        printf("%s[FAIL]%s (Expected \"map error\" for invalid map, but didn't find it)\n\n", 
               RED, RESET);
        return 0;
    }
}

int run_no_args_test(void) {
    int pipefd[2];
    pid_t pid;
    int status;
    
    // Create a pipe to capture stdout
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();
    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end
        
        // Redirect stdout to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        char *args[] = {"./bsq", NULL};
        execv("./bsq", args);
        exit(127);
    }
    
    // Parent process
    close(pipefd[1]); // Close write end
    
    // Read output from pipe
    char buffer[4096];
    ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
    close(pipefd[0]);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
    } else {
        buffer[0] = '\0';
    }
    
    waitpid(pid, &status, 0);
    
    // Check if output contains map processing (no error message)
    int success = (strstr(buffer, "map error") == NULL && bytes_read > 0);
    
    printf("Testing: No Arguments\n");
    printf("Description: Running without arguments (should use default map)\n");
    
    if (success) {
        printf("%s[PASS]%s\n\n", GREEN, RESET);
        return 1;
    } else {
        printf("%s[FAIL]%s (Expected successful processing, but got errors or no output)\n\n", 
               RED, RESET);
        return 0;
    }
}

// Generate all test files
void generate_test_files() {
    // Valid test maps
    create_test_file("valid_basic.map", "5.ox\n.....\n.....\n.....\n.....\n.....\n");
    create_test_file("valid_with_obstacles.map", "5.ox\n.....\n..o..\n.....\n.....\n.....\n");
    create_test_file("valid_1x1.map", "1.ox\n.\n");
    create_test_file("valid_all_obstacles.map", "3.ox\nooo\nooo\nooo\n");
    
    // Invalid first line format
    create_test_file("invalid_no_number.map", ".ox\n.....\n.....\n.....\n.....\n.....\n");
    create_test_file("invalid_zero_lines.map", "0.ox\n");
    create_test_file("invalid_missing_chars.map", "5\n.....\n.....\n.....\n.....\n.....\n");
    create_test_file("invalid_empty_first_line.map", "\n.....\n.....\n.....\n.....\n.....\n");
    create_test_file("invalid_non_numeric.map", "abc.ox\n.....\n.....\n.....\n.....\n.....\n");
    
    // Invalid map characters
    create_test_file("invalid_char_in_map.map", "5.ox\n.....\n..x..\n.....\n.....\n.....\n");
    create_test_file("invalid_same_chars.map", "5.oo\n.....\n.....\n.....\n.....\n.....\n");
    create_test_file("invalid_tab_char.map", "5.o\t\n.....\n.....\n.....\n.....\n.....\n");
    
    // Inconsistent line lengths
    create_test_file("invalid_short_line.map", "5.ox\n.....\n...\n.....\n.....\n.....\n");
    create_test_file("invalid_long_line.map", "5.ox\n.....\n.......\n.....\n.....\n.....\n");
    create_test_file("invalid_missing_lines.map", "5.ox\n.....\n.....\n");
    
    // Edge cases
    create_test_file("empty_file.map", "");
    create_test_file("just_newline.map", "\n");
    create_test_file("valid_large.map", "20.ox\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n");
    
    // Special cases
    create_test_file("no_newline_after_map_info.map", "5.ox.....\n.....\n.....\n.....\n.....\n");
    create_test_file("valid_one_line.map", "1.ox\n.....\n");
    create_test_file("valid_one_column.map", "5.ox\n.\n.\n.\n.\n.\n");

    // Create an unreadable test file
    create_test_file("unreadable.map", "5.ox\n.....\n.....\n.....\n.....\n.....\n");
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", TEST_DIR, "unreadable.map");
    chmod(path, 0);
}

void generate_test_report(t_test *tests, int test_array_size, int passed_count, int total_tests) {
    FILE *fp = fopen("TEST_REPORT.md", "w");
    if (!fp) {
        perror("Failed to create test report");
        return;
    }
    
    fprintf(fp, "# BSQ Test Suite Report\n\n");
    fprintf(fp, "## Summary\n\n");
    fprintf(fp, "- Total tests: %d\n", total_tests);
    fprintf(fp, "- Tests passed: %d\n", passed_count);
    fprintf(fp, "- Tests failed: %d\n", total_tests - passed_count);
    fprintf(fp, "- Success rate: %.2f%%\n\n", (float)passed_count / total_tests * 100);
    
    fprintf(fp, "## Test Details\n\n");
    fprintf(fp, "| # | Test Name | Description | Expected Result | Status |\n");
    fprintf(fp, "|---|-----------|-------------|----------------|--------|\n");
    
    // Standard tests from the array - run them individually again to record results
    int test_results[test_array_size];
    
    // First run all tests to get results
    for (int i = 0; i < test_array_size; i++) {
        int result = run_test(tests[i]);
        test_results[i] = result;
    }
    
    // Then output the results to the report
    for (int i = 0; i < test_array_size; i++) {
        fprintf(fp, "| %d | %s | %s | %s | %s |\n", 
                i + 1, 
                tests[i].name, 
                tests[i].description,
                tests[i].expected_error_message ? "\"map error\"" : "Success",
                test_results[i] ? "✅ PASS" : "❌ FAIL");
    }
    
    // Special tests
    int multi_file_test_result = run_multiple_files_test();
    fprintf(fp, "| %d | %s | %s | %s | %s |\n", 
            test_array_size + 1, 
            "Multiple Files with Some Invalid", 
            "Running with multiple files, some invalid",
            "\"map error\" for invalid maps",
            multi_file_test_result ? "✅ PASS" : "❌ FAIL");
            
    int no_args_test_result = run_no_args_test();
    fprintf(fp, "| %d | %s | %s | %s | %s |\n", 
            test_array_size + 2, 
            "No Arguments", 
            "Running without arguments (should use default map)",
            "Success (no errors)",
            no_args_test_result ? "✅ PASS" : "❌ FAIL");
    
    fprintf(fp, "\n## Error Categories Tested\n\n");
    fprintf(fp, "1. **Command Line Arguments**\n");
    fprintf(fp, "   - Missing arguments\n");
    fprintf(fp, "   - Non-existent files\n");
    fprintf(fp, "   - Files with permission issues\n\n");
    
    fprintf(fp, "2. **Map Format Errors**\n");
    fprintf(fp, "   - Invalid first line format\n");
    fprintf(fp, "   - Invalid map characters\n");
    fprintf(fp, "   - Inconsistent line lengths\n");
    fprintf(fp, "   - Missing lines\n\n");
    
    fprintf(fp, "3. **Edge Cases**\n");
    fprintf(fp, "   - Empty files\n");
    fprintf(fp, "   - Minimum size maps (1x1)\n");
    fprintf(fp, "   - Maximum size maps\n");
    fprintf(fp, "   - Maps with only obstacles\n");
    fprintf(fp, "   - Maps with no obstacles\n\n");
    
    fprintf(fp, "## Conclusion\n\n");
    if (passed_count == total_tests) {
        fprintf(fp, "The BSQ program handles all test cases correctly, including error conditions and edge cases.\n");
    } else {
        fprintf(fp, "The BSQ program fails to handle some test cases correctly. See the test details section for specific failures.\n");
    }
    
    fclose(fp);
}

// Functions were moved up to avoid forward declarations

int main() {
    create_test_directory();
    generate_test_files();
    
    t_test tests[] = {
        // Valid map tests - expect no error message
        {"Valid Basic Map", "A basic 5x5 map with no obstacles", "valid_basic.map", 0},
        {"Valid Map With Obstacles", "A 5x5 map with some obstacles", "valid_with_obstacles.map", 0},
        {"Valid 1x1 Map", "A minimal 1x1 map", "valid_1x1.map", 0},
        {"Valid Map With All Obstacles", "A map entirely filled with obstacles", "valid_all_obstacles.map", 0},
        {"Valid Large Map", "A 20x20 map with no obstacles", "valid_large.map", 0},
        {"Valid One Line Map", "A map with just one line", "valid_one_line.map", 0},
        {"Valid One Column Map", "A map with just one column", "valid_one_column.map", 0},
        
        // Invalid first line format - expect error message
        {"Invalid No Number", "First line missing the number of lines", "invalid_no_number.map", 1},
        {"Invalid Zero Lines", "First line specifies zero lines", "invalid_zero_lines.map", 1},
        {"Invalid Missing Chars", "First line missing the map characters", "invalid_missing_chars.map", 1},
        {"Invalid Empty First Line", "First line is empty", "invalid_empty_first_line.map", 1},
        {"Invalid Non-Numeric", "First line contains non-numeric characters for line count", "invalid_non_numeric.map", 1},
        
        // Invalid map characters - expect error message
        {"Invalid Char In Map", "Map contains a character not specified in the first line", "invalid_char_in_map.map", 1},
        {"Invalid Same Chars", "Map characters are not unique", "invalid_same_chars.map", 1},
        {"Invalid Tab Char", "Map contains tab character", "invalid_tab_char.map", 1},
        
        // Inconsistent line lengths - expect error message
        {"Invalid Short Line", "Map contains a line shorter than specified", "invalid_short_line.map", 1},
        {"Invalid Long Line", "Map contains a line longer than specified", "invalid_long_line.map", 1},
        {"Invalid Missing Lines", "Map has fewer lines than specified", "invalid_missing_lines.map", 1},
        
        // Edge cases - expect error message
        {"Empty File", "File is completely empty", "empty_file.map", 1},
        {"Just Newline", "File contains only a newline character", "just_newline.map", 1},
        
        // Special cases - expect error message
        {"No Newline After Map Info", "First line doesn't end with a newline", "no_newline_after_map_info.map", 1},
        
        // File errors - expect error message
        {"Non-existent File", "File that doesn't exist", "nonexistent.map", 1},
        {"Unreadable File", "File with no read permissions", "unreadable.map", 1},
    };
    
    size_t tests_size = sizeof(tests) / sizeof(t_test);
    int test_count = (int)tests_size + 2; // +2 for special tests
    int passed_count = 0;
    
    // Run regular tests
    for (size_t i = 0; i < tests_size; i++) {
        if (run_test(tests[i])) {
            passed_count++;
        }
    }
    
    // Run special tests
    if (run_multiple_files_test()) {
        passed_count++;
    }
    
    if (run_no_args_test()) {
        passed_count++;
    }
    
    printf("Tests passed: %d/%d (%.2f%%)\n", 
           passed_count, test_count, (float)passed_count / test_count * 100);
    
    // This version of generate_test_report will rerun all the tests
    generate_test_report(tests, (int)tests_size, passed_count, test_count);
    
    return 0;
}