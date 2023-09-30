#include <gtest/gtest.h>

#include "SudokuModel.hpp"


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
