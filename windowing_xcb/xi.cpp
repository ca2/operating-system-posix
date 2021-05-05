//
// Created by camilo on 17/02/2021. 00:45 BRT <3TBS_!!
//
#include "framework.h"
#ifdef WITH_XI
#include <xcb/xinput.h>
#include "aura_posix/display_lock.h"


namespace windowing_xcb
{


   bool is_return_key(xcb_ge_event_t *event)
   {

      int i;
      double *val, *raw_val;



      switch(event->event_type)
      {
         case XCB_INPUT_RAW_KEY_PRESS:
         case XCB_INPUT_RAW_KEY_RELEASE:
         {
             auto pevent = (xcb_input_raw_key_press_event_t *) event;

            //val = event->valuators.values;

            //raw_val = event->raw_values;

            //if(event->detail == 36)
            if(pevent->detail == 36)
            {

               return true;

            }

//            printf("is_return_key    detail: %d\n", event->detail);
//
//            for (i = 0; i < event->valuators.mask_len * 8; i++)
//            {
//
//               if (XIMaskIsSet(event->valuators.mask, i))
//               {
//
//                  printf("is_return_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);
//
//               }
//
//            }
//
//            printf("\n");

         }

            break;

      }

      return false;

   }


   bool is_space_key(xcb_ge_event_t *event)
   {

      int i;
      double *val, *raw_val;

      switch(event->event_type)
      {
         case XCB_INPUT_RAW_KEY_PRESS:
         case XCB_INPUT_RAW_KEY_RELEASE:
         {

            auto pevent = (xcb_input_raw_key_press_event_t *) event;
            //val = event->valuators.values;

            //raw_val = event->raw_values;

            //if(event->detail == 65)
            if(pevent->detail == 65)
            {

               return true;

            }

//            printf("is_space_key    detail: %d\n", event->detail);
//
//            for (i = 0; i < event->valuators.mask_len * 8; i++)
//            {
//
//               if (XIMaskIsSet(event->valuators.mask, i))
//               {
//
//                  printf("is_space_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);
//
//               }
//
//            }
//
//            printf("\n");

         }

            break;

      }

      return false;

   }


#if !defined(RASPBIAN)


//int xi_opcode = -1;


//__pointer(object_array) g_pobjectaExtendedEventListener;


   ::e_status windowing::register_extended_event_listener(::matter *pdata, bool bMouse, bool bKeyboard)
   {

      if (!m_pobjectaExtendedEventListener)
      {

         auto estatus = __construct_new(m_pobjectaExtendedEventListener);

         if(!estatus)
         {

            return estatus;

         }

      }

      m_pobjectaExtendedEventListener->add(pdata);

      windowing_branch(__routine([this, bMouse, bKeyboard]()
                                 {

                                    auto psystem = get_system();

                                    auto pnode = psystem->node()->m_pNodeXcb;

                                    auto pdisplay = pnode->_get_Display();

                                    synchronous_lock synchronouslock(user_mutex());

                                    ::windowing_x11::display_lock lock(pdisplay);

                                    int event, error;
                                    const xcb_query_extension_reply_t *qe_reply;
                                    xcb_xfixes_query_version_cookie_t qv_cookie;
                                    xcb_xfixes_query_version_reply_t *qv_reply;
                                    qe_reply = xcb_get_extension_data(m_pdisplay->m_pconnection, &xcb_xfixes_id);
                                    if (qe_reply && qe_reply->present) {
                                       // We *must* negotiate the XFIXES version with the server
                                       qv_cookie = xcb_xfixes_query_version(m_pdisplay->m_pconnection,
                                                                            XCB_XFIXES_MAJOR_VERSION,
                                                                            XCB_XFIXES_MINOR_VERSION);
                                       qv_reply = xcb_xfixes_query_version_reply(m_pdisplay->m_pconnection, qv_cookie, NULL);

                                       if (qv_reply->major_version < 4) {
                                          fputs("Unsupported XFIXES version\n", stderr);
                                          free(qv_reply);
                                          return;
                                       }

                                       free(qv_reply);
                                    }
                                    else {
                                       fputs("The XFIXES extension is required\n", stderr);
                                       return ;
                                    }


//                                    if (!XQueryExtension(pdisplay, "XInputExtension", &m_xi_opcode, &event, &error))
//                                    {
//
//                                       printf("X Input extension not available.\n");
//
//                                       return;
//
//                                    }
//                                    XIEventMask mask[2];
//                                    XIEventMask * m;
//                                    xcb_window_t win;
//                                    int deviceid = -1;
//                                    int use_root = 1;
//                                    int rc;
//
//                                    if (!use_root)
//                                    {
//
//                                       return;
//
//                                    }
//
//                                    win = DefaultRootWindow(pdisplay);

                                    //else
                                    //win = create_win(display);

                                    /* Select for motion events */
//                                    m = &mask[0];
//                                    m->deviceid = (deviceid == -1) ? XIAllDevices : deviceid;
//                                    m->mask_len = XIMaskLen(XI_LASTEVENT);
//                                    m->mask = (unsigned char *) calloc(m->mask_len, sizeof(char));

//                                    if (bMouse)
//                                    {
//
//                                       XISetMask(m->mask, XI_ButtonPress);
//                                       XISetMask(m->mask, XI_ButtonRelease);
//
//                                    }
//
//                                    if (bKeyboard)
//                                    {
//
//                                       XISetMask(m->mask, XI_KeyPress);
//                                       XISetMask(m->mask, XI_KeyRelease);
//
//                                    }

                                    /*

                                    XISetMask(m->mask, XI_Motion);
                                    XISetMask(m->mask, XI_DeviceChanged);
                                    XISetMask(m->mask, XI_Enter);
                                    XISetMask(m->mask, XI_Leave);
                                    XISetMask(m->mask, XI_FocusIn);
                                    XISetMask(m->mask, XI_FocusOut);

                                    #if HAVE_XI22

                                       XISetMask(m->mask, XI_TouchBegin);
                                       XISetMask(m->mask, XI_TouchUpdate);
                                       XISetMask(m->mask, XI_TouchEnd);

                                    #endif

                                    */

//      if (m->deviceid == XIAllDevices)
//       {
//
//          XISetMask(m->mask, XI_HierarchyChanged);
//
//       }

  //      XISetMask(m->mask, XI_PropertyEvent);
//
    //    m = &mask[1];

      //  m->deviceid = (deviceid == -1) ? XIAllMasterDevices : deviceid;

      //  m->mask_len = XIMaskLen(XI_LASTEVENT);

       // m->mask = (unsigned char *) calloc(m->mask_len, sizeof(char));

                                    int deviceid = -1;

         struct
         {
            xcb_input_event_mask_t head;
            xcb_input_xi_event_mask_t mask;
         } mask;

         mask.head.deviceid = deviceid == -1 ? XCB_INPUT_DEVICE_ALL : deviceid;
         mask.head.mask_len = sizeof(xcb_input_xi_event_mask_t) / sizeof(::u32);

         int iMask  = 0;
         //mask.mask = XCB_INPUT_XI_EVENT_MASK_MOTION;

        if (bMouse)
        {

           iMask |= XCB_INPUT_XI_EVENT_MASK_RAW_BUTTON_PRESS;
           iMask |= XCB_INPUT_XI_EVENT_MASK_RAW_BUTTON_RELEASE;

        }

        if (bKeyboard)
        {

           iMask |= XCB_INPUT_XI_EVENT_MASK_RAW_KEY_PRESS;
           iMask |= XCB_INPUT_XI_EVENT_MASK_RAW_KEY_RELEASE;

        }

        /*
        XISetMask(m->mask, XI_RawMotion);
    #if HAVE_XI22
        XISetMask(m->mask, XI_RawTouchBegin);
        XISetMask(m->mask, XI_RawTouchUpdate);
        XISetMask(m->mask, XI_RawTouchEnd);
    #endif
         */

        mask.mask = (xcb_input_xi_event_mask_t) iMask;

      auto cookie = xcb_input_xi_select_events(m_pdisplay->m_pconnection,  m_pdisplay->m_windowRoot, 1, &mask.head);

      auto estatus= m_pdisplay->_request_check(cookie);

      if(!estatus)
      {

         return ;

      }

      xcb_flush(m_pdisplay->m_pconnection);
        //XISelectEvents(pdisplay, win, &mask[0], use_root ? 2 : 1);
        //if (!use_root) {
        //  XISelectEvents(display, DefaultRootWindow(display), &mask[1], 1);
        //XMapWindow(display, win);
        //
        //XSync(pdisplay, false);

        //free(mask[0].mask);
        //free(mask[1].mask);

     }));

      return ::success;

   }


#endif

