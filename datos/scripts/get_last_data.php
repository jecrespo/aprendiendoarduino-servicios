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
$ayer = strtotime($hoy)-86400;
$ayer = date("Y-n-d H:i:s",$ayer);

$result = mysql_query("SELECT * FROM Datos WHERE arduino=$arduino AND date BETWEEN '$ayer' AND '$hoy' ORDER BY date DESC LIMIT 1");

$row = mysql_fetch_array($result);

echo (strtotime($row['date']));
echo(":");
echo ($row['dato']);

mysql_close($conexion);
?> 