# 42-BSQ
BSQ Maximum Sq


# Todo
- [x] Read map files
- [x] Get map spec from first line
- [x] Parse map into a matrix
- [x] Find max square from map, return its coordinator and size
- [x] Draw the square with the "full" character.
- [x] Handle multiple map files
- [x] Validate map files
- [x] Read a single map from stdin when no file is provided
- [x] Create makefile
- [x] Refactor code breaking down to smaller functions
- [x] Polish formatting for norminette
- [ ] Scan code with valgrind to check for memory leaks (verified with `leaks` on MacOS, need to check again with Valgrind on Linux)
- [ ] More test cases
- [ ] Organize code to make it easy to read and maintain

# Usage
### Compile the code
```sh
make
```
Available commands:
- `make` - Compile the code
- `make clean` - Remove the object files
- `make fclean` - Remove the object files and the executable
- `make re` - Recompile the code
- `make norm` - Check the code with norminette

Once compiled, executable file `bsq` will be generated in the current directory.

### Run
```sh
./bsq <path_to_the_map_files>
```

### Example
```sh
./bsq map/10x10_1.map map/10x10_10.map
```
