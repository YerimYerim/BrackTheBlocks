//
//  OpenglUIView.h
//  BreaktheBlocks
//
//  Created by nayayrei on 2021/12/13.
//

#import <UIKit/UIKit.h>
#include "SceneManager.h"
NS_ASSUME_NONNULL_BEGIN

@interface OpenglUIView : UIView
{
    EAGLContext *m_context;

}
@end

NS_ASSUME_NONNULL_END
