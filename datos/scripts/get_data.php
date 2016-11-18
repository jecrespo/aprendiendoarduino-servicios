<?php

date_default_timezone_set('Europe/Berlin');	//Para usar la función date

function get_val ( $val )
{

	return $_GET[$val];

}

$arduino = get_val ("arduino");

$conexion = mysql_connect("qvm602.aprendiendoarduino.com","qvm602","password");

if (!$conexion) {
  die('Could not connect: ' . mysql_error());
}

mysql_select_db("qvm602", $conexion);

$hoy = date ("Y-n-d H:i:s");
$ayer = strtotime($hoy)-7200;
$ayer = date("Y-n-d H:i:s",$ayer);

$result_t = mysql_query("SELECT * FROM Datos WHERE arduino=$arduino AND date BETWEEN '$ayer' AND '$hoy' ORDER BY date ASC");

$row = mysql_fetch_array($result_t);

while($row = mysql_fetch_array($result_t)) {
	echo (strtotime($row['date']));
	echo(":");
	echo ($row['dato']);
	echo(";");
}

mysql_close($conexion);
?> 