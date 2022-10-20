#include "randomquote.h"
#include <QNetworkReply>

RandomQuote::RandomQuote(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);
}

void RandomQuote::setQuote(const QString &newQuote)
{
    if (quote == newQuote) return;

    quote = newQuote;
    emit quoteChanged(quote);
}

void RandomQuote::newRequest()
{
    QNetworkRequest req;

    req.setUrl(QUrl("http://whatthecommit.com/index.txt"));

    QNetworkReply *res = manager->get(req);
    connect(res, &QNetworkReply::finished, this, [=]{
        setQuote(res->readAll().trimmed());
    });
}
