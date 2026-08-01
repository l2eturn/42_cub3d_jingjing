# cub3d
>This project has been created as part of the 42 curriculum by waragwon <พี่เต้อ>

## Description
Project about how Wolfenstein3d working. Written later

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
In order to run this project
```sh
./cub3d <mapPath.cub>
```
In the map.cub will look something like this
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

### Resources
- Raycasting
	- https://lodev.org/cgtutor/raycasting.html
	- https://youtu.be/g8p7nAbDz6Y?si=MRMiL-pqWvMSMRr0
	- https://youtu.be/NbSee-XM7WA?si=xMfjrApQJoOr51jT
- Textures
	- https://github.com/MichelleJiam/cub3D