import qbs
import qbs.FileInfo
import qbs.Environment
import 'tools/qbs/imports' as I

I.JSolution {
    projectName: 'ocr-devinfo'
    projectDisplayName: 'OCR-DevInfo'
    version: '1.0.3'
    buildVersion: 1

    readonly property bool useVcPkg: false
    readonly property bool useVcPkgStatic: false
    readonly property path vcpkgHome: Environment.getEnv('VCPKG_HOME')
    readonly property path vcpkgLibHome: FileInfo.joinPaths(vcpkgHome, 'installed',
                                                            useVcPkgStatic ? 'x64-windows-static'
                                                                           : 'x64-windows')
    readonly property path vcpkgLibBin: vcpkgLibHome + (qbs.buildVariant == 'debug' ? '/debug' : '') + '/bin/'
    readonly property path opencvDir: Environment.getEnv('OPENCV_HOME')
    readonly property path tesseractDir: Environment.getEnv('Tesseract_DIR')
    //readonly property path tesseractDir: "C:/Program Files/tesseract"

    readonly property string opencvVersion: '420'
}
