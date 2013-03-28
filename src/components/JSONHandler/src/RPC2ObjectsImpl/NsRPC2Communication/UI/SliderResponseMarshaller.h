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

#ifndef NSRPC2COMMUNICATION_UI_SLIDERRESPONSEMARSHALLER_INCLUDE
#define NSRPC2COMMUNICATION_UI_SLIDERRESPONSEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../src/../include/JSONHandler/RPC2Objects/NsRPC2Communication/UI/SliderResponse.h"

namespace NsRPC2Communication
{
  namespace UI
  {

    struct SliderResponseMarshaller
    {
      static bool checkIntegrity(SliderResponse& e);
      static bool checkIntegrityConst(const SliderResponse& e);
    
      static bool fromString(const std::string& s,SliderResponse& e);
      static const std::string toString(const SliderResponse& e);
    
      static bool fromJSON(const Json::Value& s,SliderResponse& e);
      static Json::Value toJSON(const SliderResponse& e);
    };
  }
}

#endif
