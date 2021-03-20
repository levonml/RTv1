MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx -I /usr/include/X11 -L /usr/lib/x86_64-linux-gnu -lXext -lX11

make:
	make -C libft
	gcc  -g main.c intersect_sphere.c  intersect_cylinder.c intersect_cone.c intersect_plane.c cylinder.c cone.c sphere.c plane.c vector.c vector_xz.c initialiser.c find_objects.c -L libft -lft  -lm $(MLX)
