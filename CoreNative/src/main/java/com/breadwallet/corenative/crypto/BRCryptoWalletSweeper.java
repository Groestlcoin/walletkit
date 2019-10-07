/*
 * Created by Michael Carrara <michael.carrara@breadwallet.com> on 7/1/19.
 * Copyright (c) 2019 Breadwinner AG.  All right reserved.
*
 * See the LICENSE file at the project root for license information.
 * See the CONTRIBUTORS file at the project root for a list of contributors.
 */
package com.breadwallet.corenative.crypto;

import com.breadwallet.corenative.CryptoLibrary;
import com.breadwallet.corenative.utility.SizeT;
import com.google.common.base.Optional;
import com.google.common.primitives.UnsignedInteger;
import com.google.common.primitives.UnsignedLong;
import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.PointerType;
import com.sun.jna.StringArray;

import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.List;

public class BRCryptoWalletSweeper extends PointerType {

    public BRCryptoWalletSweeper(Pointer address) {
        super(address);
    }

    public BRCryptoWalletSweeper() {
        super();
    }

    public static BRCryptoWalletSweeperStatus validateSupported(CoreBRCryptoNetwork network,
                                                                BRCryptoCurrency currency,
                                                                BRCryptoKey key,
                                                                CoreBRCryptoWallet wallet) {
        return BRCryptoWalletSweeperStatus.fromNative(
                CryptoLibrary.INSTANCE.cryptoWalletSweeperValidateSupported(
                        network.asBRCryptoNetwork(),
                        currency,
                        key,
                        wallet.asBRCryptoWallet())
        );
    }

    public static BRCryptoWalletSweeper createAsBtc(CoreBRCryptoNetwork network,
                                                    BRCryptoCurrency currency,
                                                    BRCryptoKey key,
                                                    int scheme) {
        return CryptoLibrary.INSTANCE.cryptoWalletSweeperCreateAsBtc(network.asBRCryptoNetwork(),
                currency, key, scheme);
    }

    public BRCryptoKey getKey() {
        return CryptoLibrary.INSTANCE.cryptoWalletSweeperGetKey(this);
    }

    public Optional<BRCryptoAmount> getBalance() {
        return Optional.fromNullable(CryptoLibrary.INSTANCE.cryptoWalletSweeperGetBalance(this));
    }

    public Optional<String> getAddress() {
        Pointer ptr = CryptoLibrary.INSTANCE.cryptoWalletSweeperGetAddress(this);
        try {
            return Optional.fromNullable(ptr).transform(p -> p.getString(0, "UTF-8"));
        } finally {
            if (ptr != null) Native.free(Pointer.nativeValue(ptr));
        }
    }

    public BRCryptoWalletSweeperStatus handleTransactionAsBtc(byte[] transaction) {
        return BRCryptoWalletSweeperStatus.fromNative(
                CryptoLibrary.INSTANCE.cryptoWalletSweeperHandleTransactionAsBTC(
                        this,
                        transaction,
                        new SizeT(transaction.length))
        );
    }

    public BRCryptoWalletSweeperStatus validate() {
        return BRCryptoWalletSweeperStatus.fromNative(
                CryptoLibrary.INSTANCE.cryptoWalletSweeperValidate(this)
        );
    }

    public static class OwnedBRCryptoWalletSweeper extends BRCryptoWalletSweeper {

        public OwnedBRCryptoWalletSweeper(Pointer address) {
            super(address);
        }

        public OwnedBRCryptoWalletSweeper() {
            super();
        }

        @Override
        protected void finalize() {
            if (null != getPointer()) {
                CryptoLibrary.INSTANCE.cryptoWalletSweeperRelease(this);
            }
        }
    }
}
