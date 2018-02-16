/****************************************************************************\
 Copyright (c) 2011-2014 Stitch Works Software
 Brian C. Milco <bcmilco@gmail.com>

 This file is part of Crochet Charts.

 Crochet Charts is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Crochet Charts is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Crochet Charts. If not, see <http://www.gnu.org/licenses/>.

 \****************************************************************************/
#ifndef UPDATER_H
#define UPDATER_H

#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QUrl>

#include <QtWidgets/QProgressDialog>

class QFile;

class Updater : public QWidget
{
    Q_OBJECT
public:
    Updater(QWidget* parent = 0);
    ~Updater();

    void checkForUpdates(bool silent = false);
private:
    bool mSilent;

public:
    void downloadInstaller(QUrl url);
    
private slots:
    void startRequest();
    void httpFinished();
    void httpReadyRead();

    void httpFinishedInstaller();
    void httpReadyReadInstaller();
    void launchInstaller();

    void cancelDownload();
    void updateDataTransferProgress(qint64 readBytes, qint64 totalBytes);
    
private:
    QUrl mUrl;
    QNetworkAccessManager qnam;
    QNetworkReply* reply,
                 * instReply;

    QProgressDialog* mProgDialog;
    
    QByteArray mData;
    QFile* installer;
    
    int httpGetId;
    bool httpRequestAborted;
};
#endif //UPDATER_H
