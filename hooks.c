#include "rt.h"

int		key_control(int key)
{
	if (key == 65307)
		exit(0);
	return (0);
}

int		expose_hook(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	render(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}
