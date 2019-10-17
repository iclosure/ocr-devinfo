import qbs
import qbs.FileInfo
import qbs.Environment
import './tools/qbs/imports' as I

I.JSetup {
    minimumQbsVersion: '1.10.0'
    projectName: 'ocr-devinfo'
    projectDisplayName: 'OCR-DevInfo'
    version: '1.0.1'
    variantSuffix: ''
    installRoot: '../build-ocr-devinfo-Qt_5_13_0_64-Release/Release/install-root'
}