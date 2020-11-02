#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // Base path to images
    base_path = "london_2018";
    dir.listDir(base_path);
    
    // Iterate through each file in the directory
    for (int i = 0; i < dir.size(); i++) {
        
        // Load image and add the color of every pixel to the color counts
        cur_img.load(dir.getPath(i));
        count_image_colors(cur_img);
    }
    
    get_top_n_colors(1024);
        
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    cur_img.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::get_top_n_colors(int n){
    

    // Make a copy of color_counts
    for (int a = 0; a < c_arr_len; a++) {
        color_counts_temp[a] = color_counts[a];
    }
    
    // NOTE: VERY INEFFICIENT - Improve if time permits
    for (int l = 0; l < n; l++) {
        int largest_val = 0;
        int largest_index = 0;
        for (int i = 0; i < c_arr_len; i++) {
            if(color_counts_temp[i] > largest_val) {
                largest_val = color_counts_temp[i];
                largest_index = i;
            }
        }
        
        // Remove this value from the temp array
        color_counts_temp[largest_index] = 0;
        top_color_indices.push_back(largest_index);
    }
    
}

//--------------------------------------------------------------
void ofApp::count_image_colors(ofImage img){
    
    // Loop through each pixel and add to the array of color counts
    for (int i = 0; i < img.getWidth(); i++) {
        for (int j = 0; j < img.getHeight(); j++) {
            
            // Get pixel color value
            ofColor cur_color = img.getColor(i,j);
            
            // Convert from color to bucketed color
            ofVec3f bucket_color = color_to_bucket(cur_color);
            
            // Get the correct array index
            int arr_index = bucket_to_array_index(bucket_color);
            
            // Add a count to the array
            color_counts[arr_index] += 1;
            
        }
    }
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
