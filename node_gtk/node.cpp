//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
//#include "gtk_shared.h"
//#include "appindicator.h"
#include "gtk_direct.h"
//#include "windowing_x11/windowing_x11.h"
#include "acme/os/ansios/pmutex_lock.h"
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <glib.h>


::e_status os_defer_init_gtk();


bool x11_message_loop_step();


gboolean gtk_quit_callback(gpointer data);


void __copy(::color::color & color, const GdkRGBA & rgba)
{

   color.set(rgba.red, rgba.green, rgba.blue, rgba.alpha);

}


void __gtk_style_context_get_color(GtkStyleContext *context, GtkStateFlags state, const char * pszProperty, ::u32 & u32)
{

   GdkRGBA * prgba = nullptr;

   gtk_style_context_get (context, state, pszProperty, &prgba, NULL);

   ::color::color color;

   __copy(color, *prgba);

   gdk_rgba_free (prgba);

   u32 = color.u32;

}


void gdk_branch(const ::routine & routine);


int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize);


void x11_add_idle_source(::node_gtk::node * pnode);


void gtk_settings_gtk_theme_name_callback(GObject* object, GParamSpec* pspec, gpointer data)
{

   node_gtk::node * pnode = (node_gtk::node *) data;

   if(pnode)
   {

      gchar *theme_name = nullptr;

      g_object_get(pnode->m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);

      pnode->m_strTheme = theme_name;

      g_free(theme_name);

   }

   pnode->m_psystem->m_papexsystem->process_subject(id_os_user_theme);

}


const char * linux_g_direct_get_file_icon_path(const char * pszPath, int iSize);


const char * linux_g_direct_get_file_content_type(const char * pszPath);


void x11_add_idle_source();


void x11_add_filter();


void x11_main();


mutex * user_mutex();


gboolean node_gtk_source_func(gpointer pUserdata);


namespace node_gtk
{

   class appindicator;

   void appindicator_destroy(appindicator * pindicator);

} // namespace node_gtk



void os_post_quit();

void apex_application_run(const char * pszAppName, const char * pszProgName);

namespace node_gtk
{


   CLASS_DECL_ACME void _os_process_user_theme(string strTheme);


   node::node()
   {

      m_pNodeGtk = this;

      defer_initialize_x11();

      m_pGtkSettingsDefault = nullptr;

   }


   node::~node()
   {

      if(m_pGtkSettingsDefault)
      {

         g_object_unref(m_pGtkSettingsDefault);

      }

   }


   int node::node_init_check(int *pi, char ***ppz)
   {

      auto iResult = gtk_init_check(pi, ppz);

      return iResult;

   }


   void node::defer_notify_startup_complete()
   {

      auto psystem = m_psystem->m_papexsystem;

      string strApplicationServerName = psystem->get_application_server_name();

      gdk_notify_startup_complete_with_id (strApplicationServerName);

      gdk_notify_startup_complete();

   }


   ::e_status node::system_main()
   {

      auto estatus = m_psystem->m_papexsystem->begin_synch();

      if (!estatus)
      {

         output_debug_string("Failed to begin_synch the system (::apex::system or ::apex::system derived)");

         return estatus;

      }
      //   ::e_status estatus = psystem->begin_synch();
      //
      //   if(!estatus)
      //   {
      //
      //      return estatus;
      //
      //   }
      //

//      const char *pszName = m_XstrAppId;

//       g_set_application_name(pszName);

//      const char *pszPrgName = m_strProgName;

//      g_set_prgname(pszPrgName);

      //auto idle_source = g_idle_source_new();

      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) m_psystem, nullptr);

      //g_source_attach(idle_source, g_main_context_default());

      //int c = 2;

      //const char * argv[]={"app", "--g-fatal-warnings"};

#if !defined(__SANITIZE_ADDRESS__)

      {

         ///auto psystem = m_psystem;

         //auto pnode = psystem->node();

         //pnode->node_init_check(&m_argc, &m_argv);
         node_init_check(&m_psystem->m_argc, &m_psystem->m_argv);

      }

#endif

//      if (m_bUser)
//      {
//
//         estatus = defer_initialize_x11();
//
//         if(!estatus)
//         {
//
//            return estatus;
//
//         }
//
//      }


