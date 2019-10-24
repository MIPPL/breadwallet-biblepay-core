/*
 * Transfer
 *
 * Created by Ed Gamble <ed@breadwallet.com> on 1/22/18.
 * Copyright (c) 2018 Breadwinner AG.  All right reserved.
 *
 * See the LICENSE file at the project root for license information.
 * See the CONTRIBUTORS file at the project root for a list of contributors.
 */
package com.swyftwallet.crypto.ethereum;

import com.swyftwallet.crypto.Address;
import com.swyftwallet.crypto.Amount;
import com.swyftwallet.crypto.Wallet;

class Transfer extends com.swyftwallet.crypto.Transfer {
    long core;

    private Transfer(long core, Wallet wallet, Address source, Address target, Amount amount, Amount fee) {
        super(wallet, source, target, amount, fee);
        this.core = core;
    }

    protected Transfer (Wallet wallet, long core) {
        this (core, wallet, null, null, null, null);
    }

}
