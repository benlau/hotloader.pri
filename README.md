Hot Reload QML files
====================

Proposed API

```
  HotLoader loader;

  #ifdef QT_DEBUG
  loader.setHotReloadEnabled(true); // By default, it is turned off.
  #endif

  loader.addResourceFile(SRCDIR + "qml.qrc");
  // Add a resource file to be loaded. It will call `rcc` to compile and load to HotLoader.resourceMapRoot()
  // If any file inside the qrc file was changed, it will trigger rebuild and restart the run()
  // If hotReloadEnabled is not true, this function will do nothing.               

  return loader.run([&]() {
    QQmlApplicationEngine engine;

    // Add HotLoader.resourceMapRoot() and `qrc:/` to the import path
    loader.init(&engine);

    // Snapshot data in previous run
    QByteArray snapshot = loader.snapshot();

    // Initialize QQmlApplicationEngine (e.g addImageProvider, setContextProperty etc)

    engine.load(loader.mappedUrl(":/main.qml")); 
    // If hotReloadEnabled is true, resolvedUrl() insert `:/hot-loader-dynamic-resource` into the url.
    // It will become ":/hot-loader-dynamic-resource/main.qml"
    // If hotReloadEnabled is false, it will simply return the original value.

    // Set state according to the snapshot data

    /* Insert your code here*/

    loader.exec(); // Execute event loop. It will be terminated if any monitored files changed

    // Convert current state to snapshot data

    /* Insert your code here*/
    snapshot = ....

    // Save snapshot data
    loader.setSnapshot(snapshot);
  });
  ```
  
  
