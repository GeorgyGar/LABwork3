// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_Stack)
{
	ASSERT_NO_THROW(Stack<double> stack(6));
}

TEST(Stack, can_create_copy)
{
	Stack<double> stack(6);
	ASSERT_NO_THROW(Stack<double> stack2(stack));
}

TEST(Stack, can_create_copy_2)
{
	Stack<double> stack(2);
	stack.StackPush(8.3);
	Stack<double> stack2(stack);
	ASSERT_EQ(8.3, stack.StackGet());
}

TEST(Stack, throws_when_create_Stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<double> stack(-1));
}

TEST(Stack, can_added_to_stack)
{
	Stack<double> stack(1);
	ASSERT_NO_THROW(stack.StackPush(12.3));
}

TEST(Stack, can_be_taken_from_the_stack)
{
	Stack<double> stack(1);
	stack.StackPush(12.3);
	ASSERT_EQ(12.3, stack.StackGet());
}

TEST(Stack, checking_for_emptiness)
{
	Stack<double> stack(1);
	stack.StackPush(12.3);
	stack.StackGet();
	ASSERT_EQ(1, stack.StackEmpty());
}

TEST(Stack, can_view_the_top_element_without_deleting_it)
{
	Stack<double> stack(1);
	stack.StackPush(15.3);
	ASSERT_EQ(15.3, stack.StackSee());
	ASSERT_EQ(0, stack.StackEmpty());
}

TEST(Stack, Cannot_be_taken_from_an_empty_stack)
{
	Stack<double> stack(1);
	ASSERT_ANY_THROW(stack.StackGet());
}

TEST(Stack, can_clear_the_stack)
{
	Stack<double> stack(2);
	stack.StackPush(15.3);
	stack.StacClean();
	ASSERT_EQ(1, stack.StackEmpty());
}

TEST(Stack, can_find_out_number_of_elements_in_stack)
{
	Stack<double> stack(5);
	stack.StackPush(15.3);
	stack.StackPush(8.3);
	stack.StackPush(0.5);
	ASSERT_EQ(3, stack.StackNum());
}

TEST(Stack, can_be_inserted_into_the_full_stack)
{
	Stack<double> stack(2);
	stack.StackPush(15.3);
	stack.StackPush(8.3);
	stack.StackPush(0.5);
	ASSERT_NO_THROW((stack.StackPush(5.6)));
	ASSERT_EQ(4, stack.StackNum());
}



