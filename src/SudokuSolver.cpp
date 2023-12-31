#include "SudokuSolver.hpp"

#include "SudokuBoard.hpp"


bool NaiveSudokuSolver(SudokuBoard &board)
{
    int y, x;
    Cell cellValue;
    quint8 currValue = 0;
    SudokuBoard originalBoard = board;
    bool isGoingBack = false;

    /// Because if last cell is non modifiable then ++i and i will be >= 9 * 9
    int i = 0;
    REVERT_BACK:
    for (; i < 9 * 9; ++i)
    {
        if (i < 0)
        {
            board = originalBoard;
            return false;
        }

        y = i / 9;
        x = i % 9;

        // TODO - delete .has_value() -> make a option to create cells that has values and are modifiable from GUI
        if (originalBoard.Cell(x, y).HasValue() || !originalBoard.Cell(x, y).IsModifiable())
        {
            if (isGoingBack)
                --i;
            else
                ++i;
            goto REVERT_BACK;
        }

        cellValue = board.Cell(x, y);
        isGoingBack = false;

        currValue = 0;
        if (cellValue.HasValue())
        {
            currValue = cellValue.Value();
            board.RemoveValue(x, y);
        }

        do
        {
            currValue += 1;
            if (currValue > 9)
            {
                --i;
                isGoingBack = true;
                goto REVERT_BACK;
            }
        } while (!board.IsAllowed(x, y, currValue));
        board.SetValue(x, y, currValue);
    }

    return true;
}
