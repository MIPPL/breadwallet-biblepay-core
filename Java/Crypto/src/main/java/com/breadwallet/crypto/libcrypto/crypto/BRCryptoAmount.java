/*
 * Created by Michael Carrara <michael.carrara@breadwallet.com> on 5/31/18.
 * Copyright (c) 2018 Breadwinner AG.  All right reserved.
 *
 * See the LICENSE file at the project root for license information.
 * See the CONTRIBUTORS file at the project root for a list of contributors.
 */
package com.breadwallet.crypto.libcrypto.crypto;

import com.breadwallet.crypto.libcrypto.CryptoLibrary;
import com.breadwallet.crypto.libcrypto.support.UInt256;
import com.google.common.primitives.UnsignedLong;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.PointerType;
import com.sun.jna.ptr.IntByReference;

import static com.google.common.base.Preconditions.checkArgument;

public class BRCryptoAmount extends PointerType implements CoreBRCryptoAmount {

    public BRCryptoAmount(Pointer address) {
        super(address);
    }

    public BRCryptoAmount() {
        super();
    }

    @Override
    public BRCryptoCurrency getCurrency() {
        return CryptoLibrary.INSTANCE.cryptoAmountGetCurrency(this);
    }

    @Override
    public double getDouble(CoreBRCryptoUnit unit, IntByReference overflowRef) {
        BRCryptoUnit unitCore = unit.asBRCryptoUnit();
        return CryptoLibrary.INSTANCE.cryptoAmountGetDouble(this, unitCore, overflowRef);
    }

    @Override
    public UnsignedLong getIntegerRaw(IntByReference overflow) {
        return UnsignedLong.fromLongBits(CryptoLibrary.INSTANCE.cryptoAmountGetIntegerRaw(this, overflow));
    }

    @Override
    public BRCryptoAmount add(CoreBRCryptoAmount o) {
        BRCryptoAmount otherCore = o.asBRCryptoAmount();
        return CryptoLibrary.INSTANCE.cryptoAmountAdd(this, otherCore);
    }

    @Override
    public BRCryptoAmount sub(CoreBRCryptoAmount o) {
        BRCryptoAmount otherCore = o.asBRCryptoAmount();
        return CryptoLibrary.INSTANCE.cryptoAmountSub(this, otherCore);
    }

    @Override
    public BRCryptoAmount negate() {
        return CryptoLibrary.INSTANCE.cryptoAmountNegate(this);
    }

    @Override
    public boolean isNegative() {
        return BRCryptoBoolean.CRYPTO_TRUE == CryptoLibrary.INSTANCE.cryptoAmountIsNegative(this);
    }

    @Override
    public int compare(CoreBRCryptoAmount o) {
        BRCryptoAmount otherCore = o.asBRCryptoAmount();
        return CryptoLibrary.INSTANCE.cryptoAmountCompare(this, otherCore);
    }

    @Override
    public boolean isCompatible(CoreBRCryptoAmount o) {
        BRCryptoAmount otherCore = o.asBRCryptoAmount();
        return BRCryptoBoolean.CRYPTO_TRUE == CryptoLibrary.INSTANCE.cryptoAmountIsCompatible(this, otherCore);
    }

    @Override
    public String toStringWithBase(int base, String preface) {
        UInt256.ByValue value = CryptoLibrary.INSTANCE.cryptoAmountGetValue(this);
        Pointer ptr = CryptoLibrary.INSTANCE.coerceStringPrefaced(value, base, preface);
        try {
            return ptr.getString(0, "UTF-8");
        } finally {
            Native.free(Pointer.nativeValue(ptr));
        }

    }

    @Override
    public BRCryptoAmount asBRCryptoAmount() {
        return this;
    }
}
