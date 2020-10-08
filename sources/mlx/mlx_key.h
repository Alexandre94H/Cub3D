#ifndef		MLX_KEY_H
# define	MLX_KEY_H

#include "mlx1.h"

#define		KEY_W 119
#define		KEY_S 115
#define		KEY_A 97
#define		KEY_D 100
#define		KEY_UP 65362
#define		KEY_DOWN 65364
#define		KEY_LEFT 65361
#define		KEY_RIGHT 65363
#define		KEY_ESC 65307
#define		KEY_F2 65471

typedef  struct  s_key
{
    unsigned short	input;
    key				function;
	char			index;
}				t_key;

void	w(t_runtime *runtime);
void	s(t_runtime *runtime);
void	a(t_runtime *runtime);
void	d(t_runtime *runtime);
void	left(t_runtime *runtime);
void	right(t_runtime *runtime);
void	f2(t_runtime *runtime);
void	esc(t_runtime *runtime);

t_key key_board[] = {
	{KEY_W, &w, -1},
	{KEY_S, &s, -1},
	{KEY_A, &a, -1},
	{KEY_D, &d, -1},
	{KEY_UP, 0, -1},
	{KEY_DOWN, 0, -1},
	{KEY_LEFT, &left, -1},
	{KEY_RIGHT, &right, -1},
	{KEY_F2, &f2, -1},
	{KEY_ESC, &esc, -1},
	{0, 0, 0},
};

#endif