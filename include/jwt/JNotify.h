#ifndef JNOTIFY_H
#define JNOTIFY_H

#include "global.h"
#include <functional>
#include <QEvent>
#include <QVariant>
#include <QString>

//
class JNEvent;
typedef ::std::function<void()> JNotifyCallbackEmpty;
typedef ::std::function<void(JNEvent &event)> JNotifyCallback;

// class JNEvent

class JWT_EXPORT JNEvent
{
public:
    explicit JNEvent();
    explicit JNEvent(const QString &channel, const QVariant &argument);
    virtual ~JNEvent();

    JNEvent(const JNEvent &other)
    {
        *this = other;
    }

    JNEvent &operator =(const JNEvent &other)
    {
        if (this == &other) {
            return *this;
        }
        _channel = other._channel;
        _argument = other._argument;
        _returnValue = other._returnValue;
        _disposeCallback = other._disposeCallback;
        return *this;
    }

    const QString &channel() const { return _channel; }
    const QVariant &argument() const { return _argument; }
    const QVariant &returnValue() const { return _returnValue; }
    void setReturnValue(const QVariant &value) { _returnValue = value; }

    JNotifyCallbackEmpty disposeCallback() const { return _disposeCallback; }
    void setDisposeCallback(JNotifyCallbackEmpty callback) { _disposeCallback = callback; }

private:
    QString _channel;
    QVariant _argument;
    QVariant _returnValue;
    JNotifyCallbackEmpty _disposeCallback;
    friend class JNotify;
};

// class JNotify

class JNotify;
typedef std::shared_ptr<JNotify> JNotifyPtr;
class JNotifyPrivate;

class JWT_EXPORT JNotify : public QObject
{
    Q_OBJECT
public:
    enum InternalEvent {
        Evt_PostMsg = QEvent::User + 1
    };

    static JNotify *inst(const QString &name, QObject *parent = nullptr);

    QString name() const;

    Q_INVOKABLE void on(const QString &channel, JNotifyCallback callback, bool sync = true);
    Q_INVOKABLE void on(const QString &channel, QObject *receiver, JNotifyCallback callback, bool sync = true);
    Q_INVOKABLE void once(const QString &channel, JNotifyCallback callback, bool sync = true);
    Q_INVOKABLE void once(const QString &channel, QObject *receiver, JNotifyCallback callback, bool sync = true);
    Q_INVOKABLE QVariant send(const QString &channel, const QVariant &argument = QVariant());
    Q_INVOKABLE QVariant send(const QString &channel, QObject *receiver, const QVariant &data = QVariant());
    Q_INVOKABLE void post(const QString &channel, const QVariant &argument = QVariant());
    Q_INVOKABLE void post(const QString &channel, QObject *receiver, const QVariant &arguments = QVariant());
    Q_INVOKABLE bool has(const QString &channel) const;
    Q_INVOKABLE void un(const QString &channel);
    Q_INVOKABLE void un(QObject *receiver);
    Q_INVOKABLE void un(QObject *receiver, const QString &channel);
    Q_INVOKABLE void clear();

    // for inter-process communication
    bool isIPCValid() const;
    bool registerIPC();
    void unregisterIPC();
    QVariant sendData(const QString &domain, const QVariant &data, qint64 pid = -1,
                      int timeout = -1);
    void postData(const QString &domain, const QVariant &data, qint64 pid = -1);

Q_SIGNALS:

public Q_SLOTS:

protected:
    void customEvent(QEvent *event) override;

public:
    explicit JNotify(QObject *parent = nullptr);
    explicit JNotify(const QString &name, QObject *parent = nullptr);
    ~JNotify() J_OVERRIDE;

private:
    Q_DISABLE_COPY(JNotify)
    J_DECLARE_PRIVATE(JNotify)
};

#endif // JNOTIFY_H
