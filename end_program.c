#include "so_long.h"

void	frontend_exit(t_data frontend_state, int code)
{
	char	**playground;

	playground = frontend_state.playground_state.playground;
	if (frontend_state.mlx)
		mlx_destroy_window(frontend_state.mlx, frontend_state.mlx_win);
	free_array(playground);
	if (code == exit_success)
		exit(EXIT_SUCCESS);
	else if (code == exit_failure)
		exit(EXIT_FAILURE);
}

void	array_playground_exit(char **array_playground, t_error error)
{
	if (error.error_code == exit_success)
	{
		free_array(array_playground);
		exit(EXIT_SUCCESS);
	}
	else if (error.error_code == INVALID)
	{
		free_array(array_playground);
		write(1, "Error\n", 6);
		ft_printf("%s\n", error.error_message);
		exit(EXIT_FAILURE);
	}
}

int	string_playground_exit(char *string_playground, int code)
{
	int	failed_to_open;

	failed_to_open = 1;
	free(string_playground);
	write(1, "Error\n", 6);
	if (code == failed_to_open)
		printf("%s\n", strerror(errno));
	exit(1);
}
