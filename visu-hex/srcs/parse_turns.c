#include "visu_hex.h"

static t_move		*parse_move(char *str)
{
	char	**split;
	t_move	*move;

	li_error(str[0] != 'L', "a move should start with L", NULL);
	str++;
	split = ft_strsplit(str, '-');
	li_error(ft_arrlen((void**)split) != 2, "move format: Lx-y", NULL);
	li_error(!ft_isuintmax(split[0]), "ant number wrong", NULL);
	move = (t_move*)malloc(sizeof(t_move));
	move->ant = ft_atouimax(split[0]);
	move->room = ft_strdup(split[1]);
	ft_arrdel((void**)split);
	return (move);
}

static t_list	*parse_turn(char *line)
{
	int	i;
	char	**split;
	t_list	*turn;
	t_move	*move;

	turn = NULL;
	split = ft_strsplit(line, ' ');
	li_error(ft_arrlen((void**)split) < 1, "a turn must contain at least one move", NULL);
	i = 0;
	while (split[i])
	{
		move = parse_move(split[i++]);
		ft_lstpushnew(&turn, move, sizeof(t_move));
		free(move);
	}
	ft_arrdel((void**)split);
	return (turn);
}

t_list		*parse_turns()
{
	int			i;
	t_list			*turns;
	t_list			*turn;
	char			*line;

	turns = NULL;
	while((i = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
			continue;
		turn = parse_turn(line);
		ft_lstpushnew(&turns, turn, sizeof(t_list));
		free(turn);
		free(line);
	}
	free(line);
	li_error(i == -1, "input error", NULL);
	ft_putendl("");
	return (turns);
}
