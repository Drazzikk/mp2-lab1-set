#include "tset.h"

#include <gtest.h>

class TestTSet :public::testing::Test
{
protected:
	TSet* set;
	TSet* set_1;
	TSet* set_2;
	TSet* set_3;
	TSet* set_4;
	TSet* set_5;
	TSet* set_6;
	TSet* set_7;
	TSet* set_8;
	TSet* set_9;
	TSet* set_10;
	TSet* set_11;
public:
	
	void SetUp()
	{
		set_1 = new TSet(3);
		set_1->InsElem(0);
		set_1->InsElem(1);

		set_2 = new TSet(3);
		set_2->InsElem(0);
		set_2->InsElem(1);

		set_3 = new TSet(4);
		set_3->InsElem(0);
		set_3->InsElem(1);
		set_3->InsElem(2);

		set_4 = new TSet(3);
		set_4->InsElem(0);
		set_4->InsElem(2);

		set_5 = new TSet(5);
		set_5->InsElem(1);
		set_5->InsElem(3);

		set_6 = new TSet(3);
		set_6->InsElem(0);
		set_6->InsElem(1);
		set_6->InsElem(2);

		set_7 = new TSet(3);
		set_7->InsElem(0);
		set_7->InsElem(1);
		set_7->InsElem(2);

		set_8 = new TSet(3);
		set_8->InsElem(2);

		set_9 = new TSet(3);
		set_9->InsElem(0);

		set_10 = new TSet(4);
		set_10->InsElem(0);
		set_10->InsElem(1);

		set_11 = new TSet(4);
	}

	void TearDown()
	{
		delete set_1;
		delete set_2;
		delete set_3;
		delete set_4;
		delete set_5;
		delete set_6;
		delete set_7;
		delete set_8;
		delete set_9;
		delete set_10;
		delete set_11;
	}
};

TEST_F(TestTSet, can_get_max_power_set)
{
	EXPECT_EQ(this->set_1->GetMaxPower(), 3);
}

TEST_F(TestTSet, can_insert_non_existing_element)
{
	EXPECT_EQ(this->set_1->IsMember(1), true);
}

TEST_F(TestTSet, can_insert_existing_element)
{
	this->set_11->InsElem(1);
	this->set_11->InsElem(1);
	EXPECT_EQ(this->set_11->IsMember(1), true);
}

TEST_F(TestTSet, can_delete_non_existing_element)
{
	this->set_1->DelElem(2);
	EXPECT_EQ(this->set_1->IsMember(2), false);
}

TEST_F(TestTSet, can_delete_existing_element)
{
	this->set_1->DelElem(1);
	EXPECT_EQ(this->set_1->IsMember(1), false);
}

TEST_F(TestTSet, compare_two_sets_of_non_equal_sizes)
{
	EXPECT_NE(*this->set_1, *this->set_3);
}

TEST_F(TestTSet, compare_two_equal_sets)
{
	EXPECT_EQ(*this->set_1, *this->set_2);
}

TEST_F(TestTSet, compare_two_non_equal_sets)
{
	EXPECT_EQ(true, *this->set_1 != *this->set_4);
}

TEST_F(TestTSet, can_assign_set_of_equal_size)
{
	*this->set_1 = *this->set_4;
	EXPECT_EQ(*this->set_1, *this->set_4);
}

TEST_F(TestTSet, can_assign_set_of_greater_size)
{
	*this->set_1 = *this->set_5;
	EXPECT_EQ(*this->set_1, *this->set_5);
}

TEST_F(TestTSet, can_assign_set_of_less_size)
{
	*this->set_3 = *this->set_1;
	EXPECT_EQ(*this->set_3, *this->set_1);
}

TEST_F(TestTSet, can_insert_non_existing_element_using_plus_operator)
{
	*this->set_5 = *this->set_1 + 2;
	EXPECT_EQ(true, this->set_5->IsMember(2));
}

TEST_F(TestTSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
	ASSERT_ANY_THROW(*this->set_5 = *this->set_1 + 10;);
}

TEST_F(TestTSet, can_insert_existing_element_using_plus_operator)
{
	*this->set_5 = *this->set_5 + 3;
	EXPECT_EQ(true, this->set_5->IsMember(3));
}

TEST_F(TestTSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
	*this->set_6 = *this->set_1 + *this->set_4;
	EXPECT_EQ(3, this->set_6->GetMaxPower());
}

TEST_F(TestTSet, can_combine_two_sets_of_equal_size)
{
	*this->set_4 = *this->set_4 + *this->set_1;
	EXPECT_EQ(*this->set_4, *this->set_7);
}

TEST_F(TestTSet, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
	*this->set_6 = *this->set_1 + *this->set_5;
	EXPECT_EQ(5, this->set_6->GetMaxPower());
}

TEST_F(TestTSet, can_combine_two_sets_of_non_equal_size)
{
	*this->set_6 = *this->set_1 + *this->set_3;
	EXPECT_EQ(*this->set_6, *this->set_3);
}

TEST_F(TestTSet, can_intersect_two_sets_of_equal_size)
{
	*this->set_2 = *this->set_1 * *this->set_4;
	EXPECT_EQ(*this->set_2, *this->set_9);
}

TEST_F(TestTSet, can_intersect_two_sets_of_non_equal_size)
{
	*this->set_4 = *this->set_1 * *this->set_3;
	EXPECT_EQ(*this->set_4, *this->set_10);
}

TEST_F(TestTSet, check_negation_operator)
{
	*this->set_2 = ~(*this->set_1);
	EXPECT_EQ(*this->set_8, *this->set_2);
}

TEST_F(TestTSet, throws_when_out_of_range_InsElem)
{
	ASSERT_ANY_THROW(this->set_1->InsElem(20));
}

TEST_F(TestTSet, throws_when_out_of_range_DelElem)
{
	ASSERT_ANY_THROW(this->set_1->DelElem(10));
}