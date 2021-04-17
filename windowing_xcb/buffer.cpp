// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing_xcb.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "aura/user/_user.h"
//#endif
//#include "_user.h"

//#define VERI_BASIC_TEST

namespace windowing_xcb
{


   buffer::buffer()
   {

//      m_gc = nullptr;

//      m_pimage = nullptr;

      m_iGoodStride = 0;

   }


   buffer::~buffer()
   {

      destroy_os_buffer();

   }


   ::e_status buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      auto estatus = double_buffer::initialize_graphics_graphics(pimpl);

      if(!estatus)
      {

         return estatus;

      }

      synchronous_lock synchronouslock(user_mutex());

      display_lock displaylock(xcb_window()->xcb_display());

      m_pdisplay = xcb_window()->xcb_display();

      //XGCValues gcvalues = {};

      //m_gc = XCreateGC(xcb_window()->xcb_connection(), xcb_window()->xcb_window(), 0, &gcvalues);

      return estatus;

   }


   void buffer::finalize()
   {

      if(!xcb_window())
      {

         return;

      }

      synchronous_lock synchronouslock(user_mutex());

      display_lock displaylock(xcb_window()->xcb_display());

//      if(m_gc != nullptr)
//      {
//
//         XFreeGC(xcb_window()->xcb_connection(), m_gc);
//
//         m_gc = nullptr;
//
//      }


   }


   bool buffer::create_os_buffer(const ::size_i32 & size, int iStrideParam)
   {

//      synchronous_lock sl(mutex());
//
//      destroy_os_buffer();
//
//      if(size.is_empty())
//      {
//
//         return false;
//
//      }
//
//      //m_mem.m_bAligned = true;
//
//      m_mem.set_size((m_iGoodStride * size.cy) * sizeof(color32_t));
//
//      m_pixmap.init(size, (color32_t *) m_mem.get_data(), m_iGoodStride);
//
//      //::acme::del(m_pdc);
//
//      {
//
//         xdisplay d(m_oswindow->display());
//
//         m_pimage = XCreateImage(d, m_oswindow->visual(), m_oswindow->m_iDepth, ZPixmap, 0, (char *) m_mem->get_data(), m_pixmap->width(), m_pixmap->height(), sizeof(color32_t) * 8, m_iGoodStride);
//
//         XGCValues gcvalues;
//
//   //      m_pdc = new device_context();
//
//         m_gc = XCreateGC(d, m_oswindow->window(), 0, &gcvalues);
//
//      }
//
//      //m_pdc->m_pdisplay = m_pimpl->m_oswindow->display();
//
      return true;

   }



   void buffer::destroy_os_buffer()
   {

//      synchronous_lock sl(mutex());
//
//      xdisplay d(m_oswindow->display());
//
//      //if(m_pdc != nullptr)
//      {
//
//         //if(m_pdc->m_gc != nullptr)
//         if(m_gc != nullptr)
//         {
//
//            XFreeGC(d, m_gc);
//
//            m_gc = nullptr;
//
//         }
//
//         //delete m_pdc;
//
//         //m_pdc = nullptr;
//
//      }
//
//      if(m_pimage != nullptr)
//      {
//
//         if(m_mem.get_data() == (byte *) m_pimage->data)
//         {
//
//            m_pimage->data = nullptr;
//
//         }
//
//         XDestroyImage(m_pimage);
//
//         m_pimage = nullptr;
//
//      }
//
   }


//   bool buffer::create_os_buffer(::image * pimage)
//   {
//
//      //synchronous_lock sl(mutex());
//
////      if(!pimage)
////      {
////
////         return false;
////
////      }
////
////      m_pixmap.init(pimage->size(), (color32_t *) pimage->get_data(), pimage->scan_size());
////
////      {
////
////         //xdisplay d(m_oswindow->display());
////
////         m_pimage =
////            XCreateImage(
////               m_oswindow->display(),
////               m_oswindow->visual(),
////               m_oswindow->m_iDepth,
////               ZPixmap,
////               0,
////               (char *) pimage->get_data(),
////               pimage->width(),
////               pimage->height(),
////               sizeof(color32_t) * 8,
////               pimage->scan_size());
////
////      }
//
//      return true;
//
//   }


