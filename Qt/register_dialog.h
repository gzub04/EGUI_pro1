#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextStream>

namespace Ui {
class register_dialog;
}

class register_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit register_dialog(QWidget *parent = nullptr);
    ~register_dialog();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::register_dialog *ui;
};

#endif // REGISTER_DIALOG_H
