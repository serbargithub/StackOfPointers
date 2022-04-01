#include "gtest/gtest.h"
#include "stack_of_pointers.h"
#include "stack_of_pointers.cpp"

#define ITEMS_MAX  3

void StackErorrHandler(uint32_t stackID, StackResults result) {
	std::cout<< "\r\n###### Into stack with ID: " << stackID << " catched an error: " << (int)result << " ####\r\n\r\n";
}

TEST(StackOfPointers, StackReset) {
	StackOfPointers<char*, ITEMS_MAX> stack(1, StackErorrHandler);
	EXPECT_EQ(StackResults::OK, stack.Reset());
}

TEST(StackOfPointers, IsEmpty) {
	StackOfPointers<uint32_t*, ITEMS_MAX> stack(2, StackErorrHandler);
	EXPECT_EQ(true, stack.IsEmpty());
	uint32_t item1 = 1;
	stack.Push(&item1);
	EXPECT_EQ(false, stack.IsEmpty());
	EXPECT_EQ(StackResults::OK, stack.Reset());
	EXPECT_EQ(true, stack.IsEmpty());
}

TEST(StackOfVoid, OnePushPop) {
	StackOfPointers<uint32_t*, ITEMS_MAX> stack(3, StackErorrHandler);
	EXPECT_EQ(true, stack.IsEmpty());
	uint32_t item1 = 1;
	uint32_t itemOdd = 99;
	stack.Push(&item1);
	uint32_t* checkedItem = &itemOdd;
	EXPECT_EQ(*checkedItem, itemOdd);
	stack.Pop(&checkedItem);
	EXPECT_EQ(*checkedItem, item1);
}

TEST(StackOfVoid, TwoPushPop) {
	StackOfPointers<uint32_t*, ITEMS_MAX> stack(4, StackErorrHandler);
	EXPECT_EQ(true, stack.IsEmpty());
	uint32_t item1 = 1;
	uint32_t item2 = 2;
	uint32_t itemOdd = 99;
	stack.Push(&item1);
	stack.Push(&item2);

	uint32_t* checkedItem = &itemOdd;
	EXPECT_EQ(*checkedItem, itemOdd);
	stack.Pop(&checkedItem);
	EXPECT_EQ(*checkedItem, item2);
	stack.Pop(&checkedItem);
	EXPECT_EQ(*checkedItem, item1);
}

TEST(StackOfVoid, ThreePushPop) {
	StackOfPointers<uint32_t*, ITEMS_MAX> stack(4, StackErorrHandler);
	EXPECT_EQ(true, stack.IsEmpty());
	uint32_t item1 = 1;
	uint32_t item2 = 2;
	uint32_t item3 = 3;
	uint32_t itemOdd = 99;
	stack.Push(&item1);
	stack.Push(&item2);
	stack.Push(&item3);

	EXPECT_EQ(stack.GetActualSize(), 3);

	uint32_t* checkedItem = &itemOdd;
	stack.Pop(&checkedItem);
	EXPECT_EQ(*checkedItem, item3);
	EXPECT_EQ(stack.GetActualSize(), 2);
	stack.Pop(&checkedItem);
	EXPECT_EQ(*checkedItem, item2);
	EXPECT_EQ(stack.GetActualSize(), 1);
	stack.Pop(&checkedItem);
	EXPECT_EQ(*checkedItem, item1);
	EXPECT_EQ(stack.GetActualSize(), 0);
	checkedItem = &itemOdd;
	StackResults result = stack.Pop(&checkedItem);
	EXPECT_EQ(StackResults::IS_EMPTY, result);
	EXPECT_EQ(stack.GetActualSize(), 0);
	EXPECT_EQ(*checkedItem, itemOdd);
}

