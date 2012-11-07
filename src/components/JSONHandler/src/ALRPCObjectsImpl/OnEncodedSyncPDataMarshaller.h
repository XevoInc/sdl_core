#ifndef APPLINKRPC_ONENCODEDSYNCPDATAMARSHALLER_INCLUDE
#define APPLINKRPC_ONENCODEDSYNCPDATAMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/ALRPCObjects/OnEncodedSyncPData.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Wed Nov  7 13:10:41 2012
  source stamp	Thu Oct 25 06:49:27 2012
  author	robok0der
*/

namespace AppLinkRPC
{

  struct OnEncodedSyncPDataMarshaller
  {
    static bool checkIntegrity(OnEncodedSyncPData& e);
    static bool checkIntegrityConst(const OnEncodedSyncPData& e);
  
    static bool fromString(const std::string& s,OnEncodedSyncPData& e);
    static const std::string toString(const OnEncodedSyncPData& e);
  
    static bool fromJSON(const Json::Value& s,OnEncodedSyncPData& e);
    static Json::Value toJSON(const OnEncodedSyncPData& e);
  };
}

#endif
