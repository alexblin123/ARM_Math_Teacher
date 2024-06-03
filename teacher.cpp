#include "teacher.h"
#include "ui_teacher.h"
#include <algorithm>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QtMath>

Teacher::Teacher(QWidget *parent) :

    QWidget(parent),

    ui(new Ui::Teacher),

    file(new QFile("grades.txt")),

    gradeInput(new QLineEdit(this)),

    equationInput(new QLineEdit(this)),

    inputContainer(new QWidget(this)),

    inputLayout(new QVBoxLayout(inputContainer)),

    inputLabel(new QLabel("Введите кол-во оценок", this)),

    equationContainer(new QWidget(this)),

    equationLayout(new QVBoxLayout(equationContainer)),

    equationLabel(new QLabel("Составленные уравнения", this))

{
    ui->setupUi(this);

    inputLayout->addWidget(inputLabel);

    inputLayout->addWidget(gradeInput);

    inputContainer->setLayout(inputLayout);

    inputContainer->hide();

    equationLayout->addWidget(equationLabel);

    equationLayout->addWidget(equationInput);

    equationContainer->setLayout(equationLayout);

    equationContainer->hide();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(inputContainer, 0, Qt::AlignCenter);

    mainLayout->addWidget(equationContainer, 0, Qt::AlignCenter);

    this->setLayout(mainLayout);

    connect(gradeInput, &QLineEdit::returnPressed, this, &Teacher::on_gradeInput_returnPressed);

    connect(ui->setGrade, &QPushButton::clicked, this, &Teacher::on_setGradeButton_clicked);

    connect(ui->makeEquation, &QPushButton::clicked, this, &Teacher::on_makeEquationButton_clicked);
}

Teacher::~Teacher()
{
    delete ui;

    file->close();

    delete file;
}

void Teacher::teacherSlot() { this->show(); }

void Teacher::on_pushButton_clicked() { emit teacherGoBack(); }

void Teacher::on_setGradeButton_clicked()
{
    equationContainer->hide();

    inputLabel->setText("Введите кол-во оценок");

    gradeInput->clear();

    inputContainer->show();

    gradeInput->setFocus();
}

void Teacher::on_gradeInput_returnPressed()
{
    gradeCount = gradeInput->text().toInt();

    gradeInput->clear();

    inputContainer->hide();

    createGradeInputs();
}

void Teacher::createGradeInputs()
{
    for (QLineEdit* input : gradeInputs)
    {
        inputLayout->removeWidget(input);

        delete input;
    }

    gradeInputs.clear();

    for (int i = 0; i < gradeCount; ++i)
    {
        QLineEdit *newGradeInput = new QLineEdit(this);

        newGradeInput->setPlaceholderText(QString("Введите оценку %1").arg(i + 1));

        gradeInputs.push_back(newGradeInput);

        inputLayout->addWidget(newGradeInput);

        connect(newGradeInput, &QLineEdit::returnPressed, this, &Teacher::on_gradeEntered);
    }
    inputContainer->show();
}

void Teacher::on_gradeEntered() // ввод оценки в файл
{

    QLineEdit *senderLineEdit = qobject_cast<QLineEdit*>(sender());

    if (!senderLineEdit) return;

    QString gradeText = senderLineEdit->text();

    if (!gradeText.isEmpty())
    {
        if (file->open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(file);

            out << gradeText << "\n";

            file->close();
        }

        auto it = std::find(gradeInputs.begin(), gradeInputs.end(), senderLineEdit);

        if (it != gradeInputs.end())
        {
            int currentIndex = std::distance(gradeInputs.begin(), it);

            senderLineEdit->setDisabled(true);

            if (currentIndex + 1 < static_cast<int>(gradeInputs.size())) { gradeInputs[currentIndex + 1]->setFocus(); }

            else { inputContainer->hide(); }
        }
    }
}

void Teacher::on_makeEquationButton_clicked()
{

    inputContainer->hide();

    equationLabel->setText("Сколько уравнений хотите составить");

    equationInput->clear();

    equationLayout->addWidget(equationInput);

    equationContainer->show();

    equationInput->setFocus();

    disconnect(equationInput, nullptr, this, nullptr);

    connect(equationInput, &QLineEdit::returnPressed, this, &Teacher::on_equationInput_returnPressed);
}

void Teacher::on_equationInput_returnPressed()
{
    equationsAmount = equationInput->text().toInt();

    equationInput->clear();

    equationContainer->hide();

    createEquations(equationsAmount);
}

void Teacher::createEquations(int amount) // генератор уравнений
{
    QFile file("equations.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл equations.txt");
        return;
    }

    QTextStream out(&file);
    QStringList equations;
    QStringList functions = {"sin", "cos", "tan", "exp", "log", "sqrt", "^"};

    for (int i = 0; i < amount; ++i)
    {
        int a = QRandomGenerator::global()->bounded(1, 50);
        int b = QRandomGenerator::global()->bounded(1, 50);
        int c = QRandomGenerator::global()->bounded(1, 50);
        int d = QRandomGenerator::global()->bounded(1, 50);
        int e = QRandomGenerator::global()->bounded(1, 50);

        QString func1 = functions[QRandomGenerator::global()->bounded(functions.size())];
        QString func2 = functions[QRandomGenerator::global()->bounded(functions.size())];

        QString equation;
        if (func1 == "^") {
            equation = QString("%1x^%2 + %3x = %4").arg(a).arg(b).arg(c).arg(d);
        } else if (func1 == "log") {
            equation = QString("log(%1x) + %2x = %3").arg(a).arg(b).arg(c);
        } else {
            equation = QString("%1(%2x) + %3x = %4").arg(func1).arg(a).arg(b).arg(c);
        }

        if (func2 == "^") {
            equation += QString(" + %1x^%2x").arg(d).arg(e);
        } else if (func2 == "log") {
            equation += QString(" + log(%1x)").arg(d);
        } else {
            equation += QString(" + %1(%2x)").arg(func2).arg(d);
        }

        equations << equation;
        out << equation << "\n";
    }
    file.close();

    displayEquations(equations);
}


void Teacher::displayEquations(const QStringList &equations)
{
    for (QLabel *label : equationLabels)
    {
        equationLayout->removeWidget(label);

        delete label;
    }
    equationLabels.clear();

    QLabel *messageLabel = new QLabel("Сформированные уравнения", this);

    equationLabels.push_back(messageLabel);

    equationLayout->addWidget(messageLabel);

    for (const QString &equation : equations)
    {
        QLabel *equationLabel = new QLabel(equation, this);

        equationLabels.push_back(equationLabel);

        equationLayout->addWidget(equationLabel);
    }
    equationContainer->show();
}
