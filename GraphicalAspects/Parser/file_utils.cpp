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

inline void updateData(VertexData &data, char *buffer, int bufferIndex, int vertexIndex)
{
    buffer[bufferIndex] = '\0';
    int value = (int) strtol(buffer, nullptr, 10);
    if ((vertexIndex) == 0) {
        data.posIndex = value;
    } else if ((vertexIndex) == 1) {
        data.uvIndex = value;
    } else if ((vertexIndex) == 2) {
        data.normalIndex = value;
    }
}

bool getVertex(char *content, VertexData &vData)
{
    static int vertexIndex = 0;
    static char* ptr = content;

    if (ptr == nullptr) {
        ptr = content;
    }

    if (*ptr == '\0') {
        ptr = nullptr;
        return false;
    }

    char* s = ptr;
    char buff [10];
    int offset = 0;
    int i = 0;
    while (*s != '\0')
    {
        if (*s == ' ')
        {
            updateData(vData, buff, i - offset, vertexIndex);
            ptr = s + 1;
            vertexIndex = 0;
            return true;
        }

        if (*s == '/')
        {
            updateData(vData, buff, i - offset, vertexIndex);
            offset = i + 1;
            vertexIndex += 1;
            s = ptr + ++i;
        }

        buff[i - offset] = *s;
        s = ptr + ++i;
    }

    updateData(vData, buff, i - offset, vertexIndex);
    *ptr = '\0';
    vertexIndex = 0;
    return true;
}

std::ostream &operator<<(std::ostream &s, const VertexData &data)
{
    s << "Position: " << data.posIndex << " ";
    if (data.uvIndex > 0) {
        s << "uv: " << data.uvIndex << " ";
    }
    if (data.normalIndex > 0) {
        s << "normal: " << data.normalIndex;
    }
    return s;
}