//
//      auto psystem = m_psystem;
//
//      auto pnode = psystem->node();
//
//      m_pcontext->branch(pnode);
//
//      return ::success;

      auto psystem = m_psystem->m_papexsystem;

      if (psystem->m_bGtkApp)
      {

         apex_application_run(psystem->m_strAppId, psystem->m_strProgName);

      }
      else
      {

         //g_set_application_name(System.m_XstrAppId);

         //g_set_prgname(System.m_strProgName);
      ////
      ////      //auto idle_source = g_idle_source_new();
      ////
      ////      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) m_psystem, nullptr);
      ////
      ////      //g_source_attach(idle_source, g_main_context_default());
      ////
      ////      //int c = 2;
      ////
      ////      //const char * argv[]={"app", "--g-fatal-warnings"};
      ////
      ////#if !defined(__SANITIZE_ADDRESS__)
      ////
      ////      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
      ////
      ////#endif

            node_fork([this]()
            {

             // This seems not to work with "foreign" windows
             // (X11 windows not created with Gdk)
             //x11_add_filter();


             auto pgtksettingsDefault = gtk_settings_get_default();

             if(pgtksettingsDefault)
             {


                m_pGtkSettingsDefault = G_OBJECT(pgtksettingsDefault);

                g_object_ref (m_pGtkSettingsDefault);

                gchar *theme_name = nullptr;

                g_object_get(m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);

                m_strTheme = theme_name;

                g_free(theme_name);

                auto preturn = g_signal_connect_data(
                   m_pGtkSettingsDefault,
                   "notify::gtk-theme-name",
                   G_CALLBACK(gtk_settings_gtk_theme_name_callback),
                   this,
                   NULL,
                   G_CONNECT_AFTER);

                //g_object_ref(preturn);

                //printf("return %" PRIiPTR, preturn);

                //printf("return %" PRIiPTR, preturn);

             }

            x11_add_idle_source(this);

            auto psystem = m_psystem->m_papexsystem;

            psystem->post_initial_request();

         });


         //x11_add_filter();
//
//         System.fork([this]()
//         {
//
//            //m_pwindowing->windowing_main();
//
//         });

         //x11_add_idle_source(this);

         //x11_add_idle_source(this);

         gtk_main();

         //x11_main();

      }

      return ::success;

   }


   ::e_status node::start_node()
   {


      __throw(error_failed, "deprecated");
      //
      //::parallelization::post_quit_and_wait(get_context_system(), one_minute());

      return ::success;

   }


   ::e_status node::initialize(::object *pobject)
   {

      //::node_gtk::g_defer_init();

      return ::success;

   }


   void node::os_calc_user_dark_mode()
   {

      ::aura::posix::node::os_calc_user_dark_mode();

   }


   bool node::windowing_message_loop_step()
   {

      auto psession = get_session();

      if(::is_null(psession))
      {

         return false;

      }

      auto paurasession = psession->m_paurasession;

      if(::is_null(paurasession))
      {

         return false;

      }

      auto puser = paurasession->user();

      if(::is_null(puser))
      {

         return false;

      }

      auto pwindowing = puser->windowing();

      if(::is_null(pwindowing))
      {

         return false;

      }

      bool bRet = pwindowing->message_loop_step();

      return bRet;

   }


   string node::os_get_user_theme()
   {

      return m_strTheme;

   }


   bool node::os_set_user_theme(const ::string &strUserTheme)
   {

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      auto psystem = m_psystem->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      switch (edesktop)
      {

      case ::user::e_desktop_gnome:
      case ::user::e_desktop_ubuntu_gnome:
      case ::user::e_desktop_unity_gnome:
      {

      bool bOk1 = ::node_gtk::gsettings_set("org.gnome.desktop.interface", "gtk-theme", strUserTheme);

      bool bOk2 = true;

      //if(::file::system_short_name().contains_ci("manjaro"))
      {

         bOk2 = ::node_gtk::gsettings_set("org.gnome.desktop.wm.preferences", "theme", strUserTheme);

      }

      sleep(300_ms);

      ::node_gtk::gsettings_sync();

      sleep(300_ms);

      return
      bOk1 &&bOk2;

      }

      case ::user::e_desktop_mate:

      //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

      case ::user::e_desktop_lxde:

      //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

      break;

      case ::user::e_desktop_xfce:
      {
      //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
      //          if(entry.contains("image-path") || entry.contains("last-image")){
      //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
      //      }
      //}

      }

      //break;

      default:

      output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
      return false;

      }

      return true;

   }


