//#include <wchar.h>
//#include <wtypes.h>
//#include <iostream>
//using namespace std;
//
//
//#define MAX_SOURCE_LEN				1024								//最大长度
//
//void main()
//{
//	WCHAR szKeyBuffer[] = L"54DE";
//	WCHAR szTempBuffer[] = L"54F0";
//	WCHAR * pEnd = NULL;
//	WCHAR szSrcData[MAX_SOURCE_LEN] = L"";
//	WCHAR wKey = (WCHAR)wcstol(szKeyBuffer, &pEnd, 16);
//	WCHAR wEncrypt = (WCHAR)wcstol(szTempBuffer, &pEnd, 16);
////	wprintf(L"wKey=%c\nwEncrypt=%c\n", wKey, wEncrypt);// << "wKey=" << wKey << "\nwEncrypt=" << wEncrypt << endl;
//	cout << "wKey=" << wKey << "\nwEncrypt=" << wEncrypt << endl;
//	for (int i = 0; i < 1; i++)
//	{
//		szSrcData[i] = (WCHAR)((WCHAR)wKey ^ (WCHAR)wEncrypt);
//		wcout << szSrcData[i] << endl;
//	}
//	
//	system("pause");
//}
#include "stdio.h"
#include "stdbool.h"
#include <stdlib.h>
#include <malloc.h>

bool check_hu(unsigned char *A, unsigned int sz);
bool check_3n(unsigned char *set, unsigned int sz);
bool remove_straight(unsigned char *set, unsigned int sz);
bool remove_three_same(unsigned char *set, unsigned int sz);
void sort_card(unsigned char *A, unsigned int sz);
bool big_than(unsigned char a, unsigned char b);
void dump(unsigned char *set, unsigned int sz);


bool check_hu(unsigned char *A, unsigned int sz){
	unsigned char *set = (unsigned char *)malloc(sizeof(char)* sz);
	sort_card(A, sz);
	unsigned int i = 0;
	for (i = 0; i < sz; i++){
		if (A[i] == A[i + 1]){
			int k = 0;
			for (size_t j = 0; j < sz; j++){
				if (j != i && j != i + 1){
					set[k] = A[j];
					k = k + 1;
				}
			}
			if (check_3n(set, sz - 2) || sz - 2 == 0){
				return true;
			}
		}

	}
	free(set);
	return false;
}

bool check_3n(unsigned char *set, unsigned int sz){
	if (sz == 0){
		return true;
	}
	int set_t[20] ={ 0 };
	for (size_t i = 0; i < sz; i++)
	{
		set_t[i] = set[i];
	}

	if (remove_straight(set, sz)){
		if (check_3n(set, sz - 3))
		{
			return true;
		}
	}

	for (size_t i = 0; i < sz; i++)
	{
		set[i] = set_t[i];
	}

	if (remove_three_same(set, sz)){
		if (check_3n(set, sz - 3))
		{
			return true;
		}
	}
	return false;
}

bool remove_straight(unsigned char *set, unsigned int sz){
	int second = 0, third = 0;
	for (size_t i = 0; i < sz; i++)
	{
		if (set[i] == set[0] + 1)
		{
			second = i;
		}
		if (set[i] == set[0] + 2)
		{
			third = i;
		}
		if (set[i] > set[0] + 2)
		{
			break;
		}
		if (second != 0 && third != 0)
		{
			break;
		}
	}
	if (second != 0 && third != 0)
	{
		int j = 0;
		for (size_t i = 1; i < sz; i++)
		{
			if (i != second && i != third)
			{
				set[j] = set[i];
				j++;
			}

		}
		return true;
	}
	return false;
}

bool remove_three_same(unsigned char *set, unsigned int sz){
	if (set[0] == set[2] && set[1] == set[0]){
		unsigned int i = 0;
		for (i = 0; i < sz - 3; i++){
			set[i] = set[i + 3];
		}
		return true;
	}
	return false;
}


//----------------------------------------------------------------------------
void sort_card(unsigned char *A, unsigned int sz){
	int i = 0, j = 0;
	int len = sz;
	for (i = len - 1; i >= 0; i--){
		unsigned char max = A[i];
		int postion = i;
		for (j = 0; j <= i; j++){
			if (big_than(A[j], max)){
				max = A[j];
				postion = j;
			}
		}
		unsigned char temp = A[i];
		A[i] = max;
		A[postion] = temp;
	}
}

bool big_than(unsigned char a, unsigned char b){
	if ((a & (unsigned int)0xf0) > (b & (unsigned int)0xf0)){
		return true;
	}
	else if ((a & (unsigned int)0xf0) == (b & (unsigned int)0xf0)){
		if ((a & (unsigned int)0xf) > (b & (unsigned int)0xf)){
			return true;
		}
	}
	return false;
}


void dump(unsigned char *set, unsigned int sz){
	for (size_t i = 0; i < sz; i++)
	{
		printf("%02x ", *(set + i));
	}
	printf("\n");
}

void main() 
{
//	unsigned char A[17] ={ 0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, 0x15 };
	unsigned char A[14] = { 0x21, 0x21, 0x21, 0x21, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14};
	bool hu1 = check_hu(A, 14);
	bool hu2 = check_hu(A, 2);
	printf("%d  %d\n", hu1, hu2);
	system("pause");
}