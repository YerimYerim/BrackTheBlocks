//
//  GLView.m
//  BreaktheBlocks
//
//  Created by nayayrei on 2021/12/14.
//

#import "GLView.h"
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES3/gl.h>
#import "SceneManager.h"
#import <OpenGLES/ES3/glext.h>
@implementation GLView

+ (Class) layerClass{
    return [CAEAGLLayer class];
}
- (id) initWithFrame:(CGRect)frame{
    if (self = [super initWithFrame:frame]) {
        //Initialize code...
        eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES3;
        
        m_context = [[EAGLContext alloc] initWithAPI:api];
        [EAGLContext setCurrentContext:m_context];
        sceneManager = new SceneManager(CGRectGetWidth(frame),CGRectGetHeight(frame));
        [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable: eaglLayer];
 
        [self drawView: nil];
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    }
    return self;
}


- (void) drawView:(CADisplayLink*) displayLink{
    if(sceneManager != nil)
    {
        sceneManager->updateScene();
        sceneManager->getRoundCount();
        
    }
    [m_context presentRenderbuffer:GL_RENDERBUFFER];

}
@end
