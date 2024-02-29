#include "pch.h"
#include <cstdlib>
#include "../include/buffer.h"
#include "../scr/buffer.cpp"

//CircularBuffer()
TEST(TestCaseCircularBuffer, TestName) {
	CircularBuffer b;
	EXPECT_EQ(b.get_length(), 0);
	EXPECT_EQ(b.get_current_length(), 0);
	EXPECT_EQ(b.get_head(), 0);
	EXPECT_EQ(b.get_tail(), 0);
	EXPECT_NE(b.get_buffer(), nullptr);
}

//CircularBuffer::CircularBuffer(int capacity)
TEST(TestCaseCircularBufferWithCapacity, TestName) {
	CircularBuffer c(4);
	EXPECT_NE(c.get_buffer(), nullptr);
	EXPECT_EQ(c.get_length(), 4);
	EXPECT_EQ(c.get_head(), 0);
	EXPECT_EQ(c.get_current_length(), 0);
	EXPECT_EQ(c.get_tail(), 0);
}

//CircularBuffer(int capacity, const value_type& elem)
TEST(TestCaseCircularBufferWithCapacityAndElem, TestName) {
	CircularBuffer b(4, '3');
	EXPECT_NE(b.get_buffer(), nullptr);
	EXPECT_EQ(b.get_length(), 4);
	EXPECT_EQ(b.get_head(), 0);
	EXPECT_EQ(b.get_current_length(), 4);
	EXPECT_EQ(b.get_tail(), 0);

	char* buf = b.get_buffer();
	for (int i = 0; i < b.get_current_length(); i++) {
		EXPECT_EQ(buf[i], '3');
	}
}
