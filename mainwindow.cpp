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
    setWindowTitle("Cowsay4k");

    m_imgGen = new ImageGenerator(ui->imagePage);
    m_imgGen->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    ui->imagePage->layout()->addWidget(m_imgGen);

    // Connect export button to generator
    connect(ui->btnExport, &QPushButton::clicked, m_imgGen, &ImageGenerator::exportImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGenerate_clicked() {
    m_imgGen->setText(ui->textCowsay->toPlainText());
    m_imgGen->setColor(ui->colorWidget->color());
    m_imgGen->generateImage();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
