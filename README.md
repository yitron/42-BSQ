# 42-BSQ
BSQ Maximum Sq


# Todo
- [x] Read map files
- [x] Get map spec from first line
- [x] Parse map into a matrix
- [x] Find max square from map, return its coordinator and size
- [x] Draw the square with the "full" character.
- [ ] Refactor code breaking down to smaller functions
- [ ] Polish formatting for norminette
- [ ] Handle multiple map files
- [ ] Validate map files
- [ ] Read a single map from stdin when no file is provided
- [x] Create makefile
- [ ] Scan code with valgrind to check for memory leaks

# Usage
### Compile the code
```sh
make
```
This will generate a executable file named `BSQ`

### Run
```sh
./BSQ <path_to_the_map_files>
```
### Example
```sh
./BSQ map/10x10_1.map map/10x10_10.map
```
