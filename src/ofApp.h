#pragma once

#include "TTModular.h"
#include "ofMain.h"

// Callback function to get data's value back
TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

class ofApp : public ofBaseApp
{
  public:
    void setup  ();
    void update ();
    void draw   ();
    void exit   ();

    void keyPressed      (ofKeyEventArgs&);
    void keyReleased     (ofKeyEventArgs&);

    void mouseMoved      (ofMouseEventArgs&);
    void mouseDragged    (ofMouseEventArgs&);
    void mousePressed    (ofMouseEventArgs&);
    void mouseReleased   (ofMouseEventArgs&);
    void mouseScrolled   (ofMouseEventArgs&);
    void mouseEntered    (ofMouseEventArgs&);
    void mouseExited     (ofMouseEventArgs&);

    void touchDown       (ofTouchEventArgs&);
    void touchMoved      (ofTouchEventArgs&);
    void touchUp         (ofTouchEventArgs&);
    void touchDoubleTap  (ofTouchEventArgs&);
    void touchCancelled  (ofTouchEventArgs&);

    void windowResized   (ofResizeEventArgs&);
    void dragged         (ofDragInfo&);
    void messageReceived (ofMessage&);

    ofParameter<int> param1;
    ofParameter<float> param2;
  private:
    ofxPanel gui;

    // Declare the application manager, our application and another one
    TTObject mApplicationManager;
    TTObject mApplicationDemo;
    TTObject mApplicationRemote;

    // Declare protocol units to use
    TTObject mProtocolMinuit;
    TTObject mProtocolWebSocket;

        // Declare publicly all datas of our application to retreive them from the callback function
    TTObject mDataDemoDecimalParameter;     // a parameter is relative to the state of our application
    TTObject mDataDemoStringParameter;      // a parameter is relative to the state of our application
    TTObject mDataDemoBoolParameter;        // a parameter is relative to the state of our application
    TTObject mDataDemoMessage;              // a message is a kind of command to send to our application
    TTObject mDataDemoReturn;               // a return is a kind of notification sent by our application

    void setupJamomaApp();
    void registerJamomaParam();

    friend TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

};
