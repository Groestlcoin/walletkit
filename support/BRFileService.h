//
//  BRFileService.h
//  Core
//
//  Created by Richard Evers on 1/4/19.
//  Copyright © 2019 breadwallet. All rights reserved.
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

#ifndef BRFileService_h
#define BRFileService_h

#if defined (TASK_DESCRIPTION)
//Both Bitcoin and Ethereum Wallet Managers include the ability to save and load peers, block,
//transactions and logs (for Ethereum) to the file system.  But, they both implement the file
//operations independently.  Pull out the implementation into BRFileService.
//
// Allow each WalletManager (Bitcoin, Bitcash, Ethereum) to create their own BRFileService (storing
// stuff in a subdirectory specific to the manager+network+whatever for a given base path).  Allow
// each WalletManager to further define 'persistent types' (peers, blocks, etc) saved.  Allow for
// a versioning system (at least on read; everything gets written/saved w/ the latest version).
// Allow an upgrade path from existing IOS/Andriod Sqlite3 databases.
//
// Candidate interface:

//{code:C}
typedef struct BRFileServiceRecord *BRFileService;

extern BRFileService
fileServiceCreate(/* args (w/ 'currency' as BTC, BCH, ETH and 'network' and ???) */);

extern void
fileServiceRelese (BRFileService fs);

extern void /* error code? or return 'results' (instead of filling `results`) */
fileServiceLoad (BRFileService fs,
                 BRSet *results,
                 const char *type);        /* blocks, peers, transactions, logs, ... */

extern void /* error code? */
fileServiceSave (BRFileService fs,
                 const char *type,  /* block, peers, transactions, logs, ... */
                 void *entity);     /* BRMerkleBlock*, BRTransaction, BREthereumTransaction, ... */

extern void
fileServiceClear (BRFileService fs,
                  const char *type);

extern void
fileServiceClearAll (BRFileService fs);

extern void
fileServiceDefineType (BRFileService fs,
                       const char *type,
                       /* VersionType */ version,
                       /* ReadFunction */ reader,
                       /* WriteFunction */ writer);

extern void
fileServiceDefineCurrentVersion (BRFileService fs,
                                 const char *type,
                                 /* VersionType */ version);
//{code}

//Example use:

//{code:C}

//
// In BRWalletManager.c
// ...
manager->fileService = fileServiceCreate (/* BTC or BCH, Mainnet or Testnet, ...*/);
fileServiceDefineType (manager->fileService,
                       "transaction",
                       SomeVersion
                       BRTransactionFileReaderForSomeVersion,     /* TBD */
                       BRTransactionFileWriter);    /* TBD */
// ... transaction, other versions ...
fileServiceDefineCurrentVersion (manager->fileService, "transaction", CurrentVersion);

// ... block ...
// ... peer ...

BRSetOf(BRTransaction) transactions;
manager->transactions = BRSetNew (/* ... */);

fileServiceLoad (manager->fileService,
                 manager->transactions,
                 "transaction");


manager->wallet = BRWalletNew (transactionsAsArray, array_count(transactionsAsArray), mpk, fork);
// ...

//
// In _BRWalletManagerTxAdded.
//
static void
_BRWalletManagerTxAdded (void *info, BRTransaction *tx) {
    BRWalletManager manager = (BRWalletManager) info;
    fileServiceSave (manager->fs,
                     "transaction",
                     tx);
    // ...
}
//{code}
#endif /* defined (TASK_DESCRIPTION) */

#endif /* BRFileService_h */
