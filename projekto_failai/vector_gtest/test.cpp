#include "pch.h"
#include "C:\Users\Arnas\Desktop\v3.0\mVector.h"
#include <stdexcept>

// Test that push_back correctly adds an element to the end of the vector
TEST(MVectorTest, PushBack) {
    mVector<int> v;
    v.push_back(1);
    EXPECT_EQ(v.back(), 1); // Verify the last element is the one just added
    EXPECT_EQ(v.size(), 1); // Verify the size is updated correctly
}

// Test that pop_back correctly removes an element from the end of the vector
TEST(MVectorTest, PopBack) {
    mVector<int> v;
    v.push_back(1);
    v.pop_back();
    EXPECT_EQ(v.size(), 0); // Verify the size is updated correctly after removal
}

// Test that at correctly returns an element at a given index
TEST(MVectorTest, At) {
    mVector<int> v;
    v.push_back(1);
    EXPECT_EQ(v.at(0), 1); // Verify the correct element is accessed
}

// Test that front correctly returns the first element of the vector
TEST(MVectorTest, Front) {
    mVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.front(), 1); // Verify the first element is correct
}

// Test that back correctly returns the last element of the vector
TEST(MVectorTest, Back) {
    mVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.back(), 2); // Verify the last element is correct
}

// Test that data correctly returns a pointer to the underlying array
TEST(MVectorTest, Data) {
    mVector<int> v;
    v.push_back(1);
    EXPECT_EQ(*v.data(), 1); // Verify the data pointer points to the correct first element
}

// Test that swap correctly swaps the contents of two vectors
TEST(VectorTest, Swap) {
    mVector<int> v1 = { 1, 2, 3 };
    mVector<int> v2 = { 4, 5, 6, 7 };

    v1.swap(v2);

    EXPECT_EQ(v1, mVector<int>({ 4, 5, 6, 7 })); // Verify v1 contains elements of v2
    EXPECT_EQ(v2, mVector<int>({ 1, 2, 3 }));    // Verify v2 contains elements of v1
}

// Test that operator== correctly checks for equality between two vectors
TEST(VectorTest, Equal) {
    mVector<int> v1 = { 1, 2, 3 };
    mVector<int> v2 = { 1, 2, 3 };

    EXPECT_TRUE(v1 == v2); // Verify the vectors are considered equal
}

// Test that operator!= correctly checks for inequality between two vectors
TEST(VectorTest, NotEqual) {
    mVector<int> v1 = { 1, 2, 3 };
    mVector<int> v2 = { 4, 5, 6 };

    EXPECT_TRUE(v1 != v2); // Verify the vectors are considered not equal
}

// Test that at throws an out_of_range exception when trying to access an out-of-range index
TEST(VectorTest, AtOutOfRange) {
    mVector<int> v;
    EXPECT_THROW(v.at(0), std::out_of_range); // Verify accessing an invalid index throws an exception
}

// Test that insert correctly inserts an element at a given index, and that erase correctly removes an element at a given index
TEST(VectorTest, InsertAndErase) {
    mVector<int> v;
    v.insert(0, 1);
    EXPECT_EQ(v.at(0), 1); // Verify the element was inserted correctly
    v.erase(0);
    EXPECT_EQ(v.size(), 0); // Verify the element was removed correctly
}

// Additional test for push_back with multiple elements
TEST(VectorTest, PushBackMultiple) {
    mVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v[0], 1); // Verify the elements were added in correct order
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

// Additional test for pop_back to handle out_of_range exception
TEST(VectorTest, PopBackOutOfRange) {
    mVector<int> v;
    v.push_back(1);
    v.pop_back();
    EXPECT_THROW(v.pop_back(), std::out_of_range); // Verify exception is thrown on pop_back when empty
}

// Test data function with multiple elements
TEST(VectorTest, DataMultiple) {
    mVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.data()[0], 1); // Verify the data pointer points to the correct first element
    EXPECT_EQ(v.data()[1], 2); // Verify the data pointer points to the correct second element
}

