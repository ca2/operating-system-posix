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


      node();
      ~node() override;


      void defer_notify_startup_complete() override;

      void start_node() override;

      void initialize(::object * pobject) override;

      bool should_launch_on_node(::topic * psubject) override;

      bool launch_on_node(::topic * psubject) override;

      //int os_launch_uri(const ::string & strUri, char * pszError = nullptr, int iBufferSize = 0) override;

      void handle(::topic * psubject, ::context * pcontext) override;


   };


} // namespace node_gnome




