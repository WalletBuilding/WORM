#ifndef WORMNODECONFIGDIALOG_H
#define WORMNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class WormNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class WormNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WormNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:28666", QString privkey="MASTERNODEPRIVKEY");
    ~WormNodeConfigDialog();

private:
    Ui::WormNodeConfigDialog *ui;
};

#endif // WORMNODECONFIGDIALOG_H
