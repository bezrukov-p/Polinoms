#include <polinom.h>
#include <gtest.h>

TEST(TPolinom, can_create_polinom)
{
	ASSERT_NO_THROW(TPolinom p("x+y"));
}

TEST(TPolinom, can_convert_coeff_to_string)
{
	EXPECT_EQ(ConvertCoeff("23"), 23);
}

TEST(Monom, can_add_monoms)
{
	Monom m;
	ASSERT_NO_THROW(m + m);
}

TEST(TPolinom, can_assign_polinoms)
{
	TPolinom p1("x+y");
	TPolinom p2("x+y+z");
	ASSERT_NO_THROW(p2 = p1);
}

//TEST(TPolinom, can_compare_polinoms)
//{
//	TPolinom p1("x+y");
//	TPolinom p2("x+y");
//	EXPECT_EQ(p2,p1);
//}