<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('predis')) {
	dl('predis.' . PHP_SHLIB_SUFFIX);
}
$module = 'predis';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}

echo predis_connection('192.168.36.131',63788);

?>
