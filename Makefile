MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx -I /usr/include/X11 -L /usr/lib/x86_64-linux-gnu -lXext -lX11

make:
	make -C libft
	gcc  -g main.c intersect_sphere.c  intersect_cylinder.c intersect_cone.c cylinder.c cone.c sphere.c -L libft -lft  -lm $(MLX)
