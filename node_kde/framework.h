#ifndef __GNUC__
#pragma once
#endif


#include "acme/_start.h"


#include "_.h"


#undef new


#include "_node_kde.h"


#define new ACME_NEW


void copy(::color::color * pcolor, const QColor * pqcolor);


#include "aura/_defer.h"



