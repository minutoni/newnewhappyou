#include "ofApp.h"

float loc_x[NUM]; //円のx座標
float loc_y[NUM]; //円のy座標
float loc_z[NUM]; //円のz座標

float speed_x[NUM]; //x軸方向のスピード
float speed_y[NUM]; //y軸方向のスピード
float speed_z[NUM]; //z軸方向のスピード

float radius[NUM]; //円の半径
int red[NUM]; //Red成分
int green[NUM]; //Green成分
int blue[NUM]; //Blue成分
bool mouse_pressed; //マウスはクリックされているか?



float gravity;
float friction;

int s;//秒
int s_num;//指標

int m;//分分
int m_num;//分指標

//--------------------------------------------------------------
void ofApp::setup(){
    
    BackgroundImage.loadImage("wall.jpg"); //画像を読み込む
    //BackgroundImage.draw(0, 0, ofGetWidth(),ofGetHeight());
    
    sound.loadSound("voyage(orchestra).mp3"); //音楽を読み込む。
    sound.play();//音楽を再生する。
    sound.setLoop(true);
    
    
    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0); //背景色の設定
    ofSetFrameRate(60); //フレームレートの設定
    ofSetCircleResolution(64); //円の解像度設定
    ofEnableAlphaBlending(); //アルファチャンネルを有効に
    mouse_pressed = false; //マウス状態を「クリックされていない」に
    ofEnableSmoothing();//スムーズに
    
    gravity = 0.1; //重力
    friction = 0.85;
    
    
    //NUMの数だけ初期値の生成を繰り返す
    for(int i = 0; i < NUM; i++){
        loc_x[i] = ofGetHeight()/2; //円のx座標初期位置
        loc_y[i] = ofGetWidth()/2; //円のy座標初期位置
        //loc_z[i] = -9223372036854775807; //円のz座標初期位置
        
        speed_x[i] = ofRandom(-10, 50); //x軸方向スピード初期値
        speed_y[i] = ofRandom(-30, 20); //y軸方向スピード初期値
        //speed_z[i] = ofRandom(-50, 8); //z軸方向スピード初期値
        
        radius[i] = ofRandom(1, 20); //の半径を設定
        red[i] = ofRandom(0, 255); //Red成分を設定
        green[i] = ofRandom(0, 255); //Green成分を設定
        blue[i] = ofRandom(0, 255); //Blue成分を設定
        
        
    }
    
    
    
    ofEnableDepthTest();
    
    light.enable();
    
    light.setSpotlight();
    
    light.setPosition(0,0,0);
    
    
    
    
    
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true); //画面の垂直同期をONに
    ofEnableAlphaBlending(); //透明度を有効化
    //ofToggleFullscreen(); //フルスクリーンにする。
    
    boxsize = 5; //boxの大きさ
    for (int i=0; i<NUM; i++ ){
        //boxの位置をランダムにする。
        mBox[i].setPosition(ofRandom(-500, 500),ofRandom(-500, 500),ofRandom(-500, 500));
        mBox[i].set(boxsize); //boxのサイズを１５に。
        
        
    }
    
    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //NUMの数だけ座標の更新を繰り返す
    for(int i = 0; i < NUM; i++){
        
        //マウスの現在位置からスピードを//もしマウスがクリックされていたらマウスに集ってくる
        if(mouse_pressed){
            //マウスの現在位置から円のスピードを再計算
            speed_x[i] = (mouseX - loc_x[i]) /2; //マウスのx座標と円のx座標の距離の1/8だけ接近
            speed_y[i] = (mouseY - loc_y[i]) /2;
            //speed_z[i] = (mouseZ - loc_z[i]) /2;
        }
        
        speed_x[i] = speed_x[i] * friction;
        speed_y[i] = speed_y[i] * friction;
        speed_z[i] = speed_z[i] * friction;
        
        loc_x[i] = loc_x[i] + speed_x[i]; //円のx座標を更新
        loc_y[i] = loc_y[i] + speed_y[i]; //円のy座標を更新
        //loc_z[i] = loc_z[i] + speed_z[i]; //円のz座標を更新
        
        //円の跳ね返り条件
        if(loc_x[i] < 0){
            loc_x[i] = 0;
            speed_x[i] = speed_x[i] * -1.0;
        }
        if(loc_x[i] > ofGetWidth()){
            loc_x[i] = ofGetWidth() ;
            speed_x[i] = speed_x[i] * -1.0;
        }
        if(loc_y[i] < 0){
            loc_y[i] = 0;
            speed_y[i] = speed_y[i] * -1.0;
        }
        if(loc_y[i] > ofGetHeight()){
            loc_y[i] = ofGetHeight();
            speed_y[i] = speed_y[i] * -1.0;
        }
        if(loc_z[i] < 0){
            loc_z[i] = 0;
            speed_z[i] = speed_z[i] * -1.0;
        }
        if(loc_z[i] > ofGetHeight()){  //*？
            loc_z[i] = ofGetHeight();
            speed_z[i] = speed_z[i] * -1.0;
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    //秒の取得
    int ms = ofGetElapsedTimeMillis() % 1000;
    //秒の取得
    s = ofGetSeconds();
    //分の取得
    m = ofGetMinutes() + (s/60.0);
    //時の取得
    float h = ofGetHours()%12 + (m/60);
    
    ofBackground(0, 0, 0);
    
    
    
    
    
    //-------------------------------------------------------------球//
    //NUMの数だけ円を描画する
    for(int i = 0; i < NUM; i++){
        ofSetColor(red[i], green[i], blue[i]); //描画色の設定
        ofSphere(loc_x[i], loc_y[i], loc_z[i], radius[i]); //円1を描画      //*?
    }
    
    if(!(s_num==s)){
        int col1 =ofRandom(0, 255);
        int col2 =ofRandom(0, 255);
        int col3 =ofRandom(0, 255);
        
        //円のスピードを再初期化
        //ofTranslate(ofGetWidth()*2, ofGetHeight()*2);
        
        for(int i = 0; i < NUM; i++){
            speed_x[i] = ofRandom(-20, 20); //x軸方向スピード初期値
            speed_y[i] = ofRandom(-20, 20); //y軸方向スピード初期値
            //speed_z[i] = ofRandom(-20, 20); //y軸方向スピード初期値
            
            red[i] = col1; //Red成分を設定
            green[i] = col2; //Green成分を設定
            blue[i] = col3; //Blue成分を設定
            radius[i] = ofRandom(1, 20); //円の半径を設定
            
        }
        s_num = s;
    }
    
    if(!(m_num==m)){
        //マウスの現在位置から円のスピードを再計算
        for(int i = 0; i < NUM; i++){
            speed_x[i] = (500 - loc_x[i]) /5.5; //マウスのx座標と円のx座標の距離の1/8だけ接近
            speed_y[i] = (10 - loc_y[i]) /5.5;
            //speed_z[i] = (10 - loc_z[i]) /5.5;
            
            red[i] = ofRandom(0, 255); //Red成分を設定
            green[i] = ofRandom(0, 255); //Green成分を設定
            blue[i] = ofRandom(0, 255); //Blue成分を設定
        }
        m_num=m;
    }
    
    printf("hage: %d\n", s_num);
    
    
    
    
    //------------------------------------------------------------球
    
    
    //---------------------------------------------------------------時計//
        
        
    
    
    //時計の大きさ
    float clockSize = 200;
    
        
    //座標全体を中心に移動
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);   //原点(0,0,0)が縦と横の中心になる。***
    
    
    //時計の背景
    ofSetColor(255, 255, 255);
    ofFill();
    
    //分の目盛を描く
    for (int i=0; i<60; i++) {
        ofRotateZ(6);
        ofCircle(clockSize, 0, 2);
    }
    
    //時の目盛を描く
    for (int i=0; i<12; i++) {
        ofRotateZ(30);
        ofCircle(clockSize, 0, 4);
    }
    
    ofSetColor(255, 255, 255);

    //秒針
    
    ofPushMatrix();
    ofRotateZ(s*6.0);
    ofSetLineWidth(1);
    ofLine(0 , 0, 0, -clockSize);
    ofPopMatrix();
    
    ofSetColor(255, 255, 255);
    
    //分
    ofPushMatrix();
    ofRotateZ(m*6.0);
    ofSetLineWidth(2);
    ofLine( 0, 0, 0, -clockSize);
    ofPopMatrix();
    
    ofSetColor(255, 255, 255);
    
    //時針
    ofPushMatrix();
    ofRotateZ(h*30.0);
    ofSetLineWidth(4);
    ofLine( 0, 0, 0, -clockSize*0.75);
    ofPopMatrix();
    
    ofSetColor(255, 255, 255);
    
    
    
    //---------------------------------------------------------時計//
    
    //全画面を半透明の黒でフェード
//    ofSetColor(0, 0, 255, 23);
//    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    
    
    
    

    

    
    
    //座標全体を中心に移動
    //ofTranslate(ofGetHeight()/2, ofGetWidth()/2); //原点(0,0,0)が縦と横の中心になる。
    
    
    
    
    cam.begin();
    
    
    
    
    vec.set(mouseX-p.x, mouseY-p.y);
    
   
    
    
    
    
    
    
    
    ofPushMatrix();
    
    ofRotateY(ofGetFrameNum()); //Y軸を軸にして回転させる。
    
    int alpha = abs(vec.x) + abs(vec.y);  //x方向の速度　＋　Y方向の速度
    ofSetColor(100, 200, 255, 255 - alpha);
    
    
    for (int i=0; i<NUM; i++) {
        mBox[i].draw(); //たくさんの小さいboxを描画。
    }
    
    ofPopMatrix();
    
    
    ofSetColor(255,255,255,(ofGetFrameNum()*6)%120); //（boxの色を指定(点滅)）
    sphere.setPosition(0, 0, 0); //boxの位置を画面の中心に
    sphere.set(200,15);
    sphere.draw();
    
    ofSetColor(255, 255, 255, 255); //ワイヤーフレームの色
    sphere.drawWireframe(); //ワイヤーフレームを描画
    
    
    
    
    
    cam.end();
    
    
    
    p.x = mouseX; //前のマウスのポイントを保存。(pointX)
    p.y = mouseY; //前のマウスのポイントを保存。(pointY)
    
    BackgroundImage.draw( 0, 0 ,-3000);   //***
    
    
    
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_pressed = true; //マウスが押されている状態に
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouse_pressed = false; //マウスが押されていない状態に
    
    //円のスピードを再初期化
    for(int i = 0; i < NUM; i++){
        speed_x[i] = ofRandom(-5, 5); //x軸方向スピード初期値
        speed_y[i] = ofRandom(-5, 5); //y軸方向スピード初期値
        //speed_z[i] = ofRandom(-5, 5); //y軸方向スピード初期値
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
