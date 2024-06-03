#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    teacher = new Teacher;

    student = new Student;

    connect(this, &MainWindow::teacherSignal, teacher, &Teacher::teacherSlot);

    connect(this, &MainWindow::studentSignal, student, &Student::studentSlot);

    connect(teacher, &Teacher::teacherGoBack, this, &MainWindow::teacherGoBackSlot);

    connect(student, &Student::studentGoBack, this, &MainWindow::studentGoBackSlot);

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();

    QString password = ui->password->text();

    if ((login == "Учитель" || login == "учитель" ) && password == "1")
    {
        teacher->show();

        emit teacherSignal();

        this->close();
    }

    else if ((login == "Ученик" || login == "ученик" ) && password == "2")
    {
        student->show();

        emit studentSignal();

        this->close();

    }
    else { QMessageBox::warning(this, "Ошибка", "Неверные данные"); }
}

void MainWindow::teacherGoBackSlot()
{
     this->show();

    teacher->close();
}

void MainWindow::studentGoBackSlot()
{
    this->show();

    student->close();
}





