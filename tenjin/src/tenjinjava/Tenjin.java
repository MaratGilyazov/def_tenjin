package com.anvil.tenjin;

import android.app.Activity;

import com.tenjin.android.TenjinSDK;

class Tenjin {

    private static TenjinSDK tenjinInstance;

    public static final void Init(Activity appActivity, String apiKey, boolean consent) {
        tenjinInstance = TenjinSDK.getInstance(appActivity, apiKey);
        
        if (consent) {
            tenjinInstance.optIn();
        }
        else {
            tenjinInstance.optOut();
        }

        tenjinInstance.connect();  
    }

    public static final void CustomEvent(String eventName) {
        tenjinInstance.eventWithName(eventName);
    }

    public static final void CustomEventWithValue(String eventName, String eventValue) {
        tenjinInstance.eventWithNameAndValue(eventName, eventValue);
    }

    public static final void PurchaseEvent(String productId, String currencyCode, int quantity, double unitPrice) {
        tenjinInstance.transaction(productId, currencyCode, quantity, unitPrice);
    }

}