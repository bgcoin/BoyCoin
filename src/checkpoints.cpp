// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2014 Boycoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
        ( 0, uint256("0x792fb39db54e16cfd83a0100559461adcc0783ad4dfdb0219357a293e94a6a05"))
		( 1, uint256("0x52a5dd145d67bd33b751de34d2969447dc3850974aaec3ea938d6c12abfdedd2"))
		( 2, uint256("0x5c4350ddaed3b09cf688eb4aed9265ab20b52766286224156f692e9055481a13"))
		( 3, uint256("0x99ec8e4b0a74bcdcda7f5ba5b11c07a48cf342dd3d645892a5134c987ab5ec84"))
		( 4, uint256("0xb748b41bd9de693eb5bf6e9b401212c59f60d8ea772d221a468e75d72980d2cf"))
		( 5, uint256("0x68e76c6d5829a21a493b591360e97171d37c998fb3cfb03fb5e30dd4c997e6f3"))
		( 6, uint256("0xf57c3cbf21751d389f56e097695954ab0da73983a7ede53fae80295b6f9b8544"))
		( 7, uint256("0xbfed35f5ccd463e494ef4e4fd2f95f3f5d7b41c068f6149260ef74678a85aa65"))
		( 8, uint256("0xac84daa4118c395f6d9cb085dbbba474226aa7feb05e5bcd30ce967324222c22"))
		( 9, uint256("0x5c548b7b415f626525520a01a64520154c1126d7290c13b0ea480e3b193dcac9"))
		( 10, uint256("0xbbef3b379cef6d727ba370a9d38a9afed1d053e81e0d80b1f7758c845c77feb9"))
		( 999, uint256("0x50cf98cc844af939126860ff51e5587a80dd456844ab58a7cc2bfa4bf1e31a64"))
		( 9999, uint256("0xeb81c61e85e02dd0253ecb3dab9dd20cfcb8ef4f645537c6dd5275d77c3974ce"))
		( 22222, uint256("0x070efc84b8a5c68fbdeda11ac9bd30623d1d9cc2602bd02a66f22944085ff21c"))
		( 33333, uint256("0x3ae7dc41e29798b24d501db66636efa253d5acc0eb6470ab8a545493c4600e88"))
		( 44444, uint256("0xdf2b88f8a0c2bae164b2be8fc62dcba68eafd1f0021dcdfd0b40a90ef0ab841d"))
		;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
		// return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
		// return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
				// return NULL;
        }
        return NULL;
    }
}
