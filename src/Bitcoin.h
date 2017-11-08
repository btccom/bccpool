#ifndef BPOOL_BITCOIN_H
#define BPOOL_BITCOIN_H

#include <string>

#include "bitcoin/base58.h"
#include "bitcoin/core_io.h"
#include "bitcoin/streams.h"
#include "bitcoin/amount.h"
#include "bitcoin/chainparams.h"
#include "bitcoin/utilstrencodings.h"

/* These functions has missing from bitcoinABC, so copied them 
   from btcpool and pasted to here. */
   
std::string EncodeHexBlock(const CBlock &block);

CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& consensusParams);

/**
 * base58-encoded Bitcoin addresses.
 * <copied from bitcoin/src/base58.cpp>
 * 
 * Public-key-hash-addresses have version 0 (or 111 testnet).
 * The data vector contains RIPEMD160(SHA256(pubkey)), where pubkey is the
 * serialized public key.
 * Script-hash-addresses have version 5 (or 196 testnet).
 * The data vector contains RIPEMD160(SHA256(cscript)), where cscript is the
 * serialized redemption script.
 */
class CBitcoinAddress : public CBase58Data {
public:
    bool Set(const CKeyID &id);
    bool Set(const CScriptID &id);
    bool Set(const CTxDestination &dest);
    bool IsValid() const;
    bool IsValid(const CChainParams &params) const;

    CBitcoinAddress() {}
    CBitcoinAddress(const CTxDestination &dest) { Set(dest); }
    CBitcoinAddress(const std::string &strAddress) { SetString(strAddress); }
    CBitcoinAddress(const char *pszAddress) { SetString(pszAddress); }

    CTxDestination Get() const;
};

class CBitcoinAddressVisitor : public boost::static_visitor<bool> {
private:
    CBitcoinAddress *addr;

public:
    CBitcoinAddressVisitor(CBitcoinAddress *addrIn) : addr(addrIn) {}

    bool operator()(const CKeyID &id) const { return addr->Set(id); }
    bool operator()(const CScriptID &id) const { return addr->Set(id); }
    bool operator()(const CNoDestination &no) const { return false; }
};


#endif // BPOOL_BITCOIN_H
