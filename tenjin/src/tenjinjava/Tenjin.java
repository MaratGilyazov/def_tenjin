package com.anvil.tenjin;

import android.app.Activity;

import com.tenjin.android.TenjinSDK;

class Tenjin {

    public static final void Init(Activity appActivity, String apiKey, boolean consent) {
        TenjinSDK instance = TenjinSDK.getInstance(appActivity, apiKey);
        instance.connect();    
    }

}