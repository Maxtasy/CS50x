#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define byte size
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check for correct input
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // remember file name
    char *inName = argv[1];

    // open inFile and check pointer value against NULL
    FILE* inFile = fopen(inName, "rb");

    if (inFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", inName);
        return 2;
    }

    // create buffer (BYTE can compare to hex values and can be used to write to FILE*)
    BYTE buffer[512];

    // 000.jpg\0 --> 8
    char outName[8];

    // count for file naming
    int count = 0;

    // set to 1 when we found the first jpg and are writing bytes
    int writing = 0;

    // declare outFile pointer
    FILE *outFile;

    // read in 512 bytes in 1 byte blocks, as long as we get a full 512 byte block
    while (fread(buffer, 1, 512, inFile) == 512)
    {
        // check if first bytes match jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // check if we are currently writing to a file. if so, close file.
            if (writing == 1)
            {
                fclose(outFile);
            }

            // format name for jpg file
            sprintf(outName, "%03i.jpg", count);

            // open new file to write jpg bytes into
            outFile = fopen(outName, "w");

            // check pointer against NULL value
            if (outFile == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", outName);
                return 3;
            }

            // set writing flag and increase count by 1 for next jpg file name
            writing = 1;
            count++;
        }

        // write bytes from buffer into outFile
        if (writing == 1)
        {
            // write current block to outFile
            fwrite(buffer, 1, 512, outFile);
        }
    }

    // clean up
    fclose(inFile);
    fclose(outFile);

    return 0;
}