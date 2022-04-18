# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Pattern rule to print variables, e.g. make print-top_srcdir
print-%: FORCE
	@echo '$*'='$($*)'

DIST_SUBDIRS = bitcoin-core

AM_LDFLAGS = $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS) $(LTO_LDFLAGS) $(CORE_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS) $(LTO_CXXFLAGS) $(CORE_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS) $(CORE_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
PTHREAD_FLAGS = $(PTHREAD_CFLAGS) $(PTHREAD_LIBS)
EXTRA_LIBRARIES =

BITCOIN_INCLUDES=-I$(builddir) -I$(srcdir)/bitcoin-core/src -I$(srcdir)/$(MINISKETCH_INCLUDE_DIR_INT) -I$(srcdir)/bitcoin-core/src/secp256k1/include -I$(srcdir)/$(UNIVALUE_INCLUDE_DIR_INT) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

LIBBITCOIN_NODE=libbitcoin_node.a
LIBBITCOIN_COMMON=libbitcoin_common.a
LIBBITCOIN_CONSENSUS=libbitcoin_consensus.a
LIBBITCOIN_CLI=libbitcoin_cli.a
LIBBITCOIN_UTIL=libbitcoin_util.a
LIBBITCOIN_CRYPTO_BASE=crypto/libbitcoin_crypto_base.a
LIBBITCOINQT=qt/libbitcoinqt.a
LIBSECP256K1=bitcoin-core/src/secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBBITCOIN_ZMQ=libbitcoin_zmq.a
endif
if BUILD_BITCOIN_LIBS
LIBBITCOINCONSENSUS=libbitcoinconsensus.la
endif
if ENABLE_WALLET
LIBBITCOIN_WALLET=libbitcoin_wallet.a
LIBBITCOIN_WALLET_TOOL=libbitcoin_wallet_tool.a
endif

LIBBITCOIN_CRYPTO= $(LIBBITCOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBBITCOIN_CRYPTO_SSE41 = crypto/libbitcoin_crypto_sse41.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBBITCOIN_CRYPTO_AVX2 = crypto/libbitcoin_crypto_avx2.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_AVX2)
endif
if ENABLE_X86_SHANI
LIBBITCOIN_CRYPTO_X86_SHANI = crypto/libbitcoin_crypto_x86_shani.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_X86_SHANI)
endif
if ENABLE_ARM_SHANI
LIBBITCOIN_CRYPTO_ARM_SHANI = crypto/libbitcoin_crypto_arm_shani.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_ARM_SHANI)
endif