//   void node::os_process_user_theme(string strTheme)
//   {
//
//      _os_process_user_theme(strTheme);
//
//   }


   bool node::set_wallpaper(index iScreen, string strLocalImagePath)
   {

      // wall-changer sourceforge.net contribution

      auto psystem = m_psystem->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      switch (edesktop)
      {

         case ::user::e_desktop_gnome:
         case ::user::e_desktop_ubuntu_gnome:
         case ::user::e_desktop_unity_gnome:

            return ::node_gtk::gsettings_set("org.gnome.desktop.background", "picture-uri", "file://" + strLocalImagePath);

         case ::user::e_desktop_mate:

            return ::node_gtk::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

         case ::user::e_desktop_lxde:

            call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

            break;

         case ::user::e_desktop_xfce:
         {
            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

         }

            //break;

         default:

            output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
            return false;

      }

      return true;

   }


   void node::enable_wallpaper_change_notification()
   {

      auto psystem = m_psystem->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      switch (edesktop)
      {

         case ::user::e_desktop_gnome:
         case ::user::e_desktop_ubuntu_gnome:
         case ::user::e_desktop_unity_gnome:

            ::node_gtk::g_enable_wallpaper_change_notification("org.gnome.desktop.background", "picture-uri");

            break;

         case ::user::e_desktop_mate:

            ::node_gtk::g_enable_wallpaper_change_notification("org.mate.background", "picture-filename");

            break;

         case ::user::e_desktop_lxde:

            //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

            break;

         case ::user::e_desktop_xfce:
         {
            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

         }

         break;
         default:

            output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
            //return "";

      }

   }


   string node::get_file_icon_path(const char * pszPath, int iSize)
   {

      return ::linux_g_direct_get_file_icon_path(pszPath, iSize);

   }


   string node::get_file_content_type(const char * pszPath)
   {

      return ::linux_g_direct_get_file_content_type(pszPath);

   }


   string node::get_wallpaper(index iScreen)
   {

      return "";

   }


   ::e_status node::node_branch(const ::routine & routine)
   {

      gdk_branch(routine);

      return ::success;

   }


//   void node::node_post_quit()
//   {
//
//      os_post_quit();
//
//   }


//   void node::on_subject(::promise::subject * psubject, ::subject::context * pcontext)
//   {
//
//      if(psubject->m_id == ::id_os_user_theme)
//      {
//
//         _on_change_os_user_theme();
//
//      }
//
//
//   }


//   ::nlinux::appindicator * node::appindicator_allocate()
//   {
//
//      return new ::node_gtk::appindicator();
//
//   }
//
//
//   void node::appindicator_destroy(::linux::appindicator * pappindicator)
//   {
//
//      //::linux::appindicator_destroy(pappindicator);
//
//      delete pappindicator;
//
//   }


//   void node::enum_display_monitors(::aura::session * psession)
//   {
//
//      node_fork(__routine([psession]
//                           {
//
//                              synchronous_lock sl(user_mutex());
//
//                              //xdisplay d(x11_get_display());
//
//                              GdkDisplay *pdisplay = gdk_display_get_default();
//
//                              if (pdisplay == nullptr)
//                              {
//
//                                 return;
//
//                              }
//
//                              synchronous_lock slSession(psession->mutex());
//
//                              ::count iMonitorCount = gdk_display_get_n_monitors(pdisplay);
//
//                              psession->m_rectaWorkspace.set_size(iMonitorCount);
//
//                              psession->m_rectaMonitor.set_size(iMonitorCount);
//
//                              for (index iMonitor = 0; iMonitor < iMonitorCount; iMonitor++)
//                              {
//
//                                 GdkMonitor *pmonitor = gdk_display_get_monitor(pdisplay, iMonitor);
//
//                                 auto &rectWorkspace = psession->m_rectaWorkspace[iMonitor];
//
//                                 auto &rectMonitor = psession->m_rectaMonitor[iMonitor];
//
//                                 if (pmonitor == nullptr)
//                                 {
//
//                                    rectWorkspace.Null();
//
//                                    rectMonitor.Null();
//
//                                    continue;
//
//                                 }
//
//                                 GdkRectangle rect;
//
//                                 __zero(rect);
//
//                                 gdk_monitor_get_workarea(pmonitor, &rect);
//
//                                 __copy(rectWorkspace, rect);
//
//                                 __zero(rect);
//
//                                 gdk_monitor_get_geometry(pmonitor, &rect);
//
//                                 __copy(rectMonitor, rect);
//
//                              }
//
//                           }));
//
//   }


   void node::os_post_quit()
   {

   }


