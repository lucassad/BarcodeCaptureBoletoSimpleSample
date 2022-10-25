/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/SDCControl.h>
#import <ScanditCaptureCore/SDCBase.h>

@class UIImage;

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.10.0
 *
 * Control that allows to switch between two camera zoom levels defined by SDCCameraSettings.zoomFactor and SDCCameraSettings.zoomGestureZoomFactor.
 *
 * You can add this control to a view by calling SDCDataCaptureView.addControl:.
 */
NS_SWIFT_NAME(ZoomSwitchControl)
SDC_EXPORTED_SYMBOL
@interface SDCZoomSwitchControl : NSObject <SDCControl>

/**
 * Added in version 6.10.0
 *
 * The button image displayed when the zoom level is set to 1x.
 */
@property (nonatomic, strong, nonnull) UIImage *zoomedOutImage;
/**
 * Added in version 6.10.0
 *
 * The button image displayed when the zoom level is set to 1x and the button is pressed.
 */
@property (nonatomic, strong, nonnull) UIImage *zoomedOutPressedImage;
/**
 * Added in version 6.10.0
 *
 * The button image displayed when the zoom level is set to 2x.
 */
@property (nonatomic, strong, nonnull) UIImage *zoomedInImage;
/**
 * Added in version 6.10.0
 *
 * The button image displayed when the zoom level is set to 2x and pressed.
 */
@property (nonatomic, strong, nonnull) UIImage *zoomedInPressedImage;

/**
 * Added in version 6.10.0
 *
 * The default button image displayed when the zoom level is set to 1x.
 */
@property (class, nonatomic, nonnull, readonly) UIImage *defaultZoomedOutImage;
/**
 * Added in version 6.10.0
 *
 * The default button image displayed when the zoom level is set to 1x and the button is pressed.
 */
@property (class, nonatomic, nonnull, readonly) UIImage *defaultZoomedOutPressedImage;
/**
 * Added in version 6.10.0
 *
 * The default button image displayed when the zoom level is set to 2x.
 */
@property (class, nonatomic, nonnull, readonly) UIImage *defaultZoomedInImage;
/**
 * Added in version 6.10.0
 *
 * The default button image displayed when the zoom level is set to 2x and pressed.
 */
@property (class, nonatomic, nonnull, readonly) UIImage *defaultZoomedInPressedImage;

/**
 * Added in version 6.10.0
 *
 * Constructs a new zoom switch control with the provided JSON serialization. See Serialization for details.
 */
+ (nullable instancetype)zoomSwitchControlFromJSONString:(nonnull NSString *)JSONString
                                                   error:(NSError *_Nullable *_Nullable)error;

/**
 * Added in version 6.10.0
 *
 * Updates the control according to a JSON serialization. See Serialization for details.
 */
- (BOOL)updateFromJSONString:(nonnull NSString *)JSONString
                       error:(NSError *_Nullable *_Nullable)error;

@end

NS_ASSUME_NONNULL_END
