import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import qbs.Environment
import tools.EnvUtils

PackageProduct {

    type: base.concat([ 'qt.conf.out' ])
    property bool useSvg: false
    property bool useOpenGL: false
    property bool useDBus: true

    property bool generateQtConf: true
    property stringList module3rdpart: {
        var items = [ 'd3dcompiler*.dll' ]
        if (useOpenGL) {
            items.push('opengl32*.dll')
            items.push(EnvUtils.incDylibFuzzy(qbs, false, 'lib*'))
        }
        return items
    }

    property stringList moduleGeneral: {
        var items = ['Concurrent', 'Core', 'Gui', 'Network', 'PrintSupport', 'Widgets']
        if (useSvg) {
            items.push('Svg')
        }
        if (useOpenGL) {
            items.push('OpenGL')
        }
        if (useDBus) {
            items.push('DBus')
        }
        return items
    }

    property stringList modulePlugins: [
        'bearer', 'iconengines', 'imageformats', 'platforms', 'printsupport', 'translations',
        'styles'
    ]
    property stringList moduleQml: []
    property stringList moduleResources: []
    property stringList moduleTranslations: []

    // 3rdpart

    Group {
        name: '3rdpart'
        prefix: Qt.core.binPath + '/'
        files: module3rdpart
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
    }

    // general

    Group {
        name: 'general'
        prefix: Qt.core.binPath + '/'
        files: {
            var files = []
            moduleGeneral.forEach(function(item){
                files.push('Qt' + Qt.core.versionMajor + item + EnvUtils.dylibSuffix(qbs))
            })
            return files
        }
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
    }

    // plugins

    Group {
        name: 'plugins'
        prefix: Qt.core.pluginPath + '/'
        files: {
            var files = []
            modulePlugins.forEach(function(item){
                files.push(item + '/**/*.dll')
            })
            return files
        }
        excludeFiles: [ EnvUtils.excDylibFuzzy(qbs, true) ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'plugins'
        qbs.installSourceBase: prefix
    }

    // qml

    Group {
        name: 'qml'
        prefix: Qt.qml.qmlPath + '/'
        files: {
            var files = []
            moduleQml.forEach(function(item){
                files.push(item + '/**/*')
            })
            return files
        }
        excludeFiles: [ '**/*.qmlc', '**/*.jsc', '**/*.qmltypes', EnvUtils.excDylibFuzzy(qbs, true) ]
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'qml'
        qbs.installSourceBase: prefix
    }

    // resources

    Group {
        name: 'resources'
        prefix: Qt.core.binPath + '/../resources/'
        files: moduleResources
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'resources'
        qbs.installSourceBase: prefix
    }

    // translations

    Group {
        name: 'translations'
        prefix: Qt.core.binPath + '/../translations/'
        files: moduleTranslations
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'translations'
        qbs.installSourceBase: prefix
    }

    // qt.conf

    Rule {
        condition: generateQtConf
        multiplex: true
        Artifact {
            fileTags: [ 'qt.conf.out' ]
            filePath: FileInfo.joinPaths(product.dataTargetPath, 'qt.conf')
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'generating ' + output.fileName + '...'
            cmd.highlight = 'codegen'
            cmd.sourceCode = function() {
                var file = new TextFile(output.filePath, TextFile.WriteOnly)
                file.write('[Paths]\n' +
                           'Prefix=.\n' +
                           'Binaries=.\n' +
                           'Libraries=.\n' +
                           'Plugins=plugins\n' +
                           'Imports=imports\n' +
                           'Qml2Imports=qml')
                file.close()
            }
            return [ cmd ]
        }
    }
}
