#include <cstdio>

int main()
{
    FILE* gp = popen("gnuplot -persistent", "w");

    fprintf(gp, "plot sin(x)\n");

    fflush(gp);

    getchar();

    pclose(gp);
}