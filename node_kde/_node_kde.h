//
// Created by camilo on 28/04/2021.
//
#pragma once


#undef new
#include <qmetatype.h>
#include <qdatastream.h>
#include <QApplication>
#include <QPalette>
#include <QAbstractNativeEventFilter>
#include <QX11Info>
#include <KStatusNotifierItem>
#include <QAction>
#include <QMenu>
#include <QClipboard>
#include <QMimeData>
#include <QImage>
#include <QDesktopServices>
#include <QUrl>
#define new ACME_NEW


#include "windowing_xcb/_windowing_xcb.h"
#include "acme/os/ansios/_pthread.h"
#include "aura/user/_user.h"
#include "aura/os/linux/appindicator.h"




#include "copydesk.h"


#include "appindicator.h"


#include "display.h"


#include "node.h"


#include "notify_icon.h"



