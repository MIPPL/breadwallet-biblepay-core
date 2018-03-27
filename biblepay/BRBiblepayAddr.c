//
//  BRBiblepayAddr.c
//
//  Created by Aaron Voisine on 9/18/15.
//  Copyright (c) 2015 breadwallet LLC
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

#include "BRBiblepayAddr.h"
#include "BRBase58.h"
#include "BRBech32.h"
#include "BRInt.h"
#include <inttypes.h>
#include <assert.h>

#define VAR_INT16_HEADER  0xfd
#define VAR_INT32_HEADER  0xfe
#define VAR_INT64_HEADER  0xff
#define MAX_SCRIPT_LENGTH 0x100 // scripts over this size will not be parsed for an address


// NOTE: It's important here to be permissive with scriptSig (spends) and strict with scriptPubKey (receives). If we
// miss a receive transaction, only that transaction's funds are missed, however if we accept a receive transaction that
// we are unable to correctly sign later, then the entire wallet balance after that point would become stuck with the
// current coin selection code

// writes the bitcoin address for a scriptPubKey to addr
// returns the number of bytes written, or addrLen needed if addr is NULL
size_t BRBiblepayAddrFromScriptPubKey(char *addr, size_t addrLen, const uint8_t *script, size_t scriptLen)
{
    assert(script != NULL || scriptLen == 0);
    if (! script || scriptLen == 0 || scriptLen > MAX_SCRIPT_LENGTH) return 0;

    char a[91];
    uint8_t data[21];
    const uint8_t *d, *elems[BRScriptElements(NULL, 0, script, scriptLen)];
    size_t r = 0, l = 0, count = BRScriptElements(elems, sizeof(elems)/sizeof(*elems), script, scriptLen);

    if (count == 5 && *elems[0] == OP_DUP && *elems[1] == OP_HASH160 && *elems[2] == 20 &&
        *elems[3] == OP_EQUALVERIFY && *elems[4] == OP_CHECKSIG) {
        // pay-to-pubkey-hash scriptPubKey
        data[0] = BITCOIN_PUBKEY_ADDRESS;
#if BIBLEPAY_TESTNET
        data[0] = BITCOIN_PUBKEY_ADDRESS_TEST;
#endif
        memcpy(&data[1], BRScriptData(elems[2], &l), 20);
        r = BRBase58CheckEncode(addr, addrLen, data, 21);
    }
    else if (count == 3 && *elems[0] == OP_HASH160 && *elems[1] == 20 && *elems[2] == OP_EQUAL) {
        // pay-to-script-hash scriptPubKey
        data[0] = BITCOIN_PUBKEY_ADDRESS;
#if BIBLEPAY_TESTNET
        data[0] = BITCOIN_SCRIPT_ADDRESS_TEST;
#endif
        memcpy(&data[1], BRScriptData(elems[1], &l), 20);
        r = BRBase58CheckEncode(addr, addrLen, data, 21);
    }
    else if (count == 2 && (*elems[0] == 65 || *elems[0] == 33) && *elems[1] == OP_CHECKSIG) {
        // pay-to-pubkey scriptPubKey
        data[0] = BITCOIN_PUBKEY_ADDRESS;
#if BIBLEPAY_TESTNET
        data[0] = BITCOIN_PUBKEY_ADDRESS_TEST;
#endif
        d = BRScriptData(elems[0], &l);
        BRHash160(&data[1], d, l);
        r = BRBase58CheckEncode(addr, addrLen, data, 21);
    }
    else if (count == 2 && ((*elems[0] == OP_0 && (*elems[1] == 20 || *elems[1] == 32)) ||
                            (*elems[0] >= OP_1 && *elems[0] <= OP_16 && *elems[1] >= 2 && *elems[1] <= 40))) {
        // pay-to-witness scriptPubKey
        r = BRBech32Encode(a, "bc", script);
#if BIBLEPAY_TESTNET
        r = BRBech32Encode(a, "tb", script);
#endif
        if (addr && r > addrLen) r = 0;
        if (addr) memcpy(addr, a, r);
    }

    return r;
}

