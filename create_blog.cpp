#include "create_blog.h"
#include "qjsonarray.h"
#include "ui_create_blog.h"

create_blog::create_blog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::create_blog)
{
    ui->setupUi(this);
}

void create_blog::setUsername(QString new_username)
{
    username = new_username;
}

QString create_blog::getUsername() const
{
    return username;
}

create_blog::~create_blog()
{
    delete ui;
}

void create_blog::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void create_blog::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void create_blog::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}


void create_blog::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void create_blog::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void create_blog::on_pushButton_cancel_clicked()
{
    this->close();
    parentWidget()->show();
}


void create_blog::on_pushButton_post_clicked()
{
    QString blog_id = ui->lineEdit_id->text();
    QString title = ui->lineEdit_title->text();

    QJsonArray main_array;
    QFile file("blogs.json");
    if(file.open(QIODevice::ReadOnly))
    {
        QJsonParseError parse_error;
        QJsonDocument input_document = QJsonDocument::fromJson(file.readAll(), &parse_error);
        file.close();
        if(parse_error.error)
        {
            QMessageBox::warning(this, "Error", "Parse error: " + parse_error.errorString());
            return;
        }
        main_array = input_document.array();
        // loop to find if there already exists this blog id
        for (int blogIndex = 0; blogIndex < main_array.size(); ++blogIndex)
        {
            QJsonObject blog_entry = main_array[blogIndex].toObject();
            QString check_id = blog_entry["id"].toString();
            if(blog_id == check_id)
            {
                QMessageBox::warning(this, "Action failed", "This id is already taken");
                return;
            }
        }
    }
    // create new blog
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Could not create blog file");
        return;
    }
    // create object and array
    QJsonObject blog_object;
    blog_object.insert("id", blog_id);
    blog_object.insert("title", title);
    blog_object.insert("ownerId", username);
    QJsonArray items_array;
    QJsonObject item;
    item.insert("title", title);
    QString curr_time = QDateTime::currentDateTime().toString();
    item.insert("datetime", curr_time);
    QString content = ui->plainTextEdit->toPlainText();
    item.insert("content", content);
    items_array.append(item);
    blog_object.insert("list of items", items_array);
    main_array.append(blog_object);

    QJsonDocument blog_document;
    blog_document.setArray(main_array);
    QByteArray in_bytes = blog_document.toJson(QJsonDocument::Indented);
    QTextStream iStream(&file);
    iStream << in_bytes;
    file.close();
    QMessageBox::information(this, "Success", "Blog posted successfully!");
    close();
    parentWidget()->show();
}




