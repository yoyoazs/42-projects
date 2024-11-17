/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:08:43 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 20:24:38 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_score(t_game *data)
{
	double	score_temps;
	double	score_movements;
	double	score_damage;
	double	score_kills;
	double	score_piece;

	score_temps = (get_milliseconds() - data->start_ms) * 0.2;
	score_movements = data->player->number_movement * 0.1;
	score_damage = data->player->number_damage * 0.3;
	score_kills = data->player->number_kill * 0.2;
	score_piece = data->player->collectables * 0.2;
	return ((int)score_temps + score_movements + score_damage
		+ score_kills + score_piece);
}

void	draw_stats2(t_game *data, t_image *img, t_player *player)
{
	draw_text_left(data, ft_itoa(player->number_damage),
		init_sprite(2130, 580, 50), img);
	draw_text(data, ft_strdup("Kills      :"), init_sprite(1510, 630, 50), img);
	draw_text_left(data, ft_itoa(player->number_kill),
		init_sprite(2130, 630, 50), img);
	draw_text(data, ft_strdup("Sauts      :"), init_sprite(1510, 680, 50), img);
	draw_text_left(data, ft_itoa(player->number_jump),
		init_sprite(2130, 680, 50), img);
	draw_text(data, ft_strdup("Score      :"), init_sprite(1510, 730, 50), img);
	draw_text_left(data, ft_itoa(get_score(data)),
		init_sprite(2130, 730, 50), img);
}

void	draw_stats(t_game *data)
{
	t_player	*player;
	t_image		*img;

	img = data->image;
	player = data->player;
	draw_rect(init_form(1500, 220, 700, 900), img);
	draw_text(data, ft_strdup("stats"), init_sprite(1760, 230, 75), img);
	draw_text(data, ft_strdup("Temps      :"), init_sprite(1510, 430, 50), img);
	draw_text_left(data, ms_to_time(get_milliseconds() - data->start_ms),
		init_sprite(2130, 430, 50), img);
	draw_text(data, ft_strdup("Mouvement :"), init_sprite(1510, 480, 50), img);
	draw_text_left(data, ft_itoa(player->number_movement),
		init_sprite(2130, 480, 50), img);
	draw_text(data, ft_strdup("Pieces     :"), init_sprite(1510, 530, 50), img);
	draw_text_left(data, ft_itoa(player->collectables),
		init_sprite(2130, 530, 50), img);
	draw_text(data, ft_strdup("Degats     :"), init_sprite(1510, 580, 50), img);
	draw_stats2(data, img, player);
}

void	draw_leaderboard(t_game *data)
{
	int		y;
	int		number_score;
	t_score	*scores;
	t_image	*img;

	img = data->image;
	scores = gc_malloc(data->memory_table, sizeof(t_score) * MAX_SCORES);
	number_score = load_scores(data, scores);
	add_scores(scores, &number_score, data->player->username, get_score(data));
	save_scores(data, scores, number_score);
	draw_rect(init_form(300, 220, 700, 900), img);
	draw_text(data, ft_strdup("Leaderboard"), init_sprite(460, 230, 75), img);
	y = -1;
	while (++y < MAX_SCORES && y < number_score)
	{
		draw_text(data, ft_strdup(scores[y].name),
			init_sprite(310, 450 + y * 50, 50), img);
		draw_text_left(data, ft_itoa(scores[y].score),
			init_sprite(930, 450 + y * 50, 50), img);
	}
	gc_free(data->memory_table, scores);
}

void	draw_screen_end(t_game *data)
{
	int		x;
	int		y;
	t_image	*image;

	image = data->images->wall_sprite;
	y = -1;
	data->state = 6;
	while (++y < data->screen_y / 100)
	{
		x = -1;
		while (++x < data->screen_x / 100 + 1)
			pus_img(data, init_sprite(x * 100, y * 100, FLOOR), image);
	}
	draw_leaderboard(data);
	draw_stats(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img_ptr, 0, 0);
}
