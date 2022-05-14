#ifndef READING_BLOG_H
#define READING_BLOG_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class reading_blog;
}

class reading_blog : public QDialog
{
    Q_OBJECT

public:
    explicit reading_blog(QWidget *parent = nullptr);
    ~reading_blog();

    void pass_data_and_print(QJsonObject);

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::reading_blog *ui;
    QJsonObject blog_obj;
};

#endif // READING_BLOG_H
