/*
  Copyright (c) 2007 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warranty.
*/

#include "chatstate.h"
#include "tag.h"
#include "util.h"

namespace gloox
{

  /* chat state type values */
  static const char* stateValues [] = {
    "active",
    "composing",
    "paused",
    "inactive",
    "gone"
  };

  static inline ChatStateType chatStateType( const std::string& type )
  {
    return (ChatStateType)util::lookup2( type, stateValues );
  }

  ChatState::ChatState( const Tag* tag )
    : StanzaExtension( ExtChatState ),
      m_state( chatStateType( tag->name() ) )
  {
  }

  Tag* ChatState::tag() const
  {
    if( m_state == ChatStateInvalid )
      return 0;

    return new Tag( util::lookup2( m_state, stateValues ), XMLNS, XMLNS_CHAT_STATES );
  }

  const std::string ChatState::filterString() const
  {
    std::string str = "/message/active[@xmlns='";
    str += XMLNS_CHAT_STATES;
    str += "']|/message/composing[@xmlns='";
    str += XMLNS_CHAT_STATES;
    str += "']|/message/paused[@xmlns='";
    str += XMLNS_CHAT_STATES;
    str += "']|/message/inactive[@xmlns='";
    str += XMLNS_CHAT_STATES;
    str += "']|/message/gone[@xmlns='";
    str += XMLNS_CHAT_STATES;
    str += "']";
    return str;
  }

}
