//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace node_gnome
{


   class CLASS_DECL_ACME node :
      virtual public ::node_gtk::node
   {
   public:


      //gpointer m_pGtkSettingsDefault;


      node();
      virtual ~node();


      virtual ::os_theme_colors * _new_os_theme_colors(string strTheme);

      virtual int node_init_check(int * pi, char *** ppz) override;

      virtual void defer_notify_startup_complete() override;

      virtual ::e_status start_node() override;

      virtual ::e_status initialize(::object * pobject) override;

      void fetch_user_color() override;

      virtual string os_get_user_theme() override;

      virtual string _os_get_user_theme();

      virtual ::e_status system_main() override;

      virtual bool os_set_user_theme(const string & strUserTheme) override;

      virtual void os_process_user_theme(string strTheme) override;

      virtual void enable_wallpaper_change_notification() override;

      string get_file_icon_path(const ::string & strPath, int iSize) override;

      string get_file_content_type(const ::string & strPath) override;

      virtual bool set_wallpaper(index iScreen, string strLocalImagePath) override;

      virtual string get_wallpaper(index iScreen) override;

      using ::aura::node::node_fork;

      virtual bool windowing_message_loop_step();

      virtual ::e_status node_branch(const ::routine & routine);

      //virtual void node_post_quit() override;

      //virtual void on_subject(::promise::subject * psubject, ::context * pcontext) override;

      //virtual void _on_change_os_user_theme(string strTheme);

      virtual void _os_process_user_theme_color(string strTheme);

      //virtual ::node_linux::appindicator * appindicator_allocate() override;

      //virtual void appindicator_destroy(::linux::appindicator * pappindicator) override;

      //virtual void enum_display_monitors(::aura::session * psession) override;

      //virtual bool _os_calc_system_dark_mode() override;

      //virtual void os_post_quit() override;

      bool should_launch_on_node(::subject * psubject) override;

      bool launch_on_node(::subject * psubject) override;

      int os_launch_uri(const ::string & strUri, char * pszError = nullptr, int iBufferSize = 0) override;

      void handle(::subject * psubject, ::context * pcontext) override;

   };


} // namespace node_gnome




