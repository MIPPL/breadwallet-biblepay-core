# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# now build app's shared lib
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -DANDROID_STL=gnustl_static -DANDROID_TOOLCHAIN=clang")

# -Wimplicit-function-declaration
# -Wno-missing-prototypes -Werror=return-type -Wdocumentation -Wunreachable-code-aggressive -Wno-missing-braces
# -Wparentheses -Wswitch -Wno-unused-function -Wunused-label -Wno-unused-parameter -Wunused-variable -Wunused-value -Wempty-body
# -Wconditional-uninitialized -Wno-unknown-pragmas -pedantic -Wshadow -Wfour-char-constants -Wno-conversion -Wconstant-conversion
# -Wint-conversion -Wbool-conversion -Wenum-conversion -Wassign-enum -Wno-shorten-64-to-32 -Wpointer-sign -Wnewline-eof
# -Wdeprecated-declarations -Wno-sign-conversion


add_library( # Sets the name of the library.
             core

             # Sets the library as a shared library.
             SHARED)

# Core
target_sources (core
                PUBLIC

                # Support Files
                ../../support/BRAddress.c
                ../../support/BRAddress.h
                ../../support/BRAssert.c
                ../../support/BRAssert.h
                ../../support/BRArray.h
                ../../support/BRBIP32Sequence.c
                ../../support/BRBIP32Sequence.h
                ../../support/BRBIP39Mnemonic.c
                ../../support/BRBIP39Mnemonic.h
                ../../support/BRBIP39WordsEn.h
                ../../support/BRBase58.c
                ../../support/BRBase58.h
                ../../support/BRBech32.c
                ../../support/BRBech32.h
                ../../support/BRCrypto.c
                ../../support/BRCrypto.h
                ../../support/BRFileService.c
                ../../support/BRFileService.h
                ../../support/BRInt.h
                ../../support/BRKey.c
                ../../support/BRKey.h
                ../../support/BRKeyECIES.c
                ../../support/BRKeyECIES.h
                ../../support/BRSet.c
                ../../support/BRSet.h

                # Bitcoin
                ../../bitcoin/BRBIP38Key.c
                ../../bitcoin/BRBIP38Key.h
                ../../bitcoin/BRBloomFilter.c
                ../../bitcoin/BRBloomFilter.h
                ../../bitcoin/BRChainParams.h
                ../../bitcoin/BRChainParams.c
                ../../bitcoin/BRMerkleBlock.c
                ../../bitcoin/BRMerkleBlock.h
                ../../bitcoin/BRPaymentProtocol.c
                ../../bitcoin/BRPaymentProtocol.h
                ../../bitcoin/BRPeer.c
                ../../bitcoin/BRPeer.h
                ../../bitcoin/BRPeerManager.c
                ../../bitcoin/BRPeerManager.h
                ../../bitcoin/BRTransaction.c
                ../../bitcoin/BRTransaction.h
                ../../bitcoin/BRWallet.c
                ../../bitcoin/BRWallet.h
                ../../bitcoin/BRWalletManager.c
                ../../bitcoin/BRWalletManager.h

                # BCash files
                ../../bcash/BRBCashAddr.c
                ../../bcash/BRBCashAddr.h
                ../../bcash/BRBCashParams.h
                ../../bcash/BRBCashParams.c
                )

# Core JNI
target_sources (core
                PUBLIC
                ../../Java/Core/src/main/cpp/jni/BRCoreJni.h
                ../../Java/Core/src/main/cpp/jni/BRCoreJni.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreJniReference.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreJniReference.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreAddress.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreAddress.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreChainParams.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreChainParams.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCorePeer.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCorePeer.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreMasterPubKey.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreMasterPubKey.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreKey.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreKey.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreMerkleBlock.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreMerkleBlock.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCorePeerManager.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCorePeerManager.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreTransaction.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreTransaction.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreTransactionInput.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreTransactionInput.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreTransactionOutput.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreTransactionOutput.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCorePaymentProtocol.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCorePaymentProtocol.h
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreWallet.c
                ../../Java/Core/src/main/cpp/jni/com_breadwallet_core_BRCoreWallet.h)

