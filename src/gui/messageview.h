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

#ifndef MESSAGEVIEW_H
#define MESSAGEVIEW_H

#include "ui_messageview.h"
#include "messageformatter.h"
#include "settings.h"
#include "viewinfo.h"
#include <QPointer>
#include <QElapsedTimer>

class SyntaxHighlighter;
class MenuFactory;
class IrcMessage;
class Session;

class MessageView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
    Q_PROPERTY(QString receiver READ receiver WRITE setReceiver NOTIFY receiverChanged)

public:
    MessageView(ViewInfo::Type type, Session* session, QWidget* parent = 0);
    ~MessageView();

    bool isActive() const;
    ViewInfo::Type viewType() const;
    Session* session() const;
    UserModel* userModel() const;
    Completer* completer() const;
    QTextBrowser* textBrowser() const;
    MessageFormatter* messageFormatter() const;

    QString receiver() const;
    void setReceiver(const QString& receiver);

    MenuFactory* menuFactory() const;
    void setMenuFactory(MenuFactory* factory);

    QByteArray saveSplitter() const;
    void restoreSplitter(const QByteArray& state);

    bool hasUser(const QString& user) const;

public slots:
    void showHelp(const QString& text, bool error = false);
    void sendMessage(const QString& message);
    void applySettings(const Settings& settings);
    void receiveMessage(IrcMessage* message);

signals:
    void activeChanged();
    void receiverChanged(const QString& receiver);

    void highlighted(IrcMessage* message);
    void missed(IrcMessage* message);
    void queried(const QString& user);
    void messaged(const QString& user, const QString& message);
    void splitterChanged(const QByteArray& state);

protected:
    void hideEvent(QHideEvent* event);
    bool eventFilter(QObject* object, QEvent* event);

private slots:
    void onEscPressed();
    void onSplitterMoved();
    void onAnchorClicked(const QUrl& link);
    void completeCommand(const QString& command);
    void onTopicEdited(const QString& topic);
    void onSessionStatusChanged();
    void onSocketError();

private:
    struct Private : public Ui::MessageView {
        ViewInfo::Type viewType;
        QString receiver;
        QPointer<Session> session;
        MessageFormatter* formatter;
        SyntaxHighlighter* highlighter;
        Settings settings;
        QString topic;
        bool joined;
        int sentId;
        QString awayMessage;
        QElapsedTimer awayReply;
    } d;
};

#endif // MESSAGEVIEW_H
