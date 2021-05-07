//
// Created by camilo on 17/02/2021. 15:16 BRT <3TBS_!!
//
#include "framework.h"
#include "_windowing_xcb.h"
#include "windowing_xcb.h"
#include "aura/user/_user.h"
#include "acme/os/_user.h"
#include "aura/user/interaction_prodevian.h"
#include "aura/platform/message_queue.h"
#include <X11/Xatom.h>
//dnf install xcb-util-wm-devel
#include <xcb/xcb_icccm.h>


namespace windowing_xcb
{

   
   /// must be run in x11 thread (user thread)
   ::e_status window::_mapped_add_net_wm_state(x_window::enum_atom eatomNetWmState)
   {

      synchronous_lock synchronouslock(user_mutex());

      auto atomFlag = xcb_display()->atom(eatomNetWmState);

      auto atomWmNetState = xcb_display()->atom(x_window::e_atom_net_wm_state);

      if (_list_has_atom(atomWmNetState, atomFlag))
      {

         return success_none;

      }

      auto estatus = _send_client_event(atomWmNetState, _NET_WM_STATE_ADD, atomFlag);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_mapped_erase_net_wm_state(x_window::enum_atom eatomNetWmState)
   {

      synchronous_lock synchronouslock(user_mutex());

      auto atomFlag = xcb_display()->atom(eatomNetWmState);

      auto atomWmNetState = xcb_display()->atom(x_window::e_atom_net_wm_state);

      if (!_list_has_atom(atomWmNetState, atomFlag))
      {

          return success_none;

      }

      auto estatus = _send_client_event(atomWmNetState, _NET_WM_STATE_REMOVE, atomFlag);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state(x_window::enum_atom eatomNetWmState)
   {

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

      if(!estatus)
      {

         return estatus;

      }

      if(m_attributes.map_state != XCB_MAP_STATE_UNMAPPED)
      {

         estatus = _mapped_add_net_wm_state(eatomNetWmState);

      }
      else
      {

         estatus = _unmapped_add_net_wm_state(eatomNetWmState);

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state(x_window::enum_atom eatomNetWmState)
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus = _get_window_attributes();

      if(!estatus)
      {

         return estatus;

      }

      if(m_attributes.map_state != XCB_MAP_STATE_UNMAPPED)
      {

         estatus = _mapped_erase_net_wm_state(eatomNetWmState);

      }
      else
      {

         estatus = _unmapped_erase_net_wm_state(eatomNetWmState);

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_clear_net_wm_state()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus1 = _erase_net_wm_state(x_window::e_atom_net_wm_state_above);

      auto estatus2 = _erase_net_wm_state(x_window::e_atom_net_wm_state_below);

      auto estatus3 = _erase_net_wm_state(x_window::e_atom_net_wm_state_hidden);

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;
      
   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state_below()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus1 = _erase_net_wm_state_hidden();

      auto estatus2 = _erase_net_wm_state_above();

      auto estatus3 = _add_net_wm_state(x_window::e_atom_net_wm_state_below);

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;
      
   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state_above()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus1 = _erase_net_wm_state_hidden();
      auto estatus2 = _add_net_wm_state(x_window::e_atom_net_wm_state_above);
      auto estatus3 = _erase_net_wm_state_hidden();

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state_hidden()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus1 = _add_net_wm_state(x_window::e_atom_net_wm_state_hidden);
      auto estatus2 = _erase_net_wm_state_above();
      auto estatus3 = _erase_net_wm_state_below();

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }




   /// must be run in x11 thread (user thread)
   ::e_status window::_unmapped_add_net_wm_state(x_window::enum_atom eatomNetWmState)
   {

      synchronous_lock synchronouslock(user_mutex());

      auto atomNetWmState = xcb_display()->atom(x_window::e_atom_net_wm_state);

      auto atomWmNetState = xcb_display()->atom(eatomNetWmState);

      auto estatus = _list_add_atom(atomWmNetState, atomWmNetState);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_unmapped_erase_net_wm_state(x_window::enum_atom eatomNetWmState)
   {

      synchronous_lock synchronouslock(user_mutex());

      auto atomNetWmState = xcb_display()->atom(x_window::e_atom_net_wm_state);

      auto atomWmNetState = xcb_display()->atom(eatomNetWmState);

      auto estatus = _list_erase_atom(atomWmNetState, atomWmNetState);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state_below()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus = _erase_net_wm_state(x_window::e_atom_net_wm_state_below);

      if(!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state_above()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus = _erase_net_wm_state(x_window::e_atom_net_wm_state_above);

      if(!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state_hidden()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus = _erase_net_wm_state(x_window::e_atom_net_wm_state_hidden);

      if(!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_tool_window(bool bToolWindow)
   {

      windowing_output_debug_string("\n::wm_toolwindow 1");

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      ::e_status estatus;

      if(bToolWindow)
      {

         estatus = _add_net_wm_state(x_window::e_atom_net_wm_state_skip_taskbar);

      }
      else
      {

         estatus = _erase_net_wm_state(x_window::e_atom_net_wm_state_skip_taskbar);

      }

      windowing_output_debug_string("\n::wm_toolwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;
   
   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_normal_window()
   {

      ::e_status estatus = ::error_failed;

      xcb_atom_t atomWindowType;

      atomWindowType = xcb_display()->atom(x_window::e_atom_net_wm_window_type_normal);

      if(atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         atomWindowTypeValue = xcb_display()->atom(x_window::e_atom_net_wm_window_type_normal);

         if(atomWindowTypeValue != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("\n::windowing_x11::window::wm_normalwindow");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_hidden_state(bool bHidden)
   {

      windowing_output_debug_string("\n::wm_hidden_state 1");

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      ::e_status estatus;

      if(bHidden)
      {

         estatus = _add_net_wm_state(x_window::e_atom_net_wm_state_skip_taskbar);

      }
      else
      {

         estatus = _erase_net_wm_state(x_window::e_atom_net_wm_state_skip_taskbar);

      }

      windowing_output_debug_string("\n::wm_hidden_state 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_desktop_window(bool bDesktopWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("\n::wm_desktopwindow 1");

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bDesktopWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_DESKTOP", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("\n::wm_desktopwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_center_window(bool bCenterWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("\n::wm_centerwindow 1");

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bCenterWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_SPLASH", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("\n::wm_centerwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;


   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_splash_window(bool bSplashWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("\n::wm_centerwindow 1");

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bSplashWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_SPLASH", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("\n::wm_centerwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_dock_window( bool bDockWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("\n::wm_dockwindow 1");

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bDockWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_DOCK", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("\n::wm_dockwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_nodecorations(int bMap)
   {

      ::e_status estatus = ::error_failed;

      xcb_atom_t atomMotifHints = xcb_display()->intern_atom("_MOTIF_WM_HINTS", true);

      if (atomMotifHints != XCB_ATOM_NONE)
      {

         MWMHints hints = {};

         hints.flags = MWM_HINTS_DECORATIONS;
         hints.decorations = MWM_DECOR_NONE;

         //XChangeProperty(xcb_connection(), xcb_window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
         //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
         estatus = _change_property(atomMotifHints, atomMotifHints, XCB_PROP_MODE_REPLACE, 32, 5, &hints);

      }

      if (bMap)
      {

         xcb_unmap_window(xcb_connection(), xcb_window());

         xcb_map_window(xcb_connection(), xcb_window());

      }

      windowing_output_debug_string("\n::wm_nodecorations 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_iconify_window()
   {

      synchronous_lock synchronouslock(user_mutex());

      //display_lock displaylock(xcb_display());

      windowing_output_debug_string("\n::wm_iconify_window 1");
      
      ::e_status estatus;

      xcb_client_message_event_t event;
      event.response_type = XCB_CLIENT_MESSAGE;
      event.format = 32;
      event.sequence = 0;
      event.window = m_window;
      event.type = xcb_display()->intern_atom("WM_CHANGE_STATE", true);
      event.data.data32[0] = XCB_ICCCM_WM_STATE_ICONIC;
      event.data.data32[1] = 0;
      event.data.data32[2] = 0;
      event.data.data32[3] = 0;
      event.data.data32[4] = 0;
      xcb_send_event(xcb_connection(), 0, xcb_windowing()->m_pdisplay->m_windowRoot,
                     XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT,
                     (const char *)&event);

      if (IsWindowVisibleRaw())
      {

         estatus = _mapped_net_state_raw(1, xcb_display()->intern_atom("_NET_WM_STATE_HIDDEN", false), 0);

      }
      else
      {

         if (m_pimpl->m_puserinteraction->layout().design().display() != ::e_display_iconic)
         {

            m_pimpl->m_puserinteraction->layout().design() = ::e_display_iconic;

         }

         estatus = _unmapped_net_state_raw(xcb_display()->intern_atom("_NET_WM_STATE_HIDDEN", false));

      }

      xcb_get_property_cookie_t cookie = xcb_icccm_get_wm_hints_unchecked(xcb_connection(), m_window);
      xcb_icccm_wm_hints_t hints;
      if (xcb_icccm_get_wm_hints_reply(xcb_connection(), cookie, &hints, nullptr)) {
         //if (state & Qt::WindowMinimized)
            xcb_icccm_wm_hints_set_iconic(&hints);
         //else
           // xcb_icccm_wm_hints_set_normal(&hints);
         xcb_icccm_set_wm_hints(xcb_connection(), m_window, &hints);
      }


      windowing_output_debug_string("\n::wm_iconify_window 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   int_bool window::IsWindowVisibleRaw()
   {

      synchronous_lock synchronouslock(user_mutex());

      auto estatus = _get_window_attributes();

      if(!estatus)
      {

         return false;

      }

      return m_attributes.map_state == XCB_MAP_STATE_VIEWABLE;

   }


} // namespace windowing_xcb




