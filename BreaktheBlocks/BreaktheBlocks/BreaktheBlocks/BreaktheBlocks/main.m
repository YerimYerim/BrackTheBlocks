//
//  main.m
//  BreaktheBlocks
//
//  Created by nayayrei on 2021/12/13.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    // Setup code that might create autoreleased objects goes here.
    appDelegateClassName = NSStringFromClass([AppDelegate class]);
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, appDelegateClassName);
    }
  
}
