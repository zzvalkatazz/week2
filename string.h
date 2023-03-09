#ifndef STRING
#define STRING
class myString
{
private:
	int size;
	char* string;
	void copy(const myString&);
	void erase();
public:
	myString(const char* str="\0");
	~myString();
	myString(const myString&);
	myString& operator=(const myString&);
    int length();
	char& at(unsigned indx);
	int find(char c, unsigned startPos = 0);
	bool empty();
	myString substr(unsigned pos = 0, unsigned n = 0);
	void append(const myString& str);
	void print() const;
};

#endif
