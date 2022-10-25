/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <UIKit/UIKit.h>

#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditCaptureCore/SDCDataCaptureOverlay.h>

@class SDCBarcodeCount;
@class SDCBarcodeCountBasicOverlay;
@class SDCBrush;
@class SDCDataCaptureView;
@class SDCTrackedBarcode;

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.14.0
 *
 * The style of the SDCBarcodeCountBasicOverlay
 */
typedef NS_CLOSED_ENUM(NSUInteger, SDCBarcodeCountBasicOverlayStyle) {
/**
     * Added in version 6.14.0
     *
     * Style that draws the highlights as a dot and adds an animation for when a code newly appears.
     */
    SDCBarcodeCountBasicOverlayStyleDot,
/**
     * Added in version 6.14.0
     *
     * Style that draws the highlights as icons and adds an animation for when a code newly appears.
     */
    SDCBarcodeCountBasicOverlayStyleIcon
} NS_SWIFT_NAME(BarcodeCountBasicOverlayStyle);

/**
 * Added in version 6.14.0
 */
NS_SWIFT_NAME(BarcodeCountBasicOverlayDelegate)
@protocol SDCBarcodeCountBasicOverlayDelegate <NSObject>

/**
 * Added in version 6.14.0
 *
 * Callback method that can be used to set a SDCBrush for a tracked barcode. It is called when a new tracked barcode appears. Called from the rendering thread.
 * If the callback returns nil, then no visualization will be drawn for the tracked barcode. Additionally, tapping on the barcode will have no effect - the action defined by barcodeCountBasicOverlay:didTapTrackedBarcode: callback will not be performed.
 */
- (nullable SDCBrush *)barcodeCountBasicOverlay:(nonnull SDCBarcodeCountBasicOverlay *)overlay
                         brushForTrackedBarcode:(nonnull SDCTrackedBarcode *)trackedBarcode;

/**
 * Added in version 6.14.0
 *
 * Callback method that can be used to set a SDCBrush for an untracked barcode. It is called when a new untracked barcode appears. Called from the rendering thread.
 * If the callback returns nil, then no visualization will be drawn for the untracked barcode. Additionally, tapping on the barcode will have no effect - the action defined by barcodeCountBasicOverlay:didTapUntrackedBarcode: callback will not be performed.
 */
- (nullable SDCBrush *)barcodeCountBasicOverlay:(nonnull SDCBarcodeCountBasicOverlay *)overlay
                       brushForUntrackedBarcode:(nonnull SDCTrackedBarcode *)untrackedBarcode;

/**
 * Added in version 6.14.0
 *
 * Callback method that can be used to define an action that should be performed once a tracked barcode is tapped. Called from the main thread.
 */
- (void)barcodeCountBasicOverlay:(nonnull SDCBarcodeCountBasicOverlay *)overlay
            didTapTrackedBarcode:(nonnull SDCTrackedBarcode *)trackedBarcode;

/**
 * Added in version 6.14.0
 *
 * Callback method that can be used to define an action that should be performed once an untracked barcode is tapped. Called from the main thread.
 */
- (void)barcodeCountBasicOverlay:(nonnull SDCBarcodeCountBasicOverlay *)overlay
          didTapUntrackedBarcode:(nonnull SDCTrackedBarcode *)untrackedBarcode;

@end

/**
 * Added in version 6.14.0
 */
NS_SWIFT_NAME(BarcodeCountBasicOverlayUIDelegate)
@protocol SDCBarcodeCountBasicOverlayUIDelegate <NSObject>

@optional

/**
 * Added in version 6.14.0
 *
 * Callback method that can be used to define an action that should be performed once the list button is tapped. Called from the main thread.
 */
- (void)listButtonTappedForBarcodeCountBasicOverlay:(nonnull SDCBarcodeCountBasicOverlay *)overlay;

/**
 * Added in version 6.14.0
 *
 * Callback method that can be used to define an action that should be performed once the exit button is tapped. Called from the main thread.
 */
- (void)exitButtonTappedForBarcodeCountBasicOverlay:(nonnull SDCBarcodeCountBasicOverlay *)overlay;

@end

