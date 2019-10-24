/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_swyftwallet_core_BRCorePaymentProtocolPayment */

#ifndef _Included_com_swyftwallet_core_BRCorePaymentProtocolPayment
#define _Included_com_swyftwallet_core_BRCorePaymentProtocolPayment
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    getMerchantData
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_getMerchantData
  (JNIEnv *, jobject);

/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    getTransactions
 * Signature: ()[Lcom_swyftwallet_/core/BRCoreTransaction;
 */
JNIEXPORT jobjectArray JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_getTransactions
  (JNIEnv *, jobject);

/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    getRefundTo
 * Signature: ()[Lcom_swyftwallet_/core/BRCoreTransactionOutput;
 */
JNIEXPORT jobjectArray JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_getRefundTo
  (JNIEnv *, jobject);

/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    getMerchantMemo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_getMerchantMemo
  (JNIEnv *, jobject);

/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    createPaymentProtocolPayment
 * Signature: ([B)J
 */
JNIEXPORT jlong JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_createPaymentProtocolPayment
  (JNIEnv *, jclass, jbyteArray);

/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    serialize
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_serialize
  (JNIEnv *, jobject);

/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    disposeNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_disposeNative
  (JNIEnv *, jobject);

/*
 * Class:     com_swyftwallet_core_BRCorePaymentProtocolPayment
 * Method:    initializeNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_swyftwallet_core_BRCorePaymentProtocolPayment_initializeNative
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
