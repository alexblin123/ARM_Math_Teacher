#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui { class Student; }

class Student : public QWidget
{
    Q_OBJECT

public:

    explicit Student(QWidget *parent = nullptr);
    ~Student();

private:

    Ui::Student *ui;

    QLabel *gradesLabel;

    QWidget *gradesContainer;

    QVBoxLayout *gradesLayout;

    void displayGrades();

    QLabel *equationLabel;

    QWidget *equationsContainer;

    QVBoxLayout *equationsLayout;

    void displayEquations();

public slots:

    void studentSlot();

signals:

    void studentGoBack();

private slots:

    void on_pushButton_clicked();

    void on_showGradesButton_clicked();

    void on_showEquationsButton_clicked();
};

#endif // STUDENT_H
