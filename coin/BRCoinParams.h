//
//  BRCoinParams.h
//
//  Created by Aaron Voisine on 1/10/18.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRCoinParams_h
#define BRCoinParams_h

#include "BRChainParams.h"
#include "BRPeer.h"
#include "BRInt.h"

#define NPOW_TARGET_TIMESPAN (24*60*60)        // Coin 1 day
#define NPOW_TARGEY_SPACING (7*60)
#define COIN_BLOCK_DIFFICULTY_INTERVAL (NPOW_TARGET_TIMESPAN/NPOW_TARGEY_SPACING)

static const char *BRCoinDNSSeeds[] = {
        "seed1.bitrad.io", "seed2.bitrad.io", "seed3.bitrad.io", "104.238.140.68", "199.255.137.77"
        , NULL
};

static const char *BRCoinTestNetDNSSeeds[] = {
        NULL
};

static const BRCheckPoint BRCoinTestNetCheckpoints[] = {
        {       1, uint256("00000385558ec1b9af7f939e1626a3116b9fb988c86c2f915e6451e8efcd0521"), 1517054400, 0x1d00ffff},
        {   20040, uint256("03a92984c2deba55ac8f9e8194b1bc745fbad9f7a0f3ed94ebb8c372935bed9c"), 1517054400, 0x1d00ffff},   // tx 40878
        {   93286, uint256("dc68d97761ceac8c177a81487569bfe92b720f513fbbf5c2184988f1d74c5061"), 1517054400, 0x1d00ffff} // tx 227380
};


// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRCoinCheckpoints[] = {
        {       1, uint256("00000b51f1ecd9a6244b59a8988370e4eaf5d2cd39521426c81352dee7763b01"), 1558155952, 0x1e0fffff }
};

static int BRCoinVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
       return 1;
}

static int BRCoinTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1; // XXX skip testnet difficulty check for now
}

static const BRChainParams BRCoinParams = {
    BRCoinDNSSeeds,
    33455,                // standardPort
    0xe43d1ad3,          // magicNumber
    0, // services
    BRCoinVerifyDifficulty,
    BRCoinCheckpoints,
    sizeof(BRCoinCheckpoints)/sizeof(*BRCoinCheckpoints)
};

static const BRChainParams BRCoinTestNetParams = {
    BRCoinTestNetDNSSeeds,
    55004,               // standardPort
    0x99d19e87,          // magicNumber
    0, // services
    BRCoinTestNetVerifyDifficulty,
    BRCoinTestNetCheckpoints,
    sizeof(BRCoinTestNetCheckpoints)/sizeof(*BRCoinTestNetCheckpoints)
};

#endif // BRChainParams_h
