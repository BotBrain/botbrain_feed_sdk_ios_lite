//
//  BotHttpRequestModel.h
//  BotBrainLib
//
//  Created by ZHAN on 2017/5/10.
//  Copyright © 2017年 ZHAN. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, BotHttpRequestType) {
    BotHttpRequestType_GET,
    BotHttpRequestType_POST,
};

typedef NS_ENUM(NSUInteger, BotRequestDataType) {
    BotRequestDataType_Form,
    BotRequestDataType_Json,
};

@interface BotHttpRequestModel : NSObject

/** 域名 */
@property (nonatomic, copy) NSString *hostURL;
/** 请求 Path */
@property (nonatomic, copy) NSString *requetURL;
/** 请求参数 */
@property (nonatomic, copy) NSDictionary *parameterDic;
/** 上传文件参数，key：对应后台字段，value对应上传数据 */
@property (nonatomic, copy) NSDictionary <NSString *, NSData *>*fileDic;
/** 请求类型，默认GET */
@property (nonatomic, assign) BotHttpRequestType requestType;
/** 请求提交数据类型，默认 From 表单 */
@property (nonatomic, assign) BotRequestDataType dataType;

@end
