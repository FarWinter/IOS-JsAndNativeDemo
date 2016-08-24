//
//  TextActionProxy.h
//  IOS-JsAndNativeDemo
//
//  Created by zhangPeng on 16/8/22.
//  Copyright © 2016年 ZhangPeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>

//首先创建一个实现了JSExport协议的协议
@protocol TestJSObjectProtocol <JSExport>

/**
 *  获取版本号
 *  无参数
 *  @return version
 */
- (NSString *)getVersion;

/**
 *  加法
 *  1.拆分js方法名
 *  例如：js方法为getNumSum  我们就把方法拆分为- (NSInteger)get:(id)number1 Num:(id)number2 Sum:(id)number3
 *  oc参数名拼起来要成为js的方法名
 */
//- (NSInteger)get:(id)number1 Num:(id)number2 Sum:(id)number3;


/**
 * Note that the JSExport macro may only be applied to a selector that takes one
 or more argument.
 * 译： JSExport只适用于一个或多个参数
 
 *  2.运用 JSExportAs(<#PropertyName#>, <#Selector#>)
 *  <#PropertyName#> --> js的方法名
 *  <#Selector#> -->  我们定义的方法需要用来完成js要做的事
 *  num1  num2   num3  js传过来的参数（一般有个几参数就要用几个来接收）
 */

JSExportAs(getSum, - (NSInteger)getNumsumNumber1:(id)num1 number2:(id)num2 number3:(id)num3);

/**
 *  调用svp
 */

- (void)showNotice;

@end


@interface TestActionProxy : NSObject<TestJSObjectProtocol>

@end
