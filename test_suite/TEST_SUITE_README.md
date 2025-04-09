# BSQ Test Suite

This test suite provides comprehensive testing for the BSQ (Biggest Square) program, covering all possible error conditions and edge cases.

## Overview

The test suite verifies that the BSQ program correctly handles:

1. **Command Line Arguments**
   - Missing arguments
   - Non-existent files
   - Files with permission issues

2. **Map Format Errors**
   - Invalid first line format
   - Invalid map characters
   - Inconsistent line lengths
   - Missing lines

3. **Edge Cases**
   - Empty files
   - Minimum size maps (1x1)
   - Maximum size maps
   - Maps with only obstacles
   - Maps with no obstacles

## Test Files

The test suite generates various test map files with different characteristics:

### Valid Maps
- Basic 5x5 map with no obstacles
- 5x5 map with some obstacles
- Minimal 1x1 map
- Map entirely filled with obstacles
- Large 20x20 map
- Single line map
- Single column map

### Invalid Maps
- First line missing the number of lines
- First line specifying zero lines
- First line missing map characters
- Empty first line
- First line with non-numeric characters for line count
- Map containing invalid characters
- Map with non-unique characters
- Map with tab characters
- Map with inconsistent line lengths
- Map with missing lines
- Empty file
- File with just a newline character
- First line without a newline character

## Running the Tests

1. First, compile the BSQ program:
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

## Test Report

The test suite generates a comprehensive report (`TEST_REPORT.md`) with:
- Summary of test results
- Detailed information for each test case
- Categorization of tested error conditions
- Success rate

## Conclusion

The test suite provides valuable insights into the robustness of the BSQ program by testing various edge cases and error conditions. It helps identify areas that need improvement to handle all possible inputs correctly.

## Found Issues

The test suite has identified a few areas where the BSQ program doesn't correctly handle invalid inputs:

1. Maps with lines longer than specified
2. The multiple files test case, where errors in one file should be reported but processing should continue with the next file

These findings can help guide future improvements to the program.