/**
 * Added in version 6.14.0
 *
 * An overlay for SDCDataCaptureView that shows a simple augmentation over each tracked barcode.
 *
 * To display the augmentations, this overlay must be attached to a SDCDataCaptureView. This may be done either by creating it with overlayWithBarcodeCount:forDataCaptureView: with a non-null view parameter or by passing this overlay to SDCDataCaptureView.addOverlay:.
 *
 * A user of this class may configure the appearance of the augmentations by implementing  SDCBarcodeCountBasicOverlayDelegate.
 *
 * For additional information about using this overlay, refer to Get Started With MatrixScan.
 */
SDC_EXPORTED_SYMBOL
NS_SWIFT_NAME(BarcodeCountBasicOverlay)
@interface SDCBarcodeCountBasicOverlay : UIView <SDCDataCaptureOverlay>

/**
 * Added in version 6.14.0
 *
 * Returns the default brush to use for a scanned barcode. Only used when setting the overlay style to SDCBarcodeCountBasicOverlayStyleDot.
 */
@property (class, nonatomic, nonnull, readonly) SDCBrush *defaultScannedBrush;
/**
 * Added in version 6.14.0
 *
 * Returns the default brush to use for an unscanned barcode. Only used when setting the overlay style to SDCBarcodeCountBasicOverlayStyleDot.
 */
@property (class, nonatomic, nonnull, readonly) SDCBrush *defaultUnscannedBrush;

/**
 * Added in version 6.14.0
 *
 * The delegate which is called whenever a new SDCTrackedBarcode is newly tracked or newly recognized.
 *
 * @remark Using this delegate requires the MatrixScan AR add-on.
 */
@property (nonatomic, weak, nullable) id<SDCBarcodeCountBasicOverlayDelegate> delegate;
/**
 * Added in version 6.14.0
 *
 * The delegate which is called whenever the exit or list button of the overlay did receive a tap.
 *
 * @remark Using this delegate requires the MatrixScan AR add-on.
 */
@property (nonatomic, weak, nullable) id<SDCBarcodeCountBasicOverlayUIDelegate> UIDelegate;
/**
 * Added in version 6.14.0
 *
 * When set to YES, this overlay will visualize the active scan area used for BarcodeCount. This is useful to check margins defined on the SDCDataCaptureView are set correctly. This property is meant for debugging during development and is not intended for use in production.
 *
 * By default this property is NO.
 */
@property (nonatomic, assign) BOOL shouldShowScanAreaGuides;
/**
 * Added in version 6.14.0
 *
 * The overlay style. Defaults to SDCBarcodeCountBasicOverlayStyleDot.
 */
@property (nonatomic, readonly) SDCBarcodeCountBasicOverlayStyle style;
/**
 * Added in version 6.14.0
 *
 * The brush applied to recognized tracked barcodes if SDCBarcodeCountBasicOverlayDelegate is not implemented.
 * Setting this brush to nil hides all tracked barcodes.
 */
@property (nonatomic, strong, nullable) SDCBrush *scannedBrush;
/**
 * Added in version 6.14.0
 *
 * The brush applied to unrecognized tracked barcodes if SDCBarcodeCountBasicOverlayDelegate is not implemented.
 * Setting this brush to nil hides all tracked barcodes.
 */
@property (nonatomic, strong, nullable) SDCBrush *unscannedBrush;
/**
 * Added in version 6.14.0
 *
 * Indicates whether the default list button should be shown to the user in the left hand corner of the screen. The behavior for this button is left entirely to the developer, and does nothing by default. When clicked, this button triggers a call to SDCBarcodeCountBasicOverlayUIDelegate.listButtonTappedForBarcodeCountBasicOverlay:.
 */
@property (nonatomic, assign) BOOL shouldShowListButton;
/**
 * Added in version 6.14.0
 *
 * Indicates whether the default exit button should be shown to the user in the right hand corner of the screen. The behavior for this button is left entirely to the developer, and does nothing by default. When clicked, this button triggers a call to SDCBarcodeCountBasicOverlayUIDelegate.exitButtonTappedForBarcodeCountBasicOverlay:.
 */
