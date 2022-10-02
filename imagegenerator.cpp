#include "imagegenerator.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QRectF>
#include <QStandardPaths>
#include <QRandomGenerator>

#define AMT_IMAGES 3
const QString ImagePaths[] = {":/assets/img/chillin.jpg", ":/assets/img/blurrycow.jpg",
                             ":/assets/img/sup.jpg"};
const QPoint MouthPoints[] = {QPoint(2000, 1200), QPoint(700, 1800), QPoint(700,1000)};

ImageGenerator::ImageGenerator(QWidget *parent)
    : QWidget{parent}
{
}

void ImageGenerator::exportImage()
{
    QString path = QFileDialog::getSaveFileName(
                this,
                "Save Cowsay4k image as",
                QDir(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))
                    .filePath("cowsay4k.png"),
                "Images (*.png *.jpeg *.jpg)"
        );
    if (!path.isEmpty()) { // TODO: check if imageResult contains an image
        m_imageResult.save(path);
    }
}

void ImageGenerator::generateImage()
{
    int index = QRandomGenerator::global()->bounded(0, AMT_IMAGES);
    QImage QPM(ImagePaths[index]);
    QPM = QPM.scaledToHeight(2160, Qt::SmoothTransformation);
    QPainter p = QPainter(&QPM);
    drawTextBubble(&p, QPM.size(), MouthPoints[index]);
    m_imageResult = QPM;
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
    if (m_imageResult.isNull()) return;

    QPainter p(this);
    QImage scaled = m_imageResult.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p.drawImage(rect().x(), rect().y(), scaled);
}

void ImageGenerator::drawTextBubble(QPainter *p, QSize imageSize, QPoint mouthPos)
{
    if (m_text.isEmpty()) return;

    QFont font = p->font();
    font.setPixelSize(72);
    p->setFont(font);

    auto padding = imageSize.width() * 0.01;
    QPen pen(m_color, 5);

    p->setPen(pen);
    p->setBrush(Qt::white);

    qDebug() << mouthPos;
    QRectF rect(padding, padding, imageSize.width() - padding*2, p->fontMetrics().height() * (m_text.count('\n')+1));
    QRectF rectText(rect.x() + 5, rect.y(), rect.width() - 10, rect.height());
    const QPointF points[4] = {
        QPointF(rectText.x()+10, rectText.y()),
        mouthPos,
        QPointF(rectText.x() + 200, rectText.y()),
    };

    p->drawPolygon(points, 3);
    p->drawRoundedRect(rect, 20, 20);
    p->drawText(rectText, m_text);
};
