#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int process_file(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes = getline(&line, &len, fp);
    if (read_bytes <= 0)
    {
        free(line);
        return 0;
    }
    if (read_bytes > 0 && line[read_bytes - 1] == '\n')
    {
        line[read_bytes - 1] = '\0';
        read_bytes--;
    }
    if (read_bytes < 4)
    {
        free(line);
        return 0;
    }
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        FILE *fp = fopen(av[1], "r");
        if (!fp)
            fprintf(stderr, "map error\n");
        else{
            if (!process_file(fp))
                fprintf(stderr, "map error\n");
            fclose(fp);
        }
        return 0;
    }
    return 1;
}