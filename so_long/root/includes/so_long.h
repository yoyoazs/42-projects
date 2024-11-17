/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:24:46 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 11:33:58 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include "struct.h"
# include "mlx.h"
# include "libft.h"
# include "gc.h"

//INITIALISATION
int					init_map(t_game *data, int argc, char **argv);
int					init_mlx(t_game *data);
void				init_player(t_game *data);
void				init_all_images(t_game *data);
t_sprite			init_sprite(int x, int y, int sprite);
t_form				init_form(int x, int y, int width, int height);
t_pos				init_pos(int x, int y);
t_image				*init_image(t_game *data, char *file_path,
						int height, int width);

//HOOKS
int					key_hook_up(int keycode, t_game *data);
int					key_hook_down(int keycode, t_game *data);

//SPRITE
void				pus_img(t_game *data, t_sprite, t_image *image);
void				push_img_game(t_game *data, t_sprite sprite,
						t_image *img);

//DRAW
void				draw_rect(t_form form, t_image *img);
void				draw_image_on_window(t_game *data, t_image *img);
void				pixel_put(t_image *img, t_sprite sprite);
void				draw_text(t_game *data, char *str, t_sprite sprite,
						t_image *img);
void				draw_text_left(t_game *data, char *str, t_sprite sprite,
						t_image *img);
int					get_pixel_value(t_game *data, t_sprite sprite, t_image *img,
						t_pos pos);

//MAP
int					check_valid_path(t_game *data);
int					check_path(char **map, t_pos pos, t_pos pos2);
char				**copy_map(t_game *data);
void				get_pos_item(t_game *data, int *x, int *y);
int					get_map(t_game *data, char *map);
int					error_map(t_game *data, char *str);
int					check_map(t_game *data);
void				get_visible_map(t_game *data);

//PLAYER
int					on_ladder(t_game *data);
int					can_exit(t_game *data);
void				handle_movement(t_game *data);
int					get_next_sprite(t_game *data, int movement);
void				update_player(t_game *data);

//UTILS
int					ft_abs(int n);
void				destroy_mlx(t_block_info *ptr);
void				destroy_mlx_win(t_block_info *ptr);
void				destroy_mlx_img(t_block_info *params);
unsigned long		get_milliseconds(void);
char				*ms_to_time(unsigned long long ms);
void				write_string(t_game *data, int fd, const char *str);
int					check_file(t_game *data, char *asset);
int					check_extension(char *file, char *extension);

//FREE
void				free_map(t_game *data, char **map);
void				free_game(t_game *data);

//GAME
void				draw_info(t_game *data);
void				update_map(t_game *data);
int					draw_map(t_game *data);
void				gravity(t_game *data);
int					check_fall(t_game *data, int x, int y, int fall);
int					check_move(t_game *data, t_pos pos,
						int movement, int print);

//ENEMY
void				update_enemy(t_game *data);
void				draw_enemy(t_game *data);
void				init_enemy(t_game *data);

//WALLS
int					get_wall_sprite_4(t_game *data, int x, int y);
int					get_wall_sprite_3(t_game *data, int x, int y);
int					get_wall_sprite_2(t_game *data, int x, int y);
int					is_wall(t_game *data, int x, int y);
int					get_wall_sprite(t_game *data, int x, int y);

//SCREEN
void				draw_screen_start(t_game *data);
void				updade_sreen_start(t_game *data);
void				draw_screen_end(t_game *data);
void				draw_dead_screen(t_game *data);

//COLLECTABLE
void				init_collectable(t_game *data);
void				get_collectable(t_game *data);
int					on_collectable(t_game *data);

//SCORE
int					load_scores(t_game *data, t_score *scores);
void				add_scores(t_score *scores, int *number_score,
						const char *username, int new_score);
void				save_scores(t_game *data, t_score *scores,
						int number_score);

#endif