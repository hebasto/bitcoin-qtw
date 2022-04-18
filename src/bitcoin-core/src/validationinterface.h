// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VALIDATIONINTERFACE_H
#define BITCOIN_VALIDATIONINTERFACE_H

#include <primitives/transaction.h> // CTransaction(Ref)
#include <sync.h>

#include <functional>
#include <memory>

extern RecursiveMutex cs_main;
class BlockValidationState;
class CBlock;
class CBlockIndex;
struct CBlockLocator;
class CConnman;
class CValidationInterface;
class uint256;
class CScheduler;
enum class MemPoolRemovalReason;

/** Register subscriber */
void RegisterValidationInterface(CValidationInterface* callbacks);
/** Unregister subscriber. DEPRECATED. This is not safe to use when the RPC server or main message handler thread is running. */
void UnregisterValidationInterface(CValidationInterface* callbacks);
/** Unregister all subscribers */
void UnregisterAllValidationInterfaces();

// Alternate registration functions that release a shared_ptr after the last
// notification is sent. These are useful for race-free cleanup, since
// unregistration is nonblocking and can return before the last notification is
// processed.
/** Register subscriber */
void RegisterSharedValidationInterface(std::shared_ptr<CValidationInterface> callbacks);
/** Unregister subscriber */
void UnregisterSharedValidationInterface(std::shared_ptr<CValidationInterface> callbacks);

/**
 * Pushes a function to callback onto the notification queue, guaranteeing any
 * callbacks generated prior to now are finished when the function is called.
 *
 * Be very careful blocking on func to be called if any locks are held -
 * validation interface clients may not be able to make progress as they often
 * wait for things like cs_main, so blocking until func is called with cs_main
 * will result in a deadlock (that DEBUG_LOCKORDER will miss).
 */
void CallFunctionInValidationInterfaceQueue(std::function<void ()> func);
/**
 * This is a synonym for the following, which asserts certain locks are not
 * held:
 *     std::promise<void> promise;
 *     CallFunctionInValidationInterfaceQueue([&promise] {
 *         promise.set_value();
 *     });
 *     promise.get_future().wait();
 */
void SyncWithValidationInterfaceQueue() LOCKS_EXCLUDED(cs_main);

/**
 * Implement this to subscribe to events generated in validation
 *
 * Each CValidationInterface() subscriber will receive event callbacks
 * in the order in which the events were generated by validation.
 * Furthermore, each ValidationInterface() subscriber may assume that
 * callbacks effectively run in a single thread with single-threaded
 * memory consistency. That is, for a given ValidationInterface()
 * instantiation, each callback will complete before the next one is
 * invoked. This means, for example when a block is connected that the
 * UpdatedBlockTip() callback may depend on an operation performed in
 * the BlockConnected() callback without worrying about explicit
 * synchronization. No ordering should be assumed across
 * ValidationInterface() subscribers.
 */
