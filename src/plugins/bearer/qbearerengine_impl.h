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

#ifndef QBEARERENGINE_IMPL_H
#define QBEARERENGINE_IMPL_H

#include <qbearerengine_p.h>

#ifndef QT_NO_BEARERMANAGEMENT

QT_BEGIN_NAMESPACE

class QBearerEngineImpl : public QBearerEngine
{
    Q_OBJECT

public:
    enum ConnectionError {
        InterfaceLookupError = 0,
        ConnectError,
        OperationNotSupported,
        DisconnectionError,
    };

    QBearerEngineImpl(QObject *parent = nullptr) : QBearerEngine(parent) {}
    ~QBearerEngineImpl() {}

    virtual void connectToId(const QString &id) = 0;
    virtual void disconnectFromId(const QString &id) = 0;

    virtual QString getInterfaceFromId(const QString &id) = 0;

    virtual QNetworkSession::State sessionStateForId(const QString &id) = 0;

    virtual quint64 bytesWritten(const QString &) { return Q_UINT64_C(0); }
    virtual quint64 bytesReceived(const QString &) { return Q_UINT64_C(0); }
    virtual quint64 startTime(const QString &) { return Q_UINT64_C(0); }

Q_SIGNALS:
    void connectionError(const QString &id, QBearerEngineImpl::ConnectionError error);
};

QT_END_NAMESPACE

#endif // QT_NO_BEARERMANAGEMENT

#endif // QBEARERENGINE_IMPL_H
