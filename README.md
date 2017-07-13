Hot Reload QML files
====================

Experimental Project. It is not usable yet, but welcome for suggestion on the proposed API.

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

    // load state in previous run
    QByteArray state = loader.state();

    // Initialize QQmlApplicationEngine (e.g addImageProvider, setContextProperty etc)

    engine.load(loader.mappedUrl(":/main.qml")); 
    // If hotReloadEnabled is true, mappedUrl() insert `:/hot-loader-dynamic-resource` into the url.
    // It will become ":/hot-loader-dynamic-resource/main.qml"
    // If hotReloadEnabled is false, it will simply return the original value.

    // Set state according to the snapshot data

    /* Insert your code here*/

    loader.exec(); // Execute event loop. It will be terminated if any monitored files changed

    // Convert current state to snapshot data

    state =  /* Insert your code here*/

    // Save state snapshot
    loader.setState(state);
  });
  ```
  
  
