#pragma once


namespace posix
{


   class CLASS_DECL_ACME pipe :
      virtual public ::operating_system::pipe
   {
   public:


      __creatable_from_library(pipe, ::operating_system::pipe, "acme_posix_node");


      char *               m_pchBuf;
      string               m_strRead;

      i32                  m_fd[2];


      pipe();
       ~pipe() override;


      virtual bool create(bool bBlock = true, bool bInherit = false);


      virtual bool not_inherit_read();
      virtual bool not_inherit_write();

      virtual bool write(const char * psz);
      virtual string read();
      virtual string one_pass_read();



   };


} // namespace posix



