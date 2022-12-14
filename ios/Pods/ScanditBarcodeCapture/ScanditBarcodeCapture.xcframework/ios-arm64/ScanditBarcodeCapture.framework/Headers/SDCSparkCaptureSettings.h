/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditBarcodeCapture/SDCSymbology.h>

@class SDCSymbologySettings;
@protocol SDCLocationSelection;

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.8.0
 *
 * Holds all the spark capture settings, such as enabled symbologies and location selection.
 *
 * For the settings to take effect, they must be applied to a spark capture instance using SDCSparkCapture.applySettings:completionHandler:.
 *
 * By default, all types of barcodes (symbologies) are disabled. To scan barcodes, you need to manually enable all the symbologies you want to scan in your application.
 *
 * The following lines of code show how to enable SDCSymbologyCode128 and apply the settings to spark capture.
 *
 * @code
 * let settings = SparkCaptureSettings()
 * settings.set(symbology: .code128, enabled: true)
 * sparkCapture.apply(settings, completionHandler: nil)
 * @endcode
 */
NS_SWIFT_NAME(SparkCaptureSettings)
SDC_EXPORTED_SYMBOL
@interface SDCSparkCaptureSettings : NSObject <NSCopying>

/**
 * Added in version 6.8.0
 *
 * Determines the time interval in which codes with the same symbology/data are filtered out as duplicates. By default, when the same code (data, symbology) is scanned in consecutive frames, it is reported again as a new scan. Use this property to change the interval or completely turn off duplicate filtering:
 *
 *   • Setting this property to value smaller than zero, means that the same code will not be reported again until the scanning has been stopped.
 *
 *   • Setting this property to a value of zero means that the same code will be reported every time it is found.
 *
 *   • Setting this property to a value larger than zero indicates the time that must pass between the same code to be reported again.
 *
 * The filtering is reset any time the capture mode is disabled (SDCDataCaptureMode.enabled is set to false) as this is when the session is cleaned and restarts from zero.
 */
@property (nonatomic, assign) NSTimeInterval codeDuplicateFilter;
/**
 * Added in version 6.8.0
 *
 * Returns the set of enabled symbologies.
 */
@property (nonatomic, nonnull, readonly)
    NSSet<NSNumber *> *enabledSymbologies NS_SWIFT_NAME(enabledSymbologyValues);
/**
 * Added in version 6.8.0
 *
 * Defines the strategy with which to select one out of many visible barcodes. See Location Selection Guide. By default, this property is set to centered, 40% of the height and full width.
 */
@property (nonatomic, strong, nullable) id<SDCLocationSelection> locationSelection;

/**
 * Added in version 6.8.0
 *
 * Get SDCSymbologySettings specific for the given SDCSymbology.
 *
 * Note that modifying the returned object doesn’t automatically apply the changes to SDCSparkCapture. After you made changes to the symbology settings, call SDCSparkCapture.applySettings:completionHandler: with these SDCSparkCaptureSettings to apply them.
 */
- (nonnull SDCSymbologySettings *)settingsForSymbology:(SDCSymbology)symbology;
/**
 * Added in version 6.8.0
 *
 * Sets a property to the provided value. Use this method to set properties that are not yet part of a stable API. Properties set through this method may or may not be used or change in a future release.
 */
- (void)setValue:(id)value forProperty:(NSString *)property NS_SWIFT_NAME(set(value:forProperty:));
/**
 * Added in version 6.8.0
 *
 * Retrieves the value of a previously set property. In case the property does not exist, nil is returned.
 */
- (nullable id)valueForProperty:(NSString *)property;
/**
 * Added in version 6.8.0
 *
 * Provides a convenient shortcut to enable decoding of particular symbologies without having to go through SDCSymbologySettings.
 * By default, all symbologies are turned off and symbologies need to be explicitly enabled.
 */
- (void)enableSymbologies:(nonnull NSSet<NSNumber *> *)symbologies;
/**
 * Added in version 6.8.0
 *
 * Provides a convenient shortcut to enable/disable decoding of a particular symbology without having to go through SDCSymbologySettings.
 *
 * Some 1d barcode symbologies allow you to encode variable-length data. By default, the Scandit Data Capture SDK only scans barcodes in a certain length range.
 *
 * If your application requires scanning of one of these symbologies, and the length is falling outside the default range, you may need to adjust the active symbol counts for the symbology in addition to enabling it.
 */
- (void)setSymbology:(SDCSymbology)symbology
             enabled:(BOOL)enabled NS_SWIFT_NAME(set(symbology:enabled:));

@end

NS_ASSUME_NONNULL_END
