# iOS JavaScript与Native交互学习笔记

------
## 通过UIWebView代理方法
```objc
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;
```
* 当点击 URL 进行页面跳转或者刷新页面的时候，UIWebView 会调用上面的方法，用上面的代理方法来截获这个 request 的参数就可以做 native 需要做的事情。
* 这中方法其实是用过 URL 来传递参数，有很多缺点，如较大的数据不能传递，对象类型的数据不能传递，**不推荐使用**。
* 有个开源的第三方可以去看看。[WebViewJavascriptBridge](https://github.com/marcuswestin/WebViewJavascriptBridge)

## JavaScriptCore framework
0. 说明： JavaScriptCore 是封装了 JavaScript 和 Objective-C 桥接的Objective-C API，只需要较少的的代码，就可以实现 JavaScript 与 Objective-C 的相互调用。
0. **iOS 7** 之后苹果推出了 JavaScriptCore 这个框架，从而让 web 页面和本地原生应用交互起来非常方便，而且使用此框架可以做到 Android 那边和 iOS 相对统一，web 前端写一套代码就可以适配客户端的两个平台，从而减少了 web 前端的工作量。
0. JavaScriptCore 中 web 页面调用原生应用的方法可以用 Delegate 或 Block 两种方法。
0. JavaScriptCore 中类及协议:
   * JSContext：给 JavaScript 提供运行的上下文环境，JSContext 是代表 JS 的执行环境，通过 -evaluateScript: 方法就可以执行 JS 代码。
   * JSValue：JSValue封装了 JS 与 ObjC 中的对应的类型，以及调用 JS 的 API 等，可以理解为 JavaScript 和 Objective-C 数据和方法的桥梁。[JSValue和Objective-C对应关系](https://developer.apple.com/library/ios/documentation/JavaScriptCore/Reference/JSValue_Ref/)
   * JSManagedValue：管理数据和方法的类。
   * JSVirtualMachine：处理线程相关，使用较少。
   * JSExport：JSExport 是一个协议，遵守此协议，就可以定义我们自己的协议，在协议中声明的 API 都会在 JS 中暴露出来，才能调用。
   
##下面介绍交互
0. oc 调用 js 的两种方法:
   * 使用 webview 调用 stringByEvaluatingJavaScriptFromString  
   * 例如：
   
   		```objc
   [self.webView stringByEvaluatingJavaScriptFromString:@"alert('这是个弹框')"];
   ```
   * 使用 JSContext 的方法 -evaluateScript,	这个方法就是执行一行 js 的代码
   * 例如：

   		```objc
   JSContext *context = [webView valueForKeyPath:@"documentView.webView.mainFrame.javaScriptContext"];
   [context evaluateScript: @"alert('这是个弹框')"]
   ```
0. js 调用 oc 的方法：
   * 这里主要说一下把我们创建的对象赋值给 JS 的对象;
   * 上面提到的，JSExport 就是一个协议，遵守这个协议，我们就可以在里面写自己的方法（js 定义的方法或者我们写方法让 js 去调）;
   * 创建一个类，导入头文件 JavaScriptCore/JavaScriptCore.h;
   * js的方法分为无参数和有参数的方法;
   * **无参数**：在我们这个类里面写一个有返回值无参数的方法，方法名和js的方法名相同，在.m中实现这个方法;
	* 例如：js想要获取我们APP当前的版本号，我们就可以定个方法;
         
         ```objc
     - (NSString *)getVersion;
     ```
     
     * 在.m中实现：
     
     		```objc
     		- (NSString *)getVersion{
     		    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
     		    NSString *appVersion = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
     		    return appVersion;
}
     ```
     
	* **有参数**：就是js的方法带有一个或者多个参数，这里说两种方法:
     * 把js的方法名进行拆分
     例如：js想要我们这边算一个加法，js的方法为getSum(A,B);带有两个参数A,B;
     * 我们就可以把方法拆分为

     		``` objc 
     -	(NSInteger)get:(id)number1  Sum:(id)number2;
           //这样其实也就是把js的方法名拆开，拼起来是js的方法名就行
```
     * .m实现：
     
     		```objc 
     - (NSInteger)get:(id)number1 Sum:(id)number2{
				NSInteger result = [number1 integerValue] + [number2 integerValue];
				return result;
}
     ```
     
     *	**这里有一个问题，如果js的参数比较多的话，那么我们这边就拆分就比较麻烦，js的方法名也要写的很长，所以就有了一个更好的系统的方法:**
     
     		```objc
      JSExportAs(PropertyName,Selector)
		```
     * 这个宏定义的方法有两个参数:
       		0. PropertyName这个就是js的方法名
       		0. Selector我们定义的方法需要用来完成js要做的事
      
      * 例如：还是算个加法

      		```objc
      JSExportAs(getSum, - (NSInteger)getNumsumNumber1:(id)num1 number2:(id)num2 number3:(id)num3);
//num1  num2   num3  js传过来的参数（一般有个几参数就要用几个来接收）
      ```
     * .m实现：

     		```objc
     - (NSInteger)getNumsumNumber1:(id)num1 number2:(id)num2 number3:(id)num3{
     			NSInteger result = [num1 integerValue] + [num2 integerValue] + [num3 integerValue];
     			//retrun 就是返回给js的结果
     			return result;
}
     ```
    
     * 这个宏定义的方法在有多个参数的时候，js不用写很长的方法名，减少了前端的工作量。
     
## 总结

运用JavaScriptCore这个系统库，更好的解决了与js交互的各种问题，减少了不必要的麻烦。不用再去使用第三方的库类，减少了项目的负载。

—— 张鹏 2016.8.2
  



