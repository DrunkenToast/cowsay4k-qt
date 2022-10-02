#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = nullptr);
    QColor color();
public slots:
    void setColor(QColor);
private:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    QColor m_color;
signals:
    void colorChanged(QColor);


};

#endif // COLORWIDGET_H
