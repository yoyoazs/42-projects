/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 00:16:43 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 12:36:20 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define FLOOR 47
# define REFRESH_RATE 45

# define GRAVITY 4
# define JUMP_VELOCITY -30
# define MAX_FALL_VELOCITY 40

# define MOVE_X 8
# define MOVE_Y 10

# define MAPS_DIR "./assets/maps/"
# define IDLE 0
# define RIGHT 1
# define LEFT 2
# define UP 3
# define DOWN 4
# define CLIMBING 5

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_Z 122
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_SPACE 32

# define MAX_SCORES 10
# define MAX_NAME_LENGTH 50

# define ERROR_FORMAT "\x1B[1m\x1B[31mError: \n\x1B[0;37m\x1B[31m"
# define RESET_COLOR "\x1B[0;37m"

# define NUMBER_THREAD 6

#endif