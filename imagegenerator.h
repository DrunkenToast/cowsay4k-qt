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
    void generateImage();

    void setText(QString text);
    void setColor(QColor color);

protected:
    void paintEvent(QPaintEvent *);

signals:
private:
    void drawTextBubble(QPainter *p, QSize imageSize, QPoint mouthPos);
    QLabel *m_imageLabel;
    QImage m_imageResult;

    QString m_text;
    QColor m_color;
};

#endif // IMAGEGENERATOR_H
