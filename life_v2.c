#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ALIVE '0'
#define DEAD ' '

// دالة لحساب عدد الجيران - نستخدم مؤشر عادي ونحسب الموقع يدوياً
int count_neighbors(int h, int w, char *grid, int y, int x) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            
            int ny = y + i;
            int nx = x + j;

            if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
                // الوصول للخلية: (y * العرض + x)
                if (grid[ny * w + nx] == 1) count++;
            }
        }
    }
    return count;
}

void evolve(int h, int w, char *grid) {
    // تخصيص ذاكرة للمصفوفة المؤقتة باستخدام malloc لضمان التوافق
    char *next = malloc(h * w);
    if (!next) return;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int neighbors = count_neighbors(h, w, grid, i, j);
            int idx = i * w + j;
            
            if (grid[idx] == 1)
                next[idx] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            else
                next[idx] = (neighbors == 3) ? 1 : 0;
        }
    }

    // نسخ النتائج للأصلية وتحرير الذاكرة
    for (int i = 0; i < h * w; i++) grid[i] = next[i];
    free(next);
}

int main(int ac, char **av) {
    if (ac != 4) return 1;

    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iterations = atoi(av[3]);

    if (width <= 0 || height <= 0 || iterations < 0) return 1;

    // تخصيص مصفوفة مسطحة (Flat Array)
    char *grid = calloc(width * height, sizeof(char));
    if (!grid) return 1;

    int x = 0, y = 0, pen_down = 0;
    unsigned char c;

    while (read(0, &c, 1) > 0) {
        switch (c) {
            case 'w': y--; break;
            case 'a': x--; break;
            case 's': y++; break;
            case 'd': x++; break;
            case 'x': pen_down = !pen_down; break;
        }
        if (pen_down && x >= 0 && x < width && y >= 0 && y < height)
            grid[y * width + x] = 1;
    }

    for (int i = 0; i < iterations; i++)
        evolve(height, width, grid);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            putchar(grid[i * width + j] ? ALIVE : DEAD);
        }
        putchar('\n');
    }

    free(grid);
    return 0;
}