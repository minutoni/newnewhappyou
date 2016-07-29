#pragma once

#include "ofMain.h"

#define NUM 1000  //小さい箱の数を指定

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofSpherePrimitive sphere;
    
    ofBoxPrimitive mBox [NUM];
    
    int boxsize;
    
    ofEasyCam cam;
    
    ofVec2f p,vec; //p:前のマウスの位置(初期位置),vec:マウスの速度(ベクトル)
    
    ofImage BackgroundImage; //読み込む背景画像の宣言。
    
    ofSoundPlayer sound;
    
    ofLight light;
    
};
