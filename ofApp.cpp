#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 60 < 3) {

		this->random_seed = ofRandom(1000);
	}

	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {


	ofTranslate(ofGetWindowSize() * 0.5);

	auto number_of_sphere = 200;
	vector<glm::vec2> location_list;
	vector<float> radius_list;

	while (location_list.size() < number_of_sphere) {

		auto location = glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300));
		auto radius = ofRandom(8, 70);
		bool flag = true;
		for (int i = 0; i < location_list.size(); i++) {

			if (glm::distance(location, location_list[i]) < (radius + radius_list[i])) {

				flag = false;
				break;
			}
		}

		if (flag) {

			location_list.push_back(location);
			radius_list.push_back(radius);
		}
	}

	ofColor color_1, color_2;
	for (int i = 0; i < location_list.size(); i++) {

		int deg = ofRandom(360) + ofGetFrameNum() * ofRandom(1, 5);
		int hue = ofRandom(255);
		color_1.setHsb(hue, 150, 255);
		color_2.setHsb(hue, 255, 150);
		this->draw_MAGATAMA(location_list[i], radius_list[i] * 0.95, deg, color_1, color_2);
		this->draw_MAGATAMA(location_list[i], radius_list[i] * 0.95, deg + 180, color_2, color_1);
	}
}

//--------------------------------------------------------------
void ofApp::draw_MAGATAMA(glm::vec2 location, float radius, float rotate_deg, ofColor fill_color, ofColor no_fill_color) {

	float len = radius * 0.5522;
	float deg = 0;

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(rotate_deg);

	vector<glm::vec2> vertices;
	vector<pair<glm::vec2, glm::vec2>> handle_list;

	vertices.push_back(glm::vec2(0, 0));
	deg = 180;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius * 0.5, radius * -0.5));
	deg = 90;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius * -1));
	deg = 0;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len  * sin(deg * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius, 0));
	deg = 270;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos((deg + 180) * DEG_TO_RAD), len * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius));
	deg = 0;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius * -0.5, radius * 0.5));
	deg = 90;
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	ofSetColor(fill_color);
	ofFill();
	ofBeginShape();
	for (int i = 0; i < vertices.size(); i++) {

		int n = (i + 1) % vertices.size();

		ofVertex(vertices[i]);
		ofBezierVertex(handle_list[i].second, handle_list[n].first, vertices[n]);
	}

	ofNextContour(true);
	for (deg = 0; deg <= 360; deg += 5) {

		ofVertex(glm::vec2(0, radius * 0.5) + glm::vec2(radius * 0.2 * cos(deg * DEG_TO_RAD), radius * 0.2 * sin(deg * DEG_TO_RAD)));
	}
	ofEndShape(true);

	ofSetColor(no_fill_color);
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < vertices.size(); i++) {

		int n = (i + 1) % vertices.size();

		ofVertex(vertices[i]);
		ofBezierVertex(handle_list[i].second, handle_list[n].first, vertices[n]);
	}

	ofNextContour(true);
	for (deg = 0; deg <= 360; deg += 5) {

		ofVertex(glm::vec2(0, radius * 0.5) + glm::vec2(radius * 0.2 * cos(deg * DEG_TO_RAD), radius * 0.2 * sin(deg * DEG_TO_RAD)));
	}
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}