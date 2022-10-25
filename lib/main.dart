/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2020- Scandit AG. All rights reserved.
 */

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_platform_widgets/flutter_platform_widgets.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:scandit_flutter_datacapture_barcode/scandit_flutter_datacapture_barcode.dart';
import 'package:scandit_flutter_datacapture_barcode/scandit_flutter_datacapture_barcode_capture.dart';
import 'package:scandit_flutter_datacapture_core/scandit_flutter_datacapture_core.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await ScanditFlutterDataCaptureBarcode.initialize();
  runApp(MyApp());
}

const String licenseKey = "-- ENTER YOUR SCANDIT LICENSE KEY HERE --";

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return PlatformApp(
      cupertino: (_, __) => CupertinoAppData(theme: CupertinoThemeData(brightness: Brightness.light)),
      home: BarcodeScannerScreen(),
    );
  }
}

class BarcodeScannerScreen extends StatefulWidget {
  // Create data capture context using your license key.
  @override
  State<StatefulWidget> createState() => _BarcodeScannerScreenState(DataCaptureContext.forLicenseKey(licenseKey));
}

class _BarcodeScannerScreenState extends State<BarcodeScannerScreen>
    with WidgetsBindingObserver
    implements BarcodeCaptureListener {
  final DataCaptureContext _context;

  // Use the world-facing (back) camera.
  Camera? _camera = Camera.defaultCamera;
  late BarcodeCapture _barcodeCapture;
  late DataCaptureView _captureView;

  bool _isPermissionMessageVisible = false;

  _BarcodeScannerScreenState(this._context);

  void _checkPermission() {
    Permission.camera.request().isGranted.then((value) => setState(() {
          _isPermissionMessageVisible = !value;
          if (value) {
            _camera?.switchToDesiredState(FrameSourceState.on);
          }
        }));
  }

  @override
  void initState() {
    super.initState();
    _ambiguate(WidgetsBinding.instance)?.addObserver(this);

    // Use the recommended camera settings for the BarcodeCapture mode.
    _camera?.applySettings(BarcodeCapture.recommendedCameraSettings);

    // Switch camera on to start streaming frames and enable the barcode tracking mode.
    // The camera is started asynchronously and will take some time to completely turn on.
    _checkPermission();

    // The barcode capture process is configured through barcode capture settings
    // which are then applied to the barcode capture instance that manages barcode capture.
    var captureSettings = BarcodeCaptureSettings();

    // The settings instance initially has all types of barcodes (symbologies) disabled. For the purpose of this
    // sample we enable a very generous set of symbologies. In your own app ensure that you only enable the
    // symbologies that your app requires as every additional enabled symbology has an impact on processing times.
    captureSettings.enableSymbologies({
      Symbology.interleavedTwoOfFive
    });

    // Some linear/1d barcode symbologies allow you to encode variable-length data. By default, the Scandit
    // Data Capture SDK only scans barcodes in a certain length range. If your application requires scanning of one
    // of these symbologies, and the length is falling outside the default range, you may need to adjust the "active
    // symbol counts" for this symbology. This is shown in the following few lines of code for one of the
    // variable-length symbologies.
    captureSettings.settingsForSymbology(Symbology.interleavedTwoOfFive).activeSymbolCounts =
        [for (var i = 40; i <= 50; i++) i].toSet();

    captureSettings.settingsForSymbology(Symbology.interleavedTwoOfFive).setExtensionEnabled("strict", enabled: true);

    // Create new barcode capture mode with the settings from above.
    _barcodeCapture = BarcodeCapture.forContext(_context, captureSettings)
      // Register self as a listener to get informed whenever a new barcode got recognized.
      ..addListener(this);

    // To visualize the on-going barcode capturing process on screen, setup a data capture view that renders the
    // camera preview. The view must be connected to the data capture context.
    _captureView = DataCaptureView.forContext(_context);

    // Add a barcode capture overlay to the data capture view to render the location of captured barcodes on top of
    // the video preview. This is optional, but recommended for better visual feedback.
    var overlay = BarcodeCaptureOverlay.withBarcodeCaptureForViewWithStyle(
        _barcodeCapture, _captureView, BarcodeCaptureOverlayStyle.frame)
      ..viewfinder = RectangularViewfinder.withStyleAndLineStyle(
          RectangularViewfinderStyle.square, RectangularViewfinderLineStyle.light);

    // Adjust the overlay's barcode highlighting to match the new viewfinder styles and improve the visibility of feedback.
    // With 6.10 we will introduce this visual treatment as a new style for the overlay.
    overlay.brush = Brush(Color.fromARGB(0, 0, 0, 0), Color.fromARGB(255, 255, 255, 255), 3);

    _captureView.addOverlay(overlay);

    // Set the default camera as the frame source of the context. The camera is off by
    // default and must be turned on to start streaming frames to the data capture context for recognition.
    if (_camera != null) {
      _context.setFrameSource(_camera!);
    }
    _camera?.switchToDesiredState(FrameSourceState.on);
    _barcodeCapture.isEnabled = true;
  }

  @override
  Widget build(BuildContext context) {
    Widget child;
    if (_isPermissionMessageVisible) {
      child = PlatformText('No permission to access the camera!',
          style: TextStyle(fontSize: 14, fontWeight: FontWeight.bold, color: Colors.black));
    } else {
      child = _captureView;
    }
    return Center(child: child);
  }

  @override
  void didChangeAppLifecycleState(AppLifecycleState state) {
    if (state == AppLifecycleState.resumed) {
      _checkPermission();
    } else if (state == AppLifecycleState.paused) {
      _camera?.switchToDesiredState(FrameSourceState.off);
    }
  }

  @override
  void didScan(BarcodeCapture barcodeCapture, BarcodeCaptureSession session) async {
    _barcodeCapture.isEnabled = false;
    var code = session.newlyRecognizedBarcodes.first;
    var data = (code.data == null || code.data?.isEmpty == true) ? code.rawData : code.data;
    data = calculaLinha(data!).toString();
    var humanReadableSymbology = SymbologyDescription.forSymbology(code.symbology);
    await showPlatformDialog(
        context: context,
        builder: (_) => PlatformAlertDialog(
          content: PlatformText(
            'Scanned: $data\n (${humanReadableSymbology.readableName})',
            style: TextStyle(fontWeight: FontWeight.bold, fontSize: 16),
          ),
          actions: [
            PlatformDialogAction(
                child: PlatformText('OK'),
                onPressed: () {
                  Navigator.of(context, rootNavigator: true).pop();
                })
          ],
        ));
    _barcodeCapture.isEnabled = true;
  }

  @override
  void didUpdateSession(BarcodeCapture barcodeCapture, BarcodeCaptureSession session) {}

  @override
  void dispose() {
    _ambiguate(WidgetsBinding.instance)?.removeObserver(this);
    _barcodeCapture.removeListener(this);
    _barcodeCapture.isEnabled = false;
    _camera?.switchToDesiredState(FrameSourceState.off);
    _context.removeAllModes();
    super.dispose();
  }

  T? _ambiguate<T>(T? value) => value;
}