//   void * node::node_wrap_window(void * pvoidDisplay, i64 window)
//   {
//
//      Display * pdisplay = (Display *) pvoidDisplay;
//
//      GdkDisplay * pd = gdk_x11_lookup_xdisplay (pdisplay);
//
//      auto pwindow = gdk_x11_window_foreign_new_for_display(GDK_DISPLAY(pd), (Window) window);
//
//      return pwindow;
//
//   }

   bool node::should_launch_on_node(::subject::subject * psubject)
   {

      if(::is_null(psubject))
      {

         return false;

      }

      if(psubject->m_id == id_os_dark_mode)
      {

         return false;

      }

      return false;

   }


   bool node::launch_on_node(::subject::subject * psubject)
   {

      ::matter * pmatter = psubject;

      node_fork(__routine([pmatter]()
      {

         auto ret = g_timeout_add(300, (GSourceFunc) &node_gtk_source_func, pmatter);

         printf("ret %d", ret);

         printf("ret %d", ret);

         g_idle_add(&node_gtk_source_func, pmatter);

      }));

      return true;

   }


   int node::os_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
   {

      int iRet = gdk_launch_uri(pszUri, pszError, iBufferSize);

      return iRet;

   }


} // namespace node_gtk


gboolean node_gtk_source_func(gpointer pUserdata)
{

   ::matter * pmatter = (::matter *) pUserdata;

   if(!pmatter->step())
   {

      return false;

   }

   return true;

}







namespace node_gtk
{


   ::logic::bit g_bitLastDarkMode;

