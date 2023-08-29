#ifndef QT_SUDOKU_CELL_HPP
#define QT_SUDOKU_CELL_HPP

#include <QTableWidgetItem>

class Cell: public QTableWidgetItem
{
public:
    explicit Cell(std::optional<uint8_t> value = std::nullopt, bool modifiable = true);

    [[nodiscard]] QTableWidgetItem* clone() const override;
    [[nodiscard]] QVariant data(int role) const override;
    void setData(int role, const QVariant &value) override;

    void write(QDataStream &out) const override;

private:
    std::optional<uint8_t> value_;
    const bool modifiable_;
};


#endif //QT_SUDOKU_CELL_HPP
