/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:19:31 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/26 08:33:55 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	save_scores(t_game *data, t_score *scores, int number_score)
{
	const int	fd = open("scores.txt", O_WRONLY | O_CREAT, 0644);
	char		*str;
	int			i;

	if (fd == -1)
		error_map(data, "Error while opening file.");
	i = -1;
	while (++i < number_score)
	{
		write_string(data, fd, scores[i].name);
		write_string(data, fd, ",");
		str = ft_itoa(scores[i].score);
		write_string(data, fd, str);
		write_string(data, fd, "\n");
		free(str);
	}
	close(fd);
}

void	sort_scores(t_score *scores, int number_score)
{
	int		i;
	int		j;
	int		swapped;
	t_score	temp;

	i = -1;
	while (++i < number_score - 1)
	{
		swapped = 0;
		j = -1;
		while (++j < number_score - i - 1)
		{
			if (scores[j].score < scores[j + 1].score)
			{
				temp = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped)
			break ;
	}
}

void	add_scores(t_score *scores, int *number_score,
const char *username, int new_score)
{
	if (*number_score < MAX_SCORES)
	{
		scores[*number_score].score = new_score;
		ft_strlcpy(scores[*number_score].name, username,
			ft_strlen(username) + 1);
		(*number_score)++;
	}
	else
	{
		if (new_score > scores[MAX_SCORES - 1].score)
		{
			scores[MAX_SCORES - 1].score = new_score;
			ft_strlcpy(scores[MAX_SCORES - 1].name, username,
				ft_strlen(username) + 1);
		}
	}
	sort_scores(scores, *number_score);
}

void	extract_data(const char *line, t_score *score, int *number_score)
{
	char	**data;
	int		i;

	i = -1;
	data = ft_split(line, ',');
	if (data[0] && data[1])
	{
		ft_strlcpy(score->name, data[0], ft_strlen(data[0]) + 1);
		score->score = ft_atoi(data[1]);
	}
	else
		(*number_score)--;
	while (data[++i])
		free(data[i]);
	free(data);
}

int	load_scores(t_game *data, t_score *scores)
{
	const int	fd = open("scores.txt", O_RDONLY | O_CREAT, 0644);
	int			number_score;
	char		*line;

	number_score = 0;
	if (fd == -1)
		error_map(data, "Error while opening file.");
	line = get_next_line(fd);
	while (line)
	{
		if (number_score < MAX_SCORES)
		{
			extract_data(line, &scores[number_score], &number_score);
			number_score++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (number_score);
}
