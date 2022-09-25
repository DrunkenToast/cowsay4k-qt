#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "imagegenerator.h"

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
    void on_btnGenerate_clicked();
    void on_btnColorPicker_clicked();
    void setColor(const QColor &color);

    void on_btnBack_clicked();

private:
    Ui::MainWindow *ui;
    QColorDialog *m_colorPicker;
    ImageGenerator *m_imgGen;
    QColor m_textColor;
};
#endif // MAINWINDOW_H
