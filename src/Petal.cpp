#include "Petal.hpp"

// Use an initializer list
Petal::Petal(){
}

// Overload the constructor
Petal::Petal(ofColor _color, float _deg, float _degreeIncrementer, float _petalScaler, int _lifespan){
    size = glm::vec2(xIncrementer, yIncrementer);
    color = _color;
    newColor = _color;
    deg = _deg;
    degreeIncrementer = _degreeIncrementer;
    petalScaler = _petalScaler;
    lifespan = _lifespan;
    noiseySize.x = ofNoise(ofGetElapsedTimef());
    noiseySize.y = ofNoise(ofGetElapsedTimef() + 100);
}

void Petal::update(){
    float time = ofGetElapsedTimef();
    noiseySize.x = (ofSignedNoise(time)) * noiseIncrementer;
    noiseySize.y = (ofSignedNoise(time + 100)) * noiseIncrementer;
    incrementer += 1;
    incrementer = ofClamp(incrementer, 0, lifespan);
    if (incrementer > lifespan * 0.75) {
        size.x -= xIncrementer/8 + noiseySize.x;
        size.y -= yIncrementer/8 + noiseySize.y;
    } else {
        size.x += xIncrementer + noiseySize.x;
        size.y += yIncrementer + noiseySize.y;
    }
    deg += degreeIncrementer;
}

void Petal::draw(){
    ofPushStyle();
    ofColor c = color;
    c.setBrightness(250);
    if (incrementer > lifespan * 0.75) {
        newColor = c;
        newColor.lerp(ofColor(0, 0, 0), (incrementer - lifespan * 0.75)/(lifespan * 0.25));
    } else {
        newColor = color;
        newColor.lerp(c, incrementer/(lifespan * 0.75 - 1));
    }
    ofSetColor(newColor);
    ofRotate(deg);
    // Draw the shape here
    ofPath path;
    path.moveTo(0, 0);
    path.curveTo(0, 0);
    path.curveTo(-size.x, size.y * petalScaler);
    path.curveTo(0, size.y);
    path.curveTo(size.x, size.y * petalScaler);
    path.curveTo(0, 0);
    path.close();
    path.setFillColor(newColor);
    path.setCircleResolution(100);
    path.draw();
    ofPopStyle();
}

float Petal::getIncrementer(){
    return incrementer;
}
