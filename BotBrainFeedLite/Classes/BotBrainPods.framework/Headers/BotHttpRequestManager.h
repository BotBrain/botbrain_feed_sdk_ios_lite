//
//  BotHttpRequestManager.h
//  BotBrainLib
//
//  Created by ZHAN on 2017/5/10.
//  Copyright © 2017年 ZHAN. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BotHttpRequestModel;

// 请求成功回调block
typedef void(^BotHttpSuccessCallBack)(NSURLSessionDataTask *task, id responseObject);
// 请求失败回调block
typedef void(^BotHttpFailureCallBack)(NSURLSessionDataTask *task, NSError *error);

@interface BotHttpRequestManager : NSObject

+ (instancetype)sharedManager;


/**
 发起一个网络请求

 @param model 请求配置Model
 @param success 成功
 @param failure 失败
 @return NSURLSessionDataTask
 */
- (NSURLSessionDataTask *)httpRequestWithModel:(BotHttpRequestModel *)model
                                       success:(BotHttpSuccessCallBack)success
                                       failure:(BotHttpFailureCallBack)failure;

/**
 *  上传文件网络请求
 *
 *  @param model    请求模型
 *  @param success  成功回调
 *  @param failure  失败回调
 *
 *  @return NSURLSessionDataTask
 */
- (NSURLSessionDataTask *)httpFileRequestWithModel:(BotHttpRequestModel *)model
                                           success:(BotHttpSuccessCallBack)success
                                           failure:(BotHttpFailureCallBack)failure;

@end
