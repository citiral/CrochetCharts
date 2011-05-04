/*************************************************\
| Copyright (c) 2010 Stitch Works Software        |
| Brian C. Milco <brian@stitchworkssoftware.com>  |
\*************************************************/
#include "licensehttp.h"

#include <QtNetwork/QHttp>
#include <QtNetwork/QNetworkRequest>

#include <QMessageBox>

#include "appinfo.h"

#include <QDebug>

LicenseHttp::LicenseHttp(QWidget *parent) :
    QWidget(parent)
{
}

void LicenseHttp::downloadFile(QUrl url)
{
    mUrl = url;
qDebug() << "downloadFile should only be called once" << url;
    // schedule the request
    httpRequestAborted = false;
    startRequest();
}

void LicenseHttp::startRequest()
{
    reply = qnam.get(QNetworkRequest(mUrl));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), SLOT(httpFinished(QNetworkReply*)));
}

void LicenseHttp::httpFinished(QNetworkReply *reply)
{   
    QString data = reply->readAll();

    if (reply->error()) {
        QMessageBox::information(this, tr("%1 Registration").arg(AppInfo::inst()->appOrg),
                                 tr("%1 was unable to connect to the server to register this software. "
                                    "Please make sure you are connected to the internet. If you have a firewall "
                                    "running please make sure it allows this software to connect to the internet. "
                                    "If you are still having problems please contact %2 at %3")
                                 .arg(AppInfo::inst()->appName).arg(AppInfo::inst()->appOrg).arg(AppInfo::inst()->appOrgContact));
        return;
    }

    emit licenseCompleted(data, false);
   
    reply->deleteLater();
    reply = 0;
}
