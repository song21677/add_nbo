#include <stdio.h>
#include <stdint.h>

void usuage() {
	printf("syntax : add_nbo <file1> <file2>");
	printf("sample : add_nbo a.bin c.bin");
}

uint32_t my_ntohl(uint32_t n) {
    return ((n & 0xFF000000) >> 24 | (n & 0x00FF0000) >> 8 | (n & 0x0000FF00) << 8 | (n & 0x000000FF) << 24);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		usuage();
		return -1;
	}

	FILE* fp1;
	FILE* fp2;
	uint32_t buffer1, buffer2;

	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	if (fp1 == NULL | fp2 == NULL) {
		printf("Can't open file.\n");
		return -1;
	}
    	fread(&buffer1, 4, 1, fp1);
    	fread(&buffer2, 4, 1, fp2);
	
    	buffer1 = my_ntohl(buffer1);
    	buffer2 = my_ntohl(buffer2);

    	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", buffer1, buffer1, buffer2, buffer2, buffer1 + buffer2, buffer1 + buffer2);
}


