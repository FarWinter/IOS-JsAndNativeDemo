# IOS  JS与Native交互学习分享

------
## 通过webview代理方法
```objc
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType；
```
* 当触发上面的js，webview会收到回调，用上面的代理方法来截获这个request的参数就可以做native需要做的事情。
* 这中方法比较的麻烦不够清晰，**不推荐使用**。
* 有个开源的第三方可以去看看。[WebViewJavascriptBridge][1]

## 从ios7开始苹果公布了JavaScriptCore.framework 这个系统库，用来解决JS与OC的交互。
0. 说明： JavaScriptCore是封装了JavaScript和Objective-C桥接的Objective-C API，只需要较少的的代码，就可以实现JavaScript与Objective-C的相互调用。
0. iOS7之后苹果推出了JavaScriptCore这个框架，从而让web页面和本地原生应用交互起来非常方便，而且使用此框架可以做到Android那边和iOS相对统一，web前端写一套代码就可以适配客户端的两个平台，从而减少了web前端的工作量。


  [1]: https://github.com/marcuswestin/WebViewJavascriptBridge



