#define _CRT_SECURE_NO_WARNINGS

#include "Refernces.h"
#include <string>

References::References(const References& references) {
	
	if (references.word != NULL) {
		size_t length = strlen(references.word);
		char* word = new char[length + 1];
		this->word = new char[length + 1];
		strcpy(word, references.word);
		strcpy(this->word, references.word);
		size_t size_array = references.size_array;
		pages = new int[size_array];
		this->pages  = new int[size_array];
		for (size_t i = 0; i < size_array; i++) {
			pages[i] = references.pages[i];
			this->pages[i]= references.pages[i];
		}
		_size = references._size;
		this->_size = references._size;
		this->size_array = references.size_array;
	}
}
References::References( const char* str)
{
	size_t length = strlen(str);
	int count = 0, j = 0;
	char* buffer = new char[99];
	char* _word = NULL;
	int* pgs = NULL;
	int buf = 0;
	for (size_t i = 0; i < length; i++, j++) {
		if (str[i] == ';') {
			count++;
			buffer[j] = '\0';
			if (count == 1) {
				_word = new char[j + 1];
				strcpy(_word, buffer);
				j = -1;
			}
			if (count == 2) {
				pgs = getpages(buffer);
				j = -1;
			}
			if (count == 3) {
				buf = atoi(buffer);
				break;
			}
		}
		else {
			buffer[j] = str[i];
		}
	}
	_size = buf;
	pages = pgs;
	word = _word;
}

References::References (const char* str, const char* page, int size)
{
	word = new char[strlen(str)+1];
	strcpy(word, str);
	char p[255];
	string pap ; 
	int count = 0;

	size_t  length = strlen(page);
	for (size_t i = 0; i < length; i++) {
		if (page[i] == ',') {
			count++;
		}
	}
	if (count > 0) {
		pages = new int[count+1];
		int k = 0, d = 1, chack = 0;;
		strcpy(p, "");
		strcat(p, page);
		strcat(p, "\n");
		for (size_t i = 0; i < length+1; i++) {
			if (p[i] != ',' and p[i] != '\n') {
				if (d == 1) {
					pap = p[i];
					d++;
				}
				else {
					pap += p[i];
				}

			}
			else {
				int ok;
				ok = atoi(pap.c_str());
				pages[k] = ok;
				k++;
				d = 1;
				pap.clear();
			}
		}
	}
	
	_size = size;
}
void References::parseFrom(char* str)
{
	size_t length = strlen(str);
	int count = 0 , j = 0 ;
	char* buffer = new char[99];
	char* _word = NULL;
	int* pgs = NULL;
	int buf = 0;
	for (size_t i = 0; i < length; i++,j++) {
		if (str[i] == ';') {
			count++;
			buffer[j] = '\0';
			if (count == 1) {
				_word = new char[j+1];
				strcpy(_word, buffer);
				j = -1;
			}
			if (count == 2) {
				pgs = getpages(buffer);
				j = -1;
			}
			if (count == 3) {
				buf = atoi(buffer);
				break;
			}
		}
		else {
			buffer[j] = str[i];
		}
	}
	_size = buf;
	pages = pgs;
	word = _word;
}

int * References::getpages(char* page)
{
	char p[255];
	string pap;
	int count = 0;
	int *bufpages = NULL;

	size_t  length = strlen(page);
	for (size_t i = 0; i < length; i++) {
		if (page[i] == ',') {
			count++;
		}
	}
	if (count > 0) {
		bufpages = new int[count + 1];
		size_array = count+1;
		int k = 0, d = 1, chack = 0;;
		strcpy(p, "");
		strcat(p, page);
		strcat(p, "\0");
		for (size_t i = 0; i < length + 1; i++) {
			if (p[i] != ',' and p[i] != '\0') {
				if (d == 1) {
					pap = p[i];
					d++;
				}
				else {
					pap += p[i];
				}

			}
			else {
				int ok;
				ok = atoi(pap.c_str());
				bufpages[k] = ok;
				k++;
				d = 1;
				pap.clear();
			}
		}
	}
	return bufpages;
}

char* References::getword()
{
	char* _word_ = new char[strlen(word) + 1];
	strcpy(_word_, word);

	return _word_;
}

void References::change(const char* wordd)
{
	char* new_word = new char[strlen(wordd)], * dell = NULL;
	strcpy(new_word, wordd);
	dell = word;
	word = new_word;
	delete[] dell;

}

int References::getsize()
{
	return _size;
}

bool References::operator==(const References& argz)
{
	if (strcmp(word, argz.word) == 0)
		return true;
	return false;
}

ostream& operator<<(ostream& stream, References& obj) {
	string pagess;
	for (int i = 0; i < obj.size_array; i++) {
		pagess += to_string(obj.pages[i]);
		if (i < obj.size_array-1) 
			pagess += ',';
	}
	stream << "Word: " << obj.word << " Pages: " << pagess << " size: " << obj._size<< endl; 
	return stream;
}
