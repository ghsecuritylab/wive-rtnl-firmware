#!/bin/sh

echo "Content-type: text/html"
echo ''
echo '<html>'
echo '<head><script type="text/javascript" src="/js/ajax.js"></script></head>'
echo '<body><script lang=\"JavaScript\">ajaxReloadDelayedPage(70000);</script></body>'
echo '</html>'

fs backup_nvram
fs save
sync
/etc/scripts/wifi_unload.sh && reboot &