TEST(StackOfVoid, FourIntPushPop) {
	StackOfPointers<uint32_t*, ITEMS_MAX> stack(6, StackErorrHandler);
	EXPECT_EQ(true, stack.IsEmpty());
	uint32_t item1 = 1;
	uint32_t item2 = 2;
	uint32_t item3 = 3;
	uint32_t itemOdd = 99;
	stack.Push(&item1);
	stack.Push(&item2);
	StackResults result = stack.Push(&item3);
	EXPECT_EQ(StackResults::OK, result);
	result= stack.Push(&itemOdd);
	EXPECT_EQ(StackResults::OVERFULL_ERROR, result);
	EXPECT_EQ(stack.GetActualSize(), 3);

	uint32_t* checkedItem = &itemOdd;
	stack.Pop(&checkedItem);
	stack.Pop(&checkedItem);
	stack.Pop(&checkedItem);
	EXPECT_EQ(*checkedItem, item1);
	EXPECT_EQ(stack.GetActualSize(), 0);
	checkedItem = &itemOdd;
	result = stack.Pop(&checkedItem);
	EXPECT_EQ(StackResults::IS_EMPTY, result);
	EXPECT_EQ(stack.GetActualSize(), 0);
	EXPECT_EQ(*checkedItem, itemOdd);
}

const char string1[] = "String 1";
const char string2[] = "String 2";
const char string3[] = "String 3";
const char stringOdd[] = "String 99";

TEST(StackOfVoid, FourStringPushPop) {
	StackOfPointers<const char*, ITEMS_MAX> stack(7, StackErorrHandler);
	EXPECT_EQ(true, stack.IsEmpty());
	stack.Push(string1);
	stack.Push(string2);
	StackResults result = stack.Push(string3);
	EXPECT_EQ(StackResults::OK, result);
	result = stack.Push(stringOdd);
	EXPECT_EQ(StackResults::OVERFULL_ERROR, result);
	EXPECT_EQ(stack.GetActualSize(), 3);

	const char* checkedString = string2;
	stack.Pop(&checkedString);
	stack.Pop(&checkedString);
	EXPECT_EQ(stack.GetActualSize(), 1);
	stack.Pop(&checkedString);
	EXPECT_EQ(0, strcmp(checkedString, string1));
	EXPECT_EQ(stack.GetActualSize(), 0);
	checkedString = stringOdd;
	result = stack.Pop(&checkedString);
	EXPECT_EQ(StackResults::IS_EMPTY, result);
	EXPECT_EQ(stack.GetActualSize(), 0);
	EXPECT_EQ(0, strcmp(checkedString, stringOdd));
}

TEST(StackOfVoid, GetByIndex) {
	StackOfPointers<uint32_t*, ITEMS_MAX> stack(8, StackErorrHandler);
	EXPECT_EQ(true, stack.IsEmpty());
	uint32_t item1 = 1;
	uint32_t item2 = 2;
	uint32_t item3 = 3;
	uint32_t itemOdd = 99;
	uint32_t* checkedItem = &itemOdd;
	StackResults result = stack.GetByIndex(&checkedItem, 1);
	EXPECT_EQ(StackResults::OUT_OF_SCOPE_ERROR, result);

	stack.Push(&item1);
	stack.Push(&item2);
	stack.Push(&item3);
	stack.Push(&itemOdd);
	EXPECT_EQ(stack.GetActualSize(), 3);

	result = stack.GetByIndex(&checkedItem, 1);
	EXPECT_EQ(StackResults::OK, result);
	EXPECT_EQ(*checkedItem, item1);

	result = stack.GetByIndex(&checkedItem, 2);
	EXPECT_EQ(StackResults::OK, result);
	EXPECT_EQ(*checkedItem, item2);

	result = stack.GetByIndex(&checkedItem, 3);
	EXPECT_EQ(StackResults::OK, result);
	EXPECT_EQ(*checkedItem, item3);

	result = stack.GetByIndex(&checkedItem, 4);
	EXPECT_EQ(StackResults::OUT_OF_SCOPE_ERROR, result);
}
