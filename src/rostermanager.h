/*
  Copyright (c) 2004-2005 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warrenty.
*/


#ifndef ROSTERMANAGER_H__
#define ROSTERMANAGER_H__

#include "subscriptionhandler.h"
#include "rosterlistener.h"

#include <map>
#include <string>
#include <list>

namespace gloox
{

  class ClientBase;
  class IqHandler;
  class PresenceHandler;
  class Stanza;

  /**
   * This class implements Jabber/XMPP roster handling in the @b jabber:iq:roster namespace.
   * It takes care of changing presence, subscriptions, etc.
   * You can modify any number of RosterItems within the Roster at any time. These changes must be
   * synchronized with the server by calling @ref synchronize(). Note that incoming Roster pushes
   * initiated by other resources may overwrite changed values.
   * @author Jakob Schroeter <js@camaya.net>
   */
  class RosterManager : public IqHandler, PresenceHandler, SubscriptionHandler
  {
    public:
      /**
       * A list of RosterItems.
       */
      typedef std::list<RosterItem> RosterItemList;

      /**
       * Constructor.
       * Creates a new RosterManager.
       * @param parent The @c Client which is used for communication.
       */
      RosterManager( ClientBase *parent );

      /**
       * Virtual destructor.
       */
      virtual ~RosterManager();

      /**
       * This function does the initial filling of the roster with
       * the current server-side roster.
       */
      void fill();

      /**
       * This function returns the roster.
       * @return Returns a map of JIDs with their current presence.
       */
      RosterListener::Roster* roster();

      /**
       * Use this function to subscribe to a new JID. The contact is added to the roster automatically
       * (by compliant servers, as required by RFC 3921).
       * @param jid The address to subscribe to.
       * @param name The displayed name of the contact.
       * @param groups A list of groups the contact belongs to.
       */
      void subscribe( const std::string& jid, const std::string& name, StringList& groups );

      /**
       * Synchronizes locally modified RosterItems back to the server.
       */
      void synchronize();

      /**
       * Use this function to add a contact to the roster. No subscription request is sent.
       * @note Use @ref unsubscribe() to remove an item from the roster.
       * @param jid The JID to add.
       * @param name The displayed name of the contact.
       * @param groups A list of groups the contact belongs to.
       */
      void add( const std::string& jid, const std::string& name, StringList& groups );

      /**
       * Use this function to unsubscribe from a JID in the roster.
       * @param jid The address to unsubscribe from.
       * @param remove Whether the contact should also be removed from the roster.
       */
      void unsubscribe( const std::string& jid, bool remove );

      /**
       * Register @c rl as object that receives updates on roster operations.
       * @param rl The object that receives roster updates.
       */
      void registerRosterListener( RosterListener *rl );

      /**
       * Complementary function to @ref registerRosterListener. Removes the current RosterListener.
       * Roster events will not be delivered anywhere.
       */
      void removeRosterListener();

      // reimplemented from IqHandler.
      virtual bool handleIq( Stanza *stanza );

      // reimplemented from IqHandler.
      virtual bool handleIqID( Stanza *stanza, int context ) { return false; };

      // reimplemented from PresenceHandler.
      virtual void handlePresence( Stanza *stanza );

      // reimplemented from SubscriptionHandler.
      virtual void handleSubscription( Stanza *stanza );

    private:
      void add( const std::string& jid, const std::string& name,
                StringList& groups, const std::string& sub, bool ask );
      void extractItems( Tag *tag, bool isPush );

      RosterListener *m_rosterListener;
      RosterListener::Roster m_roster;
      ClientBase *m_parent;

  };

};

#endif // ROSTER_H__