# Core Ethereum
target_sources (core
                PUBLIC

                #
                ../../ethereum/BREthereum.h

                # Util
                ../../ethereum/util/BRKeccak.c
                ../../ethereum/util/BRKeccak.h
                ../../ethereum/util/BRUtil.h
                ../../ethereum/util/BRUtilHex.c
                ../../ethereum/util/BRUtilHex.h
                ../../ethereum/util/BRUtilMath.c
                ../../ethereum/util/BRUtilMath.h
                ../../ethereum/util/BRUtilMathParse.c
#                ../../ethereum/util/testUtil.c

                # RLP
                ../../ethereum/rlp/BRRlp.h
                ../../ethereum/rlp/BRRlpCoder.c
                ../../ethereum/rlp/BRRlpCoder.h
#                ../../ethereum/rlp/testRlp.c

                # Event
                ../../ethereum/event/BREvent.c
                ../../ethereum/event/BREvent.h
                ../../ethereum/event/BREventAlarm.c
                ../../ethereum/event/BREventAlarm.h
                ../../ethereum/event/BREventQueue.c
                ../../ethereum/event/BREventQueue.h
#                ../../ethereum/event/testEvent.c

                # Base
                ../../ethereum/base/BREthereumAddress.c
                ../../ethereum/base/BREthereumAddress.h
                ../../ethereum/base/BREthereumBase.h
                ../../ethereum/base/BREthereumEther.c
                ../../ethereum/base/BREthereumEther.h
                ../../ethereum/base/BREthereumGas.c
                ../../ethereum/base/BREthereumGas.h
                ../../ethereum/base/BREthereumHash.c
                ../../ethereum/base/BREthereumHash.h
                ../../ethereum/base/BREthereumData.c
                ../../ethereum/base/BREthereumData.h
                ../../ethereum/base/BREthereumLogic.h
                ../../ethereum/base/BREthereumSignature.c
                ../../ethereum/base/BREthereumSignature.h
#                ../../ethereum/base/testBase.c

                # Block Chain
                ../../ethereum/blockchain/BREthereumAccountState.c
                ../../ethereum/blockchain/BREthereumAccountState.h
                ../../ethereum/blockchain/BREthereumBlock.c
                ../../ethereum/blockchain/BREthereumBlock.h
                ../../ethereum/blockchain/BREthereumBlockChain.h
                ../../ethereum/blockchain/BREthereumBloomFilter.c
                ../../ethereum/blockchain/BREthereumBloomFilter.h
                ../../ethereum/blockchain/BREthereumLog.c
                ../../ethereum/blockchain/BREthereumLog.h
                ../../ethereum/blockchain/BREthereumNetwork.c
                ../../ethereum/blockchain/BREthereumNetwork.h
                ../../ethereum/blockchain/BREthereumTransaction.c
                ../../ethereum/blockchain/BREthereumTransaction.h
                ../../ethereum/blockchain/BREthereumTransactionReceipt.c
                ../../ethereum/blockchain/BREthereumTransactionReceipt.h
                ../../ethereum/blockchain/BREthereumTransactionStatus.c
                ../../ethereum/blockchain/BREthereumTransactionStatus.h
                ../../ethereum/blockchain/BREthereumProofOfWork.c
#                ../../ethereum/blockchain/testBc.c

                # Contract
                ../../ethereum/contract/BREthereumContract.c
                ../../ethereum/contract/BREthereumContract.h
                ../../ethereum/contract/BREthereumToken.c
                ../../ethereum/contract/BREthereumToken.h
#                ../../ethereum/contract/testContract.c

                # MPT
                ../../ethereum/mpt/BREthereumMPT.c
                ../../ethereum/mpt/BREthereumMPT.h

                # LES Msg
                ../../ethereum/les/msg/BREthereumMessageDIS.c
                ../../ethereum/les/msg/BREthereumMessageDIS.h
                ../../ethereum/les/msg/BREthereumMessageETH.h
                ../../ethereum/les/msg/BREthereumMessageLES.c
                ../../ethereum/les/msg/BREthereumMessageLES.h
                ../../ethereum/les/msg/BREthereumMessageP2P.c
                ../../ethereum/les/msg/BREthereumMessageP2P.h
                ../../ethereum/les/msg/BREthereumMessagePIP.c
                ../../ethereum/les/msg/BREthereumMessagePIP.h

                # LES
                ../../ethereum/les/BREthereumLES.c
                ../../ethereum/les/BREthereumLES.h
                ../../ethereum/les/BREthereumLESBase.h
                ../../ethereum/les/BREthereumLESFrameCoder.c
                ../../ethereum/les/BREthereumLESFrameCoder.h
                ../../ethereum/les/BREthereumLESRandom.c
                ../../ethereum/les/BREthereumLESRandom.h
                ../../ethereum/les/BREthereumMessage.c
                ../../ethereum/les/BREthereumMessage.h
                ../../ethereum/les/BREthereumNode.c
                ../../ethereum/les/BREthereumNode.h
                ../../ethereum/les/BREthereumNodeEndpoint.c
                ../../ethereum/les/BREthereumNodeEndpoint.h
                ../../ethereum/les/BREthereumProvision.c
                ../../ethereum/les/BREthereumProvision.h
                ../../ethereum/les/msg/BREthereumMessageP2P.h
                ../../ethereum/les/msg/BREthereumMessageP2P.c
                ../../ethereum/les/msg/BREthereumMessageDIS.h
                ../../ethereum/les/msg/BREthereumMessageDIS.c
                ../../ethereum/les/msg/BREthereumMessageETH.h
                ../../ethereum/les/msg/BREthereumMessageLES.h
                ../../ethereum/les/msg/BREthereumMessageLES.c
                ../../ethereum/les/msg/BREthereumMessagePIP.h
                ../../ethereum/les/msg/BREthereumMessagePIP.c
#                ../../ethereum/les/test-les.c
#                ../../ethereum/les/test-les.h

                # BCS
                ../../ethereum/bcs/BREthereumBCS.c
                ../../ethereum/bcs/BREthereumBCS.h
                ../../ethereum/bcs/BREthereumBCSEvent.c
                ../../ethereum/bcs/BREthereumBCSPrivate.h
                ../../ethereum/bcs/BREthereumBCSSync.c
                ../../ethereum/bcs/BREthereumBlockChainSlice.h

                #EWM
                ../../ethereum/ewm/BREthereumBase.h
                ../../ethereum/ewm/BREthereumAccount.c
                ../../ethereum/ewm/BREthereumAccount.h
                ../../ethereum/ewm/BREthereumAmount.c
                ../../ethereum/ewm/BREthereumAmount.h
                ../../ethereum/ewm/BREthereumTransfer.c
                ../../ethereum/ewm/BREthereumTransfer.h
                ../../ethereum/ewm/BREthereumWallet.c
                ../../ethereum/ewm/BREthereumWallet.h
                ../../ethereum/ewm/BREthereumClient.h
                ../../ethereum/ewm/BREthereumEWM.c
                ../../ethereum/ewm/BREthereumEWM.h
                ../../ethereum/ewm/BREthereumEWMClient.c
                ../../ethereum/ewm/BREthereumEWMEvent.c
                ../../ethereum/ewm/BREthereumEWMPrivate.h
#                ../../ethereum/ewm/testEwm.c
                )

# Core Ethereum JNI
target_sources (core
                PUBLIC
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumAccount.h
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumAmount.h
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumBlock.h
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumEWM.c
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumEWM.h
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumNetwork.c
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumNetwork.h
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumToken.c
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumToken.h
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumTransaction.h
                ../../Java/Core/src/main/cpp/jni/ethereum/com_breadwallet_core_ethereum_BREthereumWallet.h)

include_directories(../../)
include_directories(../../support)
include_directories(../../bitcoin)
include_directories(../../bcash)
include_directories(../../ethereum/)
include_directories(../../secp256k1/)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       core

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )