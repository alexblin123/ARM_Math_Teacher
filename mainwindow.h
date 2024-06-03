#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "teacher.h"
#include "student.h"

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;

    Teacher *teacher;

    Student *student;

signals:

    void teacherSignal();

    void studentSignal();

public slots:

    void teacherGoBackSlot();

    void studentGoBackSlot();

};

#endif // MAINWINDOW_H
