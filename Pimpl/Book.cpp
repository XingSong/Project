#include "Book.h"
#include "BookImpl.h"

#define CC_SAFE_DELETE(p)	do{if(p) {delete (p);p = NULL;}}while(0)

Book::Book()
{
	m_pImpl = new BookImpl();
}


Book::~Book()
{
	CC_SAFE_DELETE(m_pImpl);
}

void Book::show()
{
	m_pImpl->show();
}
