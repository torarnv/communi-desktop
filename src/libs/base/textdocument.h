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

#ifndef TEXTDOCUMENT_H
#define TEXTDOCUMENT_H

#include <QTextDocument>
#include <QStringList>
#include <QMetaType>
#include <QColor>
#include <QMap>
#include <QSet>

class IrcBuffer;
class IrcMessage;
class TextBrowser;
class MessageFormatter;

class TextDocument : public QTextDocument
{
    Q_OBJECT

public:
    explicit TextDocument(IrcBuffer* buffer);

    IrcBuffer* buffer() const;

    int totalCount() const;

    QColor markerColor() const;
    void setMarkerColor(const QColor& color);

    QColor lowlightColor() const;
    void setLowlightColor(const QColor& color);

    QColor highlightColor() const;
    void setHighlightColor(const QColor& color);

    void ref(TextBrowser* browser);
    void deref(TextBrowser* browser);

    void beginLowlight();
    void endLowlight();

    void addHighlight(int block = -1);
    void removeHighlight(int block);

    void drawBackground(QPainter* painter, const QRect& bounds);
    void drawForeground(QPainter* painter, const QRect& bounds);

public slots:
    void append(const QString& text);

signals:
    void messageReceived(IrcMessage* message);

protected:
    void updateBlock(int number);
    void timerEvent(QTimerEvent* event);

private slots:
    void flushLines();
    void scrollToBottom();
    void receiveMessage(IrcMessage* message);

private:
    void appendLine(QTextCursor& cursor, const QString& line);

    struct Private {
        int ub;
        int dirty;
        int lowlight;
        IrcBuffer* buffer;
        QStringList lines;
        QColor markerColor;
        QColor lowlightColor;
        QColor highlightColor;
        QList<int> highlights;
        QMap<int, int> lowlights;
        MessageFormatter* formatter;
        QSet<TextBrowser*> browsers;
    } d;
};

Q_DECLARE_METATYPE(TextDocument*)

#endif // TEXTDOCUMENT_H
