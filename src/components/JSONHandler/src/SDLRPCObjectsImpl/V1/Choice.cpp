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

#include "../include/JSONHandler/SDLRPCObjects/V1/Choice.h"
#include "ChoiceMarshaller.h"

/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Thu Jan 24 06:36:21 2013
  source stamp	Thu Jan 24 06:35:34 2013
  author	RC
*/



using namespace NsSmartDeviceLinkRPC;

Choice::Choice(const Choice& c)
{
  *this=c;
}


bool Choice::checkIntegrity(void)
{
  return ChoiceMarshaller::checkIntegrity(*this);
}


Choice::Choice(void)
{
}



bool Choice::set_choiceID(unsigned int choiceID_)
{
  if(choiceID_>65535)  return false;
  choiceID=choiceID_;
  return true;
}

bool Choice::set_menuName(const std::string& menuName_)
{
  if(menuName_.length()>500)  return false;
  menuName=menuName_;
  return true;
}

bool Choice::set_vrCommands(const std::vector<std::string>& vrCommands_)
{
  unsigned int i=vrCommands_.size();
  if(i>100 || i<1)  return false;
  while(i--)
  {
    if(vrCommands_[i].length()>99)  return false;
  }
  vrCommands=vrCommands_;
  return true;
}




unsigned int Choice::get_choiceID(void) const
{
  return choiceID;
}


const std::string& Choice::get_menuName(void) const 
{
  return menuName;
}


const std::vector<std::string>& Choice::get_vrCommands(void) const 
{
  return vrCommands;
}


