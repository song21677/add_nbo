#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void usage() {
    printf("syntax : add_nbo <file1> <file2>");
    printf("sample : add_nbo a.bin c.bin");
}

uint32_t my_ntohl(uint32_t n) {
    return ((n & 0xFF000000) >> 24 | (n & 0x00FF0000) >> 8 | 
    (n & 0x0000FF00) <<8 | (n & 0x000000FF) << 24);
}

uint32_t add_nbo(char filename[]) {
    FILE *fp;
    uint32_t buffer;
    size_t num;

    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Can't open file.\n");
        exit(1);
    }
    if ((num = fread(&buffer, 4, 1, fp)) != 1) {
	    printf("Can't read file.\n");
	    exit(1);
    }
    fclose(fp);
    
    buffer = my_ntohl(buffer);
    
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        usage();
        return -1;
    }
    
    int i;
    uint32_t rv[3];
    for (i=1; i<3; i++) {
        rv[i] = add_nbo(argv[i]);
    }
    
    printf("%d(%#x) + %d(%#x) = %d(%#x)\n", rv[1], rv[1], 
    rv[2], rv[2], rv[1] + rv[2], rv[1] + rv[2]);
}

