# WORDFENCE FALCON ENGINE CODE
#Match on gzip first because ordering matters.
location ~ "/site/wp-content/wfcache/.*gzip$" {
  gzip off;
  types {}
  default_type text/html;
  add_header Vary "Accept-Encoding, Cookie";
  add_header Content-Encoding gzip;
}
#If the previous matched, the following location won't be executed.
location ~ /site/wp-content/wfcache/.* {
  add_header Vary "Accept-Encoding, Cookie";
}
set $wordfenceCacheOn 1;

#Don't cache form submissions.
if ($request_method = POST) {
  set $wordfenceCacheOn 0;
}

#Allow caching of /?123=123 because this is a common DDoS to override caches.
if ($query_string !~ "^(?:\d+=\d+)?$") {
  set $wordfenceCacheOn 0;
}

#Only cache URL's ending in /
if ($request_uri !~ \/$) {
  set $wordfenceCacheOn 0;
}
#Don't cache any cookies with this in their names e.g. users who are logged in.
if ($http_cookie ~* "(comment_author|wp\-postpass|wf_logout|wordpress_logged_in|wptouch_switch_toggle|wpmp_switcher)") {
  set $wordfenceCacheOn 0;
}
set $wordfenceEncoding "";
#Oh, you want gzipped content?
if ($http_accept_encoding ~ gzip) {
  set $wordfenceEncoding _gzip;
}
set $wordfenceHTTPS "";
if ($scheme = 'https'){
  #If you want to ENABLE HTTPS caching, comment out the next line.
  set $wordfenceCacheOn 0; #Comment this line out to enable HTTPS caching.

  set $wordfenceHTTPS '_https'; #Uncomment this line to enable HTTPS caching.
}
#The main purpose of this line is to capture the URL components into variables.
if ($request_uri !~ "^\/*(?<wfone>[^\/]*)\/*(?<wftwo>[^\/]*)\/*(?<wfthree>[^\/]*)\/*(?<wffour>[^\/]*)\/*(?<wffive>[^\/]*)(?<wfsix>.*)$"){
  set $wordfenceCacheOn 0;
}
#If the file doesn't exist then don't serve from cache.
if (!-f "$document_root/site/wp-content/wfcache/${http_host}_${wfone}/${wftwo}~${wfthree}~${wffour}~${wffive}~${wfsix}_wfcache${wordfenceHTTPS}.html${wordfenceEncoding}") {
  set $wordfenceCacheOn 0;
}

if ($wordfenceCacheOn = 1) {
  rewrite .* "/site/wp-content/wfcache/${http_host}_${wfone}/${wftwo}~${wfthree}~${wffour}~${wffive}~${wfsix}_wfcache${wordfenceHTTPS}.html${wordfenceEncoding}" last;
}
# END Wordfence Rules

location / {
  try_files $uri $uri/ /index.php?$args;
}

include inc/deny-dot-files.inc;
