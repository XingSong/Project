#pragma once
#ifndef _BOOK_H_
#define _BOOK_H_
class Book
{
public:
	Book();
	~Book();
	void show();
private:
	Book(const Book&);
	Book& operator=(const Book&);
	class BookImpl;
	BookImpl*	m_pImpl;
};

#endif