#ifndef SPRINGBOOTCPPAPP_H
#define SPRINGBOOTCPPAPP_H

#include <StandardDefines.h>
#include "ISpringBootCppApp.h"
#include <IHttpRequestManager.h>

#ifdef ARDUINO
#include <Arduino.h>
// Define print macros for Arduino
#define std_print(x) Serial.print(x)
#define std_println(x) Serial.println(x)
#endif

/* @Component */
class SpringBootCppApp : public ISpringBootCppApp {
    Public Virtual ~SpringBootCppApp() = default;

    /* @Autowired */
    Private IHttpRequestManagerPtr requestManager;

    Public Virtual Bool StartApp() override {
        
        if (requestManager == nullptr) {
            return false;
        }
        
        // Then start the HTTP server
        Bool serverStarted = requestManager->StartServer();
        
        return serverStarted;
    }

    Public Virtual Void StopApp() override {
        
        if (requestManager != nullptr) {
            requestManager->StopServer();
        }
    }

    Public Virtual Bool RestartApp() override {
        // Stop the application
        StopApp();
        
        // Start the application
        Bool result = StartApp();
        
        return result;
    }

    Public Virtual Void ListenToRequest() override {
        // Check if requestManager is available
        if (requestManager == nullptr) {
            return;
        }
        
        // Retrieve incoming requests
        requestManager->RetrieveRequest();
        
        // Process requests
        //requestManager->ProcessRequest();
        
        // Process responses
        //requestManager->ProcessResponse();
    }
};

#endif // SPRINGBOOTCPPAPP_H

