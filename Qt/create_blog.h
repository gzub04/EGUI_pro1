#ifndef CREATE_BLOG_H
#define CREATE_BLOG_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>
#include <QDir>
#include <QMessageBox>
#include <QDateTime>

namespace Ui {
class create_blog;
}

class create_blog : public QMainWindow
{
    Q_OBJECT

public:
    explicit create_blog(QWidget *parent = nullptr);
    ~create_blog();

    void setUsername(QString);
    QString getUsername() const;


private slots:
    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionPaste_triggered();

    void on_pushButton_cancel_clicked();

    void on_pushButton_post_clicked();

private:
    Ui::create_blog *ui;
    QString username = "Undefined";
};

#endif // CREATE_BLOG_H
