#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // Base path to images
    base_path = "london_2018";
    dir.listDir(base_path);
    
    // Iterate through each file in the directory
    for (int i = 0; i < 1; i++) {
        cout << dir.getPath(i) << endl;
    }
        
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::calc_top_n_colors(){

}

//--------------------------------------------------------------
ofVec3f ofApp::array_index_to_bucket(int index){

    int blue = index % color_channels;
    
    int remaining_rg = index - blue;
    int remaining_g = remaining_rg % (color_channels * color_channels);
    int remaining_r = remaining_rg - remaining_g;
    
    int red = remaining_r / (color_channels * color_channels);
    int green = remaining_g / color_channels;
    
    ofVec3f bucket = ofVec3f(red, green, blue);
    return bucket;
}

//--------------------------------------------------------------
int ofApp::bucket_to_array_index(ofVec3f bucket){
    
    int red = bucket[0];
    int green = bucket[1];
    int blue = bucket[2];
    
    int r_index = red * (color_channels * color_channels);
    int g_index = green * (color_channels);
    int b_index = blue;
    
    int index = r_index + g_index + b_index;
    return index;
    
}

//--------------------------------------------------------------
ofVec3f ofApp::color_to_bucket(ofColor color){
    
    int red = color.r;
    int green = color.g;
    int blue = color.b;
    
    int r_bucket = red / color_resolution;
    int g_bucket = green / color_resolution;
    int b_bucket = blue / color_resolution;
    
    // Account for uneven division - group extra colors at top of range
    if(r_bucket > color_channels - 1) {
        r_bucket = color_channels - 1;
    }
    if(g_bucket > color_channels - 1) {
        g_bucket = color_channels - 1;
    }
    if(b_bucket > color_channels - 1) {
        b_bucket = color_channels - 1;
    }
    
    ofVec3f bucket = ofVec3f(r_bucket, g_bucket, b_bucket);
    return bucket;
    
}

//--------------------------------------------------------------
ofColor ofApp::bucket_to_color(ofVec3f bucket){
    
    int r_bucket = bucket[0];
    int g_bucket = bucket[1];
    int b_bucket = bucket[2];
    
    ofColor color = ofColor(r_bucket*color_resolution, g_bucket*color_resolution, b_bucket*color_resolution);
    return color;
    
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
