/****************************************************************************\
 Copyright (c) 2013-2014 Stitch Works Software
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
#include "testtextview.h"
#include "../src/stitchlibrary.h"

#include <QtCore/QDebug>

void TestTextView::initTestCase()
{
    
    mScene = new Scene();
    mTv = new TextView(0, mScene);

    QList< QList<Cell*> > grid = createGrid();
    qDebug() << grid;
    foreach(QList<Cell*> row, grid) {
        QStringList rowText;
        foreach(Cell *c, row) {
            rowText.append(c->name());
        }
        mScene->gridAddRow(row, true);
        mTextGrid.append(rowText);
    }
    qDebug() << mTextGrid;
}

void TestTextView::testGenerateText()
{

}

void TestTextView::testGenerateTextRow()
{
    QFETCH(int, row);
    QFETCH(QString, defaultOutput);
    QFETCH(QString, cleanOutput);
    QFETCH(QString, repeatOutput);
    QFETCH(QString, cleanRepeat);
    
    QString output = mTv->generateTextRow(row, false, false);
    QCOMPARE(output, defaultOutput);
    qDebug() << output;
    
    output = mTv->generateTextRow(row, true, false);
    QCOMPARE(output, cleanOutput);
    qDebug() << output;
    
    output = mTv->generateTextRow(row, false, true);
    QCOMPARE(output, repeatOutput);
    qDebug() << output;
    
    output = mTv->generateTextRow(row, true, true);
    QCOMPARE(output, cleanRepeat);
    qDebug() << output;
}

void TestTextView::testGenerateTextRow_data()
{

     QTest::addColumn<int>("row");
     QTest::addColumn<QString>("defaultOutput");
     QTest::addColumn<QString>("cleanOutput");
     QTest::addColumn<QString>("repeatOutput");
     QTest::addColumn<QString>("cleanRepeat");
     
     QTest::newRow("row 1") << 1
                            << "ch 1, twisted sc 1, tr 1, hdc3tog 1, ch 1, tr 1, hdc2tog 1, twisted sc 1, tr 1"
                            << "Ch 1, twisted sc 1, tr 1, hdc3tog 1, ch 1, tr 1, hdc2tog 1, twisted sc 1, tr 1."
                            << "ch 1, twisted sc 1, tr 1, hdc3tog 1, ch 1, tr 1, hdc2tog 1, twisted sc 1, tr 1"
                            << "Ch 1, twisted sc 1, tr 1, hdc3tog 1, ch 1, tr 1, hdc2tog 1, twisted sc 1, tr 1.";

}

void TestTextView::testCopyInstructions_data()
{

}

void TestTextView::testCopyInstructions()
{
    QString instructions = mTv->copyInstructions();
    qDebug() << instructions;
}

void TestTextView::cleanupTestCase()
{

}

QList< QList< Cell* > > TestTextView::createGrid()
{
    QList< QList<Cell *> > grid;
    QList<Cell *> row1, row2, row3;

//row 1    
    Cell *c = new Cell();
    c->setStitch("ch");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("ch");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("ch");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("ch");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("ch");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("ch");
    row1.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row1.append(c);    
    
    grid.append(row1);
    
//row 2    
    c = new Cell();
    c->setStitch("ch");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("twisted sc");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("hdc3tog");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("ch");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("hdc2tog");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("twisted sc");
    row2.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row2.append(c);  
    
    c = new Cell();
    c->setStitch("tr");
    row2.append(c); 
    
    grid.append(row2);
    
//row 3    
    c = new Cell();
    c->setStitch("ext sc");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("dc");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("ch-3 sc pic");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("ch-3 picot");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("ch-3 pic");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("bouillon");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("FPsc");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("3-hdc cluster");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row3.append(c);  
    
    c = new Cell();
    c->setStitch("3-hdc cluster");
    row3.append(c);
    
    c = new Cell();
    c->setStitch("tr");
    row3.append(c); 
    
    grid.append(row3);
    
    return grid;
}
