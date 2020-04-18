# Tenjin SDK

This is a native extension for [Defold engine](http://www.defold.com) which allows to use [Tenjin SDK](https://docs.tenjin.com/en/).

ATTENTION! Not every API methods are fully supported, only initialization and sending custom events; see LUA Api section below for the list of supported methods.

ATTENTION-2! On Android "Init()" method is called by demand, from your lua code, when documentation advices to do this in Android "OnResume" event. So, probably, sessions tracking is not fully correct.

Used Tenjin iOS SDK v1.9.1: https://github.com/tenjin/tenjin-ios-sdk and Android SDK v1.9.3: https://github.com/tenjin/tenjin-android-sdk

## Installation

You can use the Tenjin extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/).
Open your game.project file and in the dependencies field under project add:

>https://github.com/MaratGilyazov/def_tenjin/archive/master.zip
## Example
```lua
if tenjin then
  
  tenjin.init("YOUR_API_KEY", true)
  tenjin.custom_event("custom_event")
  tenjin.custom_event_with_value("custom_event", "10")
  tenjin.purchase_event("com.company.inapp", "USD", 1, 0.99)

end
```

## LUA Api
#### tenjin.init(string api_key, bool gdpr_consent)
Initializes Tenjin, call this before any other calls to Tenjin. This call is enough to track your installs. 
api_key - is your API_KEY from your [Tenjin Organization tab](https://tenjin.io/dashboard/organizations)
gdpr_consent - boolean flag to forward your user's consent regarding sensitive data; send true for "OptIn", if permission are granted
#### tenjin.custom_event(string event_name)
Send custom event with event_name
#### tenjin.custom_event_with_value(string event_name, string event_value)
Send custom event with event_name and event_value. 
IMPORTANT! event_value should be send as a string BUT it should contain the integer value!
#### tenjin.purchase_event(string product_id, string currency_code, int quantity, double price)
Send purchase event. product_id -> the name or ID of your product; currency_code -> the currency of your unit price; quantity -> the number of products that are counted for this purchase event; price -> the price of each product

## SDK support level
Some APIs are not supported in this version of extention, see the full list of native SDK methods in the [Tenjin iOS SDK repo](https://github.com/tenjin/tenjin-ios-sdk) and [Tenjin Andoir SDK repo](ttps://github.com/tenjin/tenjin-android-sdk) 

## Testing
See an official documentation describing how to test your integration: https://docs.tenjin.com/en/send-events/#check

Feel free to push a Pull Request with other features implementation.