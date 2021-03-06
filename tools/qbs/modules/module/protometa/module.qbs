import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'protometa'

    Depends { name: 'Qt'; submodules: ['gui', 'concurrent', 'network'] }
//    Depends {
//        condition: qbs.targetOS.contains('windows')
//        name: 'module'; submodules: ['log4cpp', 'qtftp', 'qttelnet'];
//    }
    Depends { name: 'module.protocore' }

    Properties {
        condition: qbs.targetOS.contains('darwin')
        cpp.dynamicLibraries: []
        cpp.staticLibraries: [ moduleName + variantSuffix ]
    }
}
