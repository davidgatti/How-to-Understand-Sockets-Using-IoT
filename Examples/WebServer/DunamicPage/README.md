![Dynamic Page](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/blob/assets/dynamicPage.png)

This examples is the most advance version of the [StaticPage](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/tree/master/Examples/WebServer/StaticPage). Here you'll see how to extract the URL that the browser would like to access. Will going to even support the page not found error 404.

# Pages

In this folder you'll see many `.h` files which are being used to separate the content of the pages from the code itself. This way we can keep the code clean.

Please don't treat this as system files. Each files contains a variable with the content formatted in a way that is more readable to us humans. The `include` command just copies and paste the content of the `.h` files in to the main app file. There isn't much more to it.

# Reliability

At this stage when you request a page with a modern browser you might not get a page back. My theory is that the browser makes extra request, like getting the Favicon end more. Right now the code doesn't handle well multiple request at the same time. If this happens, just cancel the request, wait one second, and try again.
