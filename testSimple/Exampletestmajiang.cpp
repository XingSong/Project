//正常的麻将胡牌方式为满足N * ABC + M *DDD + ＥＥ 的形式，及存在一个对子(EE)，剩余牌均能组成顺子（ABC）或者刻子（DDD）。
//
//很容易发现必须满足size % 3 == 2的形式才可以去计算胡牌。
//
//数据结构的选取：
//
//麻将有万、饼、条各九种，另外还有东西南北中，春夏秋冬。
//种类不是很多，一个字节表示就可以了，前四位代表类型，后四位代表值，东西南北中，春夏秋冬可以集中到一种类型中去。
//
//普通麻将的计算方式：
//
//1.首先找出所有包含一对的情形，移除对子（注意去重），记下剩余牌的所有集合为Tn;
//2.针对每个Tn中的数组尝试移除一个顺子，成功转到2，失败到3。
//3.针对每个Tn中的数组尝试移除一个刻子（DDD），成功转到2。
//4.若当前的数组的数量变为0，则表示，当前的方案可以胡牌。
//2, 3, 4可以作为一个check_3n(检测是否满足N * ABC + M *DDD)的函数，递归调用即可。

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


bool check_hu(unsigned char *A, unsigned int sz) {
	unsigned char *set = (unsigned char *)malloc(sizeof(char)* sz);
	sort_card(A, sz);
	unsigned int i = 0;
	for (i = 0; i < sz; i++) {
		if (A[i] == A[i + 1]) {
			int k = 0;
			for (size_t j = 0; j < sz; j++) {
				if (j != i && j != i + 1) {
					set[k] = A[j];
					k = k + 1;
				}
			}
			if (check_3n(set, sz - 2) || sz - 2 == 0) {
				return true;
			}
		}

	}
	free(set);
	return false;
}

bool check_3n(unsigned char *set, unsigned int sz) {
	if (sz == 0) {
		return true;
	}
	int set_t[20] = { 0 };
	for (size_t i = 0; i < sz; i++)
	{
		set_t[i] = set[i];
	}

	if (remove_straight(set, sz)) {
		if (check_3n(set, sz - 3))
		{
			return true;
		}
	}

	for (size_t i = 0; i < sz; i++)
	{
		set[i] = set_t[i];
	}

	if (remove_three_same(set, sz)) {
		if (check_3n(set, sz - 3))
		{
			return true;
		}
	}
	return false;
}

bool remove_straight(unsigned char *set, unsigned int sz) {
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

bool remove_three_same(unsigned char *set, unsigned int sz) {
	if (set[0] == set[2] && set[1] == set[0]) {
		unsigned int i = 0;
		for (i = 0; i < sz - 3; i++) {
			set[i] = set[i + 3];
		}
		return true;
	}
	return false;
}


//----------------------------------------------------------------------------
void sort_card(unsigned char *A, unsigned int sz) {
	int i = 0, j = 0;
	int len = sz;
	for (i = len - 1; i >= 0; i--) {
		unsigned char max = A[i];
		int postion = i;
		for (j = 0; j <= i; j++) {
			if (big_than(A[j], max)) {
				max = A[j];
				postion = j;
			}
		}
		unsigned char temp = A[i];
		A[i] = max;
		A[postion] = temp;
	}
}

bool big_than(unsigned char a, unsigned char b) {
	if ((a & (unsigned int)0xf0) > (b & (unsigned int)0xf0)) {
		return true;
	}
	else if ((a & (unsigned int)0xf0) == (b & (unsigned int)0xf0)) {
		if ((a & (unsigned int)0xf) > (b & (unsigned int)0xf)) {
			return true;
		}
	}
	return false;
}


void dump(unsigned char *set, unsigned int sz) {
	for (size_t i = 0; i < sz; i++)
	{
		printf("%02x ", *(set + i));
	}
	printf("\n");
}

void main1() {
//	unsigned char A[17] = { 0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, 0x15 };
	unsigned char A[] = { 0x01, 0x03, 0x02,
		0x11, 0x12, 0x13,
		0x21, 0x22, 0x23,
		0x25, 0x35, 0x25,
		0x35, 0x25 };
	bool hu1 = check_hu(A, 14);
	//bool hu2 = check_hu(A, 2);
//	printf("%d  %d\n", hu1, hu2);
	printf("%d\n", hu1);
	system("pause");
}