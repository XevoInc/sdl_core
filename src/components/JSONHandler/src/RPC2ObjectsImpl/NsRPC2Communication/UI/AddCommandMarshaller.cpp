//
// Copyright (c) 2013, Ford Motor Company
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following
// disclaimer in the documentation and/or other materials provided with the
// distribution.
//
// Neither the name of the Ford Motor Company nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include "../src/../include/JSONHandler/RPC2Objects/NsRPC2Communication/UI/AddCommand.h"
#include "../src/SDLRPCObjectsImpl/V2/MenuParamsMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V2/ImageMarshaller.h"
#include "../src/SDLRPCObjectsImpl/V2/ResultMarshaller.h"
#include "../src/../src/RPC2ObjectsImpl//NsRPC2Communication/UI/AddCommandMarshaller.h"

/*
  interface	NsRPC2Communication::UI
  version	1.2
  generated at	Thu Jan 24 06:41:15 2013
  source stamp	Wed Jan 23 13:56:28 2013
  author	RC
*/

using namespace NsRPC2Communication::UI;

bool AddCommandMarshaller::checkIntegrity(AddCommand& s)
{
  return checkIntegrityConst(s);
}


bool AddCommandMarshaller::fromString(const std::string& s,AddCommand& e)
{
  try
  {
    Json::Reader reader;
    Json::Value json;
    if(!reader.parse(s,json,false))  return false;
    if(!fromJSON(json,e))  return false;
  }
  catch(...)
  {
    return false;
  }
  return true;
}


const std::string AddCommandMarshaller::toString(const AddCommand& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool AddCommandMarshaller::checkIntegrityConst(const AddCommand& s)
{
  if(s.cmdId>2000000000)  return false;

  if(!NsSmartDeviceLinkRPCV2::MenuParamsMarshaller::checkIntegrityConst(s.menuParams))  return false;

  if(s.cmdIcon && (!NsSmartDeviceLinkRPCV2::ImageMarshaller::checkIntegrityConst(s.cmdIcon[0])))  return false;

  return true;
}


Json::Value AddCommandMarshaller::toJSON(const AddCommand& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["jsonrpc"]=Json::Value("2.0");
  json["method"]=Json::Value("UI.AddCommand");

  json["id"]=Json::Value(e.getId());
  json["params"]=Json::Value(Json::objectValue);
  json["params"]["cmdId"]=Json::Value(e.cmdId);;
  json["params"]["menuParams"]=NsSmartDeviceLinkRPCV2::MenuParamsMarshaller::toJSON(e.menuParams);;
  if(e.cmdIcon)
    json["params"]["cmdIcon"]=NsSmartDeviceLinkRPCV2::ImageMarshaller::toJSON(e.cmdIcon[0]);;
  json["params"]["appId"]=Json::Value(e.appId);;
  return json;
}


bool AddCommandMarshaller::fromJSON(const Json::Value& json,AddCommand& c)
{
  try
  {
    if(!json.isObject())  return false;
    if(!json.isMember("jsonrpc") || !json["jsonrpc"].isString() || json["jsonrpc"].asString().compare("2.0"))  return false;
    if(!json.isMember("method") || !json["method"].isString() || json["method"].asString().compare("UI.AddCommand"))  return false;
    if(!json.isMember("id") || !json["id"].isInt()) return false;
    c.setId(json["id"].asInt());

    if(!json.isMember("params")) return false;

    Json::Value js=json["params"];
    if(!js.isObject())  return false;
    if(!js.isMember("cmdId") || !js["cmdId"].isInt())  return false;
    c.cmdId=js["cmdId"].asInt();
    if(c.cmdId>2000000000)  return false;

    if(!js.isMember("menuParams") || !NsSmartDeviceLinkRPCV2::MenuParamsMarshaller::fromJSON(js["menuParams"],c.menuParams))  return false;

    if(c.cmdIcon)  delete c.cmdIcon;
    c.cmdIcon=0;
    if(js.isMember("cmdIcon"))
    {
      c.cmdIcon=new NsSmartDeviceLinkRPCV2::Image();
      if(!NsSmartDeviceLinkRPCV2::ImageMarshaller::fromJSON(js["cmdIcon"],c.cmdIcon[0]))  return false;
    }

    if(!js.isMember("appId") || !js["appId"].isInt())  return false;
    c.appId=js["appId"].asInt();
    
  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}
