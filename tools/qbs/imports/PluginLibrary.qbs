import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile

CppLibrary {
    type: base.concat([ 'pluginSpec', 'qt_plugin_metadata' ])
    modulePath: 'plugins'

    Depends { name: 'Qt.core' }

    property string uri: ''
    property string uriDir: uri.replace('.', '/')
    property string pluginVersion: version.split('.', 2).join('.')
    property path destinationRoot: FileInfo.joinPaths(project.sourceDirectory, 'lib',
                                                      project.archDir, modulePath, 'meta')
    property stringList dependencies: []

    destinationDirectory: FileInfo.joinPaths(destinationRoot, uriDir)
    installDir: FileInfo.joinPaths(installPrefix, 'meta', uriDir)

    defaultCopyHeader: false
    defaultCopyDynamic: false
    defaultInstall: false
    defaultExport: false
    //cpp.useCxxPrecompiledHeader: false

    cpp.defines: {
        var items = base
        if (uri.length > 0) {
            items.push('PLUGIN_URI=\"' + uri + '\"')
        }
        return items
    }

    Group {
        fileTagsFilter: installFileTags
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: installDir
    }
}
