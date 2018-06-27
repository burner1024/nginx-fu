# Cache static files for as long as possible
location ~* .(ogg|ogv|svg|svgz|eot|otf|woff|woff2|mp4|ttf|css|rss|atom|js|jpg|jpeg|gif|png|ico|zip|tgz|gz|rar|bz2|doc|xls|exe|ppt|tar|mid|midi|wav|bmp|rtf)$ {
  expires max;
#  log_not_found off;
#  access_log off;
}
