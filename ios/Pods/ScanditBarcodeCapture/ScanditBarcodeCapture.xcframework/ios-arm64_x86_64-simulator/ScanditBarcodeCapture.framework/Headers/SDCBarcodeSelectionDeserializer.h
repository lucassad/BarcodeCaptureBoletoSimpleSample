/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditCaptureCore/SDCDataCaptureModeDeserializer.h>

@class SDCBarcodeSelection;
@class SDCDataCaptureContext;
@class SDCBarcodeSelectionSettings;
@class SDCBarcodeSelectionBasicOverlay;
@protocol SDCBarcodeSelectionDeserializerDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.10.0
 *
 * A deserializer to construct barcode selection from JSON. For most use cases it is enough to use SDCBarcodeSelection.barcodeSelectionFromJSONString:context:error: which internally uses this deserializer. Using the deserializer gives the advantage of being able to listen to the deserialization events as they happen and potentially influence them. Additonally warnings can be read from the deserializer that would otherwise not be available.
 *
 * Related topics: Serialization.
 */
NS_SWIFT_NAME(BarcodeSelectionDeserializer)
SDC_EXPORTED_SYMBOL
@interface SDCBarcodeSelectionDeserializer : NSObject <SDCDataCaptureModeDeserializer>

/**
 * Added in version 6.10.0
 *
 * The object informed about deserialization events.
 */
@property (nonatomic, weak, nullable) id<SDCBarcodeSelectionDeserializerDelegate> delegate;
/**
 * Added in version 6.10.0
 *
 * The warnings produced during deserialization, for example which properties were not used during deserialization.
 */
@property (nonatomic, readonly) NSArray<NSString *> *warnings;

/**
 * Added in version 6.10.0
 *
 * Creates a new deserializer object.
 */
+ (instancetype)barcodeSelectionDeserializer;

/**
 * Added in version 6.10.0
 *
 * Deserializes barcode selection from JSON.
 *
 * An error is set if the provided JSON does not contain required properties or contains properties of the wrong type.
 */
- (nullable SDCBarcodeSelection *)modeFromJSONString:(NSString *)JSONString
                                         withContext:(SDCDataCaptureContext *)context
                                               error:(NSError *_Nullable *_Nullable)error;
/**
 * Added in version 6.10.0
 *
 * Takes an existing barcode selection and updates it by deserializing new or changed properties from JSON. See Updating from JSON for details of how updates are being done.
 *
 * An error is set if the provided JSON does not contain required properties or contains properties of the wrong type.
 */
- (nullable SDCBarcodeSelection *)updateMode:(SDCBarcodeSelection *)barcodeSelection
                              fromJSONString:(NSString *)JSONString
                                       error:(NSError *_Nullable *_Nullable)error;

- (nullable SDCBarcodeSelectionSettings *)settingsFromJSONString:(NSString *)JSONString
                                                           error:
                                                               (NSError *_Nullable *_Nullable)error;
- (nullable SDCBarcodeSelectionSettings *)updateSettings:(SDCBarcodeSelectionSettings *)settings
                                          fromJSONString:(NSString *)JSONString
                                                   error:(NSError *_Nullable *_Nullable)error;

- (nullable SDCBarcodeSelectionBasicOverlay *)basicOverlayFromJSONString:(NSString *)JSONString
                                                                withMode:(SDCBarcodeSelection *)mode
                                                                   error:(NSError *_Nullable *_Nullable)error;

- (nullable SDCBarcodeSelectionBasicOverlay *)updateBasicOverlay:(SDCBarcodeSelectionBasicOverlay *)overlay
                                                  fromJSONString:(NSString *)JSONString
                                                           error:(NSError *_Nullable *_Nullable)error;

@end

NS_ASSUME_NONNULL_END
