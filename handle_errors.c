#include "so_long.h"

t_error	error(int code, char *message)
{
	t_error	error;

	error.error_code = code;
	error.error_message = message;
	return (error);
}

t_play	set_error(int code, char *message, t_play playground_state)
{
	playground_state.error = error(code, message);
	return (playground_state);
}

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
	free_array(array_playground);
	write(1, "Error\n", 6);
	ft_printf("%s\n", error.error_message);
	exit(EXIT_FAILURE);
}

int	string_playground_exit(char *string_playground, t_error error)
{
	free(string_playground);
	write(1, "Error\n", 6);
	ft_printf("%s\n", error.error_message);
	exit(1);
}
