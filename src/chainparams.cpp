// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2017-2018 The FXR Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "German Securities Trading Bank Reportedly Becomes First In Country To Trade Crypto";
    const CScript genesisOutputScript = CScript() << ParseHex("043e5a5fbfbb2caa5f4b7c8fd24d890d6c244de254d579b5ba629f64c1b48275f59e0e1c834a60f6ffb4aaa022aaa4866434ca729a12465f80618fb2070045cb16") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *    (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 350400; // one year
        consensus.nMasternodePaymentsStartBlock = 250; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 158000; // not used
        consensus.nMasternodePaymentsIncreasePeriod = 576*30; // not used
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 2100000000; // year 10000+
        consensus.nBudgetPaymentsCycleBlocks = 16616;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 2100000000; // year 10000+
        consensus.nSuperblockCycle = 16616;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 227931; // FIX
        consensus.BIP34Hash = uint256S("0x001"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 5 * 60; // FXR: 5 blocks
        consensus.nPowTargetSpacing = 1 * 60; // FXR: 60 seconds
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000; // Aug 9th, 2018

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xa1;
        vAlertPubKey = ParseHex("0462090e574e04c89c55021f8519aa34c980f3b10d1813c579c02abab25c076513d05f561df7046827bb8528e6a3c5328f9c9f567ec50382c7f6f2c5c6a7e9b390");
        nDefaultPort = 34222;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1524780000, 649319, 0x1e0ffff0, 1, 50 * COIN);
	      consensus.hashGenesisBlock = genesis.GetHash();

	      assert(consensus.hashGenesisBlock == uint256S("0x00000b79f3be91a193c0262e780fd94e739c1087a244350cc6b1f33dd4b9beaa"));
        assert(genesis.hashMerkleRoot == uint256S("0x16e24f0ac17639452d46e5644184091abd64715043691473fc2e9e64fe244be9"));

		    vFixedSeeds.clear();
        vSeeds.clear();
        //Merge Swap Seeds
        vSeeds.push_back(CDNSSeedData("Merge Seed 1", "192.95.62.169"));
        vSeeds.push_back(CDNSSeedData("Merge Seed 2", "217.144.181.130"));
        vSeeds.push_back(CDNSSeedData("Merge Seed 3", "217.144.181.130"));
        vSeeds.push_back(CDNSSeedData("Merge Seed 4", "45.32.133.252"));
        vSeeds.push_back(CDNSSeedData("Merge Seed 5", "45.32.133.252"));
        vSeeds.push_back(CDNSSeedData("Merge Seed 6", "74.91.18.98"));

        vSeeds.push_back(CDNSSeedData("fxrate.eu", "seed1.fxrate.eu"));
        vSeeds.push_back(CDNSSeedData("fxrate.eu", "seed2.fxrate.eu"));
        vSeeds.push_back(CDNSSeedData("fxrate.eu", "seed3.fxrate.eu"));
        vSeeds.push_back(CDNSSeedData("fxrate.eu", "seed4.fxrate.eu"));

        // FXRate addresses start with 'F'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
        // FXR script addresses start with '2'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,3);
        // FXR private keys start with 'z' or '2' (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,144);
        // FXR BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xF8).convert_to_container<std::vector<unsigned char> >();
        // FXR BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xCC).convert_to_container<std::vector<unsigned char> >();
        // FXR BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "0462d06a6f4df37fb4f5449bd588a4241c8eb91c45f41dc55ad7fd73bb13acf2804962a512f5f215353ec183fb6df00a10582202deb25e89400d95eb72501d3357";
        strMasternodePaymentsPubKey = "0462d06a6f4df37fb4f5449bd588a4241c8eb91c45f41dc55ad7fd73bb13acf2804962a512f5f215353ec183fb6df00a10582202deb25e89400d95eb72501d3357";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (   0, uint256S("0x00000b79f3be91a193c0262e780fd94e739c1087a244350cc6b1f33dd4b9beaa")),
            1524780000, // * UNIX timestamp of last checkpoint block
            0,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0        // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 350400;
        consensus.nMasternodePaymentsStartBlock = 1000; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 158000;
        consensus.nMasternodePaymentsIncreasePeriod = 576*30;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 2100000000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 2100000000; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 21111; // FIX
        consensus.BIP34Hash = uint256S("0x001"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60 * 60; // FXR: 1 hour, 40 blocks
        consensus.nPowTargetSpacing = 1.5 * 60; // FXR: 90 seconds
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000; // Aug 9th, 2018

        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xa1;
        vAlertPubKey = ParseHex("04aade1599f20a295ee697a836c3a9e4972275d6737528d91faacffd0dac24356cca10a0f96ad5e36303e5c892d2642df326e15b70520827741dbdc436b26d27bf");
        nDefaultPort = 35222;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1524780001, 982791, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

	      assert(consensus.hashGenesisBlock == uint256S("0x000007da732512864d172378401d1d61193fb8f1404a2977b889685d98d61367"));
        assert(genesis.hashMerkleRoot == uint256S("0x16e24f0ac17639452d46e5644184091abd64715043691473fc2e9e64fe244be9"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("fxrate.eu",  "testnet-dns.fxrate.eu"));
        vSeeds.push_back(CDNSSeedData("fxrate.eu",  "testnet2-dns.fxrate.eu"));

        // Testnet FXR addresses start with 'c'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Testnet FXR script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet FXR BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet FXR BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet FXR BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "0464edc51174a1e59c7b747d0cadbb349e5afd814ce1322774ec98e4c72920a4dd66f08f662a72885c6f1e4f3d9c62789ac20711934bddafb12d234ab1a2a9711f";
        strMasternodePaymentsPubKey = "0464edc51174a1e59c7b747d0cadbb349e5afd814ce1322774ec98e4c72920a4dd66f08f662a72885c6f1e4f3d9c62789ac20711934bddafb12d234ab1a2a9711f";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x000007da732512864d172378401d1d61193fb8f1404a2977b889685d98d61367")),

            1524780001, // * UNIX timestamp of last checkpoint block
            0,     // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0         // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // FXR: 1 hour, 40 blocks
        consensus.nPowTargetSpacing = 1.5 * 60; // FXR: 90 seconds
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xa1;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDefaultPort = 36765;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1524780001, 3, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x68f6d244745849f7b147931baf72760e0324cd26ddc0d64f48b13a00037b7937"));
        assert(genesis.hashMerkleRoot == uint256S("0x16e24f0ac17639452d46e5644184091abd64715043691473fc2e9e64fe244be9"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x68f6d244745849f7b147931baf72760e0324cd26ddc0d64f48b13a00037b7937")),
            0,
            0,
            0
        };
        // Testnet FXR addresses start with 'c'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,88);
        // Testnet FXR script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet FXR BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest FXR BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest FXR BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