   char *gsettings_get_malloc(const char *pszSchema, const char *pszKey);

   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);

   bool gsettings_get(string &str, const char *pszSchema, const char *pszKey)
   {

      char *psz = gsettings_get_malloc(pszSchema, pszKey);

      if (psz == nullptr)
      {

         return false;

      }

      try
      {

         str = psz;

      }
      catch (...)
      {

      }

      try
      {

         ::free(psz);

      }
      catch (...)
      {

      }

      return true;

   }


   bool g_bGInitialized = false;


   pthread_mutex_t g_mutexG;


   bool gsettings_set(const char *pszSchema, const char *pszKey, const char *pszValue)
   {

      if (pszSchema == nullptr)
      {

         return false;

      }

      if (pszKey == nullptr)
      {

         return false;

      }

      if (pszValue == nullptr)
      {

         return false;

      }

      if (!os_defer_init_gtk())
      {

         return false;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if (settings == nullptr)
      {

         return false;

      }

      gboolean bOk = g_settings_set_string(settings, pszKey, pszValue);

      if (settings != nullptr)
      {

         g_object_unref(settings);

      }

      return bOk;

   }


   bool gsettings_sync()
   {

      if (!os_defer_init_gtk())
      {

         return false;

      }

      g_settings_sync();

      return true;

   }


   char *gsettings_get_malloc(const char *pszSchema, const char *pszKey)
   {

      if (pszSchema == nullptr)
      {

         return nullptr;

      }

      if (pszKey == nullptr)
      {

         return nullptr;

      }

      if (!os_defer_init_gtk())
      {

         return nullptr;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if (settings == nullptr)
      {

         return nullptr;

      }

      gchar *pgchar = g_settings_get_string(settings, pszKey);

      if (pgchar == nullptr)
      {

         g_object_unref(settings);

         return nullptr;

      }

      char *psz = strdup(pgchar);

      g_free(pgchar);

      g_object_unref(settings);

      return psz;

   }


   void wallpaper_change_notification(GSettings *settings, const gchar *key, gpointer data)
   {


      ::node_gtk::node * pnode = (::node_gtk::node *) data;

      pnode->m_psystem->m_papexsystem->process_subject(id_wallpaper_change);

   }


   GAction *g_pactionWallpaper = nullptr;


   bool g_enable_wallpaper_change_notification(const char *pszSchema, const char *pszKey)
   {

      if (!g_bGInitialized)
      {

         return false;

      }

      pmutex_lock lock(&g_mutexG);

      if (g_pactionWallpaper != nullptr)
      {

         return true;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if (settings == nullptr)
      {

         return false;

      }

      g_pactionWallpaper = g_settings_create_action(settings, pszKey);

      g_object_unref(settings);

      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK(wallpaper_change_notification), nullptr);

      return true;

   }


   void g_defer_init()
   {

      if (g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = true;

      pthread_mutex_init(&g_mutexG, nullptr);

   }


   void g_defer_term()
   {

      if (!g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = false;

      if (g_pactionWallpaper != nullptr)
      {

         g_object_unref(g_pactionWallpaper);

         g_pactionWallpaper = nullptr;

      }

      pthread_mutex_destroy(&g_mutexG);

   }






   //void os_calc_user_theme()
   //{

//      string strTheme = _os_calc_user_theme();
//
//      if(System.m_strOsUserTheme != strTheme)
//      {
//
//         System.m_strOsUserTheme = strTheme;
//
//         System.set_modified(id_os_user_theme);
//
//         x11_kick_idle();
//
//      }
//
//   }


   bool g_bInitializedUserTheme = false;

   string node::_os_get_user_theme()
   {

      if (!g_bInitializedUserTheme)
      {

         g_bInitializedUserTheme = true;

         auto psystem = m_psystem->m_papexsystem;

         psystem->start_subject_handling(id_os_user_theme);

      }

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      string strTheme;

      bool bOk = false;

      auto psystem = m_psystem->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      switch (edesktop)
      {

         case ::user::e_desktop_gnome:
         case ::user::e_desktop_ubuntu_gnome:
         case ::user::e_desktop_unity_gnome:

            bOk = gsettings_get(strTheme, "org.gnome.desktop.interface", "gtk-theme");

            break;

         case ::user::e_desktop_mate:

            bOk = gsettings_get(strTheme, "org.mate.background", "picture-filename");

            break;

         case ::user::e_desktop_lxde:

            //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

            break;

         case ::user::e_desktop_xfce:
         {
            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

         }

            //break;

         default:

            output_debug_string(
               "Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
            //return "";

      }

      return strTheme;

   }


   ::os_theme_colors *node::_new_os_theme_colors(string strTheme)
   {

      auto pthemecolors = new ::os_theme_colors;

      GtkStyleContext *pstylecontext = gtk_style_context_new();

      GtkCssProvider *pprovider = gtk_css_provider_get_named(strTheme, nullptr);

      gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);

      {

         GtkWidget *pdialog = gtk_dialog_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pdialog);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_NORMAL,
            GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
            pthemecolors->m_colorBack.u32);

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_NORMAL,
            GTK_STYLE_PROPERTY_COLOR,
            pthemecolors->m_colorFore.u32);

         gtk_widget_destroy(pdialog);

      }

      {

         GtkWidget *pbutton = gtk_button_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pbutton);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_NORMAL,
            GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
            pthemecolors->m_colorFace.u32);

         double dAlpha = pthemecolors->m_colorFace.get_a_rate();

         if (dAlpha < 0.95)
         {

            pthemecolors->m_colorFace.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_PRELIGHT,
            GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
            pthemecolors->m_colorFaceHover.u32);

         dAlpha = pthemecolors->m_colorFaceHover.get_a_rate();

         if (dAlpha < 0.95)
         {

            pthemecolors->m_colorFaceHover.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_ACTIVE,
            GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
            pthemecolors->m_colorFacePress.u32);

         dAlpha = pthemecolors->m_colorFacePress.get_a_rate();

         if (dAlpha < 0.95)
         {

            pthemecolors->m_colorFacePress.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_NORMAL,
            GTK_STYLE_PROPERTY_COLOR,
            pthemecolors->m_colorButton.u32);

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_PRELIGHT,
            GTK_STYLE_PROPERTY_COLOR,
            pthemecolors->m_colorButtonHover.u32);

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_NORMAL,
            GTK_STYLE_PROPERTY_BORDER_COLOR,
            pthemecolors->m_colorBorder.u32);


