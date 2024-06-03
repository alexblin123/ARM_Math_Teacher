#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QFile>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <vector>
#include <QTextStream>

namespace Ui {
class Teacher;
}

class Teacher : public QWidget
{
    Q_OBJECT

public:

    explicit Teacher(QWidget *parent = nullptr);
    ~Teacher();

private:

    Ui::Teacher *ui;

    QFile *file;

    int gradeCount;

    int equationsAmount;

    QLineEdit *gradeInput;

    QLineEdit *equationInput;

    QWidget *inputContainer;

    QVBoxLayout *inputLayout;

    QLabel *inputLabel;

    QWidget *equationContainer;

    QVBoxLayout *equationLayout;

    QLabel *equationLabel;

    std::vector<QLineEdit*> gradeInputs;

    std::vector<QLabel*> equationLabels;

    void createGradeInputs();

    void createEquations(int amount);

    void displayEquations(const QStringList &equations);

public slots:

    void teacherSlot();

signals:

    void teacherGoBack();

private slots:

    void on_gradeEntered();

    void on_setGradeButton_clicked();

    void on_gradeInput_returnPressed();

    void on_pushButton_clicked();

    void on_makeEquationButton_clicked();

    void on_equationInput_returnPressed();
};

#endif // TEACHER_H
