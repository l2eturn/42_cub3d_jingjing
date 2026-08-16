# cub3d
>This project has been created as part of the 42 curriculum by waragwon slimvutt
## Description
A project about how Wolfenstein 3D works - raycasting using the DDA algorithm to render a 3D map from 2D space.

## Instructions
### Usage
In order to run this project use `make`
- `make` - create a whole project
- `make all` - behave the same as make
- `make clean` - clear .o file
- `make fclean` - make clean + exe and archive 
- `make re` - make fclean -> make all
- `make bonus` - create a bonus part of project
- `make libft` - create archive for libft
- `make gnl` - create archive for gnl
- `make mlx` - create archive for mlx42

MLX42 is cloned and built on the first `make`, so `cmake` and `glfw` have to be
installed already.

In order to run this project
```sh
./cub3D <mapPath.cub>
```

### Controls
| Key | Action |
| --- | --- |
| `W` / `S` | walk forward / backward |
| `A` / `D` | strafe left / right |
| `←` / `→`, `Q`/`E` | turn the camera |
| `ESC` | quit |

Movement is scaled by `delta_time`, so speed does not depend on the frame rate.
Walls are tested one axis at a time, which lets the player slide along them
instead of sticking.

### Scene file
The argument must be a file ending in `.cub`. It holds the six identifiers
first, then the map last.
```txt
NO <path_to_texture.png>
SO <path_to_texture.png>
WE <path_to_texture.png>
EA <path_to_texture.png>
F 220,100,0
C 100,180,240

1111111111
1000000001
1000N00001
1000000001
1111111111
```

Rules the parser enforces:
- every identifier appears exactly once, in any order, blank lines between them are fine
- `F` and `C` take three values in `0-255`
- the map is the last block in the file and may only contain `0 1 N S E W` and spaces
- rows do not have to be the same length; short rows are padded with spaces
- no blank line is allowed once the map has started
- exactly one starting position, and it must be enclosed by walls

Anything else stops the program before the window opens. Errors go to stderr as
`Error` followed by one line, and the exit status is `1`.
```txt
Error
Map is not closed by walls
```

| Message | Cause |
| --- | --- |
| `WIDTH and HEIGHT must be >= MIN_WIDTH and MIN_HEIGHT` | window size in `cub3d.h` is set below the minimum |
| `Scene file must end with .cub` | wrong file extension |
| `Cannot open scene file` | missing file or no read permission |
| `Unknown identifier in scene file` | a line before the map that is not `NO SO WE EA F C` |
| `Duplicate texture identifier` | the same wall direction given twice |
| `Missing NO, SO, WE or EA texture` | one of the four textures never appeared |
| `Empty texture path` | identifier with nothing after it |
| `Duplicate F or C identifier` | floor or ceiling colour given twice |
| `Missing F or C colour` | floor or ceiling colour never appeared |
| `Invalid colour, expected R,G,B in 0-255` | wrong count, not a number, or out of range |
| `Scene file has no map` | the file ends before any map row |
| `Invalid character in map` | a character outside `0 1 N S E W` and space |
| `Empty line inside map` | blank line between two map rows |
| `Map needs exactly one player start` | zero or more than one of `N S E W` |
| `Map is not closed by walls` | the player can reach the outside of the grid |

Four more exist for allocation failures, which only show up if the system runs
out of memory.

### Layout
```txt
src/
├── main.c
├── parser/       read the .cub file and validate it
├── map/          grid lookups shared by the renderer and the parser
├── player/       spawn, input, movement, rotation
├── render/       ray setup, DDA, projection, texture pick, column draw
├── graphics/     MLX42 window, image and texture lifetime
└── utils/        colour packing
```

Memory is handled two ways. Anything that has to live until the program exits
is taken from `ft_safe_calloc`, and the whole pool is released by the single
`ft_safe_calloc(0, 0, true)` call in `main`. Short lived buffers - the lines
from `get_next_line`, the arrays from `ft_split` - use plain `malloc` and are
freed where they are used.

### Testing
for a memory leak test you can run this
```sh
valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--errors-for-leak-kinds=definite \
	--log-file=output.txt \
	./cub3D maps/test.cub
```
Should show something like this (only the MLX42 lib is leak)
```txt
==67145== LEAK SUMMARY:
==67145==    definitely lost: 56 bytes in 1 blocks
==67145==    indirectly lost: 56 bytes in 1 blocks
==67145==      possibly lost: 0 bytes in 0 blocks
==67145==    still reachable: 305,476 bytes in 3,425 blocks
==67145==         suppressed: 80 bytes in 2 blocks
==67145== 
==67145== For lists of detected and suppressed errors, rerun with: -s
==67145== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

A rejected map is the cleanest thing to measure, because the parser frees
everything and exits before MLX42 ever starts. The map below is missing its
right wall, so it stops after the identifiers are read and the grid is built.
```sh
printf 'NO a\nSO b\nWE c\nEA d\nF 0,0,0\nC 0,0,0\n\n1111\n1N00\n1111\n' > /tmp/open.cub
./cub3D /tmp/open.cub
```

Two maps are kept for checking the parser by hand. `maps/test.cub` is a plain
rectangle, and `maps/uneven.cub` is the ragged example from the subject whose
rows run from 25 to 33 characters.

### Resources
- Raycasting
	- https://lodev.org/cgtutor/raycasting.html
	- https://youtu.be/g8p7nAbDz6Y?si=MRMiL-pqWvMSMRr0
	- https://youtu.be/NbSee-XM7WA?si=xMfjrApQJoOr51jT
- Textures
	- https://github.com/MichelleJiam/cub3D
