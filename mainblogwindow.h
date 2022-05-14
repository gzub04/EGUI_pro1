#ifndef MAINBLOGWINDOW_H
#define MAINBLOGWINDOW_H

#include "qjsonarray.h"
#include "qlistwidget.h"
#include <QDialog>
#include "create_blog.h"
#include "reading_blog.h"

namespace Ui {
class mainBlogWindow;
}

class mainBlogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainBlogWindow(QWidget *parent = nullptr);
    ~mainBlogWindow();

    void setUsername(QString);
    QString getUsername() const;
    void updateBlogs();

private slots:

    void on_pushButton_new_blog_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_exit_app_clicked();

    void on_listWidget_your_blogs_doubleClicked();

private:
    Ui::mainBlogWindow *ui;
    create_blog *creation_window;
    QString username = "Undefinded";
    QJsonArray main_array;
    reading_blog *curr_blog;
};

#endif // MAINBLOGWINDOW_H
