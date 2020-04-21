#include <stdio.h>
#include <limits.h>

int RleEncodeFile(FILE *inFile, FILE *outFile)
{
    int currChar;
    int prevChar;
    unsigned char count;

    prevChar = EOF;
    count = 0;

    while ((currChar = fgetc(inFile)) != EOF)
    {
        fputc(currChar, outFile);

        if (currChar == prevChar)
        {
            count = 0;

            while ((currChar = fgetc(inFile)) != EOF)
            {
                if (currChar == prevChar)
                {
                    count++;

                    if (count == UCHAR_MAX)
                    {
                        fputc(count, outFile);


                        prevChar = EOF;
                        break;
                    }
                }
                else
                {
                    fputc(count, outFile);
                    fputc(currChar, outFile);
                    prevChar = currChar;
                    break;
                }
            }
        }
        else
        {
            prevChar = currChar;
        }

        if (currChar == EOF)
        {
            fputc(count, outFile);
            break;
        }
    }
    return 0;
}
int main()
{
    FILE *inFile;
    FILE *outFile;

    outFile = fopen("output", "wb");
    if((inFile = fopen("obrazek.jpg", "rb"))==NULL) {
        printf("Nie ma takiego pliku.\n");
        return -1;
    }
    RleEncodeFile(inFile, outFile);

    fclose(inFile);
    fclose(outFile);
    return 0;
}

