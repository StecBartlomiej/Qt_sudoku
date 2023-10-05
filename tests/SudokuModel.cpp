#include <gtest/gtest.h>

#include "SudokuModel.hpp"


TEST(SudokuModelTest, RowCountAndCollumnCount)
{
    SudokuModel model{nullptr};

    // Invalid idx - RowCount and ColumnCount are independent of idx
    QModelIndex idx{};

    ASSERT_EQ(model.rowCount(idx), 9);
    ASSERT_EQ(model.columnCount(idx), 9);
}

TEST(SudokuModelTest, SetData)
{
    SudokuModel model{nullptr};

    auto idx = model.index(2, 2);

    EXPECT_TRUE(model.setData(idx, QVariant(2)));
    EXPECT_TRUE(model.setData(idx, QVariant(2u)));
    EXPECT_TRUE(model.setData(idx, QVariant("2")));
    EXPECT_TRUE(model.setData(idx, QVariant(2), Qt::EditRole));

    QModelIndex invalidIdx{};

    EXPECT_FALSE(model.setData(invalidIdx, QVariant(2)));
    EXPECT_FALSE(model.setData(idx, QVariant()));
    EXPECT_FALSE(model.setData(idx, QVariant(2.f)));
    EXPECT_FALSE(model.setData(idx, QVariant(2), Qt::DisplayRole));
}

TEST(SudokuModelTest, Data)
{
    SudokuModel model{nullptr};

    auto idx = model.index(2, 2);

    model.setData(idx, QVariant(2));

    EXPECT_EQ(model.data(idx), QVariant("2"));

    QModelIndex invalidIdx{};
    EXPECT_EQ(model.data(invalidIdx), QVariant{});

    EXPECT_EQ(model.data(idx, Qt::TextAlignmentRole), Qt::AlignCenter);
}
