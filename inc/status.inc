server {
  server_name 127.0.0.1;
  listen 127.0.0.1:80;
  access_log off;
  error_log /var/log/nginx/status-error.log;
  include inc/defaults.inc;
  location /nginx_status {
    stub_status on;
    allow 127.0.0.1;
    deny all;
  }
  location /phpfpm_status {
    include fastcgi_params;
    fastcgi_pass $fastcgi_host:$fastcgi_port;
  }
}
