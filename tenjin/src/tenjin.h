#pragma once
#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)

extern void Tenjin_Init(const char*api_key, bool gdpr_consent);
extern void Tenjin_CustomEvent(const char*event_name);
extern void Tenjin_CustomEventWithValue(const char*event_name, const char*event_value);

#endif