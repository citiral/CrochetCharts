/****************************************************************************\
 Copyright (c) 2010-2014 Stitch Works Software
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
#ifndef STITCHSET_H
#define STITCHSET_H

#include <QtCore/QList>
#include <QtCore/QAbstractItemModel>
#include "stitch.h"

class QDomElement;
#ifdef Q_WS_MAC
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QXmlStreamReader>
#else
class QXmlStreamWriter;
class QXmlStreamReader;
#endif //Q_WS_MAC
    
class StitchSet : public QAbstractItemModel
{
    Q_OBJECT
    friend class StitchLibrary;
    friend class StitchLibraryUi;
    friend class FileFactory;
    friend class File_v1;
    friend class File_v2;
public:

    enum SaveVersion { Version_1_0_0 = 100 };
    
    StitchSet(QObject* parent = 0, bool isMasterSet = false);
    ~StitchSet();

    /**
     * loadXmlFile loads the stitchset from the user directory.
     */
    bool loadXmlFile(QString fileName);

    /**
     *  saveXmlFile saves the stitchset to the user directory for later use.
     * If you don't pass in a fileName the default setFileName will be used.
     */
    void saveXmlFile(QString fileName = "");

    /**
     * load binary .set stitch set files.
     * dest is the destination filename usually generated by the software as setX.
     */
    void loadDataFile(QString fileName, QString dest);

    /**
     * save binary .set stitch set files.
     */
    void saveDataFile(QString fileName);

    const QString name() const { return mName; }
    void setName(QString n) { mName = n; }

    const QString author() { return mAuthor; }
    void setAuthor(QString a) { mAuthor = a; }

    const QString email() { return mEmail; }
    void setEmail(QString e) { mEmail = e; }

    const QString org() { return mOrg; }
    void setOrg(QString o) { mOrg = o; }

    const QString url() { return mUrl; }
    void setUrl(QString u) { mUrl = u; }

    Stitch* findStitch(QString name);

    bool hasStitch(QString name);
    void addStitch(Stitch* s);
    void createStitch(QString name);

    /**
     * removes the stitch from the set.
     * NOTE: this function doesn't delete the stitch.
     */
    void removeStitch(QString name);
    
    int stitchCount() const;

    QList<Stitch*> stitches() const { return mStitches; }
    void clearStitches();

    /**
     * The stitch set that the user is works with.
     */
    bool isMasterSet;

    /**
     * The set is temporary and wont be saved.
     */
    bool isTemporary;

    QString stitchSetFileName;

    /**
     * returns the absolute path to the stitch set. w/trailing slash.
     */
    QString stitchSetFolder();

    void clearSelection() { mSelected.clear(); }

    /**
     * reset the master stitch set to the original state as defined by the software.
     */
    void reset();

    /**
     * reload the svgs from file -- update the colors used.
     */
    void reloadStitchIcons();
    
signals:
    void stitchNameChanged(QString setName, QString oldName, QString newName);
    void movedToOverlay(QString stitchName);
    
protected:
    void loadXmlStitchSet(QXmlStreamReader* stream, bool loadIcons = false);
    void saveXmlStitchSet(QXmlStreamWriter* stream, bool saveIcons = false);

    void saveIcons(QDataStream* out);
    void loadIcons(QDataStream* in);
   
private:
    /**
     * load the individual stitch. \param loadIcon tells the function to generate the complete
     * path name for the icon.
     * FIXME: remove the loadIcon parameter?
     */
    void loadXmlStitch(QXmlStreamReader* stream, bool loadIcon = false);

    bool removeDir(const QString &dirName);

    QList<Stitch*> mStitches;
    
    /**
     * list of checked items
     */
    QList<Stitch*> mSelected;
    
    QString mName,
            mAuthor,
            mEmail,
            mOrg,
            mUrl;
    
/***************************************************************\
|QAbstractItemModel
\***************************************************************/
public:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    
/***************************************************************/
private:
    qint32 mSaveFileVersion;
};

#endif //STITCHSET_H
