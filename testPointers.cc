#include <gtest/gtest.h>

#include "Shared.h"
#include "Weak.h"
#include "Unique.h"

TEST(UniqueTests, DefaultCreation)
{
  sp::Unique<int> unique;
  EXPECT_FALSE(unique.exists());
}

TEST(UniqueTests, CreationWithValue)
{
  sp::Unique<int> unique(new int(42));
  EXPECT_TRUE(unique.exists());
}

TEST(UniqueTests, Incrementation)
{
  sp::Unique<int> unique(new int(42));
  EXPECT_TRUE(unique.exists());
  EXPECT_TRUE(*unique == 42);
  ++(*unique);
  EXPECT_TRUE(*unique == 43);
}

TEST(UniqueTests, Displacement)
{
  sp::Unique<int> unique(new int(42));
  sp::Unique<int> tmp;
  EXPECT_TRUE(unique.exists());
  EXPECT_FALSE(tmp.exists());
  EXPECT_TRUE(*unique == 42);
  tmp = std::move(unique);
  EXPECT_FALSE(unique.exists());
  EXPECT_TRUE(tmp.exists());
  EXPECT_TRUE(*tmp == 42);
}

TEST(UniqueTests, GoodMove)
{
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

TEST(UniqueTests, OverloadedMethods)
{
  sp::Unique<int> unique(new int(24));
  //unique->m_unique_ptr = 42;
  EXPECT_EQ(*unique, 42);
  EXPECT_NE(&unique, nullptr);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
