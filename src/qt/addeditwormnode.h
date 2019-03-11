#ifndef ADDEDITWORMNODE_H
#define ADDEDITWORMNODE_H

#include <QDialog>

namespace Ui {
class AddEditWormNode;
}


class AddEditWormNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditWormNode(QWidget *parent = 0);
    ~AddEditWormNode();

protected:

private Q_SLOTS:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

signals:

private:
    Ui::AddEditWormNode *ui;
};

#endif // ADDEDITWORMNODE_H
