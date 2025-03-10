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

#ifndef CAMERABINIMAGECAPTURECONTROL_H
#define CAMERABINIMAGECAPTURECONTROL_H

#include <camera_session.h>
#include <qcameraimagecapturecontrol.h>
#include <qvideosurfaceformat.h>

#include <qgstreamerbufferprobe_p.h>

#if GST_CHECK_VERSION(1,0,0)
#include <gst/video/video.h>
#endif

class CameraBinImageCapture : public QCameraImageCaptureControl, public QGstreamerBusMessageFilter
{
   CS_OBJECT(CameraBinImageCapture)
   CS_INTERFACES(QGstreamerBusMessageFilter)

 public:
   CameraBinImageCapture(CameraBinSession *session);
   virtual ~CameraBinImageCapture();

   QCameraImageCapture::DriveMode driveMode() const {
      return QCameraImageCapture::SingleImageCapture;
   }
   void setDriveMode(QCameraImageCapture::DriveMode) {}

   bool isReadyForCapture() const;
   int capture(const QString &fileName);
   void cancelCapture();

   bool processBusMessage(const QGstreamerMessage &message);

 private :
   CS_SLOT_1(Private, void updateState())
   CS_SLOT_2(updateState)

 private:
#if GST_CHECK_VERSION(1,0,0)
   static GstPadProbeReturn encoderEventProbe(GstPad *, GstPadProbeInfo *info, gpointer user_data);
#else
   static gboolean encoderEventProbe(GstElement *, GstEvent *event, gpointer user_data);
#endif

   class EncoderProbe : public QGstreamerBufferProbe
   {
    public:
      EncoderProbe(CameraBinImageCapture *capture) : capture(capture) {}
      void probeCaps(GstCaps *caps);
      bool probeBuffer(GstBuffer *buffer);

    private:
      CameraBinImageCapture *const capture;
   } m_encoderProbe;

   class MuxerProbe : public QGstreamerBufferProbe
   {
    public:
      MuxerProbe(CameraBinImageCapture *capture) : capture(capture) {}
      void probeCaps(GstCaps *caps);
      bool probeBuffer(GstBuffer *buffer);

    private:
      CameraBinImageCapture *const capture;

   } m_muxerProbe;

   QVideoSurfaceFormat m_bufferFormat;
   QSize m_jpegResolution;
   CameraBinSession *m_session;
   GstElement *m_jpegEncoderElement;
   GstElement *m_metadataMuxerElement;

#if GST_CHECK_VERSION(1,0,0)
   GstVideoInfo m_videoInfo;
#else
   int m_bytesPerLine;
#endif

   int m_requestId;
   bool m_ready;
};

#endif // CAMERABINCAPTURECORNTROL_H
