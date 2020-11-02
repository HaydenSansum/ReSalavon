#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void get_top_n_colors(int n);
        void count_image_colors(ofImage img);
        ofVec3f array_index_to_bucket(int index);
        int bucket_to_array_index(ofVec3f bucket);
        ofVec3f color_to_bucket(ofColor color);
        ofColor bucket_to_color(ofVec3f bucket);

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
    
    // FIXED VARIABLES - USER CHOICE
    int color_resolution = 5;
    int color_channels = 51; // Must be: floor(256 / color_resolution)
    int color_counts [132651] = {0}; // Must be: floor(256 / color_resolution) ^ 3
    int color_counts_temp [132651] = {0};
    int c_arr_len = 132651;
    
    
    // Backend Colors
    vector <int> top_color_indices;
    
    // File paths
    string base_path;
    ofDirectory dir;
    
    // Images
    ofImage cur_img;
    ofImage img_grab;

		
};
