#include "error.h"
#include "tag.h"
#include "parserutils.h"

/*
 - do we need tag() / how to save the XMLNS's (ie copy string or enumerated type) ?
 - std::pair / templates on all platforms ?
 - index based lookup offers short code as well as marking a clear
   relashionship between string value and error code. It also ease
   adding/modifying/removing values and is much less error prone.
*/

namespace gloox
{

  /* "generic" error values */
  static const char * genericErrorValues[] = {
    "auth",   
    "cancel", 
    "modify", 
  };

  /* "first level" error values */
  static const char * errorValues[] = {
     "bad-request",             
     "item-not-found",          
     "forbidden",               
     "feature-not-implemented", 
     "not-acceptable",          
     "not-allowed",             
     "conflict",                
     "payment-required",        
     "registration-required",   
     "service-unavailable",      
  };

  /* "second level" error values */
  static const char * subErrorValues[] = {
     "closed-node",                    
     "configuration-required",         
     "invalid-jid",                    
     "invalid-options",                
     "invalid-payload",                
     "invalid-subid",                  
     "item-forbidden",                 
     "item-required",                  
     "jid-required",                   
     "max-nodes-exceeded",             
     "nodeid-required",                
     "not-in-roster-group",            
     "not-subscribed",                 
     "payload-too-big",                
     "payload-required",               
     "pending-subscription",           
     "presence-subscription-required", 
     "subid-required",                 
     "unsupported",                    
     "unsupported-access-model",       
  };

  /* feature values */
  static const char * featureValues[] = {
     "collections",
     "config-node",
     "create-and-configure",
     "create-nodes",             
     "delete-any",               
     "delete-nodes",             
     "get-pending",              
     "instant-nodes",            
     "item-ids",                 
     "leased-subscription",      
     "manage-subscriptions",     
     "meta-data",                
     "modify-affiliations",      
     "multi-collection",         
     "multi-subscribe",          
     "outcast-affiliation",      
     "persistent-items",         
     "presence-notifications",   
     "publish",                  
     "publisher-affiliation",    
     "purge-nodes",              
     "retract-items",            
     "retrieve-affiliations",    
     "retrieve-default",         
     "retrieve-items",           
     "retrieve-subscriptions",   
     "subscribe",                
     "subscription-options",     
     "subscription-notifications",
  };

  static const int nbErrors = sizeof(errorValues)/sizeof(LookupPair);
  static const int nbFeatures = sizeof(featureValues)/sizeof(LookupPair);
  static const int nbSubErrors = sizeof(subErrorValues)/sizeof(LookupPair);
  static const int nbGenericErrors = sizeof(genericErrorValues)/sizeof(LookupPair);

  Error::Error( const Tag * error )
    : StanzaExtension( ExtError ), m_genericType( GenericErrorNone ),
      m_type( ErrorNone ), m_subType( SubErrorNone ), m_feature( FeatureNone )
  {
    const std::string& genType = error->findAttribute( "type" );
    m_genericType = (GenericErrorType)lookup( genType, genericErrorValues, nbGenericErrors );
    Tag::TagList::const_iterator it = error->children().begin();
    m_type = (ErrorType)lookup( (*it)->name(), errorValues, nbErrors );
    m_xmlns1 = (*it)->findAttribute( "xmlns" );
    if( ++it != error->children().end() )
    {
      m_subType = (SubErrorType)lookup( (*it)->name(), subErrorValues, nbSubErrors );
      m_xmlns2 = (*it)->findAttribute( "xmlns" );
      const std::string& feat = (*it)->findAttribute( "feature" );
      m_feature = (FeatureType)lookup( feat, featureValues, nbFeatures );
    }
  }
/*
  Error& Error::operator=( const Tag * error)
  {
    //setValues( error );
    const std::string& genType = error->findAttribute( "type" );
    if( genType.empty() )
    {
      printf( "error: no basic error type\n" );
    }
    int i = lookup( genType, genericErrorValues, nbGenericErrors );
    if( i == nbGenericErrors )
      return;
    m_genericType = genericErrorValues[i].second;
    Tag::TagList::const_iterator it = error->children().begin();
    i = lookup( (*it)->name(), errorValues, nbErrors );
    if( i == nbErrors )
      return;
    m_type = errorValues[i].second;
    m_xmlns1 = (*it)->findAttribute( "xmlns" );
    if( ++it != error->children().end() )
    {
      i = lookup( (*it)->name(), subErrorValues, nbSubErrors );
      if( i == nbSubErrors )
        return;
      m_subType = subErrorValues[i].second;
      m_xmlns2 = (*it)->findAttribute( "xmlns" );
      const std::string& feat = (*it)->findAttribute( "feature" );
      if( feat.empty() )
        return;
      i = lookup( feat, featureValues, nbFeatures );
      if( i == nbFeatures )
        return;
      m_feature = featureValues[i].second;
    }
    return this;
  }

  void Error::setValues( const * tag )
  {
  }
*/
  Tag * Error::tag() const
  {
    if( m_genericType == GenericErrorNone || m_type == ErrorNone )
      return 0;
    Tag * error = new Tag( "error" );
    error->addAttribute( "type", lookup( m_genericType, genericErrorValues, nbGenericErrors ) );
    new Tag( error, lookup( m_type, errorValues, nbErrors ), "xmlns", m_xmlns1 );
    if( m_subType != SubErrorNone )
    {
      Tag * tag = new Tag( error, lookup( m_subType, subErrorValues, nbSubErrors ), "xmlns", m_xmlns2 );
      if( m_subType == Unsupported )
        tag->addAttribute( "feature", m_feature );      
    }
    return error;
  }

}
