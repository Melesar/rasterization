//
// Created by serge on 23.01.2019.
//

#include <cstring>
#include "file_utils.h"

bool readLine(FILE *f, char *buff)
{
    auto result = fgets(buff, LINE_LENGTH, f) != nullptr;
    if (result) {
        buff[strlen(buff) - 1] = '\0';
    }

    return result;
}

void getToken(char *line, char *token, char *content)
{
    int i = 0;
    char* s = line + i;
    char* buffer = token;
    bool spaceMet = false;
    int spaceIndex = 0;
    while (*s != '\0')
    {
        if (!spaceMet && *s == ' ')
        {
            spaceMet = true;
            buffer[i] = '\0';
            buffer = content;
            do {
                s = line + ++i;
                spaceIndex = i;
            } while (*s == ' ');
        }

        buffer[i - spaceIndex] = *s;
        s = line + ++i;
    }

    buffer[i - spaceIndex] = '\0';
}

void getFloat3(char *content, float3 &f)
{
    const int precision = 10;
    char buff[precision];

    int offset = 0;
    int i = 0;
    char* s = content;
    int symbolsRead = 0;
    int numberIndex = 0;
    while(*s != '\0')
    {
        if (symbolsRead >= precision)
        {
            s = content + ++i;
            continue;
        }
        if (*s == ' ')
        {
            buff[i - offset] = '\0';
            *(reinterpret_cast<float*>(&f) + numberIndex) = strtof(buff, nullptr);

            symbolsRead = 0;
            numberIndex++;
            offset = i + 1;
            s = content + ++i;
        }

        buff[i - offset] = *s;
        symbolsRead++;
        s = content + ++i;
    }

    buff[i - offset] = '\0';
    *(reinterpret_cast<float*>(&f) + numberIndex) = strtof(buff, nullptr);
}

