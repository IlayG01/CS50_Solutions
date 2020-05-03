#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: recover [nameOfImage]\n");
        return 1;
    }

    // Set the file pointer
    FILE *pImage = fopen(argv[1], "r");
    printf("got the pImage\n");

    // checking if we got nulled and handle if we do
    if (pImage == NULL)
    {
        printf("Can't open %s\n", argv[1]);
        return 1;
    }

    //  JPEGs signatures - first 3 bytes of an image
    unsigned char signature[3] = {0xff, 0xd8, 0xff};

    //  buffer memory
    unsigned char buffer[512];

    //  pointer to the jpegs we will create
    FILE *pJpeg = NULL;
    char filename[8];  // File name

    //  initialize variable for the while loop
    bool isFileOpen = false;
    bool isNewJpeg = false;
    int jpegCounter = 0;

    //  loop traveling on the raw image
    while (fread(buffer, sizeof(char), 512, pImage) != 0)
    {
        //  New JPEG
        if (buffer[0] == signature[0] && buffer[1] == signature[1] && buffer[2] == signature[2] && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (isFileOpen)
            {
                fclose(pJpeg);
                isFileOpen = false;
            }
            isNewJpeg = true;
        }
        //  New Jpeg is needed and file is not open
        if (isNewJpeg && !isFileOpen)
        {
            sprintf(filename, "%03d.jpg", jpegCounter);
            pJpeg = fopen(filename, "w");
            jpegCounter++;
            //  Write the buffer into the file
            fwrite(buffer, sizeof(unsigned char), 512, pJpeg);
            //  Update the flags
            isFileOpen = true;
            isNewJpeg = false;
        }
        else if (isFileOpen)
        {
            //  Write the buffer into the file
            fwrite(buffer, sizeof(unsigned char), 512, pJpeg);
        }
    }
    // Closing files
    fclose(pJpeg);
    fclose(pImage);
    return 0;
}
