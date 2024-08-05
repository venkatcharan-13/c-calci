#pragma once
#ifdef CALCILIBRARY_EXPORTS
#define CALCILIBRARY_API __declspec(dllexport)
#else
#define CALCILIBRARY_API __declspec(dllimport)
#endif

// Hello I'm venkat charan , here is my c++/Calculator dll file and here is quick intro of the working of file.

// defining all the necessary libraries only here in this header file and not in any file that will reduce the complile runtime;
#include <iostream>
#include <libpq-fe.h>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <cmath>
#include<string>
#include<algorithm>
#include <limits>
#include <set>

//define a class calci that had all the functions of calculator;
class CALCILIBRARY_API calci {
public:
	void showCalci();
	void commonFunc(int a, int b,char sign);
	void trinoFunc(int degree, std::string function);
	void logFunc(int n,int base);
	void powFunc(int n, int power,char bse);
	void meanFunc(std::vector<int>array, std::string common);
	void stdDeviation(std::vector<int>data);
};

//some functions that will recognise the dll file and can use in any code
extern "C" CALCILIBRARY_API void CheckResult(PGresult* res, PGconn* conn);
extern "C" CALCILIBRARY_API void InsertData(std::string col1, std::string col2);
extern "C" CALCILIBRARY_API void createTable(PGconn* conn);
extern "C" CALCILIBRARY_API int CountRows(PGconn* conn, std::string tableName);
extern "C" CALCILIBRARY_API void DeleteAllRows(PGconn* conn, std::string tableName);

/*
Here are some instructions to connect postgresql database to our code:
	1.) First we have to include the path of the postgresql libraries that we want to use the here.
		-- go to properties in solution explorer and add following paths to it 
			-- C/C++ >> General >> Additional Include Directories
			(c:../postgresql/16/bin and c:../postgresql/16/include)
	2.) Second we have to include lib file 
		-- go to properties in solution explorer and add following paths to it 
			-- Linker >> input >> (enter libpq.lib)
	3.) Third we have to include path in linker
		-- go to properties in solution explorer and add following paths to it 
			-- Linker >> General >> Additional Libraries Directories
			(c:../postgresql/16/bin/$(IntDir) and c:../postgresql/16/include/$(IntDir))

These 3 steps to connect our postgresql to our code and we can now use libraries releated to it.
*/

