//
//  BotBrainConfig.h
//  Pods
//
//  Created by ZHAN on 2017/9/11.
//
//

#import <Foundation/Foundation.h>
/// 全局配置相关类
@class BotBrainFeedListConfig;
@class BotBrainFeedDetailConfig;
@class BotBrainFeedTabConfig;

// 更新提示 前部分 Key
FOUNDATION_EXTERN NSString *const BOTBRAINFEEDTIPTEXTFRONTKEY;
// 更新提示 后部分 Key
FOUNDATION_EXTERN NSString *const BOTBRAINFEEDTIPTEXTBEHINDKEY;

@interface BotBrainConfig : NSObject

/** SDK默认配置，不要重复调用此方法 */
+ (BotBrainConfig *)botDefaultConfig;
/** 用户AppKey */
@property (nonatomic, copy) NSString *appKey;
/** 用户AppSecret */
@property (nonatomic, copy) NSString *appSecret;
/** 渠道，默认AppStore */
@property (nonatomic, copy) NSString *channel;
/** 是否输出Log，默认 NO */
@property (nonatomic, assign) BOOL logEnabled;
/** 关闭广告 */
@property (nonatomic, assign) BOOL closeAD;
/** Feed流配置 */
@property (nonatomic, strong) BotBrainFeedListConfig *feedListConfig;
/** 详情配置 */
@property (nonatomic, strong) BotBrainFeedDetailConfig *feedDetailConfig;
/** 标签栏UI配置，需要修改时初始化该实例然后调用 set 方法赋值 */
@property (nonatomic, strong) BotBrainFeedTabConfig *feedTabConfig;

@end

/// Feed流相关配置
@interface BotBrainFeedListConfig : NSObject

/** 隐藏Feed流顶部栏目view， 默认NO，即显示栏目view */
@property (nonatomic, assign) BOOL hideColumnView;
/** 是否禁止左右滑动切换不同的栏目，默认NO */
@property (nonatomic, assign) BOOL forbidHorizontalScroll;
/** Feed流顶部Banner的高度，默认200，后台配置才会显示Banner */
@property (nonatomic, assign) CGFloat bannerHeight;
/** Feed流数据更新提示背景色 */
@property (nonatomic, strong) UIColor *tipViewBackgroundColor;
/** Feed流数据更新提示文字样式 */
@property (nonatomic, strong) NSDictionary<NSString *, id> *tipTextAttributed;
/** Feed下拉数据加载成功提示文字，如：又更新了 N 条数据，需要传入 N 前后两部分字符串 */
// N 前部分字符串 Key：BOTBRAINFEEDTIPTEXTFRONTKEY
// N 后部分字符串 Key：BOTBRAINFEEDTIPTEXTBEHINDKEY
// 默认：又更新了N条数据
@property (nonatomic, copy) NSDictionary *tipSuccessTextDictionary;
/** Feed下拉数据无更新提示文字 */
/** 默认：休息一会儿，暂无更新 */
@property (nonatomic, copy) NSString *tipNoDataText;
/** Feed阅读历史提示文字颜色 */
@property (nonatomic, strong) UIColor *readHistoryTipTextColor;

@end

/// 详情相关配置
@interface BotBrainFeedDetailConfig : NSObject

/** 详情导航栏 RightItem，类型只能是 NSString 或者 UIImage 或者 UIButton，为nil时不显示 */
@property (nonatomic, strong) id detailRightItemContent;
/** 详情导航栏 LeftItem，类型只能是 NSString 或者 UIImage 或者 UIButton */
@property (nonatomic, strong) id detailLeftItemContent;
/** 未点赞图片 */
@property (nonatomic, strong) UIImage *likeNormalImage;
/** 已点赞图片 */
@property (nonatomic, strong) UIImage *likeSelectedImage;
/** 底部右下角分享图片 */
@property (nonatomic, strong) UIImage *bottomShareImage;

@end

@interface BotBrainFeedTabConfig : NSObject

// 注意：设置此Config后，标签栏的夜间模式不再生效，需要开发者自己根据不同的模式设置相关配置信息。
// 没有默认值的都需要开发者赋值，有默认值开发者按需赋值
/** 标签栏高度，默认40 */
@property (nonatomic, assign) CGFloat tabViewHeight;
/** 标签间隔，默认15 */
@property (nonatomic, assign) CGFloat tabItemSpace;
/** 标签栏背景色 */
@property (nonatomic, strong) UIColor *tabBackgroundColor;
/** 标签栏指示器颜色 */
@property (nonatomic, strong) UIColor *tabIndicatorColor;
/** 标签栏指示器的高度，0 — 隐藏，默认0 */
@property (nonatomic, assign) CGFloat tabIndicatorHeight;
/** 标签栏文字正常状态样式 */
@property (nonatomic, strong) NSDictionary<NSString *, id> *tabTextNormalAttributes;
/** 标签栏文字选中状态样式 */
@property (nonatomic, strong) NSDictionary<NSString *, id> *tabTextSelectedAttributes;

@end

