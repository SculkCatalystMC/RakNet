/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#pragma once

#include "TestInterface.h"

#include "RakString.h"

#include "BitStream.h"
#include "CommonFunctions.h"
#include "DebugTools.h"
#include "GetTime.h"
#include "MessageIdentifiers.h"
#include "RakNetTime.h"
#include "RakPeer.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include "RakTimer.h"
#include "TestHelpers.h"

using namespace RakNet;
class PingTestsTest : public TestInterface {
public:
    PingTestsTest(void);
    ~PingTestsTest(void);
    int RunTest(
        DataStructures::List<RakString> params,
        bool                            isVerbose,
        bool                            noPauses
    ); // should return 0 if no error, or the error number
    RakString GetTestName();
    RakString ErrorCodeToString(int errorCode);
    void      DestroyPeers();
    int       TestAverageValue(int averagePing, int line, bool noPauses, bool isVerbose);

private:
    DataStructures::List<RakPeerInterface*> destroyList;
};
