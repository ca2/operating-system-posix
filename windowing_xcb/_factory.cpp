#include "framework.h"
#include "text_composition_client.h"
#include "keyboard.h"


__FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::windowing_xcb::buffer, ::graphics::graphics > ();

   pfactory->add_factory_item < ::windowing_xcb::display, ::windowing::display > ();
   pfactory->add_factory_item < ::windowing_xcb::window, ::windowing::window > ();
   pfactory->add_factory_item < ::windowing_xcb::windowing, ::windowing::windowing > ();
   pfactory->add_factory_item < ::windowing_xcb::text_composition_client, ::user::text_composition_client > ();

   pfactory->add_factory_item < ::windowing_xcb::icon, ::windowing::icon > ();
   pfactory->add_factory_item < ::windowing_xcb::cursor, ::windowing::cursor > ();
   pfactory->add_factory_item < ::windowing_xcb::keyboard, ::windowing::keyboard > ();

}



