//
//  BOTContentViewController.m
//  botbrain_feed_sdk_ios_demo
//
//  Created by ZHAN on 2017/11/7.
//  Copyright © 2017年 BotBrain. All rights reserved.
//

#import "BOTContentViewController.h"
#import <BotBrainPods/BotBrainManager.h>

#define BOTAppKey       @"S4EBUTASGJ"
#define BOTAppSecret    @"6E12AZUHNNP3YAWCEJR83G"

@interface BOTContentViewController ()<BotBrainFeedDelegate, BotBrainFeedDetailDelegate>

@end

@implementation BOTContentViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self config];
    [self configTabUI];
    [self configDetailUI];
    [BOTBrainDefaultManager addFeedDelegate:self];
    [BOTBrainDefaultManager addFeedDetailDelegate:self];
    [BOTBrainDefaultManager addBotBrainFeedOnView:self.view inViewController:self];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Config
// AppKey AppSecret
- (void)config {
    BotBrainConfig *config = [BotBrainConfig botDefaultConfig];
    config.appKey = BOTAppKey;
    config.appSecret = BOTAppSecret;
    [BotBrainManager startWithConfigure:config];
}

// 修改栏目标签UI
- (void)configTabUI {
    BotBrainFeedTabConfig *tabConfig = [[BotBrainFeedTabConfig alloc] init];
    tabConfig.tabIndicatorHeight = 2;
    tabConfig.tabIndicatorColor = [UIColor redColor];
    tabConfig.tabBackgroundColor = [UIColor colorWithWhite:0.90 alpha:1.];
    tabConfig.tabTextNormalAttributes = @{NSFontAttributeName: [UIFont systemFontOfSize:15], NSForegroundColorAttributeName: [UIColor blackColor]};
    tabConfig.tabTextSelectedAttributes = @{NSFontAttributeName: [UIFont boldSystemFontOfSize:17], NSForegroundColorAttributeName: [UIColor redColor]};
    BOTBrainDefaultManager.configure.feedTabConfig = tabConfig;
}
// 修改详情部分UI
- (void)configDetailUI {
    BOTBrainDefaultManagerDetailConfig.detailLeftItemContent = @"返回";
    BOTBrainDefaultManagerDetailConfig.detailRightItemContent = @"分享";
}

- (void)configFeedTip {
    BOTBrainDefaultManagerListConfig.tipViewBackgroundColor = [UIColor cyanColor];
    BOTBrainDefaultManagerListConfig.tipTextAttributed = @{NSFontAttributeName: [UIFont systemFontOfSize:14], NSForegroundColorAttributeName: [UIColor whiteColor]};
}

#pragma mark - BotBrainFeedDelegate

- (UIView *)viewForNoResultTableViewAtIndex:(NSInteger)index {
    
    UILabel *emptyView = [UILabel new];
    emptyView.backgroundColor = [UIColor whiteColor];
    emptyView.text = @"出错了，点击屏幕重新加载";
    emptyView.textAlignment = NSTextAlignmentCenter;
    emptyView.userInteractionEnabled = YES;
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(reloadFeed:)];
    [emptyView addGestureRecognizer:tapGesture];
    return emptyView;
}

// 返回一个服从 BotBrainFeedRefreshProtocol 的 View
- (UIView<BotBrainFeedRefreshProtocol> *)botRefreshHeaderForFeed {
    return nil;
}
// 返回一个服从 BotBrainFeedRefreshProtocol 的 View
- (UIView<BotBrainFeedRefreshProtocol> *)botRefreshFooterForFeed {
    return nil;
}


#pragma mark - BotBrainFeedDetailDelegate

- (void)botBrainDidShareWithShareModel:(BotBrainFeedShareModel *)shareModel {
    NSLog(@"点击顶部分享：%@", shareModel);
}

- (void)botBrainDidTapBottomShareWithShareModel:(BotBrainFeedShareModel *)shareModel {
    NSLog(@"点击底部分享：%@", shareModel);
}

- (void)botbrainWillLikeWithShareModel:(BotBrainFeedShareModel *)shareModel{
    NSLog(@"将要点赞：%@", shareModel);
}

- (void)botBrainDidLikeWithShareModel:(BotBrainFeedShareModel *)shareModel {
    NSLog(@"点赞：%@", shareModel);
}


- (void)botBrainDidCommentWithShareModel:(BotBrainFeedShareModel *)shareModel {
    NSLog(@"评论：%@", shareModel);
}

- (void)botBrainDidSelectedFeedItemWithShareModel:(BotBrainFeedShareModel *)shareModel {
    NSLog(@"阅读文章：%@", shareModel);
}


- (void)botBrainWillCommentWithShareModel:(BotBrainFeedShareModel *)shareModel {
    NSLog(@"将要评论：%@", shareModel);
    if ([BotBrainManager defaultManager].isLogin) {
        NSLog(@"已登录");
        return;
    }
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"评论前请先登录" message:nil preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *ensureAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self logInCommentSystem];
    }];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        
    }];
    [alert addAction:ensureAction];
    [alert addAction:cancelAction];
    [[BotBrainManager currentShowViewController] presentViewController:alert animated:YES completion:nil];
}

#pragma mark - private method

- (void)logInCommentSystem {
    BotBrainUserInfoModel *model = [BotBrainUserInfoModel new];
    model.userID = @"ca06423f8fe046399b3d65bdc2956075";
    model.userIcon = @"http://image-1252904967.costj.myqcloud.com/user_info/S4EBUTASGJ/1501476770200.jpg";
    model.userNickName = @"BotBrain007";
    [[BotBrainManager defaultManager] loginWithUserInfo:model success:^(BotBrainUserInfoModel *userInfo) {
        NSLog(@"登录成功：%@", userInfo);
    } failure:^(NSError *error) {
        NSLog(@"登录失败：%@", error);
    }];
}

- (void)reloadFeed:(UITapGestureRecognizer *)gesture {
    [[BotBrainManager defaultManager] reloadCurrentShowFeedListData];
}

@end
