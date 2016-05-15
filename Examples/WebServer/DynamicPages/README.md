![Dynamic Page](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/blob/assets/dynamicPage.gif)

This example is the most advanced version of the [StaticPage](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/tree/master/Examples/WebServer/StaticPage). Here you'll see how to extract the URL that the browser would like to access. We're even going to support the 404 Page not Found Error.

# Pages

In this folder, you'll see many `.h` files that are used to separate the page content from the code itself. This way, we can keep the code clean.

Please don't treat these as system files. Each file contains a variable with the content formatted in a way that is more readable to us humans. The `include` command just copies and pastes the content of the `.h` files into the main app file. There isn't much more to it.
