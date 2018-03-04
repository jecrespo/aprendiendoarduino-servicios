<?php
//recojo variables
$device = $_POST["device"];
$station = $_POST["station"];
$temperature = $_POST["temperature"];
$humidity = $_POST["humidity"];
$alarm = $_POST["alarm"];
$RSSI = $_POST["RSSI"];
$SNR = $_POST["SNR"];
$sequence = $_POST["sequence"];

//Crear conexion a la Base de Datos
$conexion = mysql_connect("qvm602.aprendiendoarduino.com","qvm602","password");
if (!$conexion){
	die("Fallo la conexi�n a la Base de Datos: " . mysql_error());
}
// Seleccionar la Base de Datos a utilizar
$seleccionar_bd = mysql_select_db("qvm602", $conexion);
if (!$seleccionar_bd) {
	die("Fallo la seleccion de la Base de Datos: " . mysql_error());
}
// compruebo que la conexion es corecta
if (!$conexion || !$seleccionar_bd) {
	die('Fallo la conexion o la seleccion de la Base de Datos: ');
}
$query = "INSERT INTO Sigfox (date, device, station, temperature, humidity, alarm, RSSI, SNR, sequence) VALUES (CURRENT_TIMESTAMP, '{$device}', '{$station}', {$temperature}, {$humidity}, {$alarm}, {$RSSI}, {$SNR}, {$sequence})";
	
$result = mysql_query($query,$conexion);
if (!$result) {
		die("Fallo en la insercion de registro en la Base de Datos: " . mysql_error());
	}

$arduino = 4;
$query_graf = "INSERT INTO Datos (date, arduino, dato) VALUES (CURRENT_TIMESTAMP, {$arduino}, {$temperature})";
$result = mysql_query($query_graf,$conexion);
if (!$result) {
		die("Fallo en la insercion de registro en la Base de Datos: " . mysql_error());
	}

if ($alarm == 1) {
	$nombre = "Sigfox " . $device;
	$mensaje = "Alerta de temperatura!";
	$query_alarm = "INSERT INTO Mensajes (date, nombre, mensaje) VALUES (CURRENT_TIMESTAMP, '{$nombre}', '{$mensaje}')";
	$result = mysql_query($query_alarm,$conexion);
	if (!$result) {
		die("Fallo en la insercion de registro en la Base de Datos: " . mysql_error());
	}
}

if ($alarm == 2) {
	$nombre = "Sigfox " . $device;
	$mensaje = "Temperatura normal. Alerta recuperada";
	$query_restore = "INSERT INTO Mensajes (date, nombre, mensaje) VALUES (CURRENT_TIMESTAMP, '{$nombre}', '{$mensaje}')";
	$result = mysql_query($query_restore,$conexion);
	if (!$result) {
		die("Fallo en la insercion de registro en la Base de Datos: " . mysql_error());
	}
}

mysql_close($conexion);
echo ("GRABADOS");
?>