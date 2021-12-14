//
//  GLView.h
//  BreaktheBlocks
//
//  Created by nayayrei on 2021/12/14.
//

#import <UIKit/UIKit.h>
#import "SceneManager.h"
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>

//
//Define GLES_SILENCE_DEPRECATION
@interface GLView : UIView
{
    EAGLContext* m_context;
    CAEAGLLayer* eaglLayer;
    SceneManager* sceneManager;
}


- (void) drawView: (CADisplayLink*) displayLink;
@end
