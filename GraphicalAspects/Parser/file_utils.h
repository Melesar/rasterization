#pragma once

#include <cstdio>
#include <Data/math_structs.h>

const int LINE_LENGTH = 50;

bool readLine (FILE* f, char* buff);
void getToken(char* line, char* token, char* content);
void getFloat3(char* content, float3& f);
