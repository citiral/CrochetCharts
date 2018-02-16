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
#ifndef STITCHICONUI_H
#define STITCHICONUI_H

#include <QtWidgets/QDialog>
#include "ui_stitchicon.h"

#include <QtCore/QDebug>

namespace Ui {
    class StitchIconDialog;
}

class StitchIconUi : public QDialog
{
    Q_OBJECT
public:
    StitchIconUi(QWidget* parent = 0);
    ~StitchIconUi();

private slots:
    void addIcon();
    void removeIcon();
    void saveIcon();
    void updateIconList(QString fileName);

    void updateIconSelection();
    
signals:
    void newIconAdded(QString fileName);

private:
    void loadIcons();
    
    Ui::StitchIconDialog* ui;
    
};
#endif //STITCHICONUI_H
