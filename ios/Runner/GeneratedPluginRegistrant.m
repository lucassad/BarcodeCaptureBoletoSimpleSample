//
//  Generated file. Do not edit.
//

// clang-format off

#import "GeneratedPluginRegistrant.h"

#if __has_include(<permission_handler_apple/PermissionHandlerPlugin.h>)
#import <permission_handler_apple/PermissionHandlerPlugin.h>
#else
@import permission_handler_apple;
#endif

#if __has_include(<scandit_flutter_datacapture_barcode/ScanditFlutterDataCaptureBarcodePlugin.h>)
#import <scandit_flutter_datacapture_barcode/ScanditFlutterDataCaptureBarcodePlugin.h>
#else
@import scandit_flutter_datacapture_barcode;
#endif

#if __has_include(<scandit_flutter_datacapture_core/ScanditFlutterDataCaptureCorePlugin.h>)
#import <scandit_flutter_datacapture_core/ScanditFlutterDataCaptureCorePlugin.h>
#else
@import scandit_flutter_datacapture_core;
#endif

@implementation GeneratedPluginRegistrant

+ (void)registerWithRegistry:(NSObject<FlutterPluginRegistry>*)registry {
  [PermissionHandlerPlugin registerWithRegistrar:[registry registrarForPlugin:@"PermissionHandlerPlugin"]];
  [ScanditFlutterDataCaptureBarcodePlugin registerWithRegistrar:[registry registrarForPlugin:@"ScanditFlutterDataCaptureBarcodePlugin"]];
  [ScanditFlutterDataCaptureCorePlugin registerWithRegistrar:[registry registrarForPlugin:@"ScanditFlutterDataCaptureCorePlugin"]];
}

@end
