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
	{
		ft_printf("\nIt’s money that makes the world go round!\n- Mr. Mini Krabs\n\nCongradulations!\n");
		exit(EXIT_SUCCESS);
	}
	else if (code == exit_failure)
	{
		ft_printf("\nI’ll fill your life with misery and woe. Even if you quit.\n- Mr. Mini Krabs\n\nYou lost!\n");
		exit(EXIT_FAILURE);
	}
}

void	array_playground_exit(char **array_playground, t_error error)
{
	free_array(array_playground);
	ft_printf("Error\n%s\n", error.error_message);
	exit(EXIT_FAILURE);
}

int	string_playground_exit(char *string_playground, t_error error)
{
	free(string_playground);
	ft_printf("Error\n%s\n", error.error_message);
	exit(1);
}
