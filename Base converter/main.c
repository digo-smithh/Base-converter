#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <ctype.h>

#include <math.h>

#include <stdbool.h>

#include <conio.h>

#include <string.h>

#include <locale.h>

void doAsciiArt()
{
    FILE * arq;
    char txt[128];
    int contador = 0;

    if ((arq = fopen("assets/title.txt", "r")) == 0)
    {
        puts("Erro");
    }
    else
    {
        while (fgets(txt, sizeof(txt), arq) != NULL)
        {
            contador++;
            printf("%s", txt);
        }
    }
}

int isValid(char* number, int currentBase)
{
    int i;
    for(i = 0; i < strlen(number); i++)
    {
        if(number[i] >= currentBase)
        {
            return 0;
        }
    }
    return 1;
}

char getCharValue(int value)
{
    char num[] =
    {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        'V',
        'W',
        'X',
        'Y',
        'Z'
    };

    return num[value];
}

char* resizeArray(char array[], int oldSize, int newSize)
{

    char* newArray = (char * ) malloc(sizeof(char) * newSize);

    if (oldSize < newSize)
    {
        for (int index = 0; index < oldSize; index++)
        {
            newArray[index] = array[index];
        }
    }
    else
    {
        for (int index = 0; index < newSize; index++)
        {
            newArray[index] = array[index];
        }
    }

    return newArray;
}

char* invertString(char array[])
{
    char * invertedString = (char*) malloc(sizeof(char) * strlen(array));
    strcpy(invertedString, array);
    strrev(invertedString);

    return invertedString;
}

int getCommaPosition(char number[], int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        if (number[i] == ',')
        {
            return i;
        }
    }
    return -1;
}

double getDoubleValue(char value)
{
    if (isdigit(value))
        return (double) value - 48;
    else
        return (double) toupper(value) - 55;
}

char * fromTen(double number, int base)
{
    char * inverted = (char * ) malloc(sizeof(char) * 20);
    int time = 0;
    int whole = (int) number;
    double decimal = number - whole;

    while (whole > 0)
    {
        inverted[time] = getCharValue((whole % base));
        whole = whole / base;
        time += 1;

        if (time == strlen(inverted) - 1)
            inverted = resizeArray(inverted, strlen(inverted), (strlen(inverted) + 5));
    }

    inverted = resizeArray(inverted, strlen(inverted), time);
    inverted = invertString(inverted);


    if (decimal > 0.0)
    {

        inverted = resizeArray(inverted, time, time + 10);

        inverted[time] = ',';
        time++;
        int i;
        for (i = 0; i < 9; i++, time++)
        {
            if (decimal == 0.0)
                break;

            decimal = decimal * base;
            inverted[time] = getCharValue(decimal);
            decimal = decimal - (int) decimal;
        }
    }

    return inverted;
}

double toTen(char * number, int base)
{
    double newNumber = 0;
    int powerIndex = 0, index = 0;
    int comma = 0;
    int size = strlen(number);

    comma = getCommaPosition(number, size);

    if (comma == -1)
        comma = size - 1;

    for (index = comma - 1, powerIndex = 0; index >= 0; index--, powerIndex++)
    {
        double value = getDoubleValue(number[index]);
        newNumber = newNumber + value * pow(base, powerIndex);
    }

    if (comma != size - 1)
    {
        for (index = comma + 1, powerIndex = 1; index < size - 1; index++, powerIndex++)
        {
            double value = getDoubleValue(number[index]);
            newNumber = newNumber + value * pow((double) 1 / base, (double) powerIndex);
        }
    }

    return newNumber;
}

int main()
{
    doAsciiArt();
    printf("\n        Developed by: Eduardo Migueis - 19167 and Rodrigo Smith - 19197\n");
    fflush(stdout);

    char number[1000];
    int currentBase = 0, futureBase = 0;

    printf("\n  Enter the number to be converted: ");
    fflush(stdout);
    fgets(number, 1000, stdin);
    fflush(stdin);

    printf("\n  Enter the current base: ");
    fflush(stdout);

    while (scanf("%d", & currentBase) == 0 || currentBase < 2 || currentBase > 36)
    {
        printf("\n  The base is invalid. Enter the current base again: ");
        fflush(stdout);
        scanf("%d", & currentBase);
        fflush(stdin);
    }

    int baseIsValid = isValid(number, currentBase);

    while (baseIsValid == 0)
    {
        printf("\n  The number contains characters which are not in base %i. Enter the current base again: ", currentBase);
        fflush(stdout);
        scanf("%d", & currentBase);
        fflush(stdin);
        baseIsValid = isValid(number, currentBase);
    }



    printf("\n  Enter the future base: ");

    while (scanf("%d", & futureBase) == 0 || futureBase < 2 || futureBase > 36)
    {
        printf("\n  The base is invalid. Enter the future base again: ");
        fflush(stdout);
        scanf("%d", & futureBase);
        fflush(stdin);
    }


    char * n = (char * ) malloc(1000 * sizeof(char));

    if (number[0] == '-')
    {
        n = number + 1;
    }
    else
        n = number;

    char * newNumber = fromTen(toTen(n, currentBase), futureBase);

    if (number[0] == '-')
    {
        char negativeNumber[1000];
        negativeNumber[0] = '-';
        strcat(negativeNumber, newNumber);
        newNumber = negativeNumber;
    }

    printf("\n  Result: %s\n\n", newNumber);

    free(newNumber);
    return 0;
}
