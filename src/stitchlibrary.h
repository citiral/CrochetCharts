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
#ifndef STITCHLIBRARY_H
#define STITCHLIBRARY_H

#include <QtGui/QFileOpenEvent>
#include <QtCore/QStringList>
#include <QtCore/QMap>

class StitchSet;
class Stitch;

class QComboBox;

/**
 * The StitchLibrary is a set of StitchSets
 *
 * The Collection keeps track of all sets. Specifically the Collection
 * keeps track of the builtIn Set, and the masterSet. And knows about
 * temporary sets that are loaded when a file with custom stitches is
 * opened.
 *
 * The StitchLibrary acts as the point of reference for StitchSet
 * based operations such as findStitch();
 *
 * The master stitchSet is a link list to the stitches in their sets.
 */
class StitchLibrary : public QObject
{
    Q_OBJECT
    friend class SaveFile;

public:
    static StitchLibrary* inst();
    ~StitchLibrary();

    //return the list of stitch sets.
    QList<StitchSet*> stitchSets() { return mStitchSets; }
    //return the master stitch set.
    StitchSet* masterStitchSet() { return mMasterSet; }
    StitchSet* overlay() { return mOverlay; }
    
    /**
     * Load all known stitch sets.
     */
    void loadStitchSets();
    
    /**
     * @brief findStitch - find a stitch from the library
     * @param name - stitch to find
     * @param fromAll - look in all set if true otherwise just search the master list.
     * @return found stitch or 0 if no stitch.
     */
    Stitch* findStitch(QString name, bool fromAll = false);

    StitchSet* findStitchSet(QString setName);

    //fill in a dropdown list for selecting a stitch set.
    QStringList stitchSetList();
    //list all categories in all sets
    QStringList categoryList() const;
    //list all stitches in the master set by default, optionally show all stitches in all sets.
    QStringList stitchList(bool showAllSets = false) const;

    //creates a new set to the collection, and returns a pointer to it.
    StitchSet* createStitchSet(QString setName);
    //Remove and delete setName.
    void removeSet(QString setName);
    //remove a set like a save file set.
    void removeSet(StitchSet *set);

    void removeMasterStitches(StitchSet *set);

    void addStitchSet(StitchSet *set);

    bool masterHasStitch(Stitch *s);
    
    void addStitchToMasterSet(StitchSet *set, Stitch *s);
    /**
     * This function removes a stitch from the master set.
     * It can be called on stitches that aren't in the master set
     * as it checks them before it removes them.
     */
    void removeStitchFormMasterSet(Stitch *s);

    void resetMasterStitchSet();

    //save all changes in the sets out to the xml files.
    void saveAllSets();

    void reloadAllStitchIcons();

    //find the name of a stitch set based on the storage location of the set.
    QString findStitchSetName(QString folderName);

    //generates the next file name that can be used for a stitch set.
    QString nextSetSaveFile();

signals:
    void stitchListChanged();
    
private slots:
    void changeStitchName(QString setName, QString oldName, QString newName);
    void moveStitchToOverlay(QString stitchName);
    
private:
    StitchLibrary();

    //loads the list of stitches and where the stitches are being pulled from.
    bool loadMasterList();
    void saveMasterList();
    
    static StitchLibrary *mInstance;

    QList<StitchSet*> mStitchSets;
    StitchSet *mMasterSet;
    StitchSet *mOverlay;

    QMap<QString, QString> mStitchList;

};

#endif //STITCHLIBRARY_H
