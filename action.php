<?php 
$lightswitch = intval($_POST['lightswitch']);
//shell_exec("let LIGHT_TOGGLE_VALUE = "$lightswitch);
shell_exec("echo $lightswitch | nc 10.216.183.183 80 -w1");
header('Location: ../lights');
?>
