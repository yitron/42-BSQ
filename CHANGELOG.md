# Changelog

## 2025-04-09
### Changed
- **Module**: src/main.c
- **Function**: main
- **Change**: Removed stdin processing and added default map file handling
- **Description**: Modified the program to use a default map file (map/10x10_1.map) when no arguments are provided, removing the unused stdin processing functionality. This change makes the program more user-friendly by providing a default example map.

### Fixed
- **Module**: src/main.c
- **Function**: process_files
- **Change**: Added a newline character between solutions when processing multiple map files
- **Description**: When the program processed multiple map files passed as command line arguments, there were no newlines between the solutions. Added a write(1, "\n", 1) call after processing each file (except the last one) to improve output readability.