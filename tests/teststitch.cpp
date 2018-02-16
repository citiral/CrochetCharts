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
#include "teststitch.h"

#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>

#include <QtCore/QFile>
#include <QtCore/QCryptographicHash>

void TestStitch::initTestCase()
{
    mS = new Stitch();
}

void TestStitch::stitchSetup()
{
    //FIXME: don't hard code the stitches.
    mS->setName("ch");
    mS->setFile("../stitches/ch.svg");
    mS->setDescription("chain");
    mS->setCategory("Basic");
    mS->setWrongSide("ch");

    QVERIFY(mS->name() == "ch");
    QVERIFY(mS->file() == "../stitches/ch.svg");
    QVERIFY(mS->description() == "chain");
    QVERIFY(mS->category() == "Basic");
    QVERIFY(mS->wrongSide() == "ch");
}

void TestStitch::stitchRender()
{
    QFETCH(QString, stitch);
    QFETCH(QString, stitchFile);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(QString, rasterHash);
    QFETCH(QString, svgHash);
    QFETCH(QString, svgHash2);

    mS->setFile(stitchFile);

    QString rasterImage = "teststitch-" + stitch + ".png";
    QString svgImage    = "teststitch-" + stitch + ".svg";
    QString svgImageAlt = "teststitch-" + stitch + "-alt.svg";

    //verify all images.
    QPixmap pix = QPixmap(width, height);
    pix.fill(QColor(Qt::white));
    QPainter pixp;
    pixp.begin(&pix);
    pixp.drawPixmap(0,0, *mS->renderPixmap());
    pixp.end();
    pix.save(rasterImage, "PNG", 100);

    QFile f(rasterImage);

    if(!f.open(QIODevice::ReadOnly)) {
        QFAIL("Could not compare png file with expected results");
    }

    QByteArray data = f.readAll();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha1);

    QString hexHash = hash.toHex();
    QCOMPARE(hexHash, rasterHash);
    f.flush();
    f.close();

    QPainter p;
    QSvgGenerator gen;
    gen.setFileName(svgImage);
    gen.setSize(QSize(width, height));
    gen.setViewBox(QRectF(0,0,width,height));

    p.begin(&gen);
    mS->renderSvg()->render(&p);
    p.end();

    f.setFileName(svgImage);

    if(!f.open(QIODevice::ReadOnly)) {
        QWARN("Could not compare svg file with expected results");
    }

    data = f.readAll();
    hash = QCryptographicHash::hash(data, QCryptographicHash::Sha1);

    hexHash = hash.toHex();
    QCOMPARE(hexHash, svgHash);
    f.flush();
    f.close();

    QPainter p2;
    QSvgGenerator gen2;

    gen2.setFileName(svgImageAlt);
    gen2.setSize(QSize(width, height));
    gen2.setViewBox(QRectF(0,0,width,height));

    p2.begin(&gen2);
    mS->renderSvg()->render(&p2);
    p2.end();

    f.setFileName(svgImageAlt);

    if(!f.open(QIODevice::ReadOnly)) {
        QWARN("Could not compare alt svg file with expected results");
    }

    data = f.readAll();
    hash = QCryptographicHash::hash(data, QCryptographicHash::Sha1);

    hexHash = hash.toHex();
    QCOMPARE(hexHash, svgHash2);
    f.flush();
    f.close();

    QVERIFY(mS->width() == width);
    QVERIFY(mS->height() == height);
}

void TestStitch::stitchRender_data()
{
    QTest::addColumn<QString>("stitch");
    QTest::addColumn<QString>("stitchFile");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<QString>("rasterHash");
    QTest::addColumn<QString>("svgHash");
    QTest::addColumn<QString>("svgHash2");

    QTest::newRow("ch")     << "ch" << "../stitches/ch.svg" << 32.0 << 16.0
                            << "dbfacd18635fef7df41086eeccdc37447760a0ed"
                            << "6a17fde341600ab3557f14c78d4257c3fe4e4cf8"
                            << "6a17fde341600ab3557f14c78d4257c3fe4e4cf8";

    QTest::newRow("hdc")    << "hdc" << "../stitches/hdc.svg" << 32.0 << 64.0
                            << "243998c731f4a7f7db339d8792585e76b53c2f45"
                            << "25ec306ceb1a8b3cefc4d861466ea2f3bad94abe"
                            << "25ec306ceb1a8b3cefc4d861466ea2f3bad94abe";
//TODO: render other stitches esp tall and wide stitches.
}

void TestStitch::cleanupTestCase()
{
}

