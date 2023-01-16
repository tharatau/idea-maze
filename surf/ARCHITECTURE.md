# Architecture

The application is broken into `chrome`, `render`, `service` "plugins". Plugins are third party libraries which are dynamically linked to the executable. How and what APIs the executable has access to is manually controlled by a `surf.json` or automatically using the application's `Plugin Store`.