#include "ofApp.h"

void ofApp::setup()
{
  gui.setup();
  gui.add(param1.set("my integer param",12,0, 255));
  gui.add(param2.set("my decimal param",0.5,0.,1.));

  setupJamomaApp();
  registerJamomaParam();
}

void ofApp::update()
{
}

void ofApp::draw()
{
  gui.draw();
}

void ofApp::exit()
{
}

void ofApp::keyPressed(ofKeyEventArgs& key)
{
}

void ofApp::keyReleased(ofKeyEventArgs& key)
{
}

void ofApp::mouseMoved(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseDragged(ofMouseEventArgs& mouse)
{
}

void ofApp::mousePressed(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseReleased(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseScrolled(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseEntered(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseExited(ofMouseEventArgs& mouse)
{
}

void ofApp::touchDown(ofTouchEventArgs& touch)
{
}

void ofApp::touchMoved(ofTouchEventArgs& touch)
{
}

void ofApp::touchUp(ofTouchEventArgs& touch)
{
}

void ofApp::touchDoubleTap(ofTouchEventArgs& touch)
{
}

void ofApp::touchCancelled(ofTouchEventArgs& touch)
{
}

void ofApp::windowResized(ofResizeEventArgs& window)
{
}

void ofApp::dragged(ofDragInfo& dragged)
{
}

void ofApp::messageReceived(ofMessage& message)
{
}

void ofApp::setupJamomaApp(){
    TTValue     args, v, out, none;
    TTAddress   address;
    TTErr       err;

    TTLogMessage("\n*** Initialisation of Modular environnement ***\n");
    /////////////////////////////////////////////////////////////////////

    // Init the Modular library (passing the folder path where all the dylibs are)
    TTModularInit("/usr/local/jamoma/lib/jamoma/");

    // Create an application manager
    mApplicationManager = TTObject("ApplicationManager");


    TTLogMessage("\n*** Creation of myDemoApp and myRemoteApp applications ***\n");
    ////////////////////////////////////////////////////////////////////////////////

    // Create a local application called "myDemoApp" and get it back
    err = mApplicationManager.send("ApplicationInstantiateLocal", "myDemoApp", out);

    if (err) {
        TTLogError("Error : can't create myDemoApp application \n");
        return;
    }
    else
        mApplicationDemo = out[0];

    // Get registered application names
    mApplicationManager.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTLogMessage("%s application is well registered into the application manager \n", name.c_str());
    }


    TTLogMessage("\n*** Enable Minuit communication ***\n");
    ////////////////////////////////////////////////////////////////////////

    // Create a Minuit protocol unit
    err = mApplicationManager.send("ProtocolInstantiate", "Minuit", out);

    if (err) {
        TTLogError("Error : can't create Minuit protocol unit \n");
        return;
    }
    else
        mProtocolMinuit = out[0];

    // Get Minuit Protocol attribute names and types
    mProtocolMinuit.get("parameterNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTSymbol type = mProtocolMinuit.attributeType(name);
        TTLogMessage("Minuit %s parameter is a %s \n", name.c_str(), type.c_str());
    }

    // Register mymyRemoteAppApp and myRemoteApp to the Minuit protocol
    mProtocolMinuit.send("ApplicationRegister", "myDemoApp", out);
    mProtocolMinuit.send("ApplicationRegister", "i-score", out);

    // Select myDemoApp to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", "myDemoApp", out);
    mProtocolMinuit.set("port", 9998);
    mProtocolMinuit.set("ip", "127.0.0.1");

    // Select myRemoteApp to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", "i-score", out);
    mProtocolMinuit.set("port", 13579);
    mProtocolMinuit.set("ip", "192.168.0.4");

    // Get Minuit parameters for each registered application
    mProtocolMinuit.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);

        mProtocolMinuit.send("ApplicationSelect", name, out);
        TTLogMessage("Minuit setup for %s application : \n", name.c_str());

        mProtocolMinuit.get("ip", v);
        TTSymbol ip = v[0];
        TTLogMessage("- ip = %s \n", ip.c_str());

        mProtocolMinuit.get("port", v);
        TTUInt16 port = v[0];
        TTLogMessage("- port = %d \n", port);
    }

    // Enable Minuit communication
    mProtocolMinuit.send("Run");


//    TTLogMessage("\n*** Enable WebSocket communication ***\n");
//    ////////////////////////////////////////////////////////////////////////
//
//    // Create a WebSocket protocol unit
//    err = mApplicationManager.send("ProtocolInstantiate", "WebSocket", out);
//
//    if (err) {
//        TTLogError("Error : can't create WebSocket protocol unit \n");
//        return;
//    }
//    else
//        mProtocolWebSocket = out[0];
//
//    // Get WebSocket Protocol attribute names and types
//    mProtocolWebSocket.get("parameterNames", out);
//    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
//        TTSymbol name = TTElement(*it);
//        TTLogMessage("WebSocket %s parameter is a %s \n", name.c_str(), mProtocolWebSocket.attributeType(name).c_str());
//    }
//
//    // Register myDemoApp and myRemoteApp to the WebSocket protocol
//    mProtocolWebSocket.send("ApplicationRegister", "myDemoApp", out);
//
//    // Select myDemoApp to set its protocol parameters
//    mProtocolWebSocket.send("ApplicationSelect", "myDemoApp", out);
//
//    // get the path where the binary resides
//    char buf[4046];
//    uint32_t bufsize = sizeof(buf);
//#ifdef TT_PLATFORM_WIN
//    GetModuleFileName(NULL, buf, bufsize);
//#elif defined(TT_PLATFORM_MAC)
//    _NSGetExecutablePath(buf, &bufsize);
//#else
//    readlink("/proc/self/exe", buf, 4046);
//#endif
//
//    std::string str = std::string(buf);
//    std::size_t found = str.find_last_of("/\\");
//    std::string stringPath = str.substr(0,found) + std::string("/jamomarmot");
//
//    std::cout << "websocket htmlPath : " << stringPath << std::endl;
//
//    /*mProtocolWebSocket.set("htmlPath", "/Users/ProLauGre/Travail/09-ossia/Jamoma/Core/Modular/implementations/Example/DemoApp/to_test_websocket/jamomarmot");*/
//  mProtocolWebSocket.set("htmlPath", stringPath.c_str());
//    mProtocolWebSocket.set("port", 9001);
//
//    // Get WebSocket parameters for each registered application
//    mProtocolWebSocket.get("applicationNames", out);
//    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
//        TTSymbol name = TTElement(*it);
//
//        mProtocolWebSocket.send("ApplicationSelect", name, out);
//        TTLogMessage("WebSocket setup for %s application : \n", name.c_str());
//
//        mProtocolWebSocket.get("htmlPath", v);
//        TTSymbol htmlPath = v[0];
//        TTLogMessage("- htmlPath = %s \n", htmlPath.c_str());
//
//        mProtocolWebSocket.get("port", v);
//        TTUInt16 port = v[0];
//        TTLogMessage("- port = %d \n", port);
//    }
//
//    // Enable WebSocket communication
//    mProtocolWebSocket.send("Run");

    TTLogMessage("\n*** Current Protocol Setup ***\n");
    // Get protocol names
    mApplicationManager.get("protocolNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTLogMessage("%s protocol is well registered into the application manager \n", name.c_str());
    }
}

void ofApp::registerJamomaParam(){
    TTValue     args, v, out, none;
    TTAddress   address;
    TTErr       err;
      TTLogMessage("\n*** Creation and registration of a decimal parameter ***\n");
    /////////////////////////////////////////////////////////

    // Create a decimal parameter data and set its callback function and baton and some attributes
    mDataDemoDecimalParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(TTPtr(this), mDataDemoDecimalParameter);
    mDataDemoDecimalParameter.set("baton", args);
    mDataDemoDecimalParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mDataDemoDecimalParameter.set("type", "decimal");
    mDataDemoDecimalParameter.set("rangeBounds", TTValue(-1., 1.));
    mDataDemoDecimalParameter.set("rangeClipmode", "both");
    mDataDemoDecimalParameter.set("rampDrive", "System");
    mDataDemoDecimalParameter.set("description", "this parameter is useful for demo purpose");
    mDataDemoDecimalParameter.set("valueDefault", 0);
    mDataDemoDecimalParameter.set("value", 0.9);

    // Register the parameter data into myDemoApp at an address
    args = TTValue("/myParameterDecimal", mDataDemoDecimalParameter);
    err = mApplicationDemo.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /myParameterDecimal address \n");

    else {
        address = out[0];
        TTLogMessage("\n /myParameterDecimal : effective registration address is %s \n", address.c_str());
    }

}


TTErr
DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& value)
{
    ofApp*    demoApp = (ofApp*)TTPtr(baton[0]);
    TTObject    anObject = baton[1];

    std::cout << "received value size : " << value.size() << std::endl;

  // Reteive which data has been updated
    if (anObject.instance() == demoApp->mDataDemoDecimalParameter.instance()) {

        // print the returned value
        TTLogMessage("/myParameterDecimal has been updated to %s \n", value.toString().data());
        demoApp->param2 = value[0];
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataDemoStringParameter.instance()) {

        // print the returned value
        TTLogMessage("/myParameterString has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataDemoBoolParameter.instance()) {

        // print the returned value
        TTLogMessage("/myParameterBool has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataDemoMessage.instance()) {

        // print the returned value
        TTLogMessage("/myMessage has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataDemoReturn.instance()) {

        // print the returned value
        TTLogMessage("/myReturn has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    return kTTErrGeneric;
}