//         pthemecolors->m_colorBorderHover4 = pthemecolors->m_colorBorderHover;
//
//         pthemecolors->m_colorBorderHover4.blend(pthemecolors->m_colorBack, 0.8);


         gtk_widget_destroy(pbutton);

      }

      {

         GtkWidget *pwidget = gtk_list_box_row_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pwidget);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_SELECTED,
            GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
            pthemecolors->m_colorBorderHover.u32);

         pthemecolors->m_colorBorderPress = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover1 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover1.blend(pthemecolors->m_colorBack, 0.3);

         pthemecolors->m_colorBorderHover2 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover2.blend(pthemecolors->m_colorBack, 0.6);

         pthemecolors->m_colorBorderHover3 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover3.blend(pthemecolors->m_colorBack, 0.9);

         __gtk_style_context_get_color(
            pstylecontext,
            GTK_STATE_FLAG_SELECTED,
            GTK_STYLE_PROPERTY_COLOR,
            pthemecolors->m_colorButtonPress.u32);

         gtk_widget_destroy(pwidget);

      }

      return pthemecolors;

   }


   void node::os_process_user_theme(string strTheme)
   {

      _os_process_user_theme_color(strTheme);

      os_calc_user_dark_mode();

   }


   void node::_os_process_user_theme_color(string strTheme)
   {

      auto pthemecolors = _new_os_theme_colors(strTheme);

      auto pthemecolorsOld = ::user::os_get_theme_colors();

      if (!pthemecolorsOld || memcmp(pthemecolors, pthemecolorsOld, sizeof(::os_theme_colors)))
      {

         ::user::os_set_theme_colors(pthemecolors);

//         auto psubject = System.subject(id_os_user_theme);
//
//         psubject->m_esubject = e_subject_deliver;
//
//         System.process(psubject);

      }
      else
      {

         ::acme::del(pthemecolors);

      }

   }


   bool node::_os_calc_system_dark_mode()
   {

      auto pthemecolors = ::user::os_get_theme_colors();

      if(!pthemecolors)
      {

         string strTheme = _os_get_user_theme();

         pthemecolors = _new_os_theme_colors(strTheme);

         ::user::os_set_theme_colors(pthemecolors);

      }

      auto dLuminance = pthemecolors->m_colorBack.get_luminance();

      return dLuminance < 0.5;

   }


//   void os_calc_dark_mode()
//   {
//
//      bool bDarkMode = _os_calc_dark_mode();
//
//      if(g_bitLastDarkMode != bDarkMode)
//      {
//
//         ::user::set_app_dark_mode(bDarkMode);
//
//         ::user::set_system_dark_mode(bDarkMode);
//
//         g_bitLastDarkMode = bDarkMode;
//
//         System.deliver(id_os_dark_mode);
//
//         x11_kick_idle();
//
//      }
//
//   }

} // namespace user





#ifdef LINUX
static void
log_handler (const gchar   *log_domain,
             GLogLevelFlags log_level,
             const gchar   *message,
             gpointer       user_data)
{
   g_log_default_handler (log_domain, log_level, message, user_data);

   g_on_error_query (nullptr);
}


#endif


::mutex * user_mutex();


::e_status run_runnable(::matter * pobjectTask);


#define GDK_BRANCH_USE_LIST 0


#if GDK_BRANCH_USE_LIST

GSource * g_psourceGdkBranch = nullptr;

routine_list * g_plistGdkBranch = nullptr;

gboolean gdk_callback_run_runnable(gpointer)
{

   synchronous_lock synchronouslock (g_mutexGdkBranch);

   if(g_plistGdkBranch->has_element())
   {

      {

         auto routine = g_plistGdkBranch->pick_head();

         synchronouslock.unlock();

         routine();

      }

      return TRUE;

   }

   return FALSE;

}


GSource * get_gdk_branch_source()
{

   if(!g_mutexGdkBranch)
   {

      g_mutexGdkBranch = new mutex();

   }

   synchronous_lock synchronouslock (g_mutexGdkBranch);

   if(g_psourceGdkBranch)
   {

      return g_psourceGdkBranch;

   }

   g_plistGdkBranch = new routine_list;

   auto idle_source = g_idle_source_new();

   g_source_set_priority(idle_source, G_PRIORITY_DEFAULT);

   g_psourceGdkBranch = idle_source;

   return g_psourceGdkBranch;

}


void gdk_branch(const ::routine & routine)
{

   auto psource = get_gdk_branch_source();

   synchronous_lock synchronouslock (g_mutexGdkBranch);

   bool bStartSourceCallback = g_plistGdkBranch->is_empty();

   g_plistGdkBranch->add_head(routine);

   if(bStartSourceCallback)
   {

      g_source_set_callback(psource, &gdk_callback_run_runnable, nullptr, nullptr);

      g_source_attach(psource, g_main_context_default());

   }

}


#else


