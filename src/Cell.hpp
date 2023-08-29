#ifndef QT_SUDOKU_CELL_HPP
#define QT_SUDOKU_CELL_HPP

#include <QTableWidgetItem>


class Cell: public QTableWidgetItem
{
public:
    explicit Cell(QVariant value = {}, bool modifiable = true);

    [[nodiscard]] QTableWidgetItem* clone() const override;
    [[nodiscard]] QVariant data(int role) const override;
    void setData(int role, const QVariant &newValue) override;

    void write(QDataStream &out) const override;
    void read(QDataStream &in) override;

private:
    QVariant value_;
    bool modifiable_;
};


#endif //QT_SUDOKU_CELL_HPP
