/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2014  Vishesh Handa <me@vhanda.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "imagelocationcategorizer.h"
#include "reversegeocodelookupjob.h"
#include <QUrl>

ImageLocationCategorizer::ImageLocationCategorizer()
{
}

void ImageLocationCategorizer::addImage(const ImageInfo& ii)
{
    if (!ii.path.startsWith('/')) {
        return;
    }
    m_images << ii;

    //
    // Location
    //
    auto addr = ii.location.address();

    QString key = addr.country();
    if (key.isEmpty()) {
        return;
    }
    m_countryHash[key].append(ii);

    if (!addr.state().isEmpty()) {
        key += ", " + addr.state();
    }
    m_stateHash[key].append(ii);

    if (!addr.city().isEmpty()) {
        key += ", " + addr.city();
    }
    m_cityHash[key].append(ii);
}

QStringList ImageLocationCategorizer::countries() const
{
    return m_countryHash.keys();
}

QStringList ImageLocationCategorizer::imagesForCountry(const QString& country) const
{
    if (m_countryHash.contains(country)) {
        QList<ImageInfo> list = m_countryHash.value(country);

        QStringList images;
        for (const ImageInfo& info : list) {
            images << info.path;
        }

        return images;
    }

    return QStringList();
}

QStringList ImageLocationCategorizer::states() const
{
    return m_stateHash.keys();

}

QStringList ImageLocationCategorizer::imagesForState(const QString& state) const
{
    if (m_stateHash.contains(state)) {
        QList<ImageInfo> list = m_stateHash.value(state);

        QStringList images;
        for (const ImageInfo& info : list) {
            images << info.path;
        }

        return images;
    }

    return QStringList();
}

QStringList ImageLocationCategorizer::cities() const
{
    return m_cityHash.keys();
}

QStringList ImageLocationCategorizer::imagesForCities(const QString& city) const
{
    if (m_cityHash.contains(city)) {
        QList<ImageInfo> list = m_cityHash.value(city);

        QStringList images;
        for (const ImageInfo& info : list) {
            images << info.path;
        }

        return images;
    }

    return QStringList();
}

QHash< QString, QList< ImageInfo > > ImageLocationCategorizer::hourImages(int hours) const
{
    Q_ASSERT(hours >= 24);

    QHash< QString, QList<ImageInfo> > hash;
    for (const ImageInfo& ii : m_images) {
        QDate date = ii.date;
        if (date.isNull()) {
            continue;
        }

        QString monthName = QDate::longMonthName(date.month());
        QString year = QString::number(date.year());

        QString key;
        if (hours == 24) {
            key = date.toString(Qt::SystemLocaleLongDate);
        }
        else if (hours == 24 * 7) {
            key = "Week " + QString::number(date.weekNumber()) + ", " + monthName + ", " + year;
        }
        else if (hours == 24 * 30) {
            key = monthName + ", " + year;
        }
        else if (hours == 24 * 365) {
            key = year;
        }

        hash[key].append(ii);
    }

    return hash;
}

QStringList ImageLocationCategorizer::groupByHours(int hours) const
{
    return hourImages(hours).keys();
}

QStringList ImageLocationCategorizer::imagesForHours(int hours, const QString& groupName) const
{
    auto hash = hourImages(hours);
    if (hash.contains(groupName)) {
        QList<ImageInfo> list = hash.value(groupName);

        QStringList images;
        for (const ImageInfo& info : list) {
            images << info.path;
        }

        return images;
    }

    return QStringList();
}

QHash< QString, QList< ImageInfo > > ImageLocationCategorizer::folderImages() const
{
    QHash< QString, QList<ImageInfo> > hash;
    for (const ImageInfo& ii : m_images) {
        QUrl url = QUrl::fromLocalFile(ii.path);
        url = url.adjusted(QUrl::RemoveFilename | QUrl::StripTrailingSlash);

        QString folderName = url.fileName();
        hash[folderName].append(ii);
    }

    return hash;
}

QStringList ImageLocationCategorizer::folders() const
{
    auto hash = folderImages();
    return hash.keys();
}

QStringList ImageLocationCategorizer::imagesForFolders(const QString& folder) const
{
    auto hash = folderImages();
    if (hash.contains(folder)) {
        QList<ImageInfo> list = hash.value(folder);

        QStringList images;
        for (const ImageInfo& info : list) {
            images << info.path;
        }

        return images;
    }

    return QStringList();
}