//Configure functions to parse the Boleto -- https://bit.ly/3zct7Yn
//-------------------------------------------------------------------
String modulo10(String numero)  {
  numero = numero.replaceAll(RegExp("[^0-9]"),"");
  double soma  = 0;
  double peso  = 2;
  int contador = numero.length-1;
  while (contador >= 0) {
    double multiplicacao = (double.parse(numero.substring(contador,contador+1)) * peso);
    if (multiplicacao >= 10) {multiplicacao = 1 + (multiplicacao-10);}
    soma = soma + multiplicacao;
    if (peso == 2) {
      peso = 1;
    } else {
      peso = 2;
    }
    contador = contador - 1;
  }
  double digito = 10 - (soma % 10);
  if (digito == 10) digito = 0;

  return digito.round().toString();
}

String modulo11Banco(String numero) {
  numero = numero.replaceAll(RegExp("[^0-9]"),"");

  double soma  = 0;
  double peso  = 2;
  double base  = 9;
  int contador = numero.length - 1;
  for (int i=contador; i >= 0; i--) {
    soma = soma +  (double.parse(numero.substring(i,i+1)) * peso);
    if (peso < base) {
      peso++;
    } else {
      peso = 2;
    }
  }
  num digito = 11 - (soma % 11);
  if (digito >  9) digito = 0;
  /* Utilizar o dígito 1(um) sempre que o resultado do cálculo padrão for igual a 0(zero), 1(um) ou 10(dez). */
  if (digito == 0) digito = 1;
  return digito.toString();
}

String calculaLinha(String barra)  {
  String linha = barra.replaceAll("[^0-9]", "");

  if (linha.length != 44) {
    return ("A linha do Código de Barras está incompleta!"); // Error
  }

  String campo1 = linha.substring(0,4)+linha.substring(19,20)+'.'+linha.substring(20,24);
  String campo2 = linha.substring(24,29)+'.'+linha.substring(29,34);
  String campo3 = linha.substring(34,39)+'.'+linha.substring(39,44);
  String campo4 = linha.substring(4,5); // Digito verificador
  String campo5 = linha.substring(5,19); // Vencimento + Valor

  var digito = modulo11Banco(  linha.substring(0,4)+linha.substring(5,44));
  var digitoValAr = digito.split('.');

  if (  digitoValAr[0] != campo4 ) {
    return ("Digito verificador "+campo4+", o correto é "+digitoValAr[0]+"\nO sistema não altera automaticamente o dígito correto na quinta casa!"); //Error
  }

  return   campo1 + modulo10(campo1)
      +' '
      +campo2 + modulo10(campo2)
      +' '
      +campo3 + modulo10(campo3)
      +' '
      +campo4
      +' '
      +campo5
  ;
}