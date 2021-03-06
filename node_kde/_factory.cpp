#include "framework.h"
#include "_node_kde.h"
#include "monitor.h"
//#include "display.h"
#include "windowing.h"


__FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_kde_factory(::factory::factory * pfactory)
{

   windowing_xcb_factory(pfactory);

   pfactory->add_factory_item < ::node_kde::display, ::windowing::display > ();

   pfactory->add_factory_item < ::node_kde::node, ::acme::node > ();
   pfactory->add_factory_item < ::node_kde::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < ::node_kde::copydesk, ::user::copydesk > ();
   pfactory->add_factory_item < ::node_kde::notify_icon, ::user::notify_icon > ();
   pfactory->add_factory_item < ::node_kde::appindicator, ::aura::posix::appindicator >();

   pfactory->add_factory_item < ::node_kde::windowing, ::windowing::windowing >();


}



