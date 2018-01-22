//
//  BotBrainFeedDetailProtocol.h
//  BotBrainLib
//
//  Created by ZHAN on 2017/5/10.
//  Copyright © 2017年 ZHAN. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import "BotBrainFeedRefreshProtocol.h"

@class BotBrainFeedColumnModel;
@class BotBrainFeedShareModel;

#pragma mark - BotFeedPlaceholderCellModelDelegate
// ========================================
// 自定义的 Cell 相关 DataModel 需要服从此协议
// ========================================
@protocol BotFeedPlaceholderCellModelDelegate <NSObject>

// 自定义Cell的下标
@property (nonatomic, assign) NSInteger index;
// 占位Cell要插入的位置，下标从0开始。注意：每次更新的数据条数为6，所以每次插入的位置范围要保证在 0 —— 6
@property (nonatomic, assign) NSInteger insertIndex;
// 自定义Cell高度
@property (nonatomic, assign) CGFloat cellHeight;

@end


#pragma mark - BotBrainFeedDelegate
// ========================================
// Feed流相关的一些代理方法
// ========================================
@protocol BotBrainFeedDelegate <NSObject>

@optional

/**
 Feed 流自定义刷新 Header

 @return 自定义 Header
 */
- (UIView<BotBrainFeedRefreshProtocol> *)botRefreshHeaderForFeed;

/**
 Feed 流自定义加载更多 Footer

 @return 自定义 Footer
 */
- (UIView<BotBrainFeedRefreshProtocol> *)botRefreshFooterForFeed;

/**
 当没有数据时显示的View
 
 @param index 当前列表下标，对应栏目，从0开始
 @return UIView
 */
- (UIView *)viewForNoResultTableViewAtIndex:(NSInteger)index;

/**
 宿主自定义的view，会被作为header的一部分，插入在搜索或者Banner和Feed之间。
 自定View的时候请设置view的frame。
 @param index 栏目下标，针对不同的栏目可定义不同的Header
 @return UIView
 */
- (UIView *)viewForFeedListHeaderAtIndex:(NSInteger)index;

/**
 动态返回配置的theme name

 @param themeName theme name
 */
- (void)didLoadThemeName:(NSString *)themeName;

/**
 栏目加载成功的回调

 @param columnssArray 栏目数据
 */
- (void)didLoadFeedColumnssArray:(NSArray <BotBrainFeedColumnModel *>*)columnssArray;

/**
 宿主可自定义显示部分栏目

 @param array 原始栏目数组
 @return 返回过滤后的栏目数组
 */
- (NSArray<BotBrainFeedColumnModel *> *)filterFeedListColumnWithOriginArray:(NSArray <BotBrainFeedColumnModel *>*)array;

#pragma mark - BotBrainFeedDelegate —— PlaceholderCell
/// 此方法会在刷新或者加载更多成功的时候回调，columnID 为栏目的下标
- (id<BotFeedPlaceholderCellModelDelegate>)cellModelForPlaceholderCellWithColumnID:(NSInteger)columnID;
/// 自定义的Cell，自主实现UI渲染，index为 CellModel的index，不是整个Feed流的 index
- (UITableViewCell *)placeholderCellForTableView:(UITableView *)tableView atIndex:(NSInteger)index;
/// 选中自定义Cell时的回调
- (void)didSelectedPlaceholderCellWithCellModel:(id<BotFeedPlaceholderCellModelDelegate>)cellMoel;

#pragma mark - BotBrainFeedDelegate —— DEPRECATED_MSG
/**
 控制左右滑动切换不同栏目
 
 @return 返回YES时禁止左右滑动
 */
- (BOOL)feedShouldForbidRoll DEPRECATED_MSG_ATTRIBUTE("Use BotBrainConfig feedListConfig forbidHorizontalScroll");

@end


#pragma mark - BotBrainFeedDetailDelegate
// ========================================
// 详情页面相关代理方法
// ========================================
@protocol BotBrainFeedDetailDelegate <NSObject>

@optional

#pragma mark - BotBrainFeedDetailDelegate —— Action
/**
 分享 - 点击详情右上角时
 
 @param shareModel 当前Model
 */
- (void)botBrainDidShareWithShareModel:(BotBrainFeedShareModel *)shareModel;
/**
 分享 - 点击底部分享按钮时
 
 @param shareModel 当前Model
 */
- (void)botBrainDidTapBottomShareWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
 点赞 — 点击点赞按钮时
 
 @param shareModel 当前model
 */
- (void)botbrainWillLikeWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
 点赞 - 点赞成功或者失败
 
 @param shareModel 当前Model
 */
- (void)botBrainDidLikeWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
 不喜欢

 @param shareModel 当前Model
 */
- (void)botBrainDidDisLikeWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
 发布评论 - 将要回复评论时（可实现此方法来提示用户登录）
 
 @param shareModel 当前Model
 */
- (void)botBrainWillCommentWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
 发布评论 - 评论发送结束 成功或者失败
 
 @param shareModel 当前Model
 */
- (void)botBrainDidCommentWithShareModel:(BotBrainFeedShareModel *)shareModel;
/**
 点击评论数
 
 @param shareModel 当前Model
 */
- (void)botBrainDidTapCommentNumberWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
 收藏事件回调

 @param shareModel 当前Model
 @param state  YES: 收藏  NO: 取消收藏
 */
- (void)botBrainDidCollectWithShareModel:(BotBrainFeedShareModel *)shareModel collectState:(BOOL)state;
/**
 点击Feed流阅读文章
 
 @param shareModel 当前点击的Model
 */
- (void)botBrainDidSelectedFeedItemWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
 用户搜索

 @param searchText 搜索的关键词
 */
- (void)botBrainDidSearchWithSearchText:(NSString *)searchText;


/**
 是否用 Safari 打开原文

 @param URLString 原文地址
 @return  BOOL YES：用 Safari 打开，NO：用 SDK WebView 打开
 */
- (BOOL)botNeedUseSDKOpenSourceURLString:(NSString *)URLString;

#pragma mark - BotBrainFeedDetailDelegate —— UI

/**
 注意：此设置仅在以view方式添加图文列表，并且详情页以模态展示时有效
 详情NavigationBar背景色默认 whiteColor
 
 @return UIColor
 */
- (UIColor *)backgroundColorForDetailNavigationBar;
/**
 注意：此设置仅在以view方式添加图文列表，并且详情页以模态展示时有效
 详情NavigationBar文字颜色,默认 blackColor
 
 @return UIColor
 */
- (UIColor *)tintColorForDetailNavigationBar;

#pragma mark - BotBrainFeedDetailDelegate —— DEPRECATED_MSG

/**
 自定义返回详情right item显示内容，只接受NSString类型或者UIImage类型，返回nil则不显示
 
 @return NSString or UIImage
 */
- (id)objectForFeedDetailRightBarButtonItem DEPRECATED_MSG_ATTRIBUTE("Use BotBrainConfig feedDetailConfig detailRightItemContent");

/**
 注意：此设置仅在以view方式添加图文列表，并且详情页以模态展示时有效
 自定义返回详情left item显示内容，只接受NSString类型或者UIImage类型，默认显示关闭
 
 @return NSString or UIImage
 */
- (id)objectForFeedDetailLeftBarButtonItem DEPRECATED_MSG_ATTRIBUTE("Use BotBrainConfig feedDetailConfig detailLeftItemContent");

@end