@property (nonatomic, assign) BOOL shouldShowExitButton;
/**
 * Added in version 6.14.0
 *
 * Indicates whether the default shutter button should be shown to the user centered in the bottom of the screen. By default, this button triggers the processing of the current video feed.
 */
@property (nonatomic, assign) BOOL shouldShowShutterButton;
/**
 * Added in version 6.14.0
 *
 * Indicates whether the default user guidance and loading view should be shown to the user. The user guidance prompts the user to move closer or further away from the target barcodes in order to scan them properly.
 */
@property (nonatomic, assign) BOOL shouldShowUserGuidanceView;
/**
 * Added in version 6.14.0
 *
 * When set to YES, this overlay will visualize some hints explaining how to use barcode count.
 *
 * By default this property is YES.
 */
@property (nonatomic, assign) BOOL shouldShowHints;

/**
 * Added in version 6.14.0
 *
 * Use this property to access or modify the accessibility label for the list button provided by the overlay.
 */
@property (nonatomic, strong, nullable) NSString *listButtonAccessibilityLabel;
/**
 * Added in version 6.14.0
 *
 * Use this property to access or modify the accessibility label for the exit button provided by the overlay.
 */
@property (nonatomic, strong, nullable) NSString *exitButtonAccessibilityLabel;
/**
 * Added in version 6.14.0
 *
 * Use this property to access or modify the accessibility label for the shutter button provided by the overlay.
 */
@property (nonatomic, strong, nullable) NSString *shutterButtonAccessibilityLabel;

/**
 * Added in version 6.14.0
 *
 * Use this property to access or modify the accessibility hint for the list button provided by the overlay.
 */
@property (nonatomic, strong, nullable) NSString *listButtonAccessibilityHint;
/**
 * Added in version 6.14.0
 *
 * Use this property to access or modify the accessibility hint for the exit button provided by the overlay.
 */
@property (nonatomic, strong, nullable) NSString *exitButtonAccessibilityHint;
/**
 * Added in version 6.14.0
 *
 * Use this property to access or modify the accessibility hint for the shutter button provided by the overlay.
 */
@property (nonatomic, strong, nullable) NSString *shutterButtonAccessibilityHint;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)decoder NS_UNAVAILABLE;

/**
 * Added in version 6.14.0
 *
 * Constructs a new barcode count basic overlay for the barcode count instance. The overlay is automatically added to the view.
 */
+ (instancetype)overlayWithBarcodeCount:(nonnull SDCBarcodeCount *)barcodeCount
                     forDataCaptureView:(nullable SDCDataCaptureView *)view
    NS_SWIFT_NAME(init(barcodeCount:view:));
/**
 * Added in version 6.14.0
 *
 * Constructs a new barcode count basic overlay for the barcode count instance with the specified style. The overlay is automatically added to the view.
 */
+ (instancetype)overlayWithBarcodeCount:(nonnull SDCBarcodeCount *)barcodeCount
                     forDataCaptureView:(nullable SDCDataCaptureView *)view
                                  style:(SDCBarcodeCountBasicOverlayStyle)style
    NS_SWIFT_NAME(init(barcodeCount:view:style:));

/**
 * Added in version 6.14.0
 *
 * Sets the text of the hint displayed when one or more unscanned barcodes are detected.
 */
- (void)setTextForUnscannedBarcodesDetectedHint:(nonnull NSString *)text;
/**
 * Added in version 6.14.0
 *
 * Sets the text of the hint which suggests to tap the shutter button.
 */
- (void)setTextForTapShutterToScanHint:(nonnull NSString *)text;
/**
 * Added in version 6.14.0
 *
 * Sets the text of the hint displayed while scanning is in progress.
 */
- (void)setTextForScanningHint:(nonnull NSString *)text;
/**
 * Added in version 6.14.0
 *
 * Sets the text of the hint displayed when camera should be moved closer to rescan.
 */
- (void)setTextForMoveCloserAndRescanHint:(nonnull NSString *)text;
/**
 * Added in version 6.14.0
 *
 * Sets the text of the hint displayed when camera should be further away to rescan.
 */
- (void)setTextForMoveFurtherAndRescanHint:(nonnull NSString *)text;

@end

NS_ASSUME_NONNULL_END
