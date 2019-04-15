#ifndef BORDER_H
#define BORDER_H

#include <QGraphicsItem>

class Border : public QGraphicsItem {
 public:
  enum { Type = UserType + 7 };

  int type() const override {
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
  }

  Border(bool upper);

  // QGraphicsItem interface
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
};

#endif  // BORDER_H
