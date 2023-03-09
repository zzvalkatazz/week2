#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include<iostream>
#include<cstring>

void myString::copy(const myString& other)
{
	size = other.size;
	string= new char[size];
	for (int i = 0; i < size; i++)
	{
		string[i] = other.string[i];
	}
}
myString::myString(const char* str) : string(nullptr), size(0)
{
	string = nullptr;
	size = 0;
	string = new char[strlen(str) + 1];
  strcpy(string, str);
}
myString::~myString()
{
	delete[]string;
}
MyString::MyString(const MyString&)
{
	copy(other);
}
myString& myString::operator=(const myString& toher)
{
	if (this != &other)
	{
		erase();
		copy(other);
	}
	return *this;
}
int myString::length()
{
	return strlen(string);
}
char& myString::at(unsigned idx)
{
	int length = strlen(string);
	if (idx < length && idx>=0)
	{
		return string[idx];
	}
	else
	{
		std::exception("no idx");
	}
}
bool myString::empty()
{
	int length = strlen(string);
	if (length <= 0)
	{
		return true;
	}
	return false;
}
myString myString:: substr(unsigned pos = 0, unsigned n = 0)
{

}
