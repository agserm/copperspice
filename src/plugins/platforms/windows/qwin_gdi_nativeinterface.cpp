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

#include <qwin_gdi_nativeinterface.h>
#include <qwin_backingstore.h>
#include <qbackingstore.h>

void *QWindowsGdiNativeInterface::nativeResourceForBackingStore(const QByteArray &resource, QBackingStore *bs)
{
   if (! bs || ! bs->handle()) {
      qWarning("%s: '%s' requested for null backingstore or backingstore without handle.", __FUNCTION__, resource.constData());
      return nullptr;
   }

   QWindowsBackingStore *wbs = static_cast<QWindowsBackingStore *>(bs->handle());

   if (resource == "getDC") {
      return wbs->getDC();
   }

   qWarning("%s: Invalid key '%s' requested.", __FUNCTION__, resource.constData());

   return nullptr;
}

