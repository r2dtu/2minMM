#include <stdio.h>

const int GRID_SIZE = 16;
int maze_cells[GRID_SIZE][GRID_SIZE] = { 0 };

int main() {

  // Initialize cells for modified floodfill algorithm
  int curr_dist = GRID_SIZE - 2;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      maze_cells[i][j] = curr_dist;
      if (j < GRID_SIZE / 2 - 1) {
        curr_dist -= 1;
      } else if (j > GRID_SIZE / 2 - 1) {
        curr_dist += 1;
      }
      printf("%2d ", maze_cells[i][j]);
    }
    if (i < GRID_SIZE / 2 - 1) {
      curr_dist -= 2;
    } else if (i == GRID_SIZE / 2 - 1) {
      curr_dist -= 1;
    }
    printf("\n");
  }
}
