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
- [ ] Refactor code breaking down to smaller functions
- [ ] Polish formatting for norminette
- [ ] Scan code with valgrind to check for memory leaks

# Usage
### Compile the code
```sh
make
```
This will generate a executable file named `BSQ`

### Run
```sh
./bsq <path_to_the_map_files>
```
### Example
```sh
./bsq map/10x10_1.map map/10x10_10.map
```