class CValidationInterface {
protected:
    /**
     * Protected destructor so that instances can only be deleted by derived classes.
     * If that restriction is no longer desired, this should be made public and virtual.
     */
    ~CValidationInterface() = default;
    /**
     * Notifies listeners when the block chain tip advances.
     *
     * When multiple blocks are connected at once, UpdatedBlockTip will be called on the final tip
     * but may not be called on every intermediate tip. If the latter behavior is desired,
     * subscribe to BlockConnected() instead.
     *
     * Called on a background thread.
     */
    virtual void UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload) {}
    /**
     * Notifies listeners of a transaction having been added to mempool.
     *
     * Called on a background thread.
     */
    virtual void TransactionAddedToMempool(const CTransactionRef& tx, uint64_t mempool_sequence) {}

    /**
     * Notifies listeners of a transaction leaving mempool.
     *
     * This notification fires for transactions that are removed from the
     * mempool for the following reasons:
     *
     * - EXPIRY (expired from mempool after -mempoolexpiry hours)
     * - SIZELIMIT (removed in size limiting if the mempool exceeds -maxmempool megabytes)
     * - REORG (removed during a reorg)
     * - CONFLICT (removed because it conflicts with in-block transaction)
     * - REPLACED (removed due to RBF replacement)
     *
     * This does not fire for transactions that are removed from the mempool
     * because they have been included in a block. Any client that is interested
     * in transactions removed from the mempool for inclusion in a block can learn
     * about those transactions from the BlockConnected notification.
     *
     * Transactions that are removed from the mempool because they conflict
     * with a transaction in the new block will have
     * TransactionRemovedFromMempool events fired *before* the BlockConnected
     * event is fired. If multiple blocks are connected in one step, then the
     * ordering could be:
     *
     * - TransactionRemovedFromMempool(tx1 from block A)
     * - TransactionRemovedFromMempool(tx2 from block A)
     * - TransactionRemovedFromMempool(tx1 from block B)
     * - TransactionRemovedFromMempool(tx2 from block B)
     * - BlockConnected(A)
     * - BlockConnected(B)
     *
     * Called on a background thread.
     */
    virtual void TransactionRemovedFromMempool(const CTransactionRef& tx, MemPoolRemovalReason reason, uint64_t mempool_sequence) {}
    /**
     * Notifies listeners of a block being connected.
     * Provides a vector of transactions evicted from the mempool as a result.
     *
     * Called on a background thread.
     */
    virtual void BlockConnected(const std::shared_ptr<const CBlock> &block, const CBlockIndex *pindex) {}
    /**
     * Notifies listeners of a block being disconnected
     *
     * Called on a background thread.
     */
    virtual void BlockDisconnected(const std::shared_ptr<const CBlock> &block, const CBlockIndex* pindex) {}
    /**
     * Notifies listeners of the new active block chain on-disk.
     *
     * Prior to this callback, any updates are not guaranteed to persist on disk
     * (ie clients need to handle shutdown/restart safety by being able to
     * understand when some updates were lost due to unclean shutdown).
     *
     * When this callback is invoked, the validation changes done by any prior
     * callback are guaranteed to exist on disk and survive a restart, including
     * an unclean shutdown.
     *
     * Provides a locator describing the best chain, which is likely useful for
     * storing current state on disk in client DBs.
     *
     * Called on a background thread.
     */
    virtual void ChainStateFlushed(const CBlockLocator &locator) {}
    /**
     * Notifies listeners of a block validation result.
     * If the provided BlockValidationState IsValid, the provided block
     * is guaranteed to be the current best block at the time the
     * callback was generated (not necessarily now)
     */
    virtual void BlockChecked(const CBlock&, const BlockValidationState&) {}
    /**
     * Notifies listeners that a block which builds directly on our current tip
     * has been received and connected to the headers tree, though not validated yet */
    virtual void NewPoWValidBlock(const CBlockIndex *pindex, const std::shared_ptr<const CBlock>& block) {};
    friend class CMainSignals;
    friend class ValidationInterfaceTest;
};

struct MainSignalsInstance;
class CMainSignals {
private:
    std::unique_ptr<MainSignalsInstance> m_internals;

    friend void ::RegisterSharedValidationInterface(std::shared_ptr<CValidationInterface>);
    friend void ::UnregisterValidationInterface(CValidationInterface*);
    friend void ::UnregisterAllValidationInterfaces();
    friend void ::CallFunctionInValidationInterfaceQueue(std::function<void ()> func);

public:
    /** Register a CScheduler to give callbacks which should run in the background (may only be called once) */
    void RegisterBackgroundSignalScheduler(CScheduler& scheduler);
    /** Unregister a CScheduler to give callbacks which should run in the background - these callbacks will now be dropped! */
    void UnregisterBackgroundSignalScheduler();
    /** Call any remaining callbacks on the calling thread */
    void FlushBackgroundCallbacks();

    size_t CallbacksPending();


    void UpdatedBlockTip(const CBlockIndex *, const CBlockIndex *, bool fInitialDownload);
    void TransactionAddedToMempool(const CTransactionRef&, uint64_t mempool_sequence);
    void TransactionRemovedFromMempool(const CTransactionRef&, MemPoolRemovalReason, uint64_t mempool_sequence);
    void BlockConnected(const std::shared_ptr<const CBlock> &, const CBlockIndex *pindex);
    void BlockDisconnected(const std::shared_ptr<const CBlock> &, const CBlockIndex* pindex);
    void ChainStateFlushed(const CBlockLocator &);
    void BlockChecked(const CBlock&, const BlockValidationState&);
    void NewPoWValidBlock(const CBlockIndex *, const std::shared_ptr<const CBlock>&);
};

CMainSignals& GetMainSignals();

#endif // BITCOIN_VALIDATIONINTERFACE_H
