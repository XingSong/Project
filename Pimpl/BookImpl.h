#pragma once
#include "Book.h"
#include <string>
class Book::BookImpl
{
public:
	void show();
private:
	std::string m_Contents;
	std::string m_Title;
};