#ifndef EVENTTRIGGER_H
#define EVENTTRIGGER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <functional>
#include <QMutex>

typedef std::function<void(uint8_t)> EventCb;
typedef std::function<void()> SimplifiedEventCb;

class EventTrigger : public QObject
{
    Q_OBJECT

    QString _name;
    bool _inEvent;
    QMap<QString, EventCb*> _callbacks;

    QMutex mutex;

public:
    explicit EventTrigger(QString name, bool inEvent, QObject* parent=0);
    ~EventTrigger();
    QString name() const {return _name;}
    QStringList definitions() const;
    bool isInEvent() const {return _inEvent;}

signals:
    void triggrered(uint8_t data);
public slots:
    void trigger(uint8_t data = 0x00);
    bool addEvent(QString definition);
    void addEvent(QString definition, EventCb cb);
    void addEvent(QString definition, SimplifiedEventCb cb);
    bool removeEvent(QString definition);

    void updateEventTrigger(QString eventType="");

protected:
    bool updateEventTrigger(QMap<QString, EventCb*>::iterator it);

};

#endif // EVENTTRIGGER_H
