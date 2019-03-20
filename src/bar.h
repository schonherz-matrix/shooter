

#ifndef BAR_H
#define BAR_H

#include <QColor>
#include <QGraphicsItem>

class Bar : public QGraphicsItem
{
    Q_OBJECT
public:
    Bar(const QColor &color, float default_value);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    Q_PROPERTY(QColor color MEMBER m_color)
    Q_PROPERTY(float value MEMBER m_value WRITE setValue)

private:
    QColor m_color;

    float m_value;

    void setValue(float val);
};

#endif // BAR_H
