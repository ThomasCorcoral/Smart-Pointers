#include <gtest/gtest.h>

#include "Shared.h"
#include "Weak.h"
#include "Unique.h"

namespace{
  struct test_vec{
      int x;
      int y;
  };
}

TEST(UniqueTests, DefaultCreation){
  sp::Unique<int> unique;
  EXPECT_FALSE(unique.exists());
}

TEST(UniqueTests, CreationWithValue){
  sp::Unique<int> unique(new int(42));
  EXPECT_TRUE(unique.exists());
}

TEST(UniqueTests, Incrementation){
  sp::Unique<int> unique(new int(42));
  EXPECT_TRUE(unique.exists());
  EXPECT_EQ(*unique, 42);
  ++(*unique);
  EXPECT_EQ(*unique, 43);
}

TEST(UniqueTests, Displacement){
  sp::Unique<int> unique(new int(42));
  EXPECT_TRUE(unique.exists());
  EXPECT_EQ(*unique, 42);
  sp::Unique<int> tmp = std::move(unique);
  EXPECT_FALSE(unique.exists());
  EXPECT_TRUE(tmp.exists());
  EXPECT_EQ(*tmp, 42);
}

TEST(UniqueTests, GoodMove){
  sp::Unique<int> unique(new int(42));
  sp::Unique<int> tmp(new int(24));
  EXPECT_TRUE(unique.exists());
  EXPECT_TRUE(tmp.exists());
  EXPECT_EQ(*unique, 42);
  EXPECT_EQ(*tmp, 24);
  tmp = std::move(unique);
  EXPECT_TRUE(unique.exists());
  EXPECT_TRUE(tmp.exists());
  EXPECT_EQ(*tmp, 42);
  EXPECT_EQ(*unique, 24);
}

TEST(UniqueTests, OverloadedMethods){
  sp::Unique<int> unique(new int(42));
  EXPECT_EQ(*unique, 42);
  EXPECT_NE(&unique, nullptr);
  sp::Unique<test_vec> unique_vec = new test_vec;
  unique_vec->x = 42;
  EXPECT_EQ(unique_vec->x, 42);
}

TEST(SharedTests, DefaultCreation){
  sp::Shared<int> shared;
  EXPECT_FALSE(shared.exists());
}

TEST(SharedTests, CreationWithValue){
  sp::Shared<int> shared(new int(42));
  EXPECT_TRUE(shared.exists());
}

TEST(SharedTests, Incrementation){
  sp::Shared<int> shared(new int(42));
  EXPECT_TRUE(shared.exists());
  EXPECT_EQ(*shared, 42);
  ++(*shared);
  EXPECT_EQ(*shared, 43);
}

TEST(SharedTests, Copy){
  sp::Shared<int> shared(new int(42));
  sp::Shared<int> tmp;
  EXPECT_TRUE(shared.exists());
  EXPECT_FALSE(tmp.exists());
  EXPECT_EQ(*shared, 42);
  tmp = shared;
  EXPECT_TRUE(shared.exists());
  EXPECT_TRUE(tmp.exists());
  EXPECT_EQ(*shared, 42);
  EXPECT_EQ(*tmp, 42);
  EXPECT_EQ(*shared, *tmp);
}

TEST(SharedTests, Displacement){
  sp::Shared<int> shared(new int(42));
  EXPECT_TRUE(shared.exists());
  EXPECT_EQ(*shared, 42);
  sp::Shared<int> tmp = std::move(shared);
  EXPECT_FALSE(shared.exists());
  EXPECT_TRUE(tmp.exists());
  EXPECT_EQ(*tmp, 42);
}

TEST(WeakTests, CreationWithValue){
  sp::Shared<int> shared(new int(42));
  sp::Weak<int> weak(shared);
  EXPECT_TRUE(shared.exists());
}

TEST(WeakTests, DoubleCreation) {
  int* object = new int(42);
  sp::Shared<int> shared(object);
  sp::Weak<int> weak(shared);
  sp::Weak<int> weak2(shared);
}

TEST(WeakTests, Incrementation){
  sp::Shared<int>shared(new int(42));
  EXPECT_EQ(*shared, 42);
  sp::Weak<int>weak1(shared);
  auto tmp = weak1.lock();
  EXPECT_TRUE(tmp.exists());
  (*tmp) /= 2;
  EXPECT_EQ(*tmp, 21);
}

TEST(WeakTests, Copy){
  sp::Shared<int> shared(new int(42));
  sp::Weak<int> weak(shared);
  sp::Weak<int> weak2;
  weak2 = weak;
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
