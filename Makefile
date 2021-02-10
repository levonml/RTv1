MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx -I /usr/include/X11 -L /usr/lib/x86_64-linux-gnu -lXext -lX11

make:
	gcc  -g main.c intersect.c -lm $(MLX)
