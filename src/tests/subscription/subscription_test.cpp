#include "../../tag.h"
#include "../../subscription.h"
#include "../../stanza.h"
#include "../../jid.h"
using namespace gloox;

#include <stdio.h>
#include <locale.h>
#include <string>

int main( int /*argc*/, char** /*argv*/ )
{
  int fail = 0;
  std::string name;
  Tag *s10n = new Tag( "presence" );
  s10n->addAttribute( "from", "me@example.net/gloox" );
  s10n->addAttribute( "to", "you@example.net/gloox" );
  new Tag( s10n, "status", "the status" );

  Subscription *i = 0;

#warning FIXME fix the following 4 tests. how to test private functions, ctors, etc?
//   // -------
//   name = "parse Subscription subscribe";
//   s10n->addAttribute( "type", "subscribe" );
//   i = new Subscription( s10n );
//   if( i->subtype() != Subscription::Subscribe
//       || !i->hasAttribute( "type", "subscribe" )
//       || !i->hasAttribute( "to", "you@example.net/gloox" )
//       || !i->hasAttribute( "from", "me@example.net/gloox" )
//       || i->from().full() != "me@example.net/gloox" || i->to().full() != "you@example.net/gloox"
//       || i->status() != "the status" )
//   {
//     ++fail;
//     printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
//   }
//   delete i;
//   i = 0;
//
//   // -------
//   name = "parse Subscription subscribed";
//   s10n->addAttribute( "type", "subscribed" );
//   i = new Subscription( s10n );
//   if( i->subtype() != Subscription::Subscribed || !i->hasAttribute( "type", "subscribed" )
//       || !i->hasAttribute( "to", "you@example.net/gloox" )
//       || !i->hasAttribute( "from", "me@example.net/gloox" )
//       || i->from().full() != "me@example.net/gloox" || i->to().full() != "you@example.net/gloox"
//       || i->status() != "the status" )
//   {
//     ++fail;
//     printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
//   }
//   delete i;
//   i = 0;
//
//   // -------
//   name = "parse Subscription unsubscribe";
//   s10n->addAttribute( "type", "unsubscribe" );
//   i = new Subscription( s10n );
//   if( i->subtype() != Subscription::Unsubscribe || !i->hasAttribute( "type", "unsubscribe" )
//       || !i->hasAttribute( "to", "you@example.net/gloox" )
//       || !i->hasAttribute( "from", "me@example.net/gloox" )
//       || i->from().full() != "me@example.net/gloox" || i->to().full() != "you@example.net/gloox"
//       || i->status() != "the status" )
//   {
//     ++fail;
//     printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
//   }
//   delete i;
//   i = 0;
//
//   // -------
//   name = "parse Subscription unsubscribed";
//   s10n->addAttribute( "type", "unsubscribed" );
//   i = new Subscription( s10n );
//   if( i->subtype() != Subscription::Unsubscribed || !i->hasAttribute( "type", "unsubscribed" )
//       || !i->hasAttribute( "to", "you@example.net/gloox" )
//       || !i->hasAttribute( "from", "me@example.net/gloox" )
//       || i->from().full() != "me@example.net/gloox" || i->to().full() != "you@example.net/gloox"
//       || i->status() != "the status" )
//   {
//     ++fail;
//     printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
//   }
//   delete i;
//   i = 0;

  // -------
  name = "new simple Subscription subscribe";
  i = new Subscription( Subscription::Subscribe, JID( "xyz@example.org/blah" ), "the status",
                        "the xmllang", JID( "foo@bar.com" ) );
  if( !i->hasAttribute( "type", "subscribe" )
      || !i->hasAttribute( "to", "xyz@example.org/blah" ) || !i->hasAttribute( "from", "foo@bar.com" )
      || !i->hasChildWithCData( "status", "the status" )
      || !i->hasChild( "status", "xml:lang", "the xmllang" ) )
  {
    ++fail;
    printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
  }
  delete i;
  i = 0;

  // -------
  name = "new simple Subscription subscribed";
  i = new Subscription( Subscription::Subscribed, JID( "xyz@example.org/blah" ), "the status",
                        "the xmllang", JID( "foo@bar.com" ) );
  if( !i->hasAttribute( "type", "subscribed" )
      || !i->hasAttribute( "to", "xyz@example.org/blah" ) || !i->hasAttribute( "from", "foo@bar.com" )
      || !i->hasChildWithCData( "status", "the status" )
      || !i->hasChild( "status", "xml:lang", "the xmllang" ) )
  {
    ++fail;
    printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
  }
  delete i;
  i = 0;

  // -------
  name = "new simple Subscription unsubscribe";
  i = new Subscription( Subscription::Unsubscribe, JID( "xyz@example.org/blah" ), "the status",
                        "the xmllang", JID( "foo@bar.com" ) );
  if( !i->hasAttribute( "type", "unsubscribe" )
      || !i->hasAttribute( "to", "xyz@example.org/blah" ) || !i->hasAttribute( "from", "foo@bar.com" )
      || !i->hasChildWithCData( "status", "the status" )
      || !i->hasChild( "status", "xml:lang", "the xmllang" ) )
  {
    ++fail;
    printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
  }
  delete i;
  i = 0;

  // -------
  name = "new simple Subscription unsubscribed";
  i = new Subscription( Subscription::Unsubscribed, JID( "xyz@example.org/blah" ), "the status",
                        "the xmllang", JID( "foo@bar.com" ) );
  if( !i->hasAttribute( "type", "unsubscribed" )
      || !i->hasAttribute( "to", "xyz@example.org/blah" ) || !i->hasAttribute( "from", "foo@bar.com" )
      || !i->hasChildWithCData( "status", "the status" )
      || !i->hasChild( "status", "xml:lang", "the xmllang" ) )
  {
    ++fail;
    printf( "test '%s' failed: %s\n", name.c_str(), i->xml().c_str() );
  }
  delete i;
  i = 0;




















  delete s10n;
  s10n = 0;

  if( fail == 0 )
  {
    printf( "Subscription: all tests passed\n" );
    return 0;
  }
  else
  {
    printf( "Subscription: %d test(s) failed\n", fail );
    return 1;
  }

}
