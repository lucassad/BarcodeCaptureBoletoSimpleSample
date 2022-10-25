/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditCaptureCore/SDCControl.h>
#import <ScanditCaptureCore/SDCMeasureUnit.h>

/**
 * Added in version 6.14.0
 *
 * The orientation in which a SDCLinearControlGroup will render its child controls.
 */
typedef NS_CLOSED_ENUM(NSUInteger, SDCLinearControlGroupOrientation) {
/**
     * Added in version 6.14.0
     *
     * Vertical orientation.
     */
    SDCLinearControlGroupOrientationVertical,
/**
     * Added in version 6.14.0
     *
     * Horizontal orientation.
     */
    SDCLinearControlGroupOrientationHorizontal
} NS_SWIFT_NAME(LinearControlGroupOrientation);

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.14.0
 *
 * A Control that contains multiple sub-controls allowing for spacing and orientation to be specified through initializer. This control will arrange child controls either horizontally in a single column or vertically in a single row. Use one of the initializers to build an instance of this control and add to a DataCaptureView by calling SDCDataCaptureView.addControl:.
 *
 * @remark The controls are added from top to bottom when vertical, from left to right when horizontal.
 */
NS_SWIFT_NAME(LinearControlGroup)
SDC_EXPORTED_SYMBOL
@interface SDCLinearControlGroup : NSObject <SDCControl>

/**
 * Added in version 6.14.0
 */
@property (nonatomic, nonnull, readonly) NSArray<id<SDCControl>> *controls;
/**
 * Added in version 6.14.0
 *
 * Get the orientation for the LinearControlGroup.
 */
@property (nonatomic, readonly) SDCLinearControlGroupOrientation orientation;
/**
 * Added in version 6.14.0
 *
 * Get the spacing applied between controls inside the LinearControlGroup being built.
 */
@property (nonatomic, readonly) SDCFloatWithUnit spacing;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * Added in version 6.14.0
 *
 * Initializes a new linear control group with controls which will be displayed inside the LinearControlGroup.
 */
- (instancetype)initWithControls:(NSArray<id<SDCControl>> *)controls;
/**
 * Added in version 6.14.0
 *
 * Initializes a new linear control group with controls which will be displayed inside the LinearControlGroup and specified orientation.
 */
- (instancetype)initWithControls:(NSArray<id<SDCControl>> *)controls
                     orientation:(SDCLinearControlGroupOrientation)orientation;
/**
 * Added in version 6.14.0
 *
 * Initializes a new linear control group with controls which will be displayed inside the LinearControlGroup and specified spacing applied between controls inside the LinearControlGroup.
 */
- (instancetype)initWithControls:(NSArray<id<SDCControl>> *)controls
                         spacing:(SDCFloatWithUnit)spacing;
/**
 * Added in version 6.14.0
 *
 * Initializes a new linear control group with controls which will be displayed inside the LinearControlGroup, specified orientation and spacing applied between controls inside the LinearControlGroup.
 */
- (instancetype)initWithControls:(NSArray<id<SDCControl>> *)controls
                     orientation:(SDCLinearControlGroupOrientation)orientation
                         spacing:(SDCFloatWithUnit)spacing NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
