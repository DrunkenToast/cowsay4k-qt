#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include <QWidget>
#include <QLabel>
#include <QPaintEvent>

class ImageGenerator : public QWidget
{
    Q_OBJECT
public:
    explicit ImageGenerator(QWidget *parent = nullptr);

public slots:
    void exportImage();

    void setText(QString text);
    void setColor(QColor color);

protected:
    void paintEvent(QPaintEvent *);

signals:
private:
    void drawTextBubble(QPainter *p, QSize imageSize);
    QLabel *m_imageLabel;
    QPixmap m_imageResult;

    QString m_text;
    QColor m_color;
};

#endif // IMAGEGENERATOR_H
