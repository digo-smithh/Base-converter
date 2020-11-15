#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <ctype.h>

#include <math.h>

#include <stdbool.h>

#include <conio.h>

#include <string.h>

#include <locale.h>

char *number;
int currentBase, futureBase;

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

int currentBaseIsValid()
{
    size_t i = 0;
    while (number[i] != '\000')
    {
        if(number[i] != '.' && number[i] != ',')
        {
            int intNumber;
            if(isalpha(number[i]))
                intNumber = (int)number[i] - 55;
            else
                intNumber = number[i] - '0';

            if(intNumber >= currentBase)
            {
                return 0;
            }
        }
        i++;
    }
    return 1;
}

int currentBaseIsCorrect()
{
    int i;
    char resultScan[1000];
    scanf("%s", &resultScan);
    fflush(stdin);

    while (resultScan[i] != '\000')
    {
        if(resultScan[i] < 48 || resultScan[i] > 57)
        {
            return 0;
        }
        i++;
    }

    currentBase = atoi(resultScan);

    if (currentBase < 2 || currentBase > 36)
        return 0;

    return 1;
}

int futureBaseIsCorrect()
{
    int i;
    char resultScan[1000];
    scanf("%s", &resultScan);
    fflush(stdin);

    while (resultScan[i] != '\000')
    {
        if(resultScan[i] < 48 || resultScan[i] > 57)
        {
            return 0;
        }
        i++;
    }

    futureBase = atoi(resultScan);

    if (futureBase < 2 || futureBase > 36)
        return 0;

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

char* invertString(char* array)
{
    size_t size = strlen(array);
    char * invertedString = (char*) malloc(sizeof(char) * size);
    strcpy(invertedString, array);
    strrev(invertedString);

    return invertedString;
}

int getCommaPosition(char number[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (number[i] == ',' || number[i] == '.')
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
    char * inverted = (char *) malloc(sizeof(char) * 20);
    inverted[19] = '\0';
    int time = 0;
    double wholeDouble = floor(number);
    int whole = wholeDouble;
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
    inverted[time] = '\0';
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
        inverted[time] = '\0';
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
        comma = size;

    for (index = comma - 1, powerIndex = 0; index >= 0; index--, powerIndex++)
    {
        double value = getDoubleValue(number[index]);
        newNumber = newNumber + value * pow(base, powerIndex);
    }

    if (comma != size)
    {
        for (index = comma + 1, powerIndex = 1; index < size - 1; index++, powerIndex++)
        {
            double value = getDoubleValue(number[index]);
            double power = pow((double) 1 / base, (double) powerIndex);
            double multiplying = value * power;
            double somatory = newNumber + multiplying;
            newNumber = somatory;
        }
    }

    return newNumber;
}

int main()
{
    doAsciiArt();
    number = (char *) malloc(1000 * sizeof(char));

    printf("\n        Developed by: Eduardo Migueis - 19167, Manuela Benassi - 19184 and Rodrigo Smith - 19197\n");
    fflush(stdout);

    printf("\n  Enter the number to be converted: ");
    fflush(stdout);
    scanf("%s",number);
    strcat(number, "\0");
    fflush(stdin);

    printf("\n  Enter the current base: ");
    fflush(stdout);

    int baseIsCorrect = currentBaseIsCorrect();
    int baseIsValid = 1;
    if (baseIsCorrect == 1)
        baseIsValid = currentBaseIsValid();

    while (baseIsValid == 0 || baseIsCorrect == 0)
    {
        printf("\n  The base is invalid. Enter the current base again: ");
        fflush(stdout);
        baseIsCorrect = currentBaseIsCorrect();
        baseIsValid = 1;
        if (baseIsCorrect == 1)
            baseIsValid = currentBaseIsValid();
    }

    printf("\n  Enter the future base: ");
    fflush(stdout);

    baseIsCorrect = futureBaseIsCorrect();

    while (baseIsCorrect == 0)
    {
        printf("\n  The base is invalid. Enter the future base again: ");
        fflush(stdout);
        baseIsCorrect = futureBaseIsCorrect();
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
        size_t size = strlen(newNumber) + 1;
        char * negativeNumber = (char * ) malloc(sizeof(char) * (2 + size));
        negativeNumber[0] = '-';
        negativeNumber[1] = '\0';
        strcat(negativeNumber, newNumber);
        newNumber = negativeNumber;
    }

    printf("\n  Result: %s\n\n", newNumber);
    printf("\n  Do you want to restart the program? Type [Y] for YES or anything for NO.  ");

    char option;
    scanf("%c", &option);

    if(option == 'Y' || option == 'y')
    {
        printf("\n\n");
        main();
    }

    return 0;
}
