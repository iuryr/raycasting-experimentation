#include "MLX42/include/MLX42/MLX42.h"
#include <unistd.h> //sleep
#include <string.h> //memset
#include <stdlib.h> //exit
#include <math.h>
#include <stdio.h>

//Screen measures
#define S_WIDTH 400
#define S_HEIGHT 400

//Map measures
#define M_WIDTH 24
#define M_HEIGHT 24

//byte per pixel
#define BPP sizeof(int)

//FOV in rad
#define FOV M_PI / 3

//wall height in pixels
#define WALL_HEIGHT 400

//hex color
#define RED 0xFF0000FF
#define BLUE 0x0000FFFF
#define GREEN 0x00FF00FF

/** component color
 * struct with reference to red, green, blue and alpha
 *
 * @param r -> red
 * @param g -> green
 * @param b -> blue
 * @param h -> hexadecimal
 */
typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	unsigned int	hex;
}					t_color;

/** component point
 * struct with reference to x and y
 *
 * @param x -> x
 * @param y -> y
 */
typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

/** entity line
 * struct that holds the line
 *
 * @param start -> start of the line
 * @param end -> end of the line
 * @param sprite -> sprite of the line
 */
typedef struct s_line
{
	t_point			start;
	t_point			end;
	t_color			color;
}					t_line;

void put_line_screen(mlx_image_t *img, t_line *line, int sx, int sy)
{
	int	dx;
	int	dy;
	int	err;
	int	temp_err;

	dx = abs(line->end.x - line->start.x);
	dy = abs(line->end.y - line->start.y);
	err = dx - dy;

  while (line->start.x != line->end.x || line->start.y != line->end.y)
	{
		mlx_put_pixel(img, line->start.x, line->start.y, line->color.hex);
		temp_err = 2 * err;
		if (temp_err > -dy)
		{
			err -= dy;
      line->start.x += sx;
		}
		if (temp_err < dx)
		{
			err += dx;
      line->start.y += sy;
		}
  }
}

void draw_line(mlx_image_t *img, t_line *line)
{
	int	sx;
	int	sy;

	if (line->start.x < line->end.x)
		sx = 1;
	else
		sx = -1;
	if (line->start.y < line->end.y)
		sy = 1;
	else
		sy = -1;
	put_line_screen(img, line, sx, sy);
}

void	sair(void *param)
{
	(void) param;
	exit(42);
}

int main(void)
{
	int map[M_WIDTH][M_HEIGHT]=
		{
		  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,3,0,3,3,0,0,0,1},
		  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,3,0,3,3,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

	mlx_t	*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(S_WIDTH, S_HEIGHT, "Prototype Raycasting", true); 
	image = mlx_new_image(mlx, S_WIDTH, S_HEIGHT);
	memset(image->pixels, 255, image->width * image->height * BPP);

	int	posX;
	int posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;

	//posição inicial - experimentar com outros valores depois
	posX = 15;
	posY = 15;

	//olhando para o norte
	dirX = -1;
	dirY = 0;

	//as coordenadas do plano de projeção estão meio hard-coded agora. É possível fazer algo mais geral depois.
	planeX = tan(FOV / 2);
	planeY = 0;

	for (int x = 0; x < S_WIDTH; x++)
	{
		//normalizing
		double cameraX = (2 * x / (double) S_WIDTH) - 1;
		//calculating ray direction
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//calculating distance to next vertical and horizontal grid line (after first)
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		int mapX = posX;
		int mapY = posY;

		//distances to the nearest vertical or horizontal gridline
		double sideDistX;
		double sideDistY;
		//se está andando para esquerda ou direita, cima ou baixo
		int stepX;
		int stepY;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0) * deltaDistY;
		}

		double perpWallDist; //perpendicular distance between wall and projection plane

		int hit = 0;
		int side; // 0 para linhas vertical, 1 para linhas verticais

		//DDA loop
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			//check if hit a wall
			if (map[mapX][mapY] > 0)
			{
				hit = 1;
			}
		}

		if (side == 0)
		{
			perpWallDist = sideDistX - deltaDistX;
		}
		else
		{
			perpWallDist = sideDistY - deltaDistY;
		}

		//altura da linha ser desenhada
		int lineHeight = (int) floor(WALL_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WALL_HEIGHT / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + WALL_HEIGHT / 2;
		if(drawEnd >= WALL_HEIGHT)drawEnd = WALL_HEIGHT - 1;

		t_color color;
		if (map[mapX][mapY] == 1)
		{
			color.hex = BLUE;
		}
		if (map[mapX][mapY] == 2)
		{
			color.hex = GREEN;
		}
		if (map[mapX][mapY] == 3)
		{
			color.hex = RED;
		}
		t_point point1 = {x, drawStart};
		t_point point2 = {x, drawEnd};
		t_line line = {point1, point2, color};
		
		printf("perpWallDist: %f \n", perpWallDist);
		printf("x: %d | y_start: %d | y_end: %d | lineheight: %d\n", x, drawStart, drawEnd, lineHeight);
		
		draw_line(image, &line);

		//see if it makes sense
		// printf("CameraX: %f | rayDirX: %f | rayDirY: %f | deltaDistX: %f | deltaDistY: %f\n", cameraX, rayDirX, rayDirY, deltaDistX, deltaDistY);
	}

	//distancia que o raio vai ter que percorrer até os limites do primeiro grid;


	mlx_image_to_window(mlx, image, 0, 0);
	mlx_close_hook(mlx, &sair, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
