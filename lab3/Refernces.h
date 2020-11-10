#include"List.h"
#include "Iterator.h"
#include <ostream>
#include <string.h>


class References {
public:
	/*
	methods
	*/
	References() { word = NULL; pages = NULL; _size =0; };
/*	~References() {
		word = NULL;
		pages = NULL;
	};*/
	References(const References &references);
	References(const char* str);
	References( const char* str, const char* page, int size);
	void parseFrom(char* str);
	int* getpages(char* page);
	char* getword();
	void change(const char * wordd);
	int getsize();
	bool operator ==(const References& argz);
	
	friend ostream& operator<<(ostream& stream, References& obj);
private:
	char* word;
	int* pages;//pages numbers
	int _size;//number of pages
	int size_array;
};
#pragma once
