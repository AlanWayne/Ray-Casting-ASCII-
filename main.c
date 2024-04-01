#include <math.h>
#include <ncurses.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

int main() {
	initscr();
	box(stdscr, 0, 0);
	int height = getmaxy(stdscr) - 2;
	int width = (getmaxx(stdscr) - 2) / 2;

	int** field = (int**)malloc(width * sizeof(int*));

	for (int i = 0; i < width; ++i) {
		field[i] = (int*)malloc(height * sizeof(int));

		for (int k = 0; k < height; ++k) {
			field[i][k] = ' ';
		}
	}

	for (int i = 20; i < 40; i += 2) {
		for (int k = 10; k < 20; ++k) {
			if (i == 20 || k == 10 || i == 38 || k == 19) {
				field[i][k] = '[';
				field[i + 1][k] = ']';
			}
		}
	}

	double x = width / 2;
	double y = height / 2;
	double x_step = 0.3;
	double y_step = 0.3;

	double look = 0;

	int input = 0;

	while (input != 'q') {
		int degree = look - 30;

		while (degree < look + 30) {
			double ray_x = x;
			double ray_y = y;

			while (true) {
				double radian = degree * PI / 180.0;

				ray_x = ray_x + cos(radian);
				ray_y = ray_y + sin(radian);

				int int_ray_x = (int)roundl(ray_x);
				int int_ray_y = (int)roundl(ray_y);

				if (int_ray_x < 0 || int_ray_y < 0) break;
				if (int_ray_x >= width || int_ray_y >= height) break;

				if (field[int_ray_x][int_ray_y] == '[' ||
					field[int_ray_x][int_ray_y] == ']')
					break;
				field[int_ray_x][int_ray_y] = '.';
			}

			degree += 2;
		}

		wclear(stdscr);

		for (int i = 0; i < width; ++i) {
			for (int k = 0; k < height; ++k) {
				if (i == roundl(x) && k == roundl(y))
					mvwprintw(stdscr, k + 1, (i + 1) * 2, "(");
				else if (i == roundl(x + 1) && k == roundl(y))
					mvwprintw(stdscr, k + 1, (i + 1) * 2, ")");
				else
					mvwprintw(stdscr, k + 1, (i + 1) * 2, "%c", field[i][k]);
				if (field[i][k] == '.') field[i][k] = ' ';
			}
		}

		wrefresh(stdscr);

		input = getch();

		switch (input) {
			case 'w':
				x += cos(look * PI / 180.0);
				y += sin(look * PI / 180.0);
				break;
			case 's':
				y += y_step;
				break;
			case 'a':
				look -= 5;
				break;
			case 'd':
				look += 5;
				break;
		}

		if (look < 0) look += 360;

		if (look > 360) look -= 360;
	}

	for (int i = 0; i < width; ++i) {
		free(field[i]);
	}
	free(field);

	endwin();
	return 0;
}