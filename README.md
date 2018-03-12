BTCPool for BitcoinCash (legacy branch)
==================

The new works for BTCPool's BitcoinCash version is merged to https://github.com/btccom/btcpool. This legacy branch will no longer have new features and will only provide security updates.

The new version of BTCPool is fully compatible with the old deployment. Only the construction method has changed. And it supported more SHA256 coins (BTC, BCH, SBTC, UBTC) in one branch. In addition, it supports RSK merge mining.

The following is a description of the legacy branch:

---------------------------

BTCPool is backend system of [https://pool.btc.com](https://pool.btc.com).

The pool backend work with Bitcoin Cash.

Note: This is still a testbed and work in progress, all things could be changed.

See Also:
* [BTCPool for Bitcoin](https://github.com/btccom/btcpool)
* [Stratum Switcher](https://github.com/btccom/stratumSwitcher)

## Architecture

![Architecture](docs/btcpool.png)

## Install

1. Install `Zookeeper`, or see [INSTALL-ZooKeeper.md](docs/INSTALL-ZooKeeper.md)
  * [https://zookeeper.apache.org/](https://zookeeper.apache.org/)
2. Install `Kafka`, or see [INSTALL-Kafka.md](docs/INSTALL-Kafka.md)
  * [https://kafka.apache.org/](https://kafka.apache.org/)
3. Install `Bitcoind`, need to enable ZMQ
4. Install `BtcPool`, see [INSTALL.md](INSTALL.md)

## Benchmark

We have test 100,000 miners online Benchmark. see [Benchmark-100000.md](docs/Benchmark-100000.md)

## BtcAgent

BtcAgent is a kind of stratum proxy which use customize protocol to communicate with the pool. It's very efficient and designed for huge mining farm.

* [AGENT.md](docs/AGENT.md)
* BtcAgent's [HomePage](https://github.com/btccom/btcagent)

## Testing

You could run `simulator` to test the system. It will simulate a lots of miners, need to enbale config `enable_simulator` on your Stratum Server.

## License
BTCPool is released under the terms of the MIT license. See [LICENSE](LICENSE) for more information or see [https://opensource.org/licenses/MIT](https://opensource.org/licenses/MIT).


Welcome aboard!

BTC.COM Team.