$(LIBSECP256K1): $(wildcard bitcoin-core/src/secp256k1/src/*.h) $(wildcard bitcoin-core/src/secp256k1/src/*.c) $(wildcard bitcoin-core/src/secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_NODE) \
  $(LIBBITCOIN_CLI) \
  $(LIBBITCOIN_IPC) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_WALLET_TOOL) \
  $(LIBBITCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBBITCOINCONSENSUS)
noinst_LTLIBRARIES =

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_BITCOIND
  bin_PROGRAMS += bitcoind
endif

if BUILD_BITCOIN_NODE
  bin_PROGRAMS += bitcoin-node
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += bitcoin-cli
endif

if BUILD_BITCOIN_TX
  bin_PROGRAMS += bitcoin-tx
endif

if ENABLE_WALLET
if BUILD_BITCOIN_WALLET
  bin_PROGRAMS += bitcoin-wallet
endif
endif

if BUILD_BITCOIN_UTIL
  bin_PROGRAMS += bitcoin-util
endif

if BUILD_BITCOIN_CHAINSTATE
  bin_PROGRAMS += bitcoin-chainstate
endif

.PHONY: FORCE check-symbols check-security
# bitcoin core #
BITCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  addrman_impl.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  blockencodings.h \
  blockfilter.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  common/bloom.h \
  compat.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/cpuid.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  dbwrapper.h \
  deploymentinfo.h \
  deploymentstatus.h \
  external_signer.h \
  flatfile.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  i2p.h \
  index/base.h \
  index/blockfilterindex.h \
  index/coinstatsindex.h \
  index/disktxpos.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  init/common.h \
  interfaces/chain.h \
  interfaces/echo.h \
  interfaces/handler.h \
  interfaces/init.h \
  interfaces/ipc.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  logging.h \
  logging/timer.h \
  mapport.h \
  memusage.h \
  merkleblock.h \
  net.h \
  net_permissions.h \
  net_processing.h \
  net_types.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  node/blockstorage.h \
  node/caches.h \
  node/chainstate.h \
  node/coin.h \
  node/coinstats.h \
  node/context.h \
  node/miner.h \
  node/minisketchwrapper.h \
  node/psbt.h \
  node/transaction.h \
  node/ui_interface.h \
  node/utxo_snapshot.h \
  noui.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/packages.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  randomenv.h \
  rest.h \
  reverse_iterator.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mempool.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/server_util.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/miniscript.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  signet.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadinterrupt.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  txorphanage.h \
  txrequest.h \
  undo.h \
  util/asmap.h \
  util/bip32.h \
  util/bytevectorhash.h \
  util/check.h \
  util/epochguard.h \
  util/error.h \
  util/fastrange.h \
  util/fees.h \
  util/getuniquepath.h \
  util/golombrice.h \
  util/hash_type.h \
  util/hasher.h \
  util/macros.h \
  util/message.h \
  util/moneystr.h \
  util/overflow.h \
  util/overloaded.h \
  util/rbf.h \
  util/readwritefile.h \
  util/serfloat.h \
  util/settings.h \
  util/sock.h \
  util/spanparsing.h \
  util/string.h \
  util/syscall_sandbox.h \
  util/system.h \
  util/thread.h \
  util/threadnames.h \
  util/time.h \
  util/tokenpipe.h \
  util/trace.h \
  util/translation.h \
  util/types.h \
  util/ui_change_type.h \
  util/url.h \
  util/vector.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/bdb.h \
  wallet/coincontrol.h \
  wallet/coinselection.h \
  wallet/context.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/dump.h \
  wallet/external_signer_scriptpubkeyman.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/receive.h \
  wallet/rpc/util.h \
  wallet/rpc/wallet.h \
  wallet/salvage.h \
  wallet/scriptpubkeyman.h \
  wallet/spend.h \
  wallet/sqlite.h \
  wallet/transaction.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  walletinitinterface.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h \
  zmq/zmqutil.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
bitcoin-core/src/libbitcoin_util_a-clientversion.$(OBJEXT): obj/build.h

ipc/capnp/libbitcoin_ipc_a-ipc.$(OBJEXT): $(libbitcoin_ipc_mpgen_input:=.h)

# server: shared between bitcoind and bitcoin-qt
# Contains code accessing mempool and chain state that is meant to be separated
# from wallet and gui code (see node/README.md). Shared code should go in
# libbitcoin_common or libbitcoin_util libraries, instead.
libbitcoin_node_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(NATPMP_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libbitcoin_node_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_node_a_SOURCES = \
  bitcoin-core/src/addrdb.cpp \
  bitcoin-core/src/addrman.cpp \
  bitcoin-core/src/banman.cpp \
  bitcoin-core/src/blockencodings.cpp \
  bitcoin-core/src/blockfilter.cpp \
  bitcoin-core/src/chain.cpp \
  bitcoin-core/src/consensus/tx_verify.cpp \
  bitcoin-core/src/dbwrapper.cpp \
  bitcoin-core/src/deploymentstatus.cpp \
  bitcoin-core/src/flatfile.cpp \
  bitcoin-core/src/httprpc.cpp \
  bitcoin-core/src/httpserver.cpp \
  bitcoin-core/src/i2p.cpp \
  bitcoin-core/src/index/base.cpp \
  bitcoin-core/src/index/blockfilterindex.cpp \
  bitcoin-core/src/index/coinstatsindex.cpp \
  bitcoin-core/src/index/txindex.cpp \
  bitcoin-core/src/init.cpp \
  bitcoin-core/src/mapport.cpp \
  bitcoin-core/src/net.cpp \
  bitcoin-core/src/net_processing.cpp \
  bitcoin-core/src/node/blockstorage.cpp \
  bitcoin-core/src/node/caches.cpp \
  bitcoin-core/src/node/chainstate.cpp \
  bitcoin-core/src/node/coin.cpp \
  bitcoin-core/src/node/coinstats.cpp \
  bitcoin-core/src/node/context.cpp \
  bitcoin-core/src/node/interfaces.cpp \
  bitcoin-core/src/node/miner.cpp \
  bitcoin-core/src/node/minisketchwrapper.cpp \
  bitcoin-core/src/node/psbt.cpp \
  bitcoin-core/src/node/transaction.cpp \
  bitcoin-core/src/node/ui_interface.cpp \
  bitcoin-core/src/noui.cpp \
  bitcoin-core/src/policy/fees.cpp \
  bitcoin-core/src/policy/packages.cpp \
  bitcoin-core/src/policy/rbf.cpp \
  bitcoin-core/src/policy/settings.cpp \
  bitcoin-core/src/pow.cpp \
  bitcoin-core/src/rest.cpp \
  bitcoin-core/src/rpc/blockchain.cpp \
  bitcoin-core/src/rpc/mempool.cpp \
  bitcoin-core/src/rpc/mining.cpp \
  bitcoin-core/src/rpc/misc.cpp \
  bitcoin-core/src/rpc/net.cpp \
  bitcoin-core/src/rpc/rawtransaction.cpp \
  bitcoin-core/src/rpc/server.cpp \
  bitcoin-core/src/rpc/server_util.cpp \
  bitcoin-core/src/rpc/txoutproof.cpp \
  bitcoin-core/src/script/sigcache.cpp \
  bitcoin-core/src/shutdown.cpp \
  bitcoin-core/src/signet.cpp \
  bitcoin-core/src/timedata.cpp \
  bitcoin-core/src/torcontrol.cpp \
  bitcoin-core/src/txdb.cpp \
  bitcoin-core/src/txmempool.cpp \
  bitcoin-core/src/txorphanage.cpp \
  bitcoin-core/src/txrequest.cpp \
  bitcoin-core/src/validation.cpp \
  bitcoin-core/src/validationinterface.cpp \
  bitcoin-core/src/versionbits.cpp \
  $(BITCOIN_CORE_H)

if ENABLE_WALLET
libbitcoin_node_a_SOURCES += bitcoin-core/src/wallet/init.cpp
endif
if !ENABLE_WALLET
libbitcoin_node_a_SOURCES += bitcoin-core/src/dummywallet.cpp
endif

if ENABLE_ZMQ
libbitcoin_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(ZMQ_CFLAGS)
libbitcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_zmq_a_SOURCES = \
  bitcoin-core/src/zmq/zmqabstractnotifier.cpp \
  bitcoin-core/src/zmq/zmqnotificationinterface.cpp \
  bitcoin-core/src/zmq/zmqpublishnotifier.cpp \
  bitcoin-core/src/zmq/zmqrpc.cpp \
  bitcoin-core/src/zmq/zmqutil.cpp
endif


# wallet: shared between bitcoind and bitcoin-qt, but only linked
# when wallet enabled
libbitcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(SQLITE_CFLAGS)
libbitcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_wallet_a_SOURCES = \
  bitcoin-core/src/wallet/coincontrol.cpp \
  bitcoin-core/src/wallet/context.cpp \
  bitcoin-core/src/wallet/crypter.cpp \
  bitcoin-core/src/wallet/db.cpp \
  bitcoin-core/src/wallet/dump.cpp \
  bitcoin-core/src/wallet/external_signer_scriptpubkeyman.cpp \
  bitcoin-core/src/wallet/feebumper.cpp \
  bitcoin-core/src/wallet/fees.cpp \
  bitcoin-core/src/wallet/interfaces.cpp \
  bitcoin-core/src/wallet/load.cpp \
  bitcoin-core/src/wallet/receive.cpp \
  bitcoin-core/src/wallet/rpc/addresses.cpp \
  bitcoin-core/src/wallet/rpc/backup.cpp \
  bitcoin-core/src/wallet/rpc/coins.cpp \
  bitcoin-core/src/wallet/rpc/encrypt.cpp \
  bitcoin-core/src/wallet/rpc/spend.cpp \
  bitcoin-core/src/wallet/rpc/signmessage.cpp \
  bitcoin-core/src/wallet/rpc/transactions.cpp \
  bitcoin-core/src/wallet/rpc/util.cpp \
  bitcoin-core/src/wallet/rpc/wallet.cpp \
  bitcoin-core/src/wallet/scriptpubkeyman.cpp \
  bitcoin-core/src/wallet/spend.cpp \
  bitcoin-core/src/wallet/transaction.cpp \
  bitcoin-core/src/wallet/wallet.cpp \
  bitcoin-core/src/wallet/walletdb.cpp \
  bitcoin-core/src/wallet/walletutil.cpp \
  bitcoin-core/src/wallet/coinselection.cpp \
  $(BITCOIN_CORE_H)

if USE_SQLITE
libbitcoin_wallet_a_SOURCES += bitcoin-core/src/wallet/sqlite.cpp
endif
if USE_BDB
libbitcoin_wallet_a_SOURCES += bitcoin-core/src/wallet/bdb.cpp bitcoin-core/src/wallet/salvage.cpp
endif

libbitcoin_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_wallet_tool_a_SOURCES = \
  bitcoin-core/src/wallet/wallettool.cpp \
  $(BITCOIN_CORE_H)

# crypto primitives library
crypto_libbitcoin_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/bitcoin-core/src
crypto_libbitcoin_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_base_a_SOURCES = \
  bitcoin-core/src/crypto/aes.cpp \
  bitcoin-core/src/crypto/aes.h \
  bitcoin-core/src/crypto/chacha_poly_aead.h \
  bitcoin-core/src/crypto/chacha_poly_aead.cpp \
  bitcoin-core/src/crypto/chacha20.h \
  bitcoin-core/src/crypto/chacha20.cpp \
  bitcoin-core/src/crypto/common.h \
  bitcoin-core/src/crypto/hkdf_sha256_32.cpp \
  bitcoin-core/src/crypto/hkdf_sha256_32.h \
  bitcoin-core/src/crypto/hmac_sha256.cpp \
  bitcoin-core/src/crypto/hmac_sha256.h \
  bitcoin-core/src/crypto/hmac_sha512.cpp \
  bitcoin-core/src/crypto/hmac_sha512.h \
  bitcoin-core/src/crypto/poly1305.h \
  bitcoin-core/src/crypto/poly1305.cpp \
  bitcoin-core/src/crypto/muhash.h \
  bitcoin-core/src/crypto/muhash.cpp \
  bitcoin-core/src/crypto/ripemd160.cpp \
  bitcoin-core/src/crypto/ripemd160.h \
  bitcoin-core/src/crypto/sha1.cpp \
  bitcoin-core/src/crypto/sha1.h \
  bitcoin-core/src/crypto/sha256.cpp \
  bitcoin-core/src/crypto/sha256.h \
  bitcoin-core/src/crypto/sha3.cpp \
  bitcoin-core/src/crypto/sha3.h \
  bitcoin-core/src/crypto/sha512.cpp \
  bitcoin-core/src/crypto/sha512.h \
  bitcoin-core/src/crypto/siphash.cpp \
  bitcoin-core/src/crypto/siphash.h

if USE_ASM
crypto_libbitcoin_crypto_base_a_SOURCES += bitcoin-core/src/crypto/sha256_sse4.cpp
endif

crypto_libbitcoin_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/bitcoin-core/src
crypto_libbitcoin_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libbitcoin_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libbitcoin_crypto_sse41_a_SOURCES = bitcoin-core/src/crypto/sha256_sse41.cpp

crypto_libbitcoin_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/bitcoin-core/src
crypto_libbitcoin_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libbitcoin_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libbitcoin_crypto_avx2_a_SOURCES = bitcoin-core/src/crypto/sha256_avx2.cpp

crypto_libbitcoin_crypto_x86_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_x86_shani_a_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/bitcoin-core/src
crypto_libbitcoin_crypto_x86_shani_a_CXXFLAGS += $(X86_SHANI_CXXFLAGS)
crypto_libbitcoin_crypto_x86_shani_a_CPPFLAGS += -DENABLE_X86_SHANI
crypto_libbitcoin_crypto_x86_shani_a_SOURCES = bitcoin-core/src/crypto/sha256_x86_shani.cpp

crypto_libbitcoin_crypto_arm_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_arm_shani_a_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/bitcoin-core/src
crypto_libbitcoin_crypto_arm_shani_a_CXXFLAGS += $(ARM_SHANI_CXXFLAGS)
crypto_libbitcoin_crypto_arm_shani_a_CPPFLAGS += -DENABLE_ARM_SHANI
crypto_libbitcoin_crypto_arm_shani_a_SOURCES = bitcoin-core/src/crypto/sha256_arm_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libbitcoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_consensus_a_SOURCES = \
  bitcoin-core/src/arith_uint256.cpp \
  bitcoin-core/src/arith_uint256.h \
  bitcoin-core/src/consensus/amount.h \
  bitcoin-core/src/consensus/merkle.cpp \
  bitcoin-core/src/consensus/merkle.h \
  bitcoin-core/src/consensus/params.h \
  bitcoin-core/src/consensus/tx_check.cpp \
  bitcoin-core/src/consensus/validation.h \
  bitcoin-core/src/hash.cpp \
  bitcoin-core/src/hash.h \
  bitcoin-core/src/prevector.h \
  bitcoin-core/src/primitives/block.cpp \
  bitcoin-core/src/primitives/block.h \
  bitcoin-core/src/primitives/transaction.cpp \
  bitcoin-core/src/primitives/transaction.h \
  bitcoin-core/src/pubkey.cpp \
  bitcoin-core/src/pubkey.h \
  bitcoin-core/src/script/bitcoinconsensus.cpp \
  bitcoin-core/src/script/interpreter.cpp \
  bitcoin-core/src/script/interpreter.h \
  bitcoin-core/src/script/script.cpp \
  bitcoin-core/src/script/script.h \
  bitcoin-core/src/script/script_error.cpp \
  bitcoin-core/src/script/script_error.h \
  bitcoin-core/src/serialize.h \
  bitcoin-core/src/span.h \
  bitcoin-core/src/tinyformat.h \
  bitcoin-core/src/uint256.cpp \
  bitcoin-core/src/uint256.h \
  bitcoin-core/src/util/strencodings.cpp \
  bitcoin-core/src/util/strencodings.h \
  bitcoin-core/src/version.h

# common: shared between bitcoind, and bitcoin-qt and non-server tools
libbitcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_common_a_SOURCES = \
  bitcoin-core/src/base58.cpp \
  bitcoin-core/src/bech32.cpp \
  bitcoin-core/src/chainparams.cpp \
  bitcoin-core/src/coins.cpp \
  bitcoin-core/src/common/bloom.cpp \
  bitcoin-core/src/compressor.cpp \
  bitcoin-core/src/core_read.cpp \
  bitcoin-core/src/core_write.cpp \
  bitcoin-core/src/deploymentinfo.cpp \
  bitcoin-core/src/external_signer.cpp \
  bitcoin-core/src/init/common.cpp \
  bitcoin-core/src/key.cpp \
  bitcoin-core/src/key_io.cpp \
  bitcoin-core/src/merkleblock.cpp \
  bitcoin-core/src/net_types.cpp \
  bitcoin-core/src/netaddress.cpp \
  bitcoin-core/src/netbase.cpp \
  bitcoin-core/src/net_permissions.cpp \
  bitcoin-core/src/outputtype.cpp \
  bitcoin-core/src/policy/feerate.cpp \
  bitcoin-core/src/policy/policy.cpp \
  bitcoin-core/src/protocol.cpp \
  bitcoin-core/src/psbt.cpp \
  bitcoin-core/src/rpc/rawtransaction_util.cpp \
  bitcoin-core/src/rpc/external_signer.cpp \
  bitcoin-core/src/rpc/util.cpp \
  bitcoin-core/src/scheduler.cpp \
  bitcoin-core/src/script/descriptor.cpp \
  bitcoin-core/src/script/miniscript.cpp \
  bitcoin-core/src/script/sign.cpp \
  bitcoin-core/src/script/signingprovider.cpp \
  bitcoin-core/src/script/standard.cpp \
  bitcoin-core/src/warnings.cpp \
  $(BITCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# sanity checks are linked.
libbitcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_util_a_SOURCES = \
  bitcoin-core/src/support/lockedpool.cpp \
  bitcoin-core/src/chainparamsbase.cpp \
  bitcoin-core/src/clientversion.cpp \
  bitcoin-core/src/compat/glibcxx_sanity.cpp \
  bitcoin-core/src/fs.cpp \
  bitcoin-core/src/interfaces/echo.cpp \
  bitcoin-core/src/interfaces/handler.cpp \
  bitcoin-core/src/interfaces/init.cpp \
  bitcoin-core/src/logging.cpp \
  bitcoin-core/src/random.cpp \
  bitcoin-core/src/randomenv.cpp \
  bitcoin-core/src/rpc/request.cpp \
  bitcoin-core/src/support/cleanse.cpp \
  bitcoin-core/src/sync.cpp \
  bitcoin-core/src/threadinterrupt.cpp \
  bitcoin-core/src/util/asmap.cpp \
  bitcoin-core/src/util/bip32.cpp \
  bitcoin-core/src/util/bytevectorhash.cpp \
  bitcoin-core/src/util/check.cpp \
  bitcoin-core/src/util/error.cpp \
  bitcoin-core/src/util/fees.cpp \
  bitcoin-core/src/util/getuniquepath.cpp \
  bitcoin-core/src/util/hasher.cpp \
  bitcoin-core/src/util/sock.cpp \
  bitcoin-core/src/util/system.cpp \
  bitcoin-core/src/util/message.cpp \
  bitcoin-core/src/util/moneystr.cpp \
  bitcoin-core/src/util/rbf.cpp \
  bitcoin-core/src/util/readwritefile.cpp \
  bitcoin-core/src/util/settings.cpp \
  bitcoin-core/src/util/thread.cpp \
  bitcoin-core/src/util/threadnames.cpp \
  bitcoin-core/src/util/serfloat.cpp \
  bitcoin-core/src/util/spanparsing.cpp \
  bitcoin-core/src/util/strencodings.cpp \
  bitcoin-core/src/util/string.cpp \
  bitcoin-core/src/util/syscall_sandbox.cpp \
  bitcoin-core/src/util/time.cpp \
  bitcoin-core/src/util/tokenpipe.cpp \
  $(BITCOIN_CORE_H)

if USE_LIBEVENT
libbitcoin_util_a_SOURCES += bitcoin-core/src/util/url.cpp
endif

# cli: shared between bitcoin-cli and bitcoin-qt
libbitcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_cli_a_SOURCES = \
  bitcoin-core/src/compat/stdin.h \
  bitcoin-core/src/compat/stdin.cpp \
  bitcoin-core/src/rpc/client.cpp \
  $(BITCOIN_CORE_H)

nodist_libbitcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# bitcoind & bitcoin-node binaries #
bitcoin_daemon_sources = bitcoind.cpp
bitcoin_bin_cppflags = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitcoin_bin_cxxflags = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoin_bin_ldflags = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitcoin_daemon_sources += bitcoind-res.rc
endif

bitcoin_bin_ldadd = \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

bitcoin_bin_ldadd += $(BDB_LIBS) $(MINIUPNPC_LIBS) $(NATPMP_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) $(SQLITE_LIBS)

bitcoind_SOURCES = $(bitcoin_daemon_sources) init/bitcoind.cpp
bitcoind_CPPFLAGS = $(bitcoin_bin_cppflags)
bitcoind_CXXFLAGS = $(bitcoin_bin_cxxflags)
bitcoind_LDFLAGS = $(bitcoin_bin_ldflags)
bitcoind_LDADD = $(LIBBITCOIN_NODE) $(bitcoin_bin_ldadd)

bitcoin_node_SOURCES = $(bitcoin_daemon_sources) init/bitcoin-node.cpp
bitcoin_node_CPPFLAGS = $(bitcoin_bin_cppflags)
bitcoin_node_CXXFLAGS = $(bitcoin_bin_cxxflags)
bitcoin_node_LDFLAGS = $(bitcoin_bin_ldflags)
bitcoin_node_LDADD = $(LIBBITCOIN_NODE) $(bitcoin_bin_ldadd) $(LIBBITCOIN_IPC) $(LIBMULTIPROCESS_LIBS)

# bitcoin-cli binary #
bitcoin_cli_SOURCES = bitcoin-cli.cpp
bitcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
bitcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitcoin_cli_SOURCES += bitcoin-cli-res.rc
endif

bitcoin_cli_LDADD = \
  $(LIBBITCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CRYPTO)

bitcoin_cli_LDADD += $(EVENT_LIBS)
#

# bitcoin-tx binary #
bitcoin_tx_SOURCES = bitcoin-tx.cpp
bitcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitcoin_tx_SOURCES += bitcoin-tx-res.rc
endif

bitcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1)
#

# bitcoin-wallet binary #
bitcoin_wallet_SOURCES = bitcoin-wallet.cpp
bitcoin_wallet_SOURCES += init/bitcoin-wallet.cpp
bitcoin_wallet_CPPFLAGS = $(bitcoin_bin_cppflags)
bitcoin_wallet_CXXFLAGS = $(bitcoin_bin_cxxflags)
bitcoin_wallet_LDFLAGS = $(bitcoin_bin_ldflags)
bitcoin_wallet_LDADD = \
  $(LIBBITCOIN_WALLET_TOOL) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1) \
  $(BDB_LIBS) \
  $(SQLITE_LIBS)

if TARGET_WINDOWS
bitcoin_wallet_SOURCES += bitcoin-wallet-res.rc
endif
#

# bitcoin-util binary #
bitcoin_util_SOURCES = bitcoin-util.cpp
bitcoin_util_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitcoin_util_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoin_util_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitcoin_util_SOURCES += bitcoin-util-res.rc
endif

bitcoin_util_LDADD = \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1)
#

# bitcoin-chainstate binary #
bitcoin_chainstate_SOURCES = \
  bitcoin-chainstate.cpp \
  arith_uint256.cpp \
  blockfilter.cpp \
  chain.cpp \
  chainparamsbase.cpp \
  chainparams.cpp \
  clientversion.cpp \
  coins.cpp \
  compat/glibcxx_sanity.cpp \
  compressor.cpp \
  consensus/merkle.cpp \
  consensus/tx_check.cpp \
  consensus/tx_verify.cpp \
  core_read.cpp \
  dbwrapper.cpp \
  deploymentinfo.cpp \
  deploymentstatus.cpp \
  flatfile.cpp \
  fs.cpp \
  hash.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/coinstatsindex.cpp \
  init/common.cpp \
  key.cpp \
  logging.cpp \
  netaddress.cpp \
  node/blockstorage.cpp \
  node/chainstate.cpp \
  node/coinstats.cpp \
  node/ui_interface.cpp \
  policy/feerate.cpp \
  policy/fees.cpp \
  policy/packages.cpp \
  policy/policy.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  random.cpp \
  randomenv.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sigcache.cpp \
  script/standard.cpp \
  shutdown.cpp \
  signet.cpp \
  support/cleanse.cpp \
  support/lockedpool.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  uint256.cpp \
  util/asmap.cpp \
  util/bytevectorhash.cpp \
  util/check.cpp \
  util/getuniquepath.cpp \
  util/hasher.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/serfloat.cpp \
  util/settings.cpp \
  util/strencodings.cpp \
  util/syscall_sandbox.cpp \
  util/system.cpp \
  util/thread.cpp \
  util/threadnames.cpp \
  util/time.cpp \
  util/tokenpipe.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  warnings.cpp
bitcoin_chainstate_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitcoin_chainstate_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoin_chainstate_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)
bitcoin_chainstate_LDADD = \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBUNIVALUE) \
  $(LIBSECP256K1) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV)

# Required for obj/build.h to be generated first.
# More details: https://www.gnu.org/software/automake/manual/html_node/Built-Sources-Example.html
bitcoin_chainstate-clientversion.$(OBJEXT): obj/build.h
#

# bitcoinconsensus library #
if BUILD_BITCOIN_LIBS
include_HEADERS = script/bitcoinconsensus.h
libbitcoinconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libbitcoin_crypto_base_a_SOURCES) $(libbitcoin_consensus_a_SOURCES)

libbitcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libbitcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libbitcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL
libbitcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crc32c/src/*.gcda crc32c/src/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += index/*.gcda index/*.gcno
CLEANFILES += interfaces/*.gcda interfaces/*.gcno
CLEANFILES += node/*.gcda node/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += rpc/*.gcda rpc/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += util/*.gcda util/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/bitcoin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/bitcoin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/bitcoin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/bitcoin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
	@echo "Running symbol and dynamic library checks..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py $(bin_PROGRAMS)
endif

libbitcoin_ipc_mpgen_input = \
  ipc/capnp/echo.capnp \
  ipc/capnp/init.capnp
EXTRA_DIST += $(libbitcoin_ipc_mpgen_input)
%.capnp:

if BUILD_MULTIPROCESS
LIBBITCOIN_IPC=libbitcoin_ipc.a
libbitcoin_ipc_a_SOURCES = \
  ipc/capnp/context.h \
  ipc/capnp/init-types.h \
  ipc/capnp/protocol.cpp \
  ipc/capnp/protocol.h \
  ipc/context.h \
  ipc/exception.h \
  ipc/interfaces.cpp \
  ipc/process.cpp \
  ipc/process.h \
  ipc/protocol.h
libbitcoin_ipc_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_ipc_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(LIBMULTIPROCESS_CFLAGS)

include $(MPGEN_PREFIX)/include/mpgen.mk
libbitcoin_ipc_mpgen_output = \
  $(libbitcoin_ipc_mpgen_input:=.c++) \
  $(libbitcoin_ipc_mpgen_input:=.h) \
  $(libbitcoin_ipc_mpgen_input:=.proxy-client.c++) \
  $(libbitcoin_ipc_mpgen_input:=.proxy-server.c++) \
  $(libbitcoin_ipc_mpgen_input:=.proxy-types.c++) \
  $(libbitcoin_ipc_mpgen_input:=.proxy-types.h) \
  $(libbitcoin_ipc_mpgen_input:=.proxy.h)
nodist_libbitcoin_ipc_a_SOURCES = $(libbitcoin_ipc_mpgen_output)
CLEANFILES += $(libbitcoin_ipc_mpgen_output)
endif

include Makefile.minisketch.include

include Makefile.crc32c.include
include Makefile.leveldb.include

include Makefile.test_util.include
include Makefile.test_fuzz.include

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif

include Makefile.univalue.include
