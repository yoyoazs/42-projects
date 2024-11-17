/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:52:20 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 11:29:11 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "define.h"
# include "gc.h"

typedef struct s_score
{
	char	name[MAX_NAME_LENGTH];
	int		score;
}	t_score;

typedef struct s_free_memory_args
{
	void	*ptr;
	void	*ptr2;
}	t_free_memory_args;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_sprite
{
	int	x;
	int	y;
	int	sprite;
	int	is_player;
}	t_sprite;

typedef struct s_form
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_form;

typedef struct s_map
{
	int		collectables;
	char	**structure;
	int		len;
	int		width;
	int		number_enemy;
	int		exit_y;
	int		exit_x;
}	t_map;

typedef struct s_collectable
{
	int						x;
	int						y;
	struct s_collectable	*next;
}	t_collectable;

typedef struct s_enemy
{
	int				x;
	int				y;
	int				last_x;
	int				last_y;
	int				sprite;
	int				direction;
	int				attack;
	int				alive;
	int				dying;
	struct s_enemy	*next;
}	t_enemy;

typedef struct s_player
{
	int					x;
	int					y;
	int					last_x;
	int					last_y;
	int					movement;
	int					direction;
	int					last_sprite;
	int					is_jumping;
	unsigned long		last_jump;
	int					health;
	int					collectables;
	int					number_damage;
	int					number_kill;
	float				number_jump;
	int					velocity_y;
	unsigned long		last_damage;
	unsigned long long	number_movement;
	unsigned long		last_mov;
	int					attack;
	char				*username;
}	t_player;

typedef struct s_image
{
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_start_game {
	int	sprite_idle;
	int	sprite_run;
	int	sprite_jump;
	int	sprite_climb;
	int	sprite_attack;
}	t_start_game;

typedef struct s_images {
	t_image	*player_sprite;
	t_image	*enemy_sprite;
	t_image	*wall_sprite;
	t_image	*collectable_sprite;
	t_image	*key_sprite;
	t_image	*alphanum_sprite;
	t_image	*exit_sprite;
	t_image	*heart_sprite;
	t_image	*door_sprite;
}	t_images;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				screen_x;
	int				screen_y;
	int				state;
	int				sprite_collectable;
	unsigned long	ms;
	unsigned long	start_ms;
	t_images		*images;
	t_enemy			*enemies;
	t_map			*map;
	t_player		*player;
	t_image			*image;
	t_image			*image_print;
	t_collectable	*collectables;
	t_start_game	*start_game;
	t_memory_table	*memory_table;
}	t_game;

typedef struct s_thread_args
{
	t_game	*data;
	int		start_y;
	int		start_x;
	int		y;
	int		end_y;
}	t_thread_args;

#endif