#pragma once


namespace apex_posix
{


   class CLASS_DECL_APEX os_context :
      virtual public ::os_context
   {
   public:


      os_context();
      ~os_context() override;


      bool is_alias(const char* path) override;
      
      
      virtual int get_pid() override;


   };


} // namespace apex_posix



