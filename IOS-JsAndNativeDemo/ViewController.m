//
//  ViewController.m
//  IOS-JsAndNativeDemo
//
//  Created by zhangPeng on 16/8/17.
//  Copyright © 2016年 ZhangPeng. All rights reserved.
//

#import "ViewController.h"
#import "WebViewTest.h"
#import "WKWebViewTest.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    
    
}
//webview与js交互界面
- (IBAction)webViewBtnClick:(UIButton *)sender {
    WebViewTest *webTest = [[WebViewTest alloc]init];
    [self.navigationController pushViewController:webTest animated:YES];
}
//wkwebview与js交互界面
- (IBAction)wkWebViewBtnClick:(UIButton *)sender {
    WKWebViewTest *wkWebTest = [[WKWebViewTest alloc]init];
    [self.navigationController pushViewController:wkWebTest animated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
