//
//  BOTCustomRefreshFooter.m
//  botbrain_feed_sdk_ios_demo
//
//  Created by ZHAN on 2017/11/7.
//  Copyright © 2017年 BotBrain. All rights reserved.
//

#import "BOTCustomRefreshFooter.h"

@implementation BOTCustomRefreshFooter

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.textLabel = [[UILabel alloc] init];
        [self addSubview:_textLabel];
        _textLabel.center = self.center;
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    _textLabel.center = self.center;
}

- (void)configTextLabelWithString:(NSString *)string {
    self.textLabel.text = string;
    [self.textLabel sizeToFit];
    self.textLabel.center = self.center;
}

#pragma mark - BotBrainFeedRefreshProtocol
// Footer 的高度
- (CGFloat)botHeightForRefreshHeader {
    return 50;
}
// 刷新状态
- (void)botRefreshStateWithType:(BotFeedRefreshType)type {
    switch (type) {
        case BotFeedRefreshType_Idle:
            [self configTextLabelWithString:@"上拉刷新数据"];
            break;
        case BotFeedRefreshType_Pulling:
            [self configTextLabelWithString:@"松手立即刷新"];
            break;
        case BotFeedRefreshType_Refreshing:
            [self configTextLabelWithString:@"正在加载更多..."];
            break;
        case BotFeedRefreshType_NoMoreData:
            [self configTextLabelWithString:@"没有数据了"];
            break;
        default:
            break;
    }
}

// 下拉时的百分比
- (void)botRefreshPullingPercent:(CGFloat)pullingPercent {
    
}


@end
