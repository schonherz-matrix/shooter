#ifndef BAR_H
#define BAR_H

#include <QColor>
#include <QGraphicsObject>
#include <QPropertyAnimation>

class Bar : public QGraphicsObject {
  Q_OBJECT
  Q_PROPERTY(float value READ getValue WRITE setValue)

 public:
  enum { Type = UserType + 5 };

  int type() const override {
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
  }

  Bar(const QColor &color, float default_value);

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *item,
             QWidget *widget) override;

  void setValue(qreal val);  // between 0.0 and 1.0
  qreal getValue();
  void setColor(const QColor &color);
  QColor &getColor();
  void startAnim(std::chrono::milliseconds duration);

 signals:
  void finished();

 private:
  QColor m_color;
  qreal m_value;
  QPropertyAnimation anim;
};

#endif  // BAR_H
