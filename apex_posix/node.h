//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace apex
{


   namespace posix
   {


      class CLASS_DECL_ACME node :
         virtual public ::apex::node,
         virtual public ::acme::posix::node
      {
      public:


         node();
         virtual ~node();


         //virtual int node_init_check(int * pi, char *** ppz) override;


      };


   } // namespace posix


} // namespace apex



