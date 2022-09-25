#include "imagegenerator.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QRectF>

ImageGenerator::ImageGenerator(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_imageLabel = new QLabel(this);
    m_imageLabel->setText("Epic cowsay image here soon!TM");
}

void ImageGenerator::exportImage()
{
    QString path = QFileDialog::getSaveFileName(this, "Save Cowsay4k image as", QString(), "Images (*.png *.jpeg *.jpg)");
    if (!path.isEmpty()) { // TODO: check if imageResult contains an image
        m_imageResult.save(path);
    }
}

void ImageGenerator::setText(QString text)
{
    m_text = text;
}

void ImageGenerator::setColor(QColor color)
{
    m_color = color;
}

void ImageGenerator::paintEvent(QPaintEvent *)
{
    QPixmap QPM(":/assets/img/blurrycow.jpg");
    QPainter p = QPainter(&QPM);
    drawTextBubble(&p, QPM.size());
    QPixmap QPMScaled = QPM.scaled(m_imageLabel->size(), Qt::KeepAspectRatio);
    //m_imageLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    m_imageLabel->setPixmap(QPMScaled);

    //m_imageLabel->resize(size());
    // Why is there not a built-in Qt method for this???
    // if there is, how??
    auto ar = QPM.size().width() / QPM.size().height();

    auto w = size().width();
    auto h = size().height();
    if (w > h) {
        m_imageLabel->resize(h * ar, h);
    }
    else {
        m_imageLabel->resize(w, w * ar );
    }
    m_imageLabel->setScaledContents(true);
    //m_imageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_imageResult = QPM;
    m_imageLabel->setPixmap(QPM);
}

void ImageGenerator::drawTextBubble(QPainter *p, QSize imageSize)
{
    if (m_text.isEmpty()) return;

    QFont font = p->font();
    font.setPixelSize(16);
    p->setFont(font);

    auto padding = imageSize.width() * 0.01;
    p->setPen(m_color);
    p->setBrush(Qt::white);
    QRectF rect(padding, padding, imageSize.width() - padding*2, p->fontMetrics().height() * (m_text.count('\n')+1));
    QRectF rectText(rect.x() + 5, rect.y(), rect.width() - 10, rect.height());
    p->drawRoundedRect(rect, 10, 10);
    p->drawText(rectText, m_text);
}
