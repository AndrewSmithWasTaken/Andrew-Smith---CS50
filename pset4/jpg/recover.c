/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>

// jpg headers
#define JPGH1 0xff
#define JPGH2 0xd8
#define JPGH3 0xff
#define JPGH4a 0xe0
#define JPGH4b 0xe1

int main(int argc, char* argv[])
{
    // declaring variables
    unsigned char buffer[512];
    int jpg_count = 0;
    char filenom[8];
    
    FILE* raw = fopen("card.raw", "r");
    if (raw == NULL)
    {
        fclose(raw);
        printf("Could not open file");
        return 1;
    }
    
    FILE* img = NULL;
    
    while (fread(&buffer, sizeof(char), 512, raw) == 512)
    {     
        // jpg header found, close/create operations as appropriate
        if ( (buffer[0] == JPGH1 && buffer[1] == JPGH2 && buffer[2] == JPGH3) && (buffer[3] == JPGH4a || buffer[3] == JPGH4b) )
        {
            if (img != NULL)
            {
                fclose(img);
                jpg_count ++;
            }
            sprintf(filenom, "%03d.jpg", jpg_count);
            img = fopen(filenom, "a");        
        }
        // write to existing/new img file
        if (img != NULL)
        {
            fwrite(&buffer, sizeof(char), 512, img);
        }
    }
    fclose(raw);
    fclose(img);
    return 0; 
}

