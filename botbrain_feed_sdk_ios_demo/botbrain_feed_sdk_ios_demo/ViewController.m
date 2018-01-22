//
//  ViewController.m
//  botbrain_feed_sdk_ios_demo
//
//  Created by ZHAN on 2017/11/7.
//  Copyright © 2017年 BotBrain. All righ.
//

#import "ViewController.h"
#import "BOTContentViewController.h"

@interface ViewController ()

@end

@implementation ViewController

#pragma mark - life cycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - create views


#pragma mark - event response
- (IBAction)showFeed:(UIButton *)sender {
    BOTContentViewController *contentViewController = [[BOTContentViewController alloc] init];
    [self.navigationController pushViewController:contentViewController animated:YES];
}


@end
