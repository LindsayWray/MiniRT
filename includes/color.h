#ifndef COLOR_H
# define COLOR_H

# include "miniRT.h"

t_color new_color(int r, int g, int b);
t_color mix_color(t_color color, t_color light);
t_color	add_colors(t_color c1, t_color c2);

#endif