#ifndef APPLINKRPC_DRIVERDISTRACTIONSTATEMARSHALLER_INCLUDE
#define APPLINKRPC_DRIVERDISTRACTIONSTATEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "PerfectHashTable.h"

#include "../include/JSONHandler/ALRPCObjects/DriverDistractionState.h"


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

//! marshalling class for DriverDistractionState

  class DriverDistractionStateMarshaller
  {
  public:
  
    static std::string toName(const DriverDistractionState& e) 	{ return getName(e.mInternal) ?: ""; }
  
    static bool fromName(DriverDistractionState& e,const std::string& s)
    { 
      return (e.mInternal=getIndex(s.c_str()))!=DriverDistractionState::INVALID_ENUM;
    }
  
    static bool checkIntegrity(DriverDistractionState& e)		{ return e.mInternal!=DriverDistractionState::INVALID_ENUM; } 
    static bool checkIntegrityConst(const DriverDistractionState& e)	{ return e.mInternal!=DriverDistractionState::INVALID_ENUM; } 
  
    static bool fromString(const std::string& s,DriverDistractionState& e);
    static const std::string toString(const DriverDistractionState& e);
  
    static bool fromJSON(const Json::Value& s,DriverDistractionState& e);
    static Json::Value toJSON(const DriverDistractionState& e);
  
    static const char* getName(DriverDistractionState::DriverDistractionStateInternal e)
    {
       return (e>=0 && e<2) ? mHashTable[e].name : NULL;
    }
  
    static const DriverDistractionState::DriverDistractionStateInternal getIndex(const char* s);
  
    static const PerfectHashTable mHashTable[2];
  };
  
}

#endif
