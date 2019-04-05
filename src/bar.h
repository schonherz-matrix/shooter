#ifndef BAR_H
#define BAR_H

#include <QColor>
#include <QGraphicsItem>

class Bar : public QGraphicsItem {
 public:
    enum { Type = UserType + 5 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

  Bar(const QColor &color, float default_value);

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *item,
             QWidget *widget) override;

  void setValue(float val);  // between 0.0 and 1.0
  float getValue();
  void setColor(const QColor &color);
  QColor &getColor();

 private:
  QColor m_color;
  float m_value;
};

#endif  // BAR_H