// Test front and back with multiple elements
TEST(VectorTest, FrontAndBackMultiple) {
    mVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.front(), 1); // Verify the first element is correct
    EXPECT_EQ(v.back(), 2);  // Verify the last element is correct
}

// Test clear function
TEST(VectorTest, Clear) {
    mVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.clear();
    EXPECT_EQ(v.size(), 0); // Verify the vector is empty after clear
}

// Test operator[] for accessing elements
TEST(VectorTest, OperatorSquareBrackets) {
    mVector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v[0], 1); // Verify the first element is correct
    EXPECT_EQ(v[1], 2); // Verify the second element is correct
}

// Test that emplace_back correctly adds an element to the vector
TEST(VectorTest, EmplaceBack_AddsElement) {
    mVector<std::pair<int, double>> v;
    v.emplace_back(1, 3.14);
    EXPECT_EQ(v.size(), 1);
}

// Test that emplace_back correctly constructs the first element of the pair
TEST(VectorTest, EmplaceBack_ConstructsFirstElement) {
    mVector<std::pair<int, double>> v;
    v.emplace_back(1, 3.14);
    EXPECT_EQ(v.back().first, 1);
}

// Test that emplace_back correctly constructs the second element of the pair
TEST(VectorTest, EmplaceBack_ConstructsSecondElement) {
    mVector<std::pair<int, double>> v;
    v.emplace_back(1, 3.14);
    EXPECT_EQ(v.back().second, 3.14);
}

// Test resize function
TEST(VectorTest, Resize) {
    mVector<int> v(5, 1); // Initialize with 5 elements, all set to 1
    v.resize(10); // Resize to 10 elements
    EXPECT_EQ(v.size(), 10); // Verify the new size
    EXPECT_EQ(v[5], 0); // Verify the additional elements are default-initialized to 0
}

// Test reserve function
TEST(VectorTest, Reserve) {
    mVector<int> v;
    v.reserve(100); // Reserve capacity for 100 elements
    EXPECT_GE(v.capacity(), 100); // Verify the capacity is at least 100
}

// Test shrink_to_fit function
TEST(VectorTest, ShrinkToFit) {
    mVector<int> v(100, 0); // Initialize with 100 elements, all set to 0
    v.resize(10); // Resize to 10 elements
    v.shrink_to_fit(); // Shrink to fit the actual size
    EXPECT_EQ(v.capacity(), 10); // Verify the capacity matches the size after shrinking
}

// Test assign function
TEST(VectorTest, Assign) {
    mVector<int> v;
    v.assign(5, 2); // Assign 5 elements, all set to 2
    EXPECT_EQ(v.size(), 5); // Verify the new size
    EXPECT_EQ(v[3], 2); // Verify the assigned value
}

// Test cbegin and cend functions
TEST(VectorTest, ConstBeginEnd) {
    const mVector<int> v = { 1, 2, 3 };
    auto it = v.cbegin();
    EXPECT_EQ(*it, 1); // Verify the value of the first element
    ++it;
    EXPECT_EQ(*it, 2); // Verify the value of the second element
    ++it;
    EXPECT_EQ(*it, 3); // Verify the value of the third element
    ++it;
    EXPECT_EQ(it, v.cend()); // Verify reaching the end
}

// Test crbegin and crend functions
TEST(VectorTest, ConstReverseBeginEnd) {
    const mVector<int> v = { 1, 2, 3 };
    auto it = v.crbegin();
    EXPECT_EQ(*it, 3); // Verify the value of the last element
    ++it;
    EXPECT_EQ(*it, 2); // Verify the value of the second to last element
    ++it;
    EXPECT_EQ(*it, 1); // Verify the value of the first element
    ++it;
    EXPECT_EQ(it, v.crend()); // Verify reaching the end
}

// Test max_size function
TEST(VectorTest, MaxSize) {
    mVector<int> v;
    EXPECT_LE(v.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(int)); // Verify the maximum size of the vector
}