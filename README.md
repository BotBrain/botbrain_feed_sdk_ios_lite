# botbrain_feed_sdk_ios_lite

[![Version](https://img.shields.io/cocoapods/v/botbrain_feed_sdk_ios_lite.svg?style=flat)](http://cocoapods.org/pods/botbrain_feed_sdk_ios_lite)
[![License](https://img.shields.io/cocoapods/l/botbrain_feed_sdk_ios_lite.svg?style=flat)](http://cocoapods.org/pods/botbrain_feed_sdk_ios_lite)
[![Platform](https://img.shields.io/cocoapods/p/botbrain_feed_sdk_ios_lite.svg?style=flat)](http://cocoapods.org/pods/botbrain_feed_sdk_ios_lite)

## 版本更新
#### v1.4.2
1. 添加详情分享和评论相关的开关，控制显示隐藏

#### v1.4.1
1. 配合新版推荐引擎更新，优化推荐效果；
2. 详情页部分 UI 修改；
3. 增加视频、音频、图集详情的支持；
4. 修复 bug。
#### v1.3.2
1. 处理低版本 Xcode 编译问题；
2. 修复 bug 。
#### v1.3.0

1. 栏目标签栏可自定义；
2. 更新提示 View 可自定义；
3. 下拉刷新样式可自定义；
4. 详情底部点赞和分享图标可自定义；
5. 新增阅读文章行为回调。

## SDK Demo
您可以下载 [SDK Demo](https://github.com/BotBrain/botbrain_feed_sdk_ios_demo) 查看基本使用方法，详细接入步骤请阅读以下文档。


## SDK使用方法

### 1、集成准备
**SDK支持最低版本为8.0。**

#### 1.1、获取AppKey和AppSecret

集成布本智能SDK之前，请您先获取相关的AppKey和AppSecret。
#### 1.2、项目工程集成配置

##### 1.2.1、CocoaPods集成
首先在 `Podfile` 文件中添加：

```
pod 'botbrain_feed_sdk_ios_lite', '~>1.4.2'
```

然后在终端 `cd` 到 `Podfile` 文件所在路径，执行 `pod install` 。

##### 1.2.2、手动集成

请先 [下载SDK](https://github.com/BotBrain/botbrain_feed_sdk_ios_lite) ，SDK包含 `BotBrainFeedLite` 下所有文件。
把SDK直接拖入进工程目录结构中，然后在选项 `TARGETS--> Build Phases-->Link Binary With Libraries` 中添加系统依赖库 `libz.tbd` 、`WebKit.framework`、`CoreMotion.framework`、`StoreKit.framework`。

然后在选项 `TARGETS--> Build Settings-->Linking-->Other Linker Flags` 添加 `-ObjC` 。

本SDK依赖于常用开源网络库 `AFNetworking` （要求最低版本3.0.0）, 图片处理库 `SDWebImage` （要求最低版本3.7.0），视频播放库 `ZFPlaye` (要求最低版本2.0.0)，请您自行导入工程。


### 2、基本功能集成
#### 2.1、配置 `AppDelegate.m`

导入头文件 `#import <BotBrainPods/BotBrainManager.h>`

在 `AppDelegate.m` 配置相关信息：

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

// 通过此方法初始化SDK，替换成自己的相关信息
BotBrainConfig *config = [BotBrainConfig botDefaultConfig];
config.appKey = @"S4EBUTASGJ";
config.appSecret = @"aaa";
config.logEnabled = YES;
[BotBrainManager startWithConfigure:config];

return YES;
}
```

或者使用下面的方法

`AppDelegate.m` 的配置主要是填写 `Appkey` 和 `AppSecret` 以及渠道标识 `channel` ，channel默认为“AppStore”。
代码示例如下:

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

// 通过此方法初始化SDK，替换成自己的相关信息
[BotBrainManager startWithAppKey:@"" appSecret:@"" channelID:@""];

return YES;
}
```

新版本可以打开 `Debug` 模式，打印出log，方便调试，开始方法：

```
[BotBrainManager setBotBrainLogEnable:YES];
```
请先于初始化SDK调用此方法开启 `Debug` 模式。

建议通过第一种方式开启服务，可通过 `BotBrainConfig` 配置来实现更多的 UI 自定义。


#### 2.2、展示图文列表

在你要展示图文列表的 `UIViewController` 中导入头文件 `#import <BotBrainPods/BotBrainManager.h>`。

在你想要展示图文列表的点击事件中调用如下代码：

```
[[BotBrainManager defaultManager] showBotBrainFeedOnViewController:self animated:YES];
```

SDK会优先选择Push方式显示ViewController，无法Push的时候会模态出一个带导航栏的图文列表。

你还可以直接添加到当前ViewController的view上：

```
[[BotBrainManager defaultManager] addBotBrainFeedOnView:self.view inViewController:self];
```

注意：分享后请调用以下方法：

```
[[BotBrainManager defaultManager] shareBotBrainFeedSuccess];
```
如果未调用此方法会影响内容的推荐效果。

#### 2.3、图文详情的回调

详情页的回调通过代理来实现。在你想要响应 `评论、点赞、分享` 等操作的类中实现代理方法即可。

首先让该类服从协议 `BotBrainFeedDetailDelegate`。
然后添加代理

```
[[BotBrainManager defaultManager] addFeedDetailDelegate:self];
```

最后在该类中实现代理方法。

目前提供的回调如下所示：

```
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
发布评论 - 将要回复评论时（可实现此方法来提示用户登录）

@param shareModel 当前Model
*/
- (void)botBrainWillCommentWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
发布评论 - 评论发送结束 成功或者失败的回调

@param shareModel 当前Model
*/
- (void)botBrainDidCommentWithShareModel:(BotBrainFeedShareModel *)shareModel;

/**
点击Feed流阅读文章

@param shareModel 当前点击的Model
*/
- (void)botBrainDidSelectedFeedItemWithShareModel:(BotBrainFeedShareModel *)shareModel;

```

其中发布评论时需要登录账号，接入者根据 `BotBrainManager` 类中属性 `isLoggedIn` 来判断当前用户是否已经登录，未登录、评论成功失败都会响应评论的代理方法， `shareModel` 里会返回相应的错误信息。

未登录时提示用户去登录，UI展示效果接入者自己实现，本地不保存用户信息，所以每次APP重新启动时都需要登录。
其中 `userID` 不能为空，其他自行选择传入，如果未传，则为默认。
登录时代码调用示例如下：

```
- (void)logInCommentSystem {
BotBrainUserInfoModel *userInfo = [BotBrainUserInfoModel new];
userInfo.userID = @"123456";
userInfo.userIcon = @"http://balabala";
userInfo.userNickName = @"BotBrain";
[[BotBrainManager defaultManager] loginWithUserInfo:userInfo success:^(BotBrainUserInfoModel *userInfo) {
NSLog(@"UserInfo：%@", userInfo);
} failure:^(NSError *error) {
NSLog(@"Error：%@", error);
}];
}
```


### 3、界面定制
目前提供有限定制，后期会开放更多。

#### 3.1、针对图文列表的定制：
图文列表相关的定制通过代理 `BotBrainFeedDelegate` 和 `BotBrainFeedListConfig` 来实现。

##### 3.1.1、部分UI修改方法

（1）可控制列表是否可以左右切换

```
BOTBrainDefaultManagerListConfig.forbidHorizontalScroll = YES;
```

（2）可隐藏和显示栏目

```
BOTBrainDefaultManagerListConfig.hideColumnView = YES;
```

（3）修改刷新成功后的顶部提示UI

```
// 背景色
BOTBrainDefaultManagerListConfig.tipViewBackgroundColor = [UIColor whiteColor];
// 提示文案样式
BOTBrainDefaultManagerListConfig.tipTextAttributed = @{NSFontAttributeName: [UIFont systemFontOfSize:14], NSForegroundColorAttributeName: [UIColor blackColor]};
```

（4）Feed流顶部栏目标签UI修改，此处需要初始化一个 `BotBrainFeedTabConfig` 的实例，进行相关UI修改后，给 `feedTabConfig` 赋值。

```
BotBrainFeedTabConfig *tabConfig = [[BotBrainFeedTabConfig alloc] init];
// 指示器高度，高度为0时隐藏
tabConfig.tabIndicatorHeight = 2;
// 指示器颜色
tabConfig.tabIndicatorColor = [UIColor redColor];
// 栏目标签背景色
tabConfig.tabBackgroundColor = [UIColor colorWithWhite:0.90 alpha:1.];
// 标签文字未选中样式
tabConfig.tabTextNormalAttributes = @{NSFontAttributeName: [UIFont systemFontOfSize:15], NSForegroundColorAttributeName: [UIColor blackColor]};
// 标签文字选中样式
tabConfig.tabTextSelectedAttributes = @{NSFontAttributeName: [UIFont boldSystemFontOfSize:17], NSForegroundColorAttributeName: [UIColor redColor]};
BOTBrainDefaultManager.configure.feedTabConfig = tabConfig;
```

（5）Feed流刷新样式修改，通过实现代理 `BotBrainFeedDelegate` 中的方法来返回一个服从 `BotBrainFeedRefreshProtocol` 协议的 `UIView` 的实例，代码如下：

```
- (UIView<BotBrainFeedRefreshProtocol> *)botRefreshHeaderForFeed {
BotUserCustomRefreshHeader *refreshHeader = [[BotUserCustomRefreshHeader alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(self.view.frame), 50)];
return refreshHeader;
}
```

`BotBrainFeedRefreshProtocol` 中定义了以下方法，由服从此协议的 View 去实现。

```
@required
// 返回自定义 Header 的高度
- (CGFloat)botHeightForRefreshHeader;
// 刷新状态，开发者可以在此方法中根据不同的状态设置不同样式
- (void)botRefreshStateWithType:(BotFeedRefreshType)type;

@optional
// 下拉时的百分比
- (void)botRefreshPullingPercent:(CGFloat)pullingPercent;
```

（6）详情底部点赞、分享图片修改

```
// 未点赞图片修改
BOTBrainDefaultManagerDetailConfig.likeNormalImage = [UIImage imageNamed:@"UnLikeImage"];
// 已点赞图片修改
BOTBrainDefaultManagerDetailConfig.likeSelectedImage = [UIImage imageNamed:@"LikeImage"];
// 底部分享按钮处图片修改
BOTBrainDefaultManagerDetailConfig.bottomShareImage = [UIImage imageNamed:@"ShareImage"];
```

注意：使用上述方法需使用 ` startWithConfigure: ` 方法初始化。

##### 3.1.2、图文列表无结果时展示View

通过实现方法 `- (UIView *)viewForNoResultTableViewAtIndex:(NSInteger)index;` 返回自定义的占位视图，默认空白。

代码示例如下：

```
- (UIView *)viewForNoResultTableViewAtIndex:(NSInteger)index {
UILabel *label = [[UILabel alloc] init];
label.text = @(index).stringValue;
label.font = [UIFont boldSystemFontOfSize:30];
return label;
}
```

如果发生没有数据展示的情况，可以调用方法来刷新列表数据：

```
[[BotBrainManager defaultManager] reloadBotBrainFeedDataAtIndex:0];
```

其中index下标从0开始，对应栏目下标。

##### 3.1.3、支持夜间模式
具体实现见Demo
##### 3.1.4、支持UC浏览器交互效果
具体实现见Demo

### 4、从Web端跳转到App并显示图文详情
SDK支持从分享出去的文章详情跳转到App对应的详情页，请提前在配置平台和工程中配置好 `URL Scheme` 。

为了能正确显示详情页，需要在 `AppDelegate` 文件中添加如下代码：

```
// iOS 8 请用这个
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
if ([BotBrainManager handleOpenURL:url]) {
[[BotBrainManager defaultManager] showBotBrainDetaiControllerWithURL:url onController:self.window.rootViewController];
return YES;
}
return YES;
}

// iOS 9 以上请用这个
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary *)options {
if ([BotBrainManager handleOpenURL:url]) {
[[BotBrainManager defaultManager] showBotBrainDetaiControllerWithURL:url onController:self.window.rootViewController];
return YES;
}
return YES;
}
```
其中，方法 `- showBotBrainDetaiControllerWithURL:onController`中参数 `controller` 是用来展示 `详情ViewController` 的，可以为 `nil` ，为 `nil` 时 `SDK` 会寻找当前显示 `ViewController` 来进行跳转。


### 5、常见问题
5.1、 针对 `iOS 9` 及以上系统的限制 `http` 协议的访问，如果 `App` 需要访问 `http://` ， 则需要在 `Info.plist` 添加如下代码:

```
<key>NSAppTransportSecurity</key>
<dict>
<key>NSAllowsArbitraryLoads</key>
<true/>
</dict>
```

5.2、针对使用 Xcode 7 编译失败，遇到错误信息为:

```
*** does not contain bitcode. You must rebuild it with bitcode enabled (Xcode setting ENABLE_BITCODE), obtain an updated library from the vendor, or disable bitcode for this target.
```
请到 `Xcode` 项目的 `Build Settings` 标签页搜索 `bitcode` ，将 `Enable Bitcode` 设置为 `NO` 即可。

5.3、共同依赖库版本冲突解决方法

SDK依赖的 `AFNetworking` 和 `SDWebImage` 的版本号已经是比较低的版本，如果还是发生了 `AFNetworking` 和 `SDWebImage` 依赖的版本有冲突，你可以 `fork` 一份代码到你的GitHub中，修改 `BotBrainFeed.podspec` 中依赖库的版本号，然后为SDK指定 `podspec` 源为你的GitHub中的地址。记得同时修改 `BotBrainFeed.podspec` 中 `s.source`。

5.4、无法搜索到 `botbrain_feed_sdk_ios`

如果遇见无法搜索到库 `botbrain_feed_sdk_ios` 的时候，请依次进行一下操作：

（1）更新 `CocoaPods` 本地 `repo`，在终端执行以下代码：

```
pod repo update
```
更新完成后再次尝试搜索。

（2）如果第一种方法依然无法解决问题，请在终端尝试以下操作：

```
rm ~/Library/Caches/CocoaPods/search_index.json
```
执行操作后再次尝试搜索。
注意：删除该文件后再次搜索会比较漫长，请耐心等待。

## Author

BotBrain, zhangzhan@firedata.cc

## License
Copyright (c) 2017 BotBrain. All rights reserved


