#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS)
#include "tenjin.h"
#include "TenjinSDK.h"

void Tenjin_Init(const char* api_key, bool gdpr_consent) {
    
    [TenjinSDK init:[NSString stringWithUTF8String:api_key]];

    if (gdpr_consent) {
        [TenjinSDK optIn];
    } else {
        [TenjinSDK optOut];
    }
    
    [TenjinSDK connect];
}

void Tenjin_CustomEvent(const char* event_name) {
    [TenjinSDK sendEventWithName:[NSString stringWithUTF8String:event_name]]; 
}

void Tenjin_CustomEventWithValue(const char* event_name, const char* event_value) {
    [TenjinSDK sendEventWithName:[NSString stringWithUTF8String:event_name] andEventValue:[NSString stringWithUTF8String:event_value]]; 
}

void Tenjin_PurchaseEvent(const char* product_id, const char* currency_code, const int quantity, const double price) {
    [TenjinSDK  transactionWithProductName: [NSString stringWithUTF8String:product_id] 
                andCurrencyCode: [NSString stringWithUTF8String:currency_code] 
                andQuantity: (NSInteger) quantity
                andUnitPrice: [NSNumber numberWithDouble:price]];
}

#endif
