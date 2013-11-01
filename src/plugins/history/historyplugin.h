/*
* Copyright (C) 2008-2013 The Communi Project
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#ifndef HISTORYPLUGIN_H
#define HISTORYPLUGIN_H

#include <QHash>
#include <QtPlugin>
#include "inputplugin.h"

class IrcBuffer;

class HistoryPlugin : public QObject, public InputPlugin
{
    Q_OBJECT
    Q_INTERFACES(InputPlugin)
    Q_PLUGIN_METADATA(IID "com.github.communi.InputPlugin")

public:
    HistoryPlugin(QObject* parent = 0);

    void initialize(TextInput* input);
};

#endif // HISTORYPLUGIN_H