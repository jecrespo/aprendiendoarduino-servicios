<?php
//Crear conexión a la Base de Datos
$conexion = mysql_connect("qvm602.aprendiendoarduino.com","qvm602","password");
if (!$conexion){
	die("Fallo la conexión a la Base de Datos: " . mysql_error());
}
// Seleccionar la Base de Datos a utilizar
$seleccionar_bd = mysql_select_db("qvm602", $conexion);
if (!$seleccionar_bd) {
	die("Fallo la selección de la Base de Datos: " . mysql_error());
}
// compruebo que la conexion es corecta
if (!$conexion || !$seleccionar_bd) {
	die('Fallo la conexión o la selección de la Base de Datos: ');
}

$hoy = date ("Y-n-d H:i:s");
$ayer = strtotime($hoy)-86400;
$ayer = date("Y-n-d H:i:s",$ayer);
$query = "SELECT date,remoteNum,txtMsg,delivered FROM SMS WHERE date > '$ayer' ORDER BY date DESC LIMIT 50";
	
$result = mysql_query($query,$conexion);
	
if (!$result) {
	die("Fallo en la consulta: " . mysql_error());
}
// Pinto los campos de la consulta
echo "<table border='2'>";
echo "<tr>";
while ($campo = mysql_fetch_field($result)){
	echo ("<td> <b> $campo->name </b> </td>");
}
echo "</tr>";
// recorro todas las filas y saco el NI y el comentario
while ($row = mysql_fetch_array($result,MYSQL_ASSOC)) {
	echo "<tr>";
	foreach ($row as $item){
		echo ("<td>$item</td>");
	}
	echo "</tr>";
}
echo "</table>";
mysql_close($conexion);	
?>