// writes the bitcoin address for a scriptSig to addr
// returns the number of bytes written, or addrLen needed if addr is NULL
size_t BRBiblepayAddrFromScriptSig(char *addr, size_t addrLen, const uint8_t *script, size_t scriptLen)
{
    assert(script != NULL || scriptLen == 0);
    if (! script || scriptLen == 0 || scriptLen > MAX_SCRIPT_LENGTH) return 0;

    uint8_t data[21];
    const uint8_t *d = NULL, *elems[BRScriptElements(NULL, 0, script, scriptLen)];
    size_t l = 0, count = BRScriptElements(elems, sizeof(elems)/sizeof(*elems), script, scriptLen);

    data[0] = BITCOIN_PUBKEY_ADDRESS;
#if BIBLEPAY_TESTNET
    data[0] = BITCOIN_PUBKEY_ADDRESS_TEST;
#endif

    if (count >= 2 && *elems[count - 2] <= OP_PUSHDATA4 &&
        (*elems[count - 1] == 65 || *elems[count - 1] == 33)) { // pay-to-pubkey-hash scriptSig
        d = BRScriptData(elems[count - 1], &l);
        if (l != 65 && l != 33) d = NULL;
        if (d) BRHash160(&data[1], d, l);
    }
    else if (count >= 2 && *elems[count - 2] <= OP_PUSHDATA4 && *elems[count - 1] <= OP_PUSHDATA4 &&
             *elems[count - 1] > 0) { // pay-to-script-hash scriptSig
        data[0] = BITCOIN_SCRIPT_ADDRESS;
#if BIBLEPAY_TESTNET
        data[0] = BITCOIN_SCRIPT_ADDRESS_TEST;
#endif
        d = BRScriptData(elems[count - 1], &l);
        if (d) BRHash160(&data[1], d, l);
    }
    else if (count >= 1 && *elems[count - 1] <= OP_PUSHDATA4 && *elems[count - 1] > 0) { // pay-to-pubkey scriptSig
        // TODO: implement Peter Wullie's pubKey recovery from signature
    }
    // pay-to-witness scriptSig's are empty

    return (d) ? BRBase58CheckEncode(addr, addrLen, data, 21) : 0;
}

// writes the bitcoin address for a witness to addr
// returns the number of bytes written, or addrLen needed if addr is NULL
size_t BRBiblepayAddrFromWitness(char *addr, size_t addrLen, const uint8_t *witness, size_t witLen)
{
    return 0; // TODO: XXX implement
}

// writes the scriptPubKey for addr to script
// returns the number of bytes written, or scriptLen needed if script is NULL
size_t BRBiblepayAddrScriptPubKey(uint8_t *script, size_t scriptLen, const char *addr)
{
    uint8_t data[42], pubkeyAddress = BITCOIN_PUBKEY_ADDRESS, scriptAddress = BITCOIN_SCRIPT_ADDRESS;
    char hrp[84], *bech32Prefix = "bc";
    size_t dataLen, r = 0;

    assert(addr != NULL);
#if BIBLEPAY_TESTNET
    pubkeyAddress = BITCOIN_PUBKEY_ADDRESS_TEST;
    scriptAddress = BITCOIN_SCRIPT_ADDRESS_TEST;
    bech32Prefix = "tb";
#endif

    if (BRBase58CheckDecode(data, sizeof(data), addr) == 21) {
        if (data[0] == pubkeyAddress) {
            if (script && 25 <= scriptLen) {
                script[0] = OP_DUP;
                script[1] = OP_HASH160;
                script[2] = 20;
                memcpy(&script[3], &data[1], 20);
                script[23] = OP_EQUALVERIFY;
                script[24] = OP_CHECKSIG;
            }

            r = (! script || 25 <= scriptLen) ? 25 : 0;
        }
        else if (data[0] == scriptAddress) {
            if (script && 23 <= scriptLen) {
                script[0] = OP_HASH160;
                script[1] = 20;
                memcpy(&script[2], &data[1], 20);
                script[22] = OP_EQUAL;
            }

            r = (! script || 23 <= scriptLen) ? 23 : 0;
        }
    }
    else {
        dataLen = BRBech32Decode(hrp, data, addr);

        if (dataLen > 2 && strcmp(hrp, bech32Prefix) == 0 && (data[0] != OP_0 || data[1] == 20 || data[1] == 32)) {
            if (script && dataLen <= scriptLen) memcpy(script, data, dataLen);
            r = (! script || dataLen <= scriptLen) ? dataLen : 0;
        }
    }

    return r;
}

// returns true if addr is a valid bitcoin address
int BRBiblepayAddrIsValid(const char *addr)
{
    uint8_t data[42];
    char hrp[84];
    int r = 0;

    assert(addr != NULL);

    if (BRBase58CheckDecode(data, sizeof(data), addr) == 21) {
        r = (data[0] == BITCOIN_PUBKEY_ADDRESS || data[0] == BITCOIN_SCRIPT_ADDRESS);
#if BIBLEPAY_TESTNET
        r = (data[0] == BITCOIN_PUBKEY_ADDRESS_TEST || data[0] == BITCOIN_SCRIPT_ADDRESS_TEST);
#endif
    }
    else if (BRBech32Decode(hrp, data, addr) > 2) {
        r = (strcmp(hrp, "bc") == 0 && (data[0] != OP_0 || data[1] == 20 || data[1] == 32));
#if BIBLEPAY_TESTNET
        r = (strcmp(hrp, "tb") == 0 && (data[0] != OP_0 || data[1] == 20 || data[1] == 32));
#endif
    }

    return r;
}

// writes the 20 byte hash160 of addr to md20 and returns true on success
int BRBiblepayAddrHash160(void *md20, const char *addr)
{
    uint8_t data[21];
    int r = 0;

    assert(md20 != NULL);
    assert(addr != NULL);
    r = (BRBase58CheckDecode(data, sizeof(data), addr) == 21);
    if (r) memcpy(md20, &data[1], 20);
    return r;
}
