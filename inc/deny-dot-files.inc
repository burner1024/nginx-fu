location ~ .well-known {}
location ~ /\. {
  deny  all;
}
