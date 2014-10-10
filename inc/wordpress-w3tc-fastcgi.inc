index index.php;

set $cache_uri $request_uri;

# POST requests and urls with a query string should always go to PHP
if ($request_method = POST) {
  set $cache_uri 'null cache';
}
if ($query_string != "") {
  set $cache_uri 'null cache';
}

# Don't cache uris containing the following segments
if ($request_uri ~* "(/wp-admin/|/xmlrpc.php|/wp-(app|cron|login|register|mail).php|wp-.*.php|/feed/|index.php|wp-comments-popup.php|wp-links-opml.php|wp-locations.php|sitemap(_index)?.xml|[a-z0-9_-]+-sitemap([0-9]+)?.xml)") {
  set $cache_uri 'null cache';
}

# Don't use the cache for logged in users or recent commenters
if ($http_cookie ~* "comment_author|wordpress_[a-f0-9]+|wp-postpass|wordpress_logged_in") {
  set $cache_uri 'null cache';
}

# Use cached or actual file if they exists, otherwise pass request to WordPress
location / {
  try_files /wp-content/cache/page_enhanced/${host}${cache_uri}_index.html $uri $uri/ /index.php?$args ;
}

location ~ ^/wp-content/cache/minify/[^/]+/(.*)$ {
  try_files $uri /wp-content/plugins/w3-total-cache/pub/minify.php?file=$1;
}

location = /favicon.ico { log_not_found off; access_log off; }
location = /robots.txt  { log_not_found off; access_log off; }

location ~ \.php$ {
  try_files $uri =404; 
  include fastcgi_params;
  fastcgi_pass $fastcgi_host:$fastcgi_port;
}

# Cache static files for as long as possible
location ~* .(ogg|ogv|svg|svgz|eot|otf|woff|mp4|ttf|css|rss|atom|js|jpg|jpeg|gif|png|ico|zip|tgz|gz|rar|bz2|doc|xls|exe|ppt|tar|mid|midi|wav|bmp|rtf)$ {
  expires max; log_not_found off; access_log off;
}

include inc/deny-dot-files.inc;