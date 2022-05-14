#include "mainwindow.h"
#include "mainblogwindow.h"
#include "ui_mainwindow.h"
#include "register_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    blog_window = new mainBlogWindow(this);
    ui->label_login_failed->setStyleSheet("QLabel{color : red}"); // set red colour for error messages
    ui->register_button->setStyleSheet("QPushButton{color : blue}");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_register_button_clicked()
{
    register_dialog reg_dialog;
    reg_dialog.setModal(true);
    reg_dialog.exec();
}


void MainWindow::on_login_button_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QString user_filepath ="accounts/" + username + ".json";
    QFile file(user_filepath);
    if(!file.open(QIODevice::ReadOnly))
    {
        ui->label_login_failed->setText("Wrong username.");
        return;
    }
    // read password
    QByteArray in_bytes = file.readAll();
    file.close();
    QJsonParseError parse_error;
    QJsonDocument account_document = QJsonDocument::fromJson(in_bytes, &parse_error);
    if(parse_error.error)
    {
        QMessageBox::warning(this, "Error", "Parse error: "+parse_error.errorString());
        return;
    }
    QJsonObject account_object = account_document.object();
    QString real_password = account_object["password"].toString();
    if (password == real_password)
    {
        hide();
        blog_window->setUsername(username);
        blog_window->updateBlogs();
        blog_window->show();
    }
    else
    {
        ui->label_login_failed->setText("Wrong password");
    }

}

