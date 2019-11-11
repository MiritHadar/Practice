/*
********************************************************************************

Developer : Mirit Hadar
Reviewer : Ben Eliezer
Last Update : 8/8/19
Status : Approved

********************************************************************************
*/


#include <stdio.h>
#include "str.hpp"

void RegularTest();
void ConstTest();
void SelfAssignTest();
void ShiftingTest();

const int CHAR_ASCII = 97;

int main(void)
{
	RegularTest();
	ConstTest();
	SelfAssignTest();
	ShiftingTest();

	return 0;
}


void RegularTest()
{
	const char *str_mirit = "mirit hadar";
	const char *str_hello = "hello ";
	const char *str_world = "world!";
	const char *str_h_w = "hello world!";
	const char *str_abc = "abc";
	const char *str_abcd = "abcd";

	Str s1, s4, s7;
	Str s2(str_mirit);
	Str s3(s2);
	Str s5(str_hello);
	Str s6(str_world);
	
	Str s9(str_abc);
	Str s10(str_abcd);

	for(int i = 0; i < int(strlen(str_abcd)); ++i)
	{
		if (s10[i] != (i + CHAR_ASCII))
		{
			printf("failed [] %d\n", __LINE__);
		}
	}

	if (s9 > s10)
	{
		printf("failed > %d\n", __LINE__);
	}

	if (s10 < s9)
	{
		printf("failed > %d\n", __LINE__);
	}

	if (s5 > s6)
	{
		printf("failed > %d\n", __LINE__);
	}

	if (s6 < s5)
	{
		printf("failed > %d\n", __LINE__);
	}
	/* assign str = char* */
	s7 = str_abc;

	if (str_abc != s7)
	{
		printf("failed str = char* %d\n", __LINE__);
	}

	size_t len5 = s5.GetLength();
	size_t len6 = s6.GetLength();

	s5 += s6;

	if (s5.GetLength() != (len5 + len6))
	{
		printf("%s - %lu\n", s5.ToCString(), s5.GetLength());
		printf("failed += or GetLength %d\n", __LINE__);
	}

	if (!(str_h_w == s5))
	{
		printf("failed += / == %d\n", __LINE__);
	}

	if (str_h_w != s5)
	{
		printf("failed += / == %d\n", __LINE__);
	}

	if (s5 != str_h_w)
	{
		printf("failed += / == %d\n", __LINE__);
	}

	s6 = s5;

	if (s5 != s6)
	{
		printf("failed != for classes %d\n", __LINE__);
	}

	if (str_mirit == s5)
	{
		printf("failed += / == %d\n", __LINE__);
	}
	 
	if (0 != strcmp(str_mirit, s2.ToCString()))
	{
		printf("failed ToCString / Ctor(char*) %d\n", __LINE__);
	}
	
	if (0 != strcmp(str_mirit, s3.ToCString()))
	{
		printf("failed ToCString / Ctor(Str) %d\n", __LINE__);
	}

	if (s2 != s3)
	{
		printf("failed != or Ctors %d\n", __LINE__);
	}

	if (s1 == s3)
	{
		printf("failed == or Ctors %d\n", __LINE__);
	}

	s2 = s4;

	if (s2 != s4)
	{
		printf("failed != or Ctors %d\n", __LINE__);
	}

	if (s1 == str_mirit)
	{
		printf("failed class==char* %d\n", __LINE__);
	}

	if (!(s3 == str_mirit))
	{
		printf("failed class==char* %d\n", __LINE__);
	}

	if (str_mirit == s1)
	{
		printf("failed class==char* %d\n", __LINE__);
	}

	if (!(str_mirit == s3))
	{
		printf("failed class==char* %d\n", __LINE__);
	}
}

void ConstTest()
{
	Str s1 = "string literal";
	if (s1 != "string literal")
	{
		printf("failed assign of string literal or str != const char[] %d\n", __LINE__);
	}

	s1[6] = 's';
	if (s1 != "stringsliteral")
	{
		printf("failed writing in to [] %d\n", __LINE__);
	}
	if (s1 == "something else")
	{
		printf("failed writing in to [] %d\n", __LINE__);
	}

	const Str con_str = "I'm a const";

	if (con_str[0] != 'I')
	{
		printf("failed reading with [] from const %d\n", __LINE__);
	}

	if (con_str > "I'm a const")
	{
		printf("failed reading with > from const %d\n", __LINE__);
	}

	//con_str.PrintStr();
	//con_str[0] = 'D'; sholdn't work
	//con_str.PrintStr();
}

void SelfAssignTest()
{
	Str s1 = "assign to me";
	s1 = s1;

	if (s1 != "assign to me")
	{
		printf("failed Self assignment %d\n", __LINE__);
	}

	s1 += s1;
	if (s1 != "assign to meassign to me")
	{
		printf("failed += to my self %d\n", __LINE__);
	}
	s1 += "add something";

	if (s1 > "me")
	{
		s1.PrintStr();
	}
}

void ShiftingTest()
{
	Str s1 = "test shifting out";
	std::cout << s1;
}