gboolean gdk_callback_run_runnable(gpointer pdata)
{

   auto pmatter = (::matter *) pdata;

   try
   {

      pmatter->run();

   }
   catch(...)
   {

   }

   ::release(pmatter);

   return FALSE;

}


void gdk_branch(const ::routine & routine)
{

   ::matter * pmatter = routine.m_p;

   ::add_ref(pmatter);

   synchronous_lock synchronouslock (user_mutex());

   auto psource = g_idle_source_new();

   g_source_set_priority(psource, G_PRIORITY_DEFAULT);

   g_source_set_callback(psource, &gdk_callback_run_runnable, pmatter, nullptr);

   g_source_attach(psource, g_main_context_default());

}


#endif


gboolean x11_source_func(gpointer p)
{

   ::node_gtk::node *pnode = (::node_gtk::node *) p;

   if (!pnode->windowing_message_loop_step())
   {

      return FALSE;

   }

   return TRUE;

}


void x11_add_idle_source(::node_gtk::node * pnode)
{

   gdk_threads_add_idle(&x11_source_func, pnode);

}


bool x11_message_handler(XEvent * pevent);


GdkFilterReturn x11_event_func(GdkXEvent *xevent, GdkEvent *event, gpointer  data)
{

   XEvent * pevent = (XEvent *) xevent;

   ::node_gtk::node * pnode = (::node_gtk::node *) data;

   auto pwindowing = pnode->windowing();

   pwindowing->_message_handler(pevent);

   return GDK_FILTER_CONTINUE;

}


// This seems not to work with "foreign" windows
// (X11 windows not created with Gdk)
void x11_add_filter()
{

   // This seems not to work with "foreign" windows
   // (X11 windows not created with Gdk)
   gdk_window_add_filter(nullptr, &x11_event_func, nullptr);

}


int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
{

   gboolean ret;

   GError * error = NULL;

   g_type_init();

   ret = g_app_info_launch_default_for_uri(pszUri, NULL, &error);

   if(ret)
   {

      return true;

   }

   if(pszError != nullptr)
   {

      strncpy(pszError, error->message, iBufferSize);

   }

   return 0;

}


const char * linux_g_direct_get_file_icon_path(const char * pszPath, int iSize)
{

   GFile * pfile = g_file_new_for_path (pszPath);

   if(pfile == nullptr)
   {

      return nullptr;

   }

   GError * perror = nullptr;

   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);

   if(pfileinfo == nullptr)
   {

      return nullptr;

   }

   /* you'd have to use g_loadable_icon_load to get the actual icon */
   GIcon * picon = g_file_info_get_icon (pfileinfo);

   if(picon == nullptr)
   {

      return nullptr;

   }

   if(G_IS_FILE_ICON(G_OBJECT(picon)))
   {

      GFileIcon * pfileicon = G_FILE_ICON(G_OBJECT(picon));

      if(pfileicon == nullptr)
      {

         return nullptr;

      }

      GFile * pfileIcon = g_file_icon_get_file(pfileicon);

      if(pfileIcon == nullptr)
      {

         return nullptr;

      }

      char * psz = strdup(g_file_get_path(pfileIcon));

      return psz;

   }
   else if(G_IS_THEMED_ICON(G_OBJECT(picon)))
   {

      GtkIconInfo *pGtkIconInfo;

      GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_default();

      if(pGtkIconTheme == nullptr)
      {

         return nullptr;

      }

      pGtkIconInfo = gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon,(gint)iSize,GTK_ICON_LOOKUP_USE_BUILTIN);

      if(pGtkIconInfo == nullptr)
      {

         return nullptr;

      }

      const char * point = gtk_icon_info_get_filename(pGtkIconInfo);

      char * psz = nullptr;

      if(point != nullptr)
      {

         psz = strdup(point);

      }

      return psz;

   }

   return nullptr;

}


const char * linux_g_direct_get_file_content_type(const char * pszPath)
{

   GFile * pfile = g_file_new_for_path (pszPath);

   if(pfile == nullptr)
   {

      return nullptr;

   }

   GError * perror = nullptr;

   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);

   if(pfileinfo == nullptr)
   {

      return nullptr;

   }

   const char * pszContentType = g_file_info_get_content_type (pfileinfo);

   const char * point = nullptr;

   if(pszContentType != nullptr)
   {

      point = strdup(pszContentType);

   }

   return point;

}



