#include "register_dialog.h"
#include "ui_register_dialog.h"

register_dialog::register_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_dialog)
{
    ui->setupUi(this);
}

register_dialog::~register_dialog()
{
    delete ui;
}

void register_dialog::on_pushButton_cancel_clicked()
{
    this->close();
}

void register_dialog::on_pushButton_register_clicked()
{   // assign values as provided by the user
    QString username = ui->lineEdit_username->text();
    QString email = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();

    ui->label_wrong_data->setStyleSheet("QLabel{color : red}"); // set red colour for error messages
    auto atpos = email.indexOf("@");
    auto dotpos = email.lastIndexOf(".");
    if(username == "")
    {
        ui->label_wrong_data->setText("No username given!");
        return;
    }
    else if (atpos < 2 || dotpos <= atpos + 2 || dotpos + 2 >= email.length())   // check if proper e-mail
    {
        ui->label_wrong_data->setText("Wrong e-mail adress");
        return;
    }
    else if(password == "")
    {
        ui->label_wrong_data->setText("No password given!");
        return;
    }
    if(password != ui->lineEdit_confPassword->text())   // check if password == confirm password
    {
        ui->label_wrong_data->setText("The passwords provided are not the same!");
    }

    // create directory for accounts if doesn't exist
    if(!QDir("accounts").exists())
    {
        QDir().mkdir("accounts");
    }
    // check if user exists
    QString user_filename ="accounts/" + username + ".json";
    QFile file(user_filename);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->label_wrong_data->setText("This username is already taken!");
        return;
    }
    // create new user
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Could not create user file");
        return;
    }
    QJsonObject user_object;
    user_object.insert("userId", username);
    user_object.insert("email", email);
    user_object.insert("password", password);

    QJsonDocument user_document;
    user_document.setObject(user_object);
    QByteArray in_bytes = user_document.toJson(QJsonDocument::Indented);
    QTextStream iStream(&file);
    iStream << in_bytes;
    file.close();

    QMessageBox::information(this, "Registration completed!", "You can now log in to your new account.");
    close();
}

