#include "colorwidget.h"

#include <QPainter>
#include <QColorDialog>
#include <QDebug>

ColorWidget::ColorWidget(QWidget *parent)
    : QWidget{parent}
{
    m_color = Qt::black;
}

QColor ColorWidget::color()
{
    return m_color;
}

void ColorWidget::setColor(QColor color)
{
    if (color == m_color) return;
    m_color = color;
    emit colorChanged(m_color);
}

void ColorWidget::mousePressEvent(QMouseEvent *)
{
    QColor c = QColorDialog::getColor(m_color, this, "Pick a new color");
    if(c.isValid()){
        setColor(c);
        update();
    }
}

void ColorWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(m_color);
    p.setPen(m_color);
    p.drawRect(rect());

    p.setPen(m_color.lightness() > 127 ? Qt::black : Qt::white); // make text contrast with background color
    p.drawText(rect(), Qt::AlignCenter, m_color.name(), nullptr);
}
