#include <list.h>
#include <gtest.h>

TEST(Iterator, can_create_iterator)
{
	ASSERT_NO_THROW(TList<int>::Iterator i);
}

TEST(Iterator, can_create_copied_iterator)
{
	TList<int>::Iterator i1;
	ASSERT_NO_THROW(TList<int>::Iterator i2(i1));
}

TEST(Iterator, can_assign_iterator)
{
	TList<int>::Iterator i1, i2;
	ASSERT_NO_THROW(i2 = i1);
}

TEST(Iterator, can_rename_iterator)
{
	TList<int> l;
	TList<int>::Iterator i;
	l.AddNodeEnd(1);
	i = l.Begin();
	EXPECT_EQ(1, *(i));
}

TEST(Iterator, can_increment_iterator)
{
	TList<int> l;
	l.AddNodeEnd(1);
	l.AddNodeEnd(2);
	TList<int>::Iterator i;
	i = l.Begin();
	++i;
	EXPECT_EQ(2, *(i));
}

TEST(TList, can_create_list)
{
  ASSERT_NO_THROW(TList<int> l);
}

TEST(TList, can_push_back)
{
	TList<int> l;
	ASSERT_NO_THROW(l.AddNodeEnd(1));
}

TEST(TList, can_compare_two_lists_by_value)
{
	TList<int> l1, l2;
	l1.AddNodeEnd(1);
	l2.AddNodeEnd(1);
	EXPECT_TRUE(l1 == l2);
}

TEST(TList, two_lists_with_different_sizes_are_not_equal)
{
	TList<int> l1, l2;
	l1.AddNodeEnd(1); l1.AddNodeEnd(1);
	l2.AddNodeEnd(1);
	EXPECT_FALSE(l1 == l2);
}

TEST(TList, two_lists_are_not_equal)
{
	TList<int> l1, l2;
	l1.AddNodeEnd(1);
	l2.AddNodeEnd(2);
	EXPECT_TRUE(l1 != l2);
}

TEST(TList, can_create_copied_list)
{
	TList<int> l1,l2;
	l1.AddNodeEnd(5);
	ASSERT_NO_THROW(TList<int> l2 = l1);
}

TEST(TList, can_assign_list)
{
	TList<int> l1, l2;
	l1.AddNodeEnd(5);
	ASSERT_NO_THROW(l2 = l1);
}

TEST(TList, can_check_for_empty)
{
	TList<int> l;
	EXPECT_TRUE(l.IsEmpty());
}

TEST(TList, can_return_size_of_list)
{
	TList<int> l;
	for (int i = 0; i < 3; i++)
		l.AddNodeEnd(i);
	EXPECT_EQ(3, l.GetSize());
}

TEST(TList, method_del_delete_all_values_of_list)
{
	TList<int> l;
	for (int i = 0; i < 5; i++)
		l.AddNodeEnd(i);
	l.DelAllNode();
	EXPECT_TRUE(l.IsEmpty());
}

TEST(TList, can_erace_elem_by_iterator)
{
	TList<int> l;
	TList<int>::Iterator i;
	l.AddNodeEnd(10);
	i = l.Begin();
	ASSERT_NO_THROW(l.Erase(i));
}

TEST(TList, can_insert_elem_by_iterator)
{
	TList<int> l;
	TList<int>::Iterator i;
	i = l.Begin();
	l.Insert(i, 3);
	EXPECT_EQ(1, l.GetSize());
}









