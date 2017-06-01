/*
 * Copyright (C) 2017 Atul Sharma <atulsharma406@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

import QtQuick 2.1
import QtQuick.Controls 2.1 as Controls

import org.kde.kirigami 2.1 as Kirigami

Kirigami.GlobalDrawer {
    
    signal filterBy(string value)
    
    title: qsTr("Navigation") 
    handleVisible: true
    
    actions: [
        Kirigami.Action {
            text: qsTr("Locations")
            enabled: false
        },
        Kirigami.Action {
            text: qsTr("By Country")
            onTriggered: filterBy("country")
        },
        Kirigami.Action {
            text: qsTr("By State")
            onTriggered: filterBy("state")
        },
        Kirigami.Action {
            text: qsTr("By City")
            onTriggered: filterBy("city")
        },
        Kirigami.Action {
            text: qsTr("Time")
            enabled: false
        },
        Kirigami.Action {
            text: qsTr("By Year")
            onTriggered: filterBy("year")
        },
        Kirigami.Action {
            text: qsTr("By month")
            onTriggered: filterBy("month")
        },
        Kirigami.Action {
            text: qsTr("By Week")
            onTriggered: filterBy("week")
        },
        Kirigami.Action {
            text: qsTr("By Day")
            onTriggered: filterBy("day")
        },
        Kirigami.Action {
            text: qsTr("Path")
            enabled: false
        },
        Kirigami.Action {
            text: qsTr("By Folder")
            onTriggered: filterBy("folder")
        }
    ]       
}
