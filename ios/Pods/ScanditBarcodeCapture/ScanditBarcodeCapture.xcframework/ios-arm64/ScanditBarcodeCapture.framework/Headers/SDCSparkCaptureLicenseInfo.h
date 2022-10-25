/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/SDCBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.12.0
 *
 * Contains information about spark-capture-specific licensing.
 */
NS_SWIFT_NAME(SparkCaptureLicenseInfo)
SDC_EXPORTED_SYMBOL
@interface SDCSparkCaptureLicenseInfo : NSObject

/**
 * Added in version 6.12.0
 *
 * Which symbologies are licensed and can be used for spark capture.
 */
@property (nonatomic, nonnull, readonly) NSSet<NSNumber *> *licensedSymbologies;
/**
 * Added in version 6.13.0
 *
 * Returns the JSON representation of spark capture license info.
 */
@property (nonatomic, nonnull, readonly) NSString *JSONString;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
