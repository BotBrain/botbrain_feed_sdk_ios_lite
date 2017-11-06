//
//  BotFeedRefreshProtocol.h
//  BotBrainPods
//
//  Created by ZHAN on 2017/10/28.
//

#ifndef BotBrainFeedRefreshProtocol_h
#define BotBrainFeedRefreshProtocol_h

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, BotFeedRefreshType) {
    // 闲置状态
    BotFeedRefreshType_Idle,
    // 下拉状态，松开刷新
    BotFeedRefreshType_Pulling,
    // 刷新中
    BotFeedRefreshType_Refreshing,
    // 数据加载完毕没有更多数据
    BotFeedRefreshType_NoMoreData,
};

// 自定义的刷新header服从此协议，并实现以下方法
@protocol BotBrainFeedRefreshProtocol

@optional
// 下拉时的百分比
- (void)botRefreshPullingPercent:(CGFloat)pullingPercent;

@required
// Header 的高度
- (CGFloat)botHeightForRefreshHeader;
// 刷新状态
- (void)botRefreshStateWithType:(BotFeedRefreshType)type;


@end


#endif /* BotBrainFeedRefreshProtocol_h */
