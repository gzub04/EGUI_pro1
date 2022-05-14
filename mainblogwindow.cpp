#include "mainblogwindow.h"
#include "reading_blog.h"
#include "ui_mainblogwindow.h"
#include "mainwindow.cpp"

mainBlogWindow::mainBlogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainBlogWindow)
{
    ui->setupUi(this);
    creation_window = new create_blog(this);
    curr_blog = new reading_blog(this);
    ui->pushButton_remove->setEnabled(false);
}

mainBlogWindow::~mainBlogWindow()
{
    delete ui;
}

void mainBlogWindow::setUsername(QString new_username)
{
    username = new_username;
    ui->label_username->setText(username);
}

QString mainBlogWindow::getUsername() const
{
    return username;
}

void mainBlogWindow::updateBlogs()
{
    // read all blogs
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
        ui->listWidget_your_blogs->clear();
        ui->listWidget_others_blogs->clear();
        main_array = input_document.array();
        // loop to add all entires to Widget List
        for (int blogIndex = 0; blogIndex < main_array.size(); ++blogIndex)
        {
            QJsonObject blog_entry = main_array[blogIndex].toObject();
            QString ownerId = blog_entry["ownerId"].toString();
            QString listed_name;
            if (ownerId == username)
            {
                listed_name = blog_entry["title"].toString();
            }
            else
            {
                listed_name = blog_entry["title"].toString() + " - by " + ownerId;
            }
            QListWidgetItem *blog = new QListWidgetItem(listed_name);
            QString blog_id = blog_entry["id"].toString();
            QVariant blog_data(blog_id);
            blog->setData(Qt::UserRole, blog_data);
            blog->setText(listed_name);
            if (ownerId == username)
            {
                blog->setCheckState(Qt::Unchecked);
                ui->listWidget_your_blogs->addItem(blog);
            }
            else
            {
                ui->listWidget_others_blogs->addItem(blog);
            }
        }
    }
}


void mainBlogWindow::on_pushButton_new_blog_clicked()
{
    hide();
    creation_window->setUsername(username);
    creation_window->show();
}


void mainBlogWindow::on_pushButton_refresh_clicked()
{
    this->updateBlogs();
}

// doesn't work
void mainBlogWindow::on_pushButton_remove_clicked()
{
    for (int i = 0; i < ui->listWidget_your_blogs->count(); ++i)    // loop through all
    {
        QListWidgetItem* item = ui->listWidget_your_blogs->item(i);
        if (ui->listWidget_your_blogs->item(i)->checkState())
        {
            QVariant v = item->data(Qt::UserRole);
            QString blog_id_delete = v.value<QString>();
            for (int blogIndex = 0; blogIndex < main_array.size(); ++i)
            {
                QJsonObject blog_entry = main_array[blogIndex].toObject();
                QString blog_id = blog_entry["id"].toString();
                if (blog_id == blog_id_delete)
                {
                    main_array.removeAt(i);
                    break;
                }
            }
        }
    }
    this->updateBlogs();
}


void mainBlogWindow::on_pushButton_exit_app_clicked()
{
    close();
}


void mainBlogWindow::on_listWidget_your_blogs_doubleClicked()
{
    QListWidgetItem* chosen_item = ui->listWidget_your_blogs->currentItem();
    if (chosen_item != 0)
    {
        QVariant data = chosen_item->data(Qt::UserRole);
        QString blog_id = data.toString();
        for (int blogIndex = 0; blogIndex < main_array.size(); ++blogIndex)
        {
            QJsonObject blog_entry = main_array[blogIndex].toObject();
            QString id = blog_entry["id"].toString();
            if (id == blog_id)
            {
                hide();
                curr_blog->pass_data_and_print(blog_entry);
                curr_blog->show();
            }
        }

    }
}

