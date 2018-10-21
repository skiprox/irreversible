#include "Petal.hpp"

// Use an initializer list
Petal::Petal(){
}

// Overload the constructor
Petal::Petal(ofColor _color, float _deg, float _degreeIncrementer, int _lifespan, float _petalScaler){
    width = ofGetWidth();
    height = ofGetHeight();
    size = glm::vec2(xIncrementer, yIncrementer);
    color = _color;
    deg = _deg;
    degreeIncrementer = _degreeIncrementer;
    petalScaler = _petalScaler;
    lifespan = _lifespan;
    noiseySize.x = ofNoise(ofGetElapsedTimef());
    noiseySize.y = ofNoise(ofGetElapsedTimef() + 100);
}

void Petal::update(){
    noiseySize.x = ofNoise(ofGetElapsedTimef()) - 0.5;
    noiseySize.y = ofNoise(ofGetElapsedTimef() + 100) - 0.5;
    incrementer += 1;
    incrementer = ofClamp(incrementer, 0, lifespan);
    if (incrementer > lifespan/1.5) {
        size.x -= xIncrementer/8 + noiseySize.x;
        size.y -= yIncrementer/8 + noiseySize.y;
    } else {
        size.x += (xIncrementer * petalScaler) + noiseySize.x;
        size.y += (yIncrementer * petalScaler) + noiseySize.y;
    }
    deg += degreeIncrementer;
}

void Petal::draw(){
    ofPushStyle();
    ofPushMatrix();
    ofColor c = color;
    if (incrementer > 50) {
        c.lerp(ofColor(0, 0, 0), (incrementer - 50)/(lifespan - 50));
    }
    ofSetColor(c);
    ofTranslate(width/2, height/2);
    ofRotate(deg);
    ofDrawEllipse(0, 0, size.x, size.y);
    ofPopMatrix();
    ofPopStyle();
}

float Petal::getIncrementer(){
    return incrementer;
}
