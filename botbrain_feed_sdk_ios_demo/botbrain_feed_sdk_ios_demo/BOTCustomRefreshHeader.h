//
//  BOTCustomRefreshHeader.h
//  botbrain_feed_sdk_ios_demo
//
//  Created by ZHAN on 2017/11/7.
//  Copyright © 2017年 BotBrain. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BotBrainPods/BotBrainFeedRefreshProtocol.h>

@interface BOTCustomRefreshHeader : UIView<BotBrainFeedRefreshProtocol>

@property (nonatomic, strong) UILabel *textLabel;

@end
