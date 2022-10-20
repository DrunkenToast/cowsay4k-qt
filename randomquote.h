#ifndef RANDOMQUOTE_H
#define RANDOMQUOTE_H

#include <QObject>
#include <QNetworkAccessManager>

class RandomQuote : public QObject
{
    Q_OBJECT
public:
    explicit RandomQuote(QObject *parent = nullptr);
    void newRequest();

public slots:
    void setQuote(const QString&);

signals:
    void quoteChanged(const QString &res);

private:
    QNetworkAccessManager* manager;
    QString quote;

signals:

};

#endif // RANDOMQUOTE_H
