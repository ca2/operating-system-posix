// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


//!!!#include <X11/Xlib.h>


//Display * x11_get_display();


Visual * get_32bit_visual(Display * pdisplay);


void x11_kick_idle();


void x11_wait_timer_or_event(Display * pdisplay);
void __x11_hook_on_idle(Display * pdisplay);


CLASS_DECL_ACME mutex * user_mutex();


//#include "x11_exception.h"
//#include "x11_keyboard.h"
//#include "x11_hook.h"
//#include "x11_button.h"
//#include "x11_simple_ui_display.h"
//#include "x11_message_box.h"


::e_status defer_initialize_x11();
void x11_handle_just_hooks();
void x11_defer_handle_just_hooks();
int x11_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);

#include "display.h"
#include "window.h"

