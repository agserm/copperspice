/***********************************************************************
*
* Copyright (c) 2012-2022 Barbara Geller
* Copyright (c) 2012-2022 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://www.gnu.org/licenses/
*
***********************************************************************/

#ifndef QSCRIPTDEBUGGERFRONTEND_P_P_H
#define QSCRIPTDEBUGGERFRONTEND_P_P_H


#include <QtCore/qobjectdefs.h>
#include <QtCore/qlist.h>
#include <QtCore/qhash.h>
#include <qscriptdebuggercommand_p.h>

QT_BEGIN_NAMESPACE

class QScriptDebuggerEventHandlerInterface;
class QScriptDebuggerResponseHandlerInterface;
class QEvent;
class QScriptDebuggerFrontend;

class QScriptDebuggerFrontendPrivate
{
   Q_DECLARE_PUBLIC(QScriptDebuggerFrontend)

 public:
   QScriptDebuggerFrontendPrivate();
   virtual ~QScriptDebuggerFrontendPrivate();

   void postEvent(QEvent *e);
   virtual bool event(QEvent *);
   void processCommands();

   QScriptDebuggerEventHandlerInterface *eventHandler;
   QList<QScriptDebuggerCommand> pendingCommands;
   QList<int> pendingCommandIds;
   QHash<int, QScriptDebuggerResponseHandlerInterface *> responseHandlers;
   int nextCommandId;
   QObject *eventReceiver;

   QScriptDebuggerFrontend *q_ptr;
};

QT_END_NAMESPACE

#endif
