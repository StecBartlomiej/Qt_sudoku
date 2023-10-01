#include <gtest/gtest.h>

#include "SudokuModel.hpp"


TEST(CellTest, DefaultInitialization)
{
    Cell c(2);
    ASSERT_EQ(c.Value(), 2);
    ASSERT_EQ(c.isModifiable(), false);

    Cell c2(9, true);
    ASSERT_EQ(c2.Value(), 9);
    ASSERT_EQ(c2.isModifiable(), true);
}

TEST(CellTest, DeleteValue)
{
    Cell cell(2, true);

    ASSERT_TRUE(cell.hasValue());
    ASSERT_TRUE(cell.isModifiable());

    cell.deleteValue();

    EXPECT_FALSE(cell.hasValue());
    EXPECT_TRUE(cell.isModifiable());
}

TEST(CellDeathTest, DeleteValue)
{
    Cell cell(2);

    ASSERT_TRUE(cell.hasValue());
    ASSERT_FALSE(cell.isModifiable());

    EXPECT_DEATH_IF_SUPPORTED(cell.deleteValue(), "");
}

TEST(CellTest, SetValue)
{
    Cell cell(3, true);

    ASSERT_EQ(cell.Value(), 3);
    ASSERT_TRUE(cell.isModifiable());

    cell.setValue(13);
    EXPECT_EQ(cell.Value(), 13);
}

TEST(CellDeathTest, SetValue)
{
    Cell cell(3);

    ASSERT_EQ(cell.Value(), 3);
    ASSERT_FALSE(cell.isModifiable());

    EXPECT_DEATH_IF_SUPPORTED(cell.setValue(13), "");
}

TEST(CellTest, Value)
{
    Cell cell(2);

    ASSERT_EQ(cell.Value(), 2);
}

TEST(CellTest, ValueThrow)
{
    Cell cell{};

    // casting to void to surpass nodiscard warning
    ASSERT_THROW(static_cast<void>(cell.Value()), std::bad_optional_access);
}

TEST(CellTest, AssignmentOperator)
{
    Cell c1(3);

    Cell c2 = c1;

    ASSERT_EQ(c1.Value(), c2.Value());
    ASSERT_EQ(c1.isModifiable(), c2.isModifiable());
}

TEST(CellTest, CopyConstructor)
{
    Cell c1(3);

    Cell c2{c1};

    ASSERT_EQ(c1.Value(), c2.Value());
    ASSERT_EQ(c1.isModifiable(), c2.isModifiable());
}
