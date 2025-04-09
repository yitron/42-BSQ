# BSQ Test Suite

This test suite is designed to test the BSQ (Biggest Square) program for all possible error conditions and edge cases.

## Features

- Tests command-line argument handling (missing arguments, invalid file paths)
- Tests map format errors (invalid first line, wrong characters, inconsistent line lengths)
- Tests edge cases (empty files, minimum/maximum size maps)
- Generates a comprehensive test report in Markdown format

## How to Run

1. First, make sure you have compiled the BSQ program:
   ```
   make
   ```

2. Compile the test suite:
   ```
   make -f Makefile.test
   ```

3. Run the tests:
   ```
   ./tests
   ```
   
   Alternatively, you can use:
   ```
   make -f Makefile.test test
   ```

4. View the test results in the terminal or check the `TEST_REPORT.md` file for detailed results.

## Test Categories

The test suite covers the following categories of tests:

### Command Line Arguments
- Missing arguments
- Non-existent files
- Files with permission issues

### Map Format Errors
- Invalid first line format
- Invalid map characters
- Inconsistent line lengths
- Missing lines

### Edge Cases
- Empty files
- Minimum size maps (1x1)
- Maximum size maps
- Maps with only obstacles
- Maps with no obstacles

## Cleaning Up

To clean the test files:
```
make -f Makefile.test clean
```

To completely remove the test suite and its artifacts:
```
make -f Makefile.test fclean
```