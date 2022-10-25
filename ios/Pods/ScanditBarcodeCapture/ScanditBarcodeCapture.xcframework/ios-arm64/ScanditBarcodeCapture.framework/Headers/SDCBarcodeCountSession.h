/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <ScanditCaptureCore/SDCBase.h>

@class SDCTrackedBarcode;

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.14.0
 *
 * The count session contains all the currently tracked barcodes and changes that were made specifically in the last processed frame.
 *
 * The count session should only be accessed from within barcodeCount:didUpdateSession:frameData: to which it is provided as an argument. It is not safe to be accessed from anywhere else since it may be concurrently modified.
 *
 * Specifically no reference to trackedBarcodes should be kept and traversed outside of barcodeCount:didUpdateSession:frameData:. Instead a copy of the lists should be made to avoid concurrent modification. The individual tracked barcodes can be referenced without copying as they are not further modified.
 */
SDC_EXPORTED_SYMBOL
NS_SWIFT_NAME(BarcodeCountSession)
@interface SDCBarcodeCountSession : NSObject

/**
 * Added in version 6.14.0
 *
 * A map from identifiers to tracked barcodes. It contains all currently tracked barcodes.
 */
@property (nonatomic, nonnull, readonly)
    NSDictionary<NSNumber *, SDCTrackedBarcode *> *trackedBarcodes;
/**
 * Added in version 6.14.0
 *
 * The identifier of the current frame sequence.
 *
 * As long as there is no interruptions of frames coming from the camera, the frameSequenceId will stay the same.
 */
@property (nonatomic, readonly) NSInteger frameSequenceId;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * Added in version 6.14.0
 *
 * Resets the barcode count session, effectively clearing the history of tracked barcodes.
 */
- (void)reset;

@end

NS_ASSUME_NONNULL_END