   bool windowing::xcb_process_ge_event(xcb_ge_event_t * pgeevent)
   {

      e_id eid = id_none;

      switch (pgeevent->event_type)
      {
         case XCB_INPUT_RAW_KEY_PRESS:
            eid = id_raw_keydown;
            break;
         case XCB_INPUT_RAW_KEY_RELEASE:
            eid = id_raw_keyup;
            break;
         case XCB_INPUT_RAW_BUTTON_PRESS:
            {

                auto prawevent =(xcb_input_raw_button_press_event_t *) pgeevent;

                if(prawevent->detail == 1)
                {
                   //left_button
                   eid = id_raw_buttondown;
                }
                else if(prawevent->detail == 2)
                {
                   //middle_button
                   eid = id_raw_buttondown;
                }
                else if(prawevent->detail == 3)
                {
                   //right_button
                   eid = id_raw_buttondown;
                }
                else if(prawevent->detail == 4)
                {
                   //wheel_up
                   //eid = id_raw_buttondown;
                }
                else if(prawevent->detail == 5)
                {
                   //wheel_down
                   //eid = id_raw_buttondown;
                }

            }
            break;
         case XCB_INPUT_RAW_BUTTON_RELEASE:
            {

               auto prawevent =(xcb_input_raw_button_release_event_t *) pgeevent;

               if(prawevent->detail == 1)
               {
                  //left_button
                  eid = id_raw_buttonup;
               }
               else if(prawevent->detail == 2)
               {
                  //middle_button
                  eid = id_raw_buttonup;
               }
               else if(prawevent->detail == 3)
               {
                  //right_button
                  eid = id_raw_buttonup;
               }
               else if(prawevent->detail == 4)
               {
                  //wheel_up
                  //eid = id_raw_buttonup;
               }
               else if(prawevent->detail == 5)
               {
                  //wheel_down
                  //eid = id_raw_buttonup;
               }

            }
            break;

      }

      auto psystem = m_psystem->m_papexsystem;

      auto psubject = psystem->subject(eid);

      if(eid != id_none)
      {

         if (eid == id_raw_keydown || eid == id_raw_keyup)
         {

            psubject->payload("return") = is_return_key(pgeevent);

            psubject->payload("space") = is_space_key(pgeevent);

         }

         ::subject::context context;

         for (auto & p : *m_pobjectaExtendedEventListener)
         {

            p->on_subject(psubject, &context);

         }

      }

      return true;

   }


} // namespace windowing_xcb


#endif



