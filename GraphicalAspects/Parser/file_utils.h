#pragma once

#include <cstdio>
#include <Data/math_structs.h>

const int LINE_LENGTH = 75;

bool readLine (FILE* f, char* buff);
void getToken(char* line, char* token, char* content);
void getFloat3(char* content, float3& f);

struct VertexData
{
    int posIndex;
    int uvIndex;
    int normalIndex;

    VertexData() : posIndex(-1), uvIndex(-1), normalIndex(-1) {}
    friend std::ostream& operator << (std::ostream& s, const VertexData& data);
};


bool getVertex (char* content, VertexData& vData);

