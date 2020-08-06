#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int isJpeg(unsigned char bytes[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    // check correct usage
    if (argc != 2)
    {
        printf("Correct usage: ./recover name_of_the_file\n");
        return 1;
    }

    // Open file
    FILE *file_read = fopen(argv[1], "r");
    if (file_read == NULL)
    {
        printf("File \"%s\" was not found.\n", argv[1]);
        return 1;
    }

    unsigned char block[BLOCK_SIZE];
    int bytes_read = 0;
    int first_jpeg = 1;
    FILE *file_write = NULL;
    char filename[8];
    int num_of_files = 0;

    // read 512 bytes
    do
    {
        bytes_read = fread(block, 1, BLOCK_SIZE, file_read);
        // check if is the beginning of a new picture. If this is the case, start writing to a new file.
        // if it's the first file, open the file for the first time. If not, close the "old" file and open
        // a "new" one
        // do this until there is no more bytes
        if (isJpeg(block))
        {
            sprintf(filename, "%03i.jpg", num_of_files);
            num_of_files += 1;

            if (first_jpeg)
            {
                file_write = fopen(filename, "a");
                first_jpeg = 0;
            }
            else
            {
                fclose(file_write);
                file_write = fopen(filename, "a");
            }
        }

        if (file_write && bytes_read > 0)
        {
            fwrite(block, BLOCK_SIZE, 1, file_write);
        }

    }
    while (bytes_read == BLOCK_SIZE);

    // close last opened write file
    fclose(file_write);

    // Close file
    fclose(file_read);
}


int isJpeg(unsigned char bytes[BLOCK_SIZE])
{
    // checking if header is in the proper size. Masking (bitwise operation) byte 4
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
    {
        return 1; // true
    }
    return 0; // false
}
