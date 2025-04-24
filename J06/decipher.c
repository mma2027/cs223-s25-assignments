#include <stdio.h>

int main(int argc, char* argv[])
{
    char* filename = argv[1];
    unsigned int mask = 0b01111111;
    FILE* fp = fopen(filename, "rb");
    char c;
    while (fread(&c, 1, sizeof(c), fp) > 0)
    {
        c = (c >> 1) & mask;
        printf("%c", c);
    }
    fclose(fp);
    return 0;
}
