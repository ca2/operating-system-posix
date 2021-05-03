// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "framework.h"


namespace windowing_xcb
{


   icon::icon()
   {

   }


   icon::~icon()
   {


   }


   string icon::get_tray_icon_name() const
   {

      return m_strTrayIconName;

   }


   ::e_status icon::set_tray_icon_name(const ::string & strTrayIconName)
   {

      auto estatus = ::windowing::icon::set_tray_icon_name(strTrayIconName);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void * icon::get_os_data(const ::size_i32 & size) const
   {

      return nullptr;

   }


   ::e_status icon::load_file(string strPath)
   {

      __throw(error_interface_only);

      return false;

   }


   ::e_status icon::load_matter(string strMatter)
   {

      auto pcontext = m_pcontext;

      string strPath = pcontext->m_papexcontext->dir().matter(strMatter);

      if (!load_file(strPath))
      {

         return false;

      }

//      on_update_icon();

      return true;

   }


   ::e_status icon::load_app_tray_icon(string strAppId)
   {

      auto estatus = set_tray_icon_name(strAppId);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   image_pointer icon::get_image(const concrete < ::size_i32 > & size)
   {

      __throw(error_interface_only);
      
      return nullptr;

   }


   void icon::get_sizes(array < concrete < ::size_i32 > > & a)
   {


   }


} // namespace windowing_xcb



