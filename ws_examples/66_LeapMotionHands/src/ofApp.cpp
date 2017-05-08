#include "ofApp.h"

void ofApp::setup(){
    //画面の基本設定
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //カメラとライトの設定
    cam.setOrientation(ofPoint(-20, 0, 0));
    light.setPosition(0, 0, 1000);
    light.enable();
    
    //LeapMotion開始
    leap.open();
}

void ofApp::update(){
    //検出した手を配列に格納
    simpleHands = leap.getSimpleHands();
    
    //検出した手の配列
    vector <Hand> hands = leap.getLeapHands();
    if( leap.isFrameNew() && hands.size() ){
        //スケールを調整
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        //関節と指の位置を取得
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        for(int i = 0; i < hands.size(); i++){
            for(int j = 0; j < 5; j++){
                ofPoint pt;
                const Finger & finger = hands[i].fingers()[ fingerTypes[j] ];
                pt = leap.getMappedofPoint( finger.tipPosition() );
                pt = leap.getMappedofPoint( finger.jointPosition(finger.JOINT_DIP) );
                
                fingersFound.push_back(finger.id());
            }
        }
    }
    //フレーム更新
    leap.markFrameAsOld();
}

void ofApp::draw(){
    //背景
    ofBackgroundGradient(ofColor(90, 90, 90), ofColor(30, 30, 30),  OF_GRADIENT_BAR);
    
    //ログ表示
    ofSetColor(200);
    ofDrawBitmapString("ofxLeapMotion - Example App\nLeap Connected? " + ofToString(leap.isConnected()), 20, 20);
    
    ofEnableDepthTest();
    cam.begin();
    
    //地面のグリッドを描画
    ofPushMatrix();
    ofRotate(90, 0, 0, 1);
    ofSetColor(20);
    ofDrawGridPlane(800, 20, false);
    ofPopMatrix();
    
    //検出した手を描画
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
    
    for(int i = 0; i < simpleHands.size(); i++){
        bool isLeft = simpleHands[i].isLeft;
        ofPoint handPos = simpleHands[i].handPos;
        ofPoint handNormal = simpleHands[i].handNormal;
        
        //手の中心位置を描画
        ofSetColor(0, 0, 255);
        ofDrawSphere(handPos.x, handPos.y, handPos.z, 20);
        
        //手の平の向きを描画
        ofSetColor(255, 255, 0);
        ofDrawArrow(handPos, handPos + 100*handNormal);
        
        //5本の指をそれぞれ描画
        for (int f=0; f<5; f++) {
            ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;  // 関節1
            ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;  // 関節2
            ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;  // 関節3
            ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;  // 指先
            
            //関節と指先を描画
            ofSetColor(0, 255, 0);
            ofDrawSphere(mcp.x, mcp.y, mcp.z, 12);
            ofDrawSphere(pip.x, pip.y, pip.z, 12);
            ofDrawSphere(dip.x, dip.y, dip.z, 12);
            ofDrawSphere(tip.x, tip.y, tip.z, 12);
            
            //線で結ぶ
            ofSetColor(255, 0, 0);
            ofSetLineWidth(20);
            ofDrawLine(mcp.x, mcp.y, mcp.z, pip.x, pip.y, pip.z);
            ofDrawLine(pip.x, pip.y, pip.z, dip.x, dip.y, dip.z);
            ofDrawLine(dip.x, dip.y, dip.z, tip.x, tip.y, tip.z);
        }
    }
    
    cam.end();
    ofDisableDepthTest();
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
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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

//--------------------------------------------------------------
void ofApp::exit(){
    //プログラム終了したらLeapMotionを閉じる
    leap.close();
}
