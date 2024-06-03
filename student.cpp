#include "student.h"
#include "ui_student.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

Student::Student(QWidget *parent)

    : QWidget(parent)

    , ui(new Ui::Student)

    , gradesLabel(new QLabel(this))

    , gradesContainer(new QWidget(this))

    , gradesLayout(new QVBoxLayout(gradesContainer))

    , equationLabel(new QLabel(this))

    , equationsContainer(new QWidget(this))

    , equationsLayout(new QVBoxLayout(equationsContainer))

{
    ui->setupUi(this);

    gradesLayout->addWidget(gradesLabel);

    gradesContainer->setLayout(gradesLayout);

    gradesContainer->hide();

    equationsLayout->addWidget(equationLabel);

    equationsContainer->setLayout(equationsLayout);

    equationsContainer->hide();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(gradesContainer, 0, Qt::AlignCenter);

    mainLayout->addWidget(equationsContainer, 0, Qt::AlignCenter);

    this->setLayout(mainLayout);

    connect(ui->showGrades, &QPushButton::clicked, this, &Student::on_showGradesButton_clicked);

    connect(ui->showEquations, &QPushButton::clicked, this, &Student::on_showEquationsButton_clicked);
}

Student::~Student() { delete ui; }

void Student::studentSlot() { this->show(); }

void Student::on_pushButton_clicked() { emit studentGoBack(); }

void Student::on_showGradesButton_clicked()
{
    equationsContainer->hide();

    displayGrades();
}

void Student::on_showEquationsButton_clicked()
{
    gradesContainer->hide();

    displayEquations();
}

void Student::displayGrades() { // вывод оценок

    QFile file("grades.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл grades.txt");

        return;
    }

    QTextStream in(&file);

    QString gradesText;

    int gradeNumber = 1;

    if (file.size() == 0) { gradesText = "Оценок еще нет"; }

    else
    {
        while (!in.atEnd())
        {
            QString line = in.readLine();

            gradesText += QString("Оценка %1: %2\n").arg(gradeNumber++).arg(line);
        }
    }

    file.close();

    gradesLabel->setText(gradesText);

    gradesContainer->show();
}

void Student::displayEquations() { // вывод уравнений

    QFile file_2("equations.txt");

    if (!file_2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл equations.txt");

        return;
    }

    QTextStream in(&file_2);

    QString equationsText;

    int equationsNumber = 1;

    if (file_2.size() == 0) { equationsText = "Уравнений еще нет"; }

    else
    {
        while (!in.atEnd())
        {
            QString line = in.readLine();

            equationsText += QString("Уравнение %1: %2\n").arg(equationsNumber++).arg(line);
        }
    }

    file_2.close();

    equationLabel->setText(equationsText);

    equationsContainer->show();
}
