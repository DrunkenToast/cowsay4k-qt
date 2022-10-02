#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imagegenerator.h"

#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->m_colorPicker = new QColorDialog(this);
    connect(this->m_colorPicker, &QColorDialog::colorSelected, this, &MainWindow::setColor);
    setColor(QColor(Qt::black)); // set default color

    m_imgGen = new ImageGenerator(ui->imagePage);
    m_imgGen->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QLabel *label = new QLabel(this);
    ui->imagePage->layout()->addWidget(m_imgGen);

    connect(ui->btnExport, &QPushButton::clicked, this, [=]{
        m_imgGen->exportImage();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGenerate_clicked() {
    m_imgGen->setText(ui->textCowsay->toPlainText());
    m_imgGen->setColor(m_textColor);
    m_imgGen->generateImage();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_btnColorPicker_clicked()
{
    this->m_colorPicker->open();
}

void MainWindow::setColor(const QColor &color)
{
    // Maybe also change text color for higher contrast
    QPalette pal = ui->btnColorPicker->palette();
    pal.setColor(QPalette::Button, QColor(color));
    ui->btnColorPicker->setAutoFillBackground(true);
    ui->btnColorPicker->setPalette(pal);
    ui->btnColorPicker->update();

    this->m_textColor = color;
}