//   void buffer::destroy_os_buffer(::image * pimage)
//   {
//
//      if(m_pimage != nullptr)
//      {
//
//         if((byte *) m_pimage->data == (byte *) pimage->get_data())
//         {
//
//            m_pimage->data = nullptr;
//
//         }
//
//         XDestroyImage(m_pimage);
//
//         m_pimage = nullptr;
//
//      }
//
//   }
//

   bool buffer::buffer_lock_round_swap_key_buffers()
   {

      bool bOk1 = double_buffer::buffer_lock_round_swap_key_buffers();

      bool bOk2 = bitmap_source_buffer::buffer_lock_round_swap_key_buffers();

      return bOk1 && bOk2;

   }




   bool buffer::update_window(void)
   {

      if(m_pimpl == nullptr)
      {

         return false;

      }

      if(!m_pimpl->m_pwindow)
      {

         return false;

      }

      string strType = m_pimpl->m_puserinteraction->type_c_str();

      bool bComboList = strType.contains_ci("combo_list");

      if(bComboList)
      {

         //output_debug_string("combo_list update_window");

      }

      if(!m_pimpl->m_puserinteraction->is_window_screen_visible())
      {

         //bool bReallyNotVisible = !(m_pimpl->m_puserinteraction->GetStyle() & WS_VISIBLE);

         INFO("XPutImage not called. Ui is not visible.");

         return false;

      }

      if(!m_pwindow)
      {

         return false;

      }

      synchronous_lock slGraphics(mutex());

//      if(m_gc == nullptr)
//      {
//
//         return false;
//
//      }

      auto psync = get_screen_sync();

      synchronous_lock sl(psync);

      auto & pimage = get_screen_image();

      if(!::is_ok(pimage))
      {

         return false;

      }

      slGraphics.unlock();

      //pimage->map();

      synchronous_lock synchronouslock(user_mutex());

      display_lock displayLock(xcb_window()->xcb_display());

      //xcb_image_t * pximage = (xcb_image_t *)pimage->payload("pximage").i64();

//      xcb_image_t * pximage;
//
//      //if(!pximage)
//      {
//
//         color32_t colora[8];
//
//         memcpy(colora, pimage->get_data(), sizeof(colora));
//
//         //int iDefaultDepth = DefaultDepth(xcb_window()->xcb_connection(), xcb_window()->m_iScreen);
//
//         //int iWindowDepth = xcb_window()->m_iDepth;
//
//         pximage =
//            xcb_image_create (pimage->width(),
//                              pimage->height(),
//                              XCB_IMAGE_FORMAT_XY_BITMAP,
//            0,
//            1,
//            32,
//            0,
//                              XCB_IMAGE_ORDER_LSB_FIRST,
//                              XCB_IMAGE_ORDER_LSB_FIRST,
//            nullptr,
//            pimage->width() * pimage->height() * 4,
//                              (uint8_t *) pimage->get_data());
////            xcb_image_create(
////               xcb_window()->xcb_connection(),
////               xcb_window()->Visual(),
////               iWindowDepth,
////               ZPixmap,
////               0,
////               (char *) pimage->get_data(),
////               pimage->width(),
////               pimage->height(),
////               sizeof(color32_t) * 8,
////               pimage->scan_size());
////
//         //pimage->payload("pximage") = (::i64) pximage;
//
//      }

      auto pxcbconnection = m_pdisplay->xcb_connection();

      //auto pixmap = m_pdisplay->_xcb_create_pixmap(pimage);

      //printf("pimage (%d, %d, %d)\n", pimage->width(), pimage->height(), pimage->get_pixel(100, 600));

      //if(!pximage || pximage->width <= 0 || pximage->height <= 0)
      //{

        // return false;

      //}

      try
      {

         //auto pixmap =

         //XGCValues gcvalues = {};

//       auto gc = XCreateGC(m_oswindow->display(), m_oswindow->window(), 0, &gcvalues);

         int iWidth = pimage->width();

         int iHeight = pimage->height();

         //if(!bComboList)
         //{
         int xTotalOffsetInBytes = 0;
         //buffer.pixels +
         //buffer.bytes_per_row * y

         xcb_put_image(
            pxcbconnection,
            XCB_IMAGE_FORMAT_XY_BITMAP,
            xcb_window()->xcb_window(),
            m_gcontext,
            iWidth,
            iHeight,
            0, 0, 0, 32,
            iWidth * 4,
            (uint8_t *) pimage->get_data());

            //XPutImage(xcb_window()->xcb_connection(), xcb_window()->xcb_window(), m_gc, pximage, 0, 0, 0, 0, iWidth, iHeight);

         //}

  //     XFreeGC(m_oswindow->display(), gc);

//         if(bComboList)
//         {
//
//            XColor xcolour;
//
//            // I guess XParseColor will work here
//
//            xcolour.red = 32000;
//
//            xcolour.green = 65000;
//
//            xcolour.blue = 32000;
//
//            xcolour.flags = DoRed | DoGreen | DoBlue;
//
//            XAllocColor(m_oswindow->display(), m_oswindow->m_colormap, &xcolour);
//
//            XSetForeground(m_oswindow->display(), m_gc, xcolour.pixel);
//
//            XFillRectangle(m_oswindow->display(), m_oswindow->window(), m_gc, 0, 0, iWidth, iHeight);
//
//         }

         #ifdef VERI_BASIC_TEST

         XColor xcolour;

         // I guess XParseColor will work here

         xcolour.red = 32000; xcolour.green = 65000; xcolour.blue = 32000;

         xcolour.flags = DoRed | DoGreen | DoBlue;

         XAllocColor(m_oswindow->display(), m_oswindow->m_colormap, &xcolour);

         XSetForeground(m_oswindow->display(), m_gc, xcolour.pixel);

         XFillRectangle(m_oswindow->display(), m_oswindow->window(), m_gc, 0, 0, iWidth, iHeight);

         #endif

      }
      catch(...)
      {

      }

      //pximage->data = nullptr;

      //xcb_free_pixmap(pxcbconnection, pixmap);

      if(m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning)
      {

         //XFlush(m_oswindow->display());

         //XSync(m_oswindow->display(), false);

      }

      return true;

   }


   bool buffer::update_window(::image * pimage)
   {

      throw("use update_window(void)");

      return true;

   }


   ::draw2d::graphics * buffer::on_begin_draw()
   {

      m_iGoodStride = maximum(m_iGoodStride, window_size().cx);

      bitmap_source_buffer::on_begin_draw();

      return double_buffer::on_begin_draw();

   }


} // namespace windowing_xcb



