// ==WindhawkMod==
// @id windhawk-mawaqit
// @name Mawaqit Prayer Clock
// @description Mawaqit prayer clock for the Windows 11 taskbar. Displays the upcoming prayer, a live countdown, and a clickable prayer schedule.
// @version 0.6.3
// @author Sensei
// @github https://github.com/hheitlager
// @include explorer.exe
// @architecture x86-64
// @compilerOptions -lgdi32 -luser32 -lwinhttp -lshell32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Mawaqit Prayer Clock
An unofficial, customizable Mawaqit prayer clock for the Windows 11 taskbar.
Displays the upcoming prayer, a live countdown, and a clickable prayer schedule.

## Features
- Five appearance themes
- Customizable pill and popup colors
- Prayer label, countdown, and popup visibility controls
- Adjustable taskbar positioning and dimensions
- Automatic prayer schedule updates
- Live settings updates without restarting Explorer

## Screenshots
### Windows/System Defaul | Traditional Islamic
![Windows](https://raw.githubusercontent.com/hheitlager/windhawk-mawaqit/main/screenshots/Mawaqit-Windows-System-Default.png) ![Traditional](https://raw.githubusercontent.com/hheitlager/windhawk-mawaqit/main/screenshots/Mawaqit-Traditional-Islamic.png)

### Catppucchin Mocha | Emberveil
![Catppucchin Mocha](https://raw.githubusercontent.com/hheitlager/windhawk-mawaqit/main/screenshots/Mawaqit-Catppucchin-Moca.png) ![Emberveil](https://raw.githubusercontent.com/hheitlager/windhawk-mawaqit/main/screenshots/Mawaqit-Emberveil.png)

### My fully custom desktop preview
![Desktop](https://raw.githubusercontent.com/hheitlager/windhawk-mawaqit/main/screenshots/My-Desktop.png)

## Configuration
Choose a mosque identifier or Mawaqit URL in Settings.
Select an appearance theme and customize the widget as desired.

Custom color settings only apply when the Custom theme is selected.

## More information
For installation instructions, additional screenshots,
troubleshooting, and release information, visit:

[GitHub Project](https://github.com/hheitlager/windhawk-mawaqit)

## License
MIT License.

## Disclaimer
This is an unofficial community project and is not affiliated
with or endorsed by Mawaqit.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- Mosque: masjidomar
  $name: Mawaqit - Mosque ID or URL
  $description: "Mosque identifier or full Mawaqit URL (e.g. https://mawaqit.net/en/al-haram-makkah-saudi-arabia)."
- RefreshHours: 24
  $name: Mawaqit - Refresh interval (hours)
  $description: "How often to refresh the prayer schedule. Failed updates retry after one hour."
- Theme: emberveil
  $name: Appearance - Theme
  $description: "Choose a preset for both pill and popup. Select Custom to use the independent colors below."
  $options:
  - emberveil: Emberveil
  - system: Windows / System
  - traditional: Traditional Islamic
  - catppuccin: Catppucchin Mocha
  - custom: Custom
- ShowNextPrayer: true
  $name: Display - Show next prayer
  $description: "Show the upcoming prayer name and scheduled time in the taskbar pill."
- ShowCountdown: true
  $name: Display - Show countdown
  $description: "Show the time remaining until the next prayer. The separator only appears when both are visible."
- EnablePopup: true
  $name: Display - Enable prayer popup
  $description: "Allow clicking the taskbar pill to open the prayer schedule. Turning this off closes an open popup."
- CustomPillBackground: "#211E32"
  $name: Custom pill - Background
  $description: "Custom theme only. Hex color (#RRGGBB) for the taskbar pill background."
- CustomPillText: "#F5E6C8"
  $name: Custom pill - Prayer text
  $description: "Custom theme only. Hex color (#RRGGBB) for prayer name and time."
- CustomPillSeparator: "#B8A98A"
  $name: Custom pill - Separator
  $description: "Custom theme only. Hex color (#RRGGBB) for the separator dot."
- CustomPillCountdown: "#FFBC5E"
  $name: Custom pill - Countdown
  $description: "Custom theme only. Hex color (#RRGGBB) for the countdown timer."
- CustomPopupBackground: "#1D1D2D"
  $name: Custom popup - Background
  $description: "Custom theme only. Hex color (#RRGGBB) for the popup background."
- CustomPopupBorder: "#3B3B58"
  $name: Custom popup - Border
  $description: "Custom theme only. Hex color (#RRGGBB) for the popup outline."
- CustomPopupText: "#D3D0E8"
  $name: Custom popup - Main text
  $description: "Custom theme only. Hex color (#RRGGBB) for mosque name and prayer rows."
- CustomPopupMuted: "#B8B3D1"
  $name: Custom popup - Secondary text
  $description: "Custom theme only. Hex color (#RRGGBB) for the Hijri date and secondary text."
- CustomPopupRule: "#424158"
  $name: Custom popup - Dividers
  $description: "Custom theme only. Hex color (#RRGGBB) for horizontal dividing lines."
- CustomPopupFooter: "#A29DBB"
  $name: Custom popup - Footer
  $description: "Custom theme only. Hex color (#RRGGBB) for the countdown summary at the bottom."
- Width: 220
  $name: Layout - Widget width (px)
  $description: "Width of the taskbar pill (180-400 px)."
- OffsetX: 0
  $name: Layout - Horizontal offset (px)
  $description: "Fine-tune position left (negative) or right (positive)."
- OffsetY: 0
  $name: Layout - Vertical offset (px)
  $description: "Fine-tune position up (negative) or down (positive)."
- TrayGap: 0
  $name: Layout - Gap before system tray (px)
  $description: "Space between the taskbar pill and system tray (0-100 px)."
- PillHeight: 26
  $name: Layout - Pill height (px)
  $description: "Height of the painted pill (12-30 px); the widget window remains 30 px high."
- FontSize: 15
  $name: Layout - Font size (px)
  $description: "Taskbar pill text size (10-24 px). Default 15 preserves the original appearance."
- CornerRadius: 13
  $name: Layout - Corner radius (px)
  $description: "Corner radius; clamped to half the pill height. Smaller values give squarer corners."
- PillPadding: 0
  $name: Advanced - Minimum left text inset (px)
  $description: "Only affects text if its centered position would be closer than this inset. Usually has no visible effect; retained for compatibility."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <winhttp.h>
#include <shlobj.h>
#include <map>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cwchar>
#include <iterator>
#include <cstdlib>
#include <cstring>

namespace NativeUpdater {

static void fail(const char* s){throw std::runtime_error(s);}

static std::string narrow(const std::wstring& s){if(s.empty())return {};int n=WideCharToMultiByte(CP_UTF8,0,s.data(),(int)s.size(),nullptr,0,nullptr,nullptr);std::string r(n,0);WideCharToMultiByte(CP_UTF8,0,s.data(),(int)s.size(),r.data(),n,nullptr,nullptr);return r;}

static std::string quote(const std::string& s){std::string o="\"";for(unsigned char c:s){switch(c){case '"':o+="\\\"";break;case '\\':o+="\\\\";break;case '\n':o+="\\n";break;case '\r':o+="\\r";break;case '\t':o+="\\t";break;default:if(c<32){char b[7];snprintf(b,sizeof(b),"\\u%04x",c);o+=b;}else o+=(char)c;}}return o+"\"";}

struct J {
 enum Kind{Null,Str,Arr,Obj,Other} kind=Null;
 std::string s;std::vector<J> a;std::map<std::string,J> o;
 const J& key(const std::string& k)const{auto it=o.find(k);if(it==o.end())fail("Missing JSON key");return it->second;}
 const J& idx(size_t i)const{if(i>=a.size())fail("JSON array index missing");return a[i];}
};

struct Parser {
 const std::string& s;size_t p=0;int depth=0;
 void ws(){while(p<s.size()&&(s[p]==' '||s[p]=='\r'||s[p]=='\n'||s[p]=='\t'))p++;}
 void expect(char c){ws();if(p>=s.size()||s[p++]!=c)fail("Malformed JSON");}
 static void utf8(std::string& out,unsigned cp){if(cp<128)out+=(char)cp;else if(cp<2048){out+=(char)(0xC0|(cp>>6));out+=(char)(0x80|(cp&63));}else if(cp<65536){out+=(char)(0xE0|(cp>>12));out+=(char)(0x80|((cp>>6)&63));out+=(char)(0x80|(cp&63));}else{out+=(char)(0xF0|(cp>>18));out+=(char)(0x80|((cp>>12)&63));out+=(char)(0x80|((cp>>6)&63));out+=(char)(0x80|(cp&63));}}
 unsigned hex4(){if(p+4>s.size())fail("Invalid Unicode escape");unsigned v=0;for(int i=0;i<4;i++){char c=s[p++];v<<=4;if(c>='0'&&c<='9')v+=c-'0';else if(c>='a'&&c<='f')v+=c-'a'+10;else if(c>='A'&&c<='F')v+=c-'A'+10;else fail("Invalid Unicode hex");}return v;}
 std::string str(){expect('"');std::string o;bool done=false;while(p<s.size()){unsigned char c=s[p++];if(c=='"'){done=true;break;}if(c<32)fail("Control char in JSON string");if(c!='\\'){o+=(char)c;continue;}if(p>=s.size())fail("Invalid JSON escape");char e=s[p++];switch(e){case '"':case '\\':case '/':o+=e;break;case 'n':o+='\n';break;case 'r':o+='\r';break;case 't':o+='\t';break;case 'b':o+='\b';break;case 'f':o+='\f';break;case 'u':{unsigned cp=hex4();if(cp>=0xD800&&cp<=0xDBFF){if(p+2>s.size()||s[p++]!='\\'||s[p++]!='u')fail("Bad surrogate");unsigned low=hex4();if(low<0xDC00||low>0xDFFF)fail("Bad low surrogate");cp=0x10000+((cp-0xD800)<<10)+(low-0xDC00);}else if(cp>=0xDC00&&cp<=0xDFFF)fail("Bad surrogate");utf8(o,cp);break;}default:fail("Unknown JSON escape");}}if(!done)fail("Unterminated JSON string");return o;}
 J value(){ws();if(++depth>80)fail("JSON nesting too deep");if(p>=s.size())fail("Truncated JSON");J v;char c=s[p];if(c=='"'){v.kind=J::Str;v.s=str();}else if(c=='{'){v.kind=J::Obj;p++;ws();if(p<s.size()&&s[p]=='}')p++;else for(;;){std::string k=str();expect(':');v.o.emplace(std::move(k),value());ws();if(p>=s.size())fail("Truncated object");char t=s[p++];if(t=='}')break;if(t!=',')fail("Invalid object separator");}}else if(c=='['){v.kind=J::Arr;p++;ws();if(p<s.size()&&s[p]==']')p++;else for(;;){v.a.push_back(value());ws();if(p>=s.size())fail("Truncated array");char t=s[p++];if(t==']')break;if(t!=',')fail("Invalid array separator");}}else{v.kind=J::Other;size_t b=p;while(p<s.size()&&s[p]!=','&&s[p]!=']'&&s[p]!='}'&&s[p]!=' '&&s[p]!='\r'&&s[p]!='\n')p++;if(b==p)fail("Invalid JSON token");v.s=s.substr(b,p-b);}depth--;return v;}
};

struct Http {HINTERNET h=nullptr;explicit Http(HINTERNET x):h(x){if(!h)fail("WinHTTP failed");}~Http(){if(h)WinHttpCloseHandle(h);}Http(const Http&)=delete;Http& operator=(const Http&)=delete;};

static std::string fetch(const std::wstring& path){
 Http session(WinHttpOpen(L"EmberveilMawaqit/0.5",WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,WINHTTP_NO_PROXY_NAME,WINHTTP_NO_PROXY_BYPASS,0));
 WinHttpSetTimeouts(session.h,5000,5000,15000,15000);
 Http conn(WinHttpConnect(session.h,L"mawaqit.net",INTERNET_DEFAULT_HTTPS_PORT,0));
 Http req(WinHttpOpenRequest(conn.h,L"GET",path.c_str(),nullptr,WINHTTP_NO_REFERER,WINHTTP_DEFAULT_ACCEPT_TYPES,WINHTTP_FLAG_SECURE));
 DWORD redirects=WINHTTP_OPTION_REDIRECT_POLICY_NEVER;WinHttpSetOption(req.h,WINHTTP_OPTION_REDIRECT_POLICY,&redirects,sizeof(redirects));
 if(!WinHttpSendRequest(req.h,WINHTTP_NO_ADDITIONAL_HEADERS,0,WINHTTP_NO_REQUEST_DATA,0,0,0)||!WinHttpReceiveResponse(req.h,nullptr))fail("HTTP request failed");
 DWORD status=0,len=sizeof(status);if(!WinHttpQueryHeaders(req.h,WINHTTP_QUERY_STATUS_CODE|WINHTTP_QUERY_FLAG_NUMBER,WINHTTP_HEADER_NAME_BY_INDEX,&status,&len,WINHTTP_NO_HEADER_INDEX)||status!=200)fail("Mawaqit did not return HTTP 200");
 std::string result;char b[8192];for(;;){DWORD got=0;if(!WinHttpReadData(req.h,b,sizeof(b),&got))fail("HTTP read failed");if(!got)break;if(result.size()+got>8*1024*1024)fail("HTML too large");result.append(b,got);}return result;
}

static std::string extract(const std::string& html){
 size_t pos=html.find("let confData");if(pos==std::string::npos)fail("Mawaqit confData not found");pos=html.find('=',pos);if(pos==std::string::npos)fail("confData assignment missing");pos=html.find('{',pos);if(pos==std::string::npos)fail("confData object missing");
 // The parser consumes exactly one JSON object, so nested braces and quoted strings are safe.
 std::string rest=html.substr(pos);Parser p{rest};J root=p.value();if(root.kind!=J::Obj)fail("confData is not an object");return rest.substr(0,p.p);
}

static bool leap(int y){return y%4==0&&(y%100!=0||y%400==0);}

static int days(int y,int m){static const int d[]={31,28,31,30,31,30,31,31,30,31,30,31};return d[m-1]+(m==2&&leap(y));}

static std::string date(int y,int m,int d){char b[16];snprintf(b,sizeof(b),"%04d-%02d-%02d",y,m,d);return b;}

static bool validTime(const std::string& t){return t.size()==5&&t[2]==':'&&t[0]>='0'&&t[0]<='2'&&t[1]>='0'&&t[1]<='9'&&t[3]>='0'&&t[3]<='5'&&t[4]>='0'&&t[4]<='9'&&((t[0]-'0')*10+t[1]-'0')<24;}

static void writeFile(const std::wstring& path,const std::string& content){HANDLE h=CreateFileW(path.c_str(),GENERIC_WRITE,0,nullptr,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,nullptr);if(h==INVALID_HANDLE_VALUE)fail("Cannot create temporary cache file");DWORD written=0;BOOL ok=WriteFile(h,content.data(),(DWORD)content.size(),&written,nullptr);FlushFileBuffers(h);CloseHandle(h);if(!ok||written!=content.size())fail("Cache write failed");}

static void replace(const std::wstring& from,const std::wstring& to){if(!MoveFileExW(from.c_str(),to.c_str(),MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH))fail("Cache replace failed");}

static std::wstring normalize(std::wstring input,std::wstring& slug){
 const std::wstring prefix=L"https://mawaqit.net/";if(input.rfind(prefix,0)==0)input=input.substr(prefix.size());
 if(input.empty()||input.find_first_of(L"?#\\@")!=std::wstring::npos||input.find(L"://")!=std::wstring::npos)fail("Invalid mosque URL/identifier");
 if(input.back()==L'/')input.pop_back();std::wstring lang=L"nl";size_t slash=input.find(L'/');if(slash!=std::wstring::npos){lang=input.substr(0,slash);slug=input.substr(slash+1);}else slug=input;
 auto valid=[](wchar_t c){return(c>=L'a'&&c<=L'z')||(c>=L'A'&&c<=L'Z')||(c>=L'0'&&c<=L'9')||c==L'_'||c==L'-';};
 if(lang.size()!=2||!std::all_of(lang.begin(),lang.end(),[](wchar_t c){return c>=L'a'&&c<=L'z';})||slug.empty()||slug.size()>120||!std::all_of(slug.begin(),slug.end(),valid))fail("Invalid mosque slug or language");
 return L"/"+lang+L"/"+slug;
}

static bool Run(const std::wstring& mosque) {
 std::wstring slug;std::wstring path=normalize(mosque,slug);std::string html=fetch(path);std::string json=extract(html);Parser parser{json};J root=parser.value();
 const J& cal=root.key("calendar");if(cal.kind!=J::Arr||cal.a.size()!=12)fail("Calendar must have 12 months");
 const J& nameVal=root.key("name");const J& tzVal=root.key("timezone");if(tzVal.kind!=J::Str||tzVal.s.empty())fail("Missing timezone");std::string name=nameVal.kind==J::Str&&!nameVal.s.empty()?nameVal.s:narrow(slug);
 // Stage 1 uses the local Windows date; matching the mosque timezone is handled in stage 2.
 SYSTEMTIME now;GetLocalTime(&now);int year=now.wYear;std::ostringstream sched;sched<<"# Emberveil Mawaqit schedule v1\n# Source: https://mawaqit.net"<<narrow(path)<<"\n# Year: "<<year<<"\n";
 for(int m=1;m<=12;m++){const J& month=cal.idx(m-1);if(month.kind!=J::Obj)fail("Month is not an object");for(int d=1;d<=days(year,m);d++){
  const J& entry=month.key(std::to_string(d));if(entry.kind!=J::Arr||entry.a.size()!=6)fail("Invalid calendar day");
  sched<<date(year,m,d);for(int i:{0,2,3,4,5}){const J& t=entry.idx(i);if(t.kind!=J::Str||!validTime(t.s))fail("Invalid prayer time");sched<<'|'<<t.s;}sched<<'\n';
 }}
 wchar_t base[MAX_PATH];if(!GetEnvironmentVariableW(L"LOCALAPPDATA",base,MAX_PATH))fail("LOCALAPPDATA unavailable");std::wstring dir=std::wstring(base)+L"\\EmberveilMawaqit";if(!CreateDirectoryW(dir.c_str(),nullptr)&&GetLastError()!=ERROR_ALREADY_EXISTS)fail("Cannot create cache folder");
 // Retain existing Hijri date metadata only if it is from the same mosque and day.
 std::string hijri="",hijriSource="unavailable";std::wstring old=dir+L"\\metadata.json";
 {HANDLE h=CreateFileW(old.c_str(),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);if(h!=INVALID_HANDLE_VALUE){DWORD sz=GetFileSize(h,nullptr);if(sz<65536){std::string data(sz,0);DWORD got=0;if(ReadFile(h,data.data(),sz,&got,nullptr)){try{Parser mp{data};J prev=mp.value();if(prev.key("mosqueIdentifier").s==narrow(slug)&&prev.key("localDate").s==date(now.wYear,now.wMonth,now.wDay)){hijri=prev.key("hijriDate").s;hijriSource=prev.key("hijriDateSource").s;}}catch(...){}}}CloseHandle(h);}}
 FILETIME ft;GetSystemTimeAsFileTime(&ft);SYSTEMTIME utc;GetSystemTime(&utc);char stamp[40];snprintf(stamp,sizeof(stamp),"%04u-%02u-%02uT%02u:%02u:%02uZ",utc.wYear,utc.wMonth,utc.wDay,utc.wHour,utc.wMinute,utc.wSecond);
 std::ostringstream meta;meta<<"{\n  \"schemaVersion\": 1,\n  \"mosqueName\": "<<quote(name)<<",\n  \"mosqueIdentifier\": "<<quote(narrow(slug))<<",\n  \"mosqueUrl\": "<<quote("https://mawaqit.net"+narrow(path))<<",\n  \"timezone\": "<<quote(tzVal.s)<<",\n  \"scheduleYear\": "<<year<<",\n  \"localDate\": "<<quote(date(now.wYear,now.wMonth,now.wDay))<<",\n  \"hijriDate\": "<<quote(hijri)<<",\n  \"hijriDateSource\": "<<quote(hijriSource)<<",\n  \"updatedAtUtc\": "<<quote(stamp)<<"\n}\n";
 std::wstring tmp1=dir+L"\\schedule.native.tmp",tmp2=dir+L"\\metadata.native.tmp";DeleteFileW(tmp1.c_str());DeleteFileW(tmp2.c_str());
 try{writeFile(tmp1,sched.str());writeFile(tmp2,meta.str());replace(tmp1,dir+L"\\schedule.txt");replace(tmp2,dir+L"\\metadata.json");}catch(...){DeleteFileW(tmp1.c_str());DeleteFileW(tmp2.c_str());throw;}
 return true;
}

}

static HANDLE g_updaterThread=nullptr, g_stopEvent=nullptr, g_settingsEvent=nullptr;

static SRWLOCK g_updaterLock = SRWLOCK_INIT;

static std::wstring g_mosque=L"masjidomar";

static int g_refreshHours=24;

static constexpr UINT WM_EMBERVEIL_UPDATED=WM_APP+42;

static constexpr UINT WM_EMBERVEIL_APPLY_SETTINGS=WM_APP+43;

struct SettingsSnapshot {
 int width=220, x=0, y=0, trayGap=8;
 int pillHeight=26, cornerRadius=13, pillPadding=12;
 int fontSize=15;
 int refreshHours=24;
 std::wstring mosque=L"masjidomar";
 std::wstring theme=L"emberveil";
 bool showNextPrayer=true, showCountdown=true, enablePopup=true;
};

static SettingsSnapshot ReadSettings() {
 SettingsSnapshot s;
 s.width=Wh_GetIntSetting(L"Width");if(s.width<180||s.width>400)s.width=220;
 s.x=Wh_GetIntSetting(L"OffsetX");s.y=Wh_GetIntSetting(L"OffsetY");
 s.trayGap=Wh_GetIntSetting(L"TrayGap");if(s.trayGap<0||s.trayGap>100)s.trayGap=8;
 s.pillHeight=Wh_GetIntSetting(L"PillHeight");if(s.pillHeight<12||s.pillHeight>30)s.pillHeight=26;
 s.fontSize=Wh_GetIntSetting(L"FontSize");
 if(s.fontSize<10||s.fontSize>24)s.fontSize=15;
 s.cornerRadius=Wh_GetIntSetting(L"CornerRadius");if(s.cornerRadius<0||s.cornerRadius>30)s.cornerRadius=13;
 s.pillPadding=Wh_GetIntSetting(L"PillPadding");if(s.pillPadding<0||s.pillPadding>40)s.pillPadding=12;
 PCWSTR mosque=Wh_GetStringSetting(L"Mosque");
 if(mosque){s.mosque=mosque;Wh_FreeStringSetting(mosque);}
  PCWSTR theme=Wh_GetStringSetting(L"Theme");
  if(theme){s.theme=theme;Wh_FreeStringSetting(theme);}
 s.refreshHours=Wh_GetIntSetting(L"RefreshHours");
 if(s.refreshHours<1||s.refreshHours>168)s.refreshHours=24;
 s.showNextPrayer=Wh_GetIntSetting(L"ShowNextPrayer")!=0;
 s.showCountdown=Wh_GetIntSetting(L"ShowCountdown")!=0;
 s.enablePopup=Wh_GetIntSetting(L"EnablePopup")!=0;
 return s;
}

static void ApplyUpdaterSettings(const SettingsSnapshot& s) {
 bool changed=false;
 AcquireSRWLockExclusive(&g_updaterLock);
 changed=(g_mosque!=s.mosque || g_refreshHours!=s.refreshHours);
 g_mosque=s.mosque;
 g_refreshHours=s.refreshHours;
 ReleaseSRWLockExclusive(&g_updaterLock);
 if(changed && g_settingsEvent)SetEvent(g_settingsEvent);
}

static HWND g_window=nullptr, g_popup=nullptr;

static bool g_lastMouseDown=false;
static bool g_showNextPrayer=true, g_showCountdown=true, g_enablePopup=true;

static std::wstring g_mosqueName=L"Mosque", g_hijriDate=L"";

static constexpr wchar_t kPopupClass[]=L"EmberveilMawaqitPrayerPopup";

static HANDLE g_thread=nullptr;

static DWORD g_threadId=0;

static int g_width=220,g_x=0,g_y=0,g_trayGap=8;

static int g_pillHeight=26,g_cornerRadius=13,g_pillPadding=12;

static int g_fontSize=15;

static constexpr wchar_t kClass[]=L"EmberveilMawaqitLiveWindow";

struct Prayer { std::wstring name; int minute; };

static const wchar_t* kNames[]={L"Fajr",L"Dhuhr",L"Asr",L"Maghrib",L"Isha"};

static std::wstring g_label=L"Loading schedule",g_countdown=L"--:--";

static std::wstring g_loadedDate;

static std::vector<Prayer> g_today,g_tomorrow;

static COLORREF Hex(unsigned int c){return RGB((c>>16)&255,(c>>8)&255,c&255);}

struct ThemePalette {
 COLORREF pillBackground, pillText, pillSeparator, pillCountdown;
 COLORREF popupBackground, popupBorder, popupText, popupMuted, popupRule, popupFooter;
};
static ThemePalette g_palette={
 Hex(0x211E32),Hex(0xF5E6C8),Hex(0xB8A98A),Hex(0xFFBC5E),
 Hex(0x1D1D2D),Hex(0x3B3B58),Hex(0xD3D0E8),Hex(0xB8B3D1),Hex(0x424158),Hex(0xA29DBB)
};
static ThemePalette EmberveilPalette(){return {
 Hex(0x211E32),Hex(0xF5E6C8),Hex(0xB8A98A),Hex(0xFFBC5E),
 Hex(0x1D1D2D),Hex(0x3B3B58),Hex(0xD3D0E8),Hex(0xB8B3D1),Hex(0x424158),Hex(0xA29DBB)
};}
static ThemePalette TraditionalPalette(){return {
 Hex(0x123D34),Hex(0xF5EAD3),Hex(0xC9B789),Hex(0xE4C784),
 Hex(0x102F29),Hex(0x527361),Hex(0xF5EAD3),Hex(0xC9B789),Hex(0x527361),Hex(0xE4C784)
};}
static ThemePalette CatppuccinMochaPalette(){return {
 Hex(0x211E32),Hex(0xCDD6F4),Hex(0xB4BEFE),Hex(0xCFA1FF),
 Hex(0x302D47),Hex(0x58536F),Hex(0xCDD6F4),Hex(0xA6ADC8),Hex(0x58536F),Hex(0xB4BEFE)
};}
static bool WindowsLightMode(){
 DWORD value=0,bytes=sizeof(value);
 HKEY key=nullptr;
 if(RegOpenKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",0,KEY_QUERY_VALUE,&key)!=ERROR_SUCCESS)return false;
 LONG result=RegQueryValueExW(key,L"AppsUseLightTheme",nullptr,nullptr,reinterpret_cast<BYTE*>(&value),&bytes);
 RegCloseKey(key);return result==ERROR_SUCCESS && value!=0;
}
static ThemePalette SystemPalette(){
 bool light=WindowsLightMode();
 COLORREF accent=GetSysColor(COLOR_HIGHLIGHT);
 if(light)return {Hex(0xF2F2F2),Hex(0x202020),Hex(0x686868),accent,
 Hex(0xFAFAFA),Hex(0xD1D1D1),Hex(0x202020),Hex(0x666666),Hex(0xD1D1D1),accent};
 return {Hex(0x292929),Hex(0xF4F4F4),Hex(0xB8B8B8),accent,
 Hex(0x202020),Hex(0x505050),Hex(0xF4F4F4),Hex(0xB8B8B8),Hex(0x505050),accent};
}
static COLORREF ParseHexColor(const std::wstring& s,COLORREF fallback){
 size_t i=(s.size()==7 && s[0]==L'#')?1:0;
 if(s.size()-i!=6)return fallback;
 unsigned value=0;
 for(;i<s.size();++i){wchar_t c=s[i];unsigned digit;
  if(c>=L'0'&&c<=L'9')digit=c-L'0';
  else if(c>=L'a'&&c<=L'f')digit=c-L'a'+10;
  else if(c>=L'A'&&c<=L'F')digit=c-L'A'+10;
  else return fallback;
  value=(value<<4)|digit;
 }
 return Hex(value);
}
static std::wstring StringSetting(PCWSTR name){
 PCWSTR p=Wh_GetStringSetting(name);
 if(!p)return L"";
 std::wstring result=p;Wh_FreeStringSetting(p);return result;
}
static ThemePalette ReadPalette(const std::wstring& theme){
 if(theme==L"traditional")return TraditionalPalette();
 if(theme==L"catppuccin")return CatppuccinMochaPalette();
 if(theme==L"system")return SystemPalette();
 ThemePalette p=EmberveilPalette();
 if(theme!=L"custom")return p;
 p.pillBackground=ParseHexColor(StringSetting(L"CustomPillBackground"),p.pillBackground);
 p.pillText=ParseHexColor(StringSetting(L"CustomPillText"),p.pillText);
 p.pillSeparator=ParseHexColor(StringSetting(L"CustomPillSeparator"),p.pillSeparator);
 p.pillCountdown=ParseHexColor(StringSetting(L"CustomPillCountdown"),p.pillCountdown);
 p.popupBackground=ParseHexColor(StringSetting(L"CustomPopupBackground"),p.popupBackground);
 p.popupBorder=ParseHexColor(StringSetting(L"CustomPopupBorder"),p.popupBorder);
 p.popupText=ParseHexColor(StringSetting(L"CustomPopupText"),p.popupText);
 p.popupMuted=ParseHexColor(StringSetting(L"CustomPopupMuted"),p.popupMuted);
 p.popupRule=ParseHexColor(StringSetting(L"CustomPopupRule"),p.popupRule);
 p.popupFooter=ParseHexColor(StringSetting(L"CustomPopupFooter"),p.popupFooter);
 return p;
}
static std::wstring g_theme=L"emberveil";

static std::wstring DateKey(const SYSTEMTIME& t){wchar_t b[16];swprintf(b,16,L"%04u-%02u-%02u",t.wYear,t.wMonth,t.wDay);return b;}

static std::wstring CachePath(){
 wchar_t base[MAX_PATH]={}; DWORD n=GetEnvironmentVariableW(L"LOCALAPPDATA",base,MAX_PATH);
 if(!n||n>=MAX_PATH)return L"";
 return std::wstring(base)+L"\\EmberveilMawaqit\\schedule.txt";
}

static std::wstring Utf8ToWide(const std::string& s) {
 int n=MultiByteToWideChar(CP_UTF8,0,s.data(),(int)s.size(),nullptr,0);
 if(n<=0)return L"";
 std::wstring result(n,L'\0');
 MultiByteToWideChar(CP_UTF8,0,s.data(),(int)s.size(),&result[0],n);
 return result;
}

// Minimal JSON string reader for the two fields written by our trusted updater.
// Handles standard JSON escapes and Unicode escapes, including surrogate pairs.

static std::wstring JsonField(const std::wstring& json,const wchar_t* key){
 std::wstring token=L"\""+std::wstring(key)+L"\"";
 size_t at=json.find(token);if(at==std::wstring::npos)return L"";
 at=json.find(L':',at+token.size());if(at==std::wstring::npos)return L"";
 at=json.find_first_not_of(L" \r\n\t",at+1);
 if(at==std::wstring::npos||json[at]!=L'"')return L"";
 std::wstring out;
 for(size_t i=at+1;i<json.size();i++){
  wchar_t c=json[i];if(c==L'"')break;
  if(c!=L'\\'){out+=c;continue;}
  if(++i>=json.size())break;
  c=json[i];
  if(c==L'u' && i+4<json.size()){
   unsigned code=0;bool valid=true;
   for(int j=0;j<4;j++){wchar_t h=json[i+1+j];unsigned v;
    if(h>=L'0'&&h<=L'9')v=h-L'0';
    else if(h>=L'a'&&h<=L'f')v=h-L'a'+10;
    else if(h>=L'A'&&h<=L'F')v=h-L'A'+10;
    else {valid=false;break;}code=code*16+v;
   }
   if(valid){out+=(wchar_t)code;i+=4;}continue;
  }
  switch(c){case L'n':out+=L'\n';break;case L'r':out+=L'\r';break;
   case L't':out+=L'\t';break;default:out+=c;break;}
 }
 return out;
}

static void LoadMetadata(){
 g_mosqueName=L"Mosque";g_hijriDate=L"";
 std::wstring path=CachePath();if(path.empty())return;
 size_t slash=path.find_last_of(L'\\');if(slash==std::wstring::npos)return;
 path=path.substr(0,slash+1)+L"metadata.json";
 std::ifstream f(path.c_str(),std::ios::binary);
 if(!f)return;
 std::string bytes((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());
 if(bytes.size()>65536)return;
 std::wstring json=Utf8ToWide(bytes);
 std::wstring name=JsonField(json,L"mosqueName");
 if(!name.empty())g_mosqueName=name;
 std::wstring hijri=JsonField(json,L"hijriDate");
 if(hijri.size()==10 && hijri[4]==L'-' && hijri[7]==L'-'){
  static const wchar_t* months[]={L"Muharram",L"Safar",L"Rabi' al-Awwal",L"Rabi' al-Thani",L"Jumada al-Ula",L"Jumada al-Akhirah",L"Rajab",L"Sha'ban",L"Ramadan",L"Shawwal",L"Dhu al-Qi'dah",L"Dhu al-Hijjah"};
  int month=_wtoi(hijri.substr(5,2).c_str()),day=_wtoi(hijri.substr(8,2).c_str());
  if(month>=1&&month<=12&&day>=1&&day<=30){
   wchar_t text[120];swprintf(text,120,L"%d %ls %ls AH",day,months[month-1],hijri.substr(0,4).c_str());g_hijriDate=text;
  }
 }
}

static bool ParseDay(const std::wstring& line,const std::wstring& date,std::vector<Prayer>& out){
 if(line.size()<date.size()+1||line.compare(0,date.size(),date)!=0||line[date.size()]!=L'|')return false;
 std::wistringstream s(line.substr(date.size()+1));std::wstring item;std::vector<Prayer> result;
 for(int i=0;i<5;i++){
  if(!std::getline(s,item,L'|')||item.size()!=5||item[2]!=L':'||item[0]<L'0'||item[0]>L'2'||item[1]<L'0'||item[1]>L'9'||item[3]<L'0'||item[3]>L'5'||item[4]<L'0'||item[4]>L'9')return false;
  int hour=(item[0]-L'0')*10+item[1]-L'0';int minute=(item[3]-L'0')*10+item[4]-L'0';if(hour>23)return false;
  result.push_back({kNames[i],hour*60+minute});
 }
 if(std::getline(s,item,L'|'))return false;
 out=result;return true;
}

static void LoadSchedule(const SYSTEMTIME& now){
 std::wstring today=DateKey(now);if(today==g_loadedDate)return;
 SYSTEMTIME next=now;
 FILETIME ft;SystemTimeToFileTime(&next,&ft);
 ULARGE_INTEGER v;v.LowPart=ft.dwLowDateTime;v.HighPart=ft.dwHighDateTime;v.QuadPart+=864000000000ULL;
 ft.dwLowDateTime=v.LowPart;ft.dwHighDateTime=v.HighPart;FileTimeToSystemTime(&ft,&next);
 std::wstring tomorrow=DateKey(next);
 std::wstring path=CachePath();
 std::wifstream file(path.c_str());if(!file)return;
 std::wstring line;std::vector<Prayer> a,b;
 while(std::getline(file,line)){
  if(a.empty())ParseDay(line,today,a);
  if(b.empty())ParseDay(line,tomorrow,b);
  if(!a.empty()&&!b.empty())break;
 }
 if(a.size()!=5)return;
 g_today=a;g_tomorrow=b;g_loadedDate=today;
}

static void UpdateCountdown(){
 SYSTEMTIME now;GetLocalTime(&now);LoadSchedule(now);
 if(g_today.empty()){g_label=L"Schedule unavailable";g_countdown=L"--:--";return;}
 int nowSec=now.wHour*3600+now.wMinute*60+now.wSecond;
 for(const auto& p:g_today){int sec=p.minute*60-nowSec;if(sec>0){
  wchar_t label[80],count[32];swprintf(label,80,L"%ls  %02d:%02d",p.name.c_str(),p.minute/60,p.minute%60);
  swprintf(count,32,L"%02d:%02d:%02d",sec/3600,(sec/60)%60,sec%60);
  g_label=label;g_countdown=count;return;
 }}
 if(!g_tomorrow.empty()){
  const auto& p=g_tomorrow.front();int sec=86400-nowSec+p.minute*60;
  wchar_t label[80],count[32];swprintf(label,80,L"%ls  %02d:%02d",p.name.c_str(),p.minute/60,p.minute%60);
  swprintf(count,32,L"%02d:%02d:%02d",sec/3600,(sec/60)%60,sec%60);
  g_label=label;g_countdown=count;
 }else{g_label=L"Tomorrow unavailable";g_countdown=L"--:--";}
}

static void PaintPopup(HWND hwnd){
 PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);RECT r{};GetClientRect(hwnd,&r);
 HDC mem=CreateCompatibleDC(dc);HBITMAP bmp=CreateCompatibleBitmap(dc,r.right,r.bottom);
 HGDIOBJ oldBmp=SelectObject(mem,bmp);
 HBRUSH clear=CreateSolidBrush(RGB(0,0,0));FillRect(mem,&r,clear);DeleteObject(clear);
 HBRUSH bg=CreateSolidBrush(g_palette.popupBackground);HGDIOBJ oldBrush=SelectObject(mem,bg);
 HPEN pen=CreatePen(PS_SOLID,1,g_palette.popupBorder);HGDIOBJ oldPen=SelectObject(mem,pen);
 RoundRect(mem,0,0,r.right,r.bottom,10,10);
 SelectObject(mem,oldPen);DeleteObject(pen);SelectObject(mem,oldBrush);DeleteObject(bg);
 SetBkMode(mem,TRANSPARENT);
 HFONT font=CreateFontW(-15,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH,L"Segoe UI");
 HGDIOBJ oldFont=SelectObject(mem,font);
 auto line=[&](const std::wstring& text,int left,int top,int right,int height,COLORREF color,UINT flags){
  RECT rect{left,top,right,top+height};SetTextColor(mem,color);
  DrawTextW(mem,text.c_str(),-1,&rect,flags|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX|DT_END_ELLIPSIS);
 };
 // Reserve two lines for long mosque names instead of truncating them.
 RECT nameRect{14,9,r.right-14,53};
 SetTextColor(mem,g_palette.popupText);
 DrawTextW(mem,g_mosqueName.c_str(),-1,&nameRect,DT_CENTER|DT_WORDBREAK|DT_NOPREFIX|DT_END_ELLIPSIS);
 line(g_hijriDate,14,54,r.right-14,19,g_palette.popupMuted,DT_CENTER);
 HPEN rule=CreatePen(PS_SOLID,1,g_palette.popupRule);HGDIOBJ prev=SelectObject(mem,rule);
 MoveToEx(mem,12,85,nullptr);LineTo(mem,r.right-12,85);
 MoveToEx(mem,12,218,nullptr);LineTo(mem,r.right-12,218);
 SelectObject(mem,prev);DeleteObject(rule);
 for(int i=0;i<5;i++){
  std::wstring time=L"--:--";
  if(i<(int)g_today.size()){
   wchar_t b[16];swprintf(b,16,L"%02d:%02d",g_today[i].minute/60,g_today[i].minute%60);time=b;
  }
  int y=92+i*25;
  line(kNames[i],20,y,r.right-20,23,g_palette.popupText,DT_LEFT);
  line(time,20,y,r.right-20,23,g_palette.popupText,DT_RIGHT);
 }
 std::wstring footer=g_label+L" - in "+g_countdown;
 line(footer,12,223,r.right-12,24,g_palette.popupFooter,DT_CENTER);
 SelectObject(mem,oldFont);DeleteObject(font);
 BitBlt(dc,0,0,r.right,r.bottom,mem,0,0,SRCCOPY);
 SelectObject(mem,oldBmp);DeleteObject(bmp);DeleteDC(mem);EndPaint(hwnd,&ps);
}

static LRESULT CALLBACK PopupProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp){
 switch(msg){
 case WM_NCHITTEST:return HTCLIENT;
 case WM_SETCURSOR:SetCursor(LoadCursorW(nullptr,IDC_ARROW));return TRUE;
 case WM_MOUSEACTIVATE:return MA_NOACTIVATE;
 case WM_ERASEBKGND:return 1;
 case WM_PAINT:PaintPopup(hwnd);return 0;
 case WM_CLOSE:ShowWindow(hwnd,SW_HIDE);return 0;
 case WM_DESTROY:if(g_popup==hwnd)g_popup=nullptr;return 0;
 }
 return DefWindowProcW(hwnd,msg,wp,lp);
}

static void PositionPopup(){
 if(!g_popup||!g_window)return;
 RECT pill{},work{};GetWindowRect(g_window,&pill);
 HMONITOR monitor=MonitorFromWindow(g_window,MONITOR_DEFAULTTONEAREST);
 MONITORINFO mi{};mi.cbSize=sizeof(mi);
 if(!GetMonitorInfoW(monitor,&mi))return;work=mi.rcWork;
 // Top-mounted taskbar: prefer below. Bottom-mounted: prefer above.
 RECT taskbar{};HWND bar=FindWindowW(L"Shell_TrayWnd",nullptr);
 if(bar)GetWindowRect(bar,&taskbar);
 constexpr int width=270,height=252;
 bool topBar=taskbar.top<=mi.rcMonitor.top+10;
 int x=pill.left+(pill.right-pill.left-width)/2;
 int y=topBar?taskbar.bottom+5:taskbar.top-height-5;
 if(x<mi.rcMonitor.left+4)x=mi.rcMonitor.left+4;
 if(x+width>mi.rcMonitor.right-4)x=mi.rcMonitor.right-width-4;
 if(y+height>mi.rcMonitor.bottom)y=mi.rcMonitor.bottom-height-4;
 if(y<mi.rcMonitor.top)y=mi.rcMonitor.top+4;
 SetWindowPos(g_popup,HWND_TOPMOST,x,y,width,height,SWP_NOACTIVATE|SWP_SHOWWINDOW);
}

static void TogglePopup(){
 if(!g_enablePopup||!g_popup)return;
 if(IsWindowVisible(g_popup)){ShowWindow(g_popup,SW_HIDE);return;}
 LoadMetadata();g_lastMouseDown=(GetAsyncKeyState(VK_LBUTTON)&0x8000)!=0;PositionPopup();InvalidateRect(g_popup,nullptr,FALSE);
}

static void Position(HWND hwnd) {
 HWND taskbar = GetParent(hwnd);
 if (!taskbar || !IsWindow(taskbar)) { ShowWindow(hwnd, SW_HIDE); return; }
 HWND tray = FindWindowExW(taskbar, nullptr, L"TrayNotifyWnd", nullptr);
 RECT trayRect{}, clientRect{};
 if (!tray || !GetWindowRect(tray, &trayRect) || !GetClientRect(taskbar, &clientRect)) {
  ShowWindow(hwnd, SW_HIDE); return;
 }
 POINT trayPoint{trayRect.left, trayRect.top};
 if (!ScreenToClient(taskbar, &trayPoint)) { ShowWindow(hwnd, SW_HIDE); return; }
 constexpr int height = 30;
 int x = trayPoint.x - g_width - g_trayGap + g_x;
 int y = (clientRect.bottom - clientRect.top - height) / 2 + g_y;
 if (x < 0 || x + g_width > clientRect.right) { ShowWindow(hwnd, SW_HIDE); return; }
 SetWindowPos(hwnd, HWND_TOP, x, y, g_width, height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

static DWORD WINAPI UpdateWorker(void*) {
 HANDLE events[]={g_stopEvent,g_settingsEvent};
 DWORD waitMs=0;
 for(;;) {
  DWORD result=WaitForMultipleObjects(2,events,FALSE,waitMs);
  if(result==WAIT_OBJECT_0 || result==WAIT_FAILED)return 0;
  if(result!=WAIT_TIMEOUT && result!=WAIT_OBJECT_0+1)return 0;
  std::wstring mosque;
  int hours;
  AcquireSRWLockShared(&g_updaterLock);
  mosque=g_mosque;
  hours=g_refreshHours;
  ReleaseSRWLockShared(&g_updaterLock);
  bool ok=false;
  try { ok=NativeUpdater::Run(mosque); }
  catch (const std::exception& e) { Wh_Log(L"[Emberveil] Update failed: %hs",e.what()); }
  catch (...) { Wh_Log(L"[Emberveil] Update failed (unknown error)"); }
  if(ok) {
   Wh_Log(L"[Emberveil] Schedule updated successfully");
   HWND taskbar=FindWindowW(L"Shell_TrayWnd",nullptr);
   HWND hwnd=taskbar?FindWindowExW(taskbar,nullptr,kClass,nullptr):nullptr;
   if(hwnd)PostMessageW(hwnd,WM_EMBERVEIL_UPDATED,0,0);
  }
  // A change during the HTTP request should not be lost.
  if(WaitForSingleObject(g_settingsEvent,0)==WAIT_OBJECT_0){waitMs=0;continue;}
  AcquireSRWLockShared(&g_updaterLock);
  hours=g_refreshHours;
  ReleaseSRWLockShared(&g_updaterLock);
  waitMs=(DWORD)(ok?hours:1)*60u*60u*1000u;
 }
}

static LRESULT CALLBACK Proc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp){
 switch(msg){
 case WM_EMBERVEIL_APPLY_SETTINGS:{
  const SettingsSnapshot* s=reinterpret_cast<const SettingsSnapshot*>(lp);
  if(!s)return 0;
  g_width=s->width;g_x=s->x;g_y=s->y;g_trayGap=s->trayGap;
  g_pillHeight=s->pillHeight;g_cornerRadius=s->cornerRadius;
  g_fontSize=s->fontSize;
  g_pillPadding=s->pillPadding;
  g_theme=s->theme;
  g_showNextPrayer=s->showNextPrayer;
  g_showCountdown=s->showCountdown;
  g_enablePopup=s->enablePopup;
  if(!g_enablePopup && g_popup && IsWindowVisible(g_popup))ShowWindow(g_popup,SW_HIDE);
  g_palette=ReadPalette(g_theme);
  Position(hwnd);
  InvalidateRect(hwnd,nullptr,FALSE);
  if(g_popup && IsWindowVisible(g_popup))PositionPopup();
  Wh_Log(L"[Emberveil] Visual settings applied live");
  return 0;
 }
 case WM_EMBERVEIL_UPDATED:
  g_loadedDate.clear();g_today.clear();g_tomorrow.clear();
  LoadMetadata();UpdateCountdown();
  InvalidateRect(hwnd,nullptr,FALSE);
  if(g_popup)InvalidateRect(g_popup,nullptr,FALSE);
  return 0;
 case WM_NCHITTEST:return HTCLIENT;
 case WM_SETCURSOR:SetCursor(LoadCursorW(nullptr,IDC_ARROW));return TRUE;
 case WM_MOUSEACTIVATE:return MA_NOACTIVATE;
 case WM_LBUTTONUP:TogglePopup();return 0;
 case WM_ERASEBKGND:return 1;
 case WM_PAINT:{
  PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);RECT r;GetClientRect(hwnd,&r);
  HDC mem=CreateCompatibleDC(dc);HBITMAP bmp=CreateCompatibleBitmap(dc,r.right,r.bottom);HGDIOBJ old=SelectObject(mem,bmp);
  // Black is the layered-window transparency key; the pill alone remains visible.
  HBRUSH clear=CreateSolidBrush(RGB(0,0,0));FillRect(mem,&r,clear);DeleteObject(clear);
  int top=(r.bottom-g_pillHeight)/2;
  RECT pill={2,top,r.right-2,top+g_pillHeight};
  int radius=g_cornerRadius;
  if(radius>g_pillHeight/2)radius=g_pillHeight/2;
  if(radius>(pill.right-pill.left)/2)radius=(pill.right-pill.left)/2;
  HBRUSH bg=CreateSolidBrush(g_palette.pillBackground);
  HGDIOBJ oldBrush=SelectObject(mem,bg);
  HGDIOBJ oldPen=SelectObject(mem,GetStockObject(NULL_PEN));
  if(radius>0)RoundRect(mem,pill.left,pill.top,pill.right,pill.bottom,radius*2,radius*2);
  else Rectangle(mem,pill.left,pill.top,pill.right,pill.bottom);
  SelectObject(mem,oldPen);SelectObject(mem,oldBrush);DeleteObject(bg);
  HFONT font=CreateFontW(
    -g_fontSize,0,0,0,FW_MEDIUM,
    FALSE,FALSE,FALSE,
    DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,
    DEFAULT_PITCH,L"Segoe UI"
  );
  HGDIOBJ oldfont=SelectObject(mem,font);SetBkMode(mem,TRANSPARENT);
  // Center the enabled text elements as one group; omit the separator unless both are shown.
  const bool showLabel=g_showNextPrayer;
  const bool showCount=g_showCountdown;
  const wchar_t* separator=L"·";
  SIZE labelSize{},separatorSize{},countSize{};
  if(showLabel)GetTextExtentPoint32W(mem,g_label.c_str(),(int)g_label.size(),&labelSize);
  if(showLabel&&showCount)GetTextExtentPoint32W(mem,separator,1,&separatorSize);
  if(showCount)GetTextExtentPoint32W(mem,g_countdown.c_str(),(int)g_countdown.size(),&countSize);
  constexpr int gap=7;
  int total=labelSize.cx+countSize.cx;
  if(showLabel&&showCount)total+=separatorSize.cx+2*gap;
  int x=(r.right-total)/2;
  if(x<g_pillPadding+2)x=g_pillPadding+2;
  if(showLabel){
   RECT labelRect={x,0,x+labelSize.cx,r.bottom};
   SetTextColor(mem,g_palette.pillText);
   DrawTextW(mem,g_label.c_str(),-1,&labelRect,DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_NOPREFIX);
   x+=labelSize.cx;
  }
  if(showLabel&&showCount){
   x+=gap;
   RECT separatorRect={x,0,x+separatorSize.cx,r.bottom};
   SetTextColor(mem,g_palette.pillSeparator);
   DrawTextW(mem,separator,-1,&separatorRect,DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_NOPREFIX);
   x+=separatorSize.cx+gap;
  }
  if(showCount){
   RECT countdownRect={x,0,x+countSize.cx,r.bottom};
   SetTextColor(mem,g_palette.pillCountdown);
   DrawTextW(mem,g_countdown.c_str(),-1,&countdownRect,DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_NOPREFIX);
  }
  BitBlt(dc,0,0,r.right,r.bottom,mem,0,0,SRCCOPY);SelectObject(mem,oldfont);DeleteObject(font);SelectObject(mem,old);DeleteObject(bmp);DeleteDC(mem);EndPaint(hwnd,&ps);return 0;
 }
 case WM_TIMER:{
  if(wp==1){
   UpdateCountdown();Position(hwnd);InvalidateRect(hwnd,nullptr,FALSE);
   if(g_popup&&IsWindowVisible(g_popup)){
    PositionPopup();InvalidateRect(g_popup,nullptr,FALSE);
   }
  }else if(wp==2){
   bool down=(GetAsyncKeyState(VK_LBUTTON)&0x8000)!=0;
   if(g_popup&&IsWindowVisible(g_popup)&&down&&!g_lastMouseDown){
    POINT p{};GetCursorPos(&p);RECT pill{},popup{};
    GetWindowRect(hwnd,&pill);GetWindowRect(g_popup,&popup);
    if(!PtInRect(&pill,p)&&!PtInRect(&popup,p))ShowWindow(g_popup,SW_HIDE);
   }
   g_lastMouseDown=down;
  }
  return 0;
 }
 case WM_CLOSE:DestroyWindow(hwnd);return 0;
 case WM_DESTROY:KillTimer(hwnd,1);KillTimer(hwnd,2);if(g_popup){DestroyWindow(g_popup);g_popup=nullptr;}PostQuitMessage(0);return 0;
 }
 return DefWindowProcW(hwnd,msg,wp,lp);
}

static DWORD WINAPI Thread(void*){
 g_palette=ReadPalette(g_theme);
 WNDCLASSEXW wc{};wc.cbSize=sizeof(wc);wc.lpfnWndProc=Proc;wc.hInstance=GetModuleHandleW(nullptr);wc.lpszClassName=kClass;wc.hCursor=LoadCursorW(nullptr,IDC_ARROW);
 if(!RegisterClassExW(&wc)&&GetLastError()!=ERROR_CLASS_ALREADY_EXISTS)return 1;
 HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
 if (!taskbar) return 2;
 HWND hwnd=CreateWindowExW(WS_EX_LAYERED,kClass,L"Emberveil Mawaqit",WS_CHILD|WS_VISIBLE,0,0,g_width,30,taskbar,nullptr,wc.hInstance,nullptr);
 if(!hwnd)return 2;
 WNDCLASSEXW popupClass{};popupClass.cbSize=sizeof(popupClass);
 popupClass.lpfnWndProc=PopupProc;popupClass.hInstance=wc.hInstance;popupClass.lpszClassName=kPopupClass;popupClass.hCursor=LoadCursorW(nullptr,IDC_ARROW);
 RegisterClassExW(&popupClass);
 g_popup=CreateWindowExW(WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE|WS_EX_TOPMOST|WS_EX_LAYERED,
  kPopupClass,L"Emberveil Prayer Times",WS_POPUP,0,0,270,252,nullptr,nullptr,wc.hInstance,nullptr);
 if(g_popup)SetLayeredWindowAttributes(g_popup,RGB(0,0,0),0,LWA_COLORKEY);
 LoadMetadata();
 SetLayeredWindowAttributes(hwnd,RGB(0,0,0),0,LWA_COLORKEY);g_window=hwnd;UpdateCountdown();Position(hwnd);SetTimer(hwnd,1,1000,nullptr);SetTimer(hwnd,2,50,nullptr);
 MSG msg;while(GetMessageW(&msg,nullptr,0,0)>0){TranslateMessage(&msg);DispatchMessageW(&msg);}g_window=nullptr;return 0;
}

BOOL Wh_ModInit(){
 Wh_Log(L"[Emberveil] Wh_ModInit called");
 SettingsSnapshot settings=ReadSettings();
 g_width=settings.width;g_x=settings.x;g_y=settings.y;
 g_trayGap=settings.trayGap;g_pillHeight=settings.pillHeight;
 g_cornerRadius=settings.cornerRadius;g_pillPadding=settings.pillPadding;
 g_fontSize=settings.fontSize;
 g_theme=settings.theme;
 g_showNextPrayer=settings.showNextPrayer;
 g_showCountdown=settings.showCountdown;
 g_enablePopup=settings.enablePopup;
 ApplyUpdaterSettings(settings);
 g_stopEvent=CreateEventW(nullptr,TRUE,FALSE,nullptr);
 if(!g_stopEvent)return FALSE;
 g_settingsEvent=CreateEventW(nullptr,FALSE,FALSE,nullptr);
 if(!g_settingsEvent){CloseHandle(g_stopEvent);g_stopEvent=nullptr;return FALSE;}
 g_thread=CreateThread(nullptr,0,Thread,nullptr,0,&g_threadId);
 if(!g_thread){CloseHandle(g_settingsEvent);g_settingsEvent=nullptr;CloseHandle(g_stopEvent);g_stopEvent=nullptr;return FALSE;}
 g_updaterThread=CreateThread(nullptr,0,UpdateWorker,nullptr,0,nullptr);
 if(!g_updaterThread)Wh_Log(L"[Emberveil] Could not start background updater");
 return TRUE;
}

void Wh_ModUninit(){
 if(g_stopEvent)SetEvent(g_stopEvent);
 if(g_updaterThread){WaitForSingleObject(g_updaterThread,INFINITE);CloseHandle(g_updaterThread);g_updaterThread=nullptr;}
 if(g_settingsEvent){CloseHandle(g_settingsEvent);g_settingsEvent=nullptr;}
 if(g_stopEvent){CloseHandle(g_stopEvent);g_stopEvent=nullptr;}
 HWND taskbar=FindWindowW(L"Shell_TrayWnd",nullptr);
 HWND hwnd=taskbar?FindWindowExW(taskbar,nullptr,kClass,nullptr):nullptr;
 if(hwnd)PostMessageW(hwnd,WM_CLOSE,0,0);
 if(g_thread){WaitForSingleObject(g_thread,3000);CloseHandle(g_thread);g_thread=nullptr;}
}

void Wh_ModSettingsChanged() {
    Wh_Log(L"[Emberveil] Settings callback reached!");
    SettingsSnapshot settings = ReadSettings();
    Wh_Log(
        L"[Emberveil] New Width setting: %d",
        settings.width
    );
    HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    HWND hwnd = taskbar
        ? FindWindowExW(taskbar, nullptr, kClass, nullptr)
        : nullptr;
    if (!hwnd) {
        Wh_Log(L"[Emberveil] Widget window not found");
        return;
    }
    SendMessageW(
        hwnd,
        WM_EMBERVEIL_APPLY_SETTINGS,
        0,
        reinterpret_cast<LPARAM>(&settings)
    );
    ApplyUpdaterSettings(settings);
    Wh_Log(L"[Emberveil] Settings update delivered");
}
