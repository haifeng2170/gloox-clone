/*
  Copyright (c) 2004-2005 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warrenty.
*/



#ifndef PRESENCEHANDLER_H__
#define PRESENCEHANDLER_H__

#include "stanza.h"

namespace gloox
{

  /**
   * A virtual interface.
   * Derived classes can be registered as IqHandlers with the Client.
   * Upon an incoming Presence packet @ref handlePresence() will be called.
   * @author Jakob Schroeter <js@camaya.net>
   */
  class PresenceHandler
  {
    public:
      /**
       * Reimplement this function if you want to be updated on
       * incoming presence notifications.
       * @param stanza The complete stanza.
       */
      virtual void handlePresence( Stanza *stanza ) = 0;
  };

};

#endif // PRESENCEHANDLER_H__
