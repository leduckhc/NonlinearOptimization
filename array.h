// util.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

bool readFile();


class Matrix {
private:
	int d0, d1;
	float** data;
public:
	Matrix();

	float** getData() const;
};


// TODO: Reference additional headers your program requires here.
