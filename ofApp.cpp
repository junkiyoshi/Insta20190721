#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	vector<glm::vec3> line;
	for (int v = 0; v < 360; v += 5) {

		auto noise_location = glm::vec2(cos(v * DEG_TO_RAD), sin(v * DEG_TO_RAD));

		vector<glm::vec3> vertices;
		int u_start = ofMap(ofNoise(noise_location.x * 0.5, noise_location.y * 0.5, ofGetFrameNum() * 0.005), 0, 1, -360, 360);

		ofFill();
		ofSetColor(39);

		line.push_back(this->make_point(250, 65, u_start * DEG_TO_RAD, v * DEG_TO_RAD));
		ofDrawSphere(line.back(), 5);

		for (int u = u_start + 30; u <= u_start + 330; u += 10) {

			vertices.push_back(this->make_point(250, 65, u * DEG_TO_RAD, v * DEG_TO_RAD));
		}

		ofNoFill();
		ofSetColor(139);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();
	}

	ofSetColor(39);
	ofBeginShape();
	ofVertices(line);
	ofEndShape(true);

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	float x = (R + r * cos(u)) * cos(v);
	float y = (R + r * cos(u)) * sin(v);
	float z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}