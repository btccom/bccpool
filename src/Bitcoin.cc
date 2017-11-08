#include "Bitcoin.h"

std::string EncodeHexBlock(const CBlock &block) {
  CDataStream ssBlock(SER_NETWORK, PROTOCOL_VERSION);
  ssBlock << block;
  return HexStr(ssBlock.begin(), ssBlock.end());
}

CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& consensusParams)
{
  int halvings = nHeight / consensusParams.nSubsidyHalvingInterval;
  // Force block reward to zero when right shift is undefined.
  if (halvings >= 64)
    return 0;

  CAmount nSubsidy = 50 * COIN.GetSatoshis();
  // Subsidy is cut in half every 210,000 blocks which will occur approximately every 4 years.
  nSubsidy >>= halvings;
  return nSubsidy;
}

bool CBitcoinAddress::Set(const CKeyID &id) {
    SetData(Params().Base58Prefix(CChainParams::PUBKEY_ADDRESS), &id, 20);
    return true;
}

bool CBitcoinAddress::Set(const CScriptID &id) {
    SetData(Params().Base58Prefix(CChainParams::SCRIPT_ADDRESS), &id, 20);
    return true;
}

bool CBitcoinAddress::Set(const CTxDestination &dest) {
    return boost::apply_visitor(CBitcoinAddressVisitor(this), dest);
}

bool CBitcoinAddress::IsValid() const {
    return IsValid(Params());
}

bool CBitcoinAddress::IsValid(const CChainParams &params) const {
    bool fCorrectSize = vchData.size() == 20;
    bool fKnownVersion =
        vchVersion == params.Base58Prefix(CChainParams::PUBKEY_ADDRESS) ||
        vchVersion == params.Base58Prefix(CChainParams::SCRIPT_ADDRESS);
    return fCorrectSize && fKnownVersion;
}

CTxDestination CBitcoinAddress::Get() const {
    if (!IsValid()) return CNoDestination();
    uint160 id;
    memcpy(&id, &vchData[0], 20);
    if (vchVersion == Params().Base58Prefix(CChainParams::PUBKEY_ADDRESS)) {
        return CKeyID(id);
    } else if (vchVersion ==
               Params().Base58Prefix(CChainParams::SCRIPT_ADDRESS)) {
        return CScriptID(id);
    } else {
        return CNoDestination();
    }
}
