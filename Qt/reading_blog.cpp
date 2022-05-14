#include "reading_blog.h"
#include "qjsonarray.h"
#include "ui_reading_blog.h"

reading_blog::reading_blog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reading_blog)
{
    ui->setupUi(this);
}

reading_blog::~reading_blog()
{
    delete ui;
}

void reading_blog::pass_data_and_print(QJsonObject blog_obj)
{
    this->blog_obj = blog_obj;
    ui->label_title->setText(blog_obj["title"].toString());
    QJsonArray inner_array = blog_obj.value("list of items").toArray();
    QString output;
    for ( int i=0; i<inner_array.size(); ++i)
    {
        QJsonObject inner_object = inner_array[i].toObject();
        QString sub_title = inner_object["title"].toString();
        QString date_and_time = inner_object["datetime"].toString();
        QString content = inner_object["content"].toString();
        QString endl = "\n";
        output = output + "Sub title: " + sub_title + endl + date_and_time + endl + endl + content;
    }
    ui->textBrowser_main->setPlainText(output);
}

void reading_blog::on_pushButton_back_clicked()
{
    this->close();
    parentWidget()->show();
}

