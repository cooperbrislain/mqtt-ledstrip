//
// Created by Cooper Brislain on 6/21/20.
//

#include "touchcontrol.h"

TouchControl::TouchControl(String name, int pin, int threshold) {
    _name = name;
    _pin = pin;
    _threshold = threshold;
    _pressed = 0;
    _val = 0;
    _pressFn = default_pressFn;
    _releaseFn = default_releaseFn;
    _stilldownFn = default_stilldownFn;
}

void TouchControl::update() {
    int val = touchRead(_pin);
    Serial.print("pin ");
    Serial.print(_pin);
    Serial.print(": ");
    Serial.println(val);
    if (val <= _threshold) {
        _pressed++;
        if (_pressed == 10) _pressFn(val);
        if (_pressed > 20) _stilldownFn(val);
    } else {
        if (_pressed > 5) _releaseFn(val);
        _pressed = 0;
    }
}

int TouchControl::get_state() {
    int val = touchRead(_pin);
    return _val;
}

bool TouchControl::is_pressed() {
    return _pressed!=0;
}

void TouchControl::set_press(ControlFn pressFn) {
    _pressFn = pressFn;
}

void TouchControl::set_release(ControlFn releaseFn) {
    _releaseFn = releaseFn;
}

void TouchControl::set_stilldown(ControlFn stilldownFn) {
    _stilldownFn = stilldownFn;
}

// Default Control Functions

ControlFn default_pressFn = [](int val){
    Serial.print("default pressFn");
    Serial.println(val);
};

ControlFn default_releaseFn = [](int val){
    Serial.print("default releaseFn");
    Serial.println(val);
};

ControlFn default_stilldownFn = [](int val){
    Serial.print("default stilldownFn");
    Serial.println(val);
};
