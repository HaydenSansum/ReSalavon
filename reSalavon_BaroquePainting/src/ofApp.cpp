#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // Variables
    saturation_order = 1; // 1 to draw in saturation ordered else 0
    
    // Base path to images
    base_path = "scotland_2019";
    dir.listDir(base_path);
    
    // Iterate through each file in the directory
    for (int i = 0; i < dir.size(); i++) {
        
        // Load image and add the color of every pixel to the color counts
        cur_img.load(dir.getPath(i));
        count_image_colors(cur_img);
    }
    
    get_top_n_colors(1024);
    
    
    // SATURATION ORDERING
    create_saturation_order();
    
        
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw vertical lines
    draw_vertical_lines(saturation_order);
    
    // Draw squares
    
    
}



//--------------------HELPER FUNCTIONS--------------------------
//--------------------------------------------------------------
void ofApp::get_top_n_colors(int n){
    

    // Make a copy of color_counts
    for (int a = 0; a < c_arr_len; a++) {
        color_counts_temp[a] = color_counts[a];
    }
    
    // NOTE: INEFFICIENT - Improve if time permits (negligible compared to image step)
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
        top_color_indices[l] = (largest_index);
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
void ofApp::create_saturation_order(){
    
    // Create copy
    for (int a = 0; a < num_colors; a++) {
        top_color_indices_temp[a] = top_color_indices[a];
    }
    
    // Order max to min
    for (int i = 0; i < num_colors; i++) {
        
        int max_s = 0;
        int max_index = 0;
        int color_int = 0;
        
        for (int j = 0; j < num_colors; j++) {
            
            ofVec3f cur_bucket = array_index_to_bucket(top_color_indices_temp[j]);
            ofColor cur_color = bucket_to_color(cur_bucket);
            
            float h = 0;
            float s = 0;
            float b = 0;
            cur_color.getHsb(h, s, b);
            
            if(s > max_s) {
                max_s = s;
                max_index = j;
            }
        }
        
        saturation_ordered_indices[i] = top_color_indices_temp[max_index];
        top_color_indices_temp[max_index] = 0;
    }
    
}


//-------------------DRAWING FUNCTIONS--------------------------
//--------------------------------------------------------------
void ofApp::draw_vertical_lines(int saturation_order){
    // Draw vertical lines
    for (int i = 0; i < num_colors; i++) {
        
        ofVec3f bucket_color;
        
        // Get color from index
        if(saturation_order == 0) {
            bucket_color = array_index_to_bucket(top_color_indices[i]);
        } else {
            bucket_color = array_index_to_bucket(saturation_ordered_indices[i]);
        }
        ofColor actual_color = bucket_to_color(bucket_color);
        
        // Set color
        ofSetColor(actual_color);
        
        // Draw vertical lines
        ofDrawRectangle(i, 0, 1, ofGetHeight());
    }
}





//------------------BUILT IN FUNCTIONS--------------------------
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        save_img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        save_img.save(ofGetTimestampString() + "screenshot.png");
    }
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
