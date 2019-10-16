<?php

date_default_timezone_set('Europe/Berlin');	//Para usar la funciÃ³n date

function get_val ( $val )
{

	return $_GET[$val];

}

$arduino = get_val ("arduino");

$conexion = mysqli_connect("qvm602.aprendiendoarduino.com","qvm602","password","qvm602");

if (!$conexion) {
    echo "Error: No se pudo conectar a MySQL." . PHP_EOL;
    echo "errno de depuración: " . mysqli_connect_errno() . PHP_EOL;
    echo "error de depuración: " . mysqli_connect_error() . PHP_EOL;
    exit;
}

$hoy = date ("Y-n-d H:i:s");
$ayer = strtotime($hoy)-86400;
$ayer = date("Y-n-d H:i:s",$ayer);

$result_t = $conexion->query("SELECT * FROM Datos WHERE arduino=$arduino AND date BETWEEN '$ayer' AND '$hoy' ORDER BY date DESC LIMIT 1");

$row = mysqli_fetch_array($result_t);

echo (strtotime($row['date']));
echo(":");
echo ($row['dato']);

$conexion ->close();
?> 