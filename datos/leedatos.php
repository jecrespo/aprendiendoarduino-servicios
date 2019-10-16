<?php
//Crear conexi�n a la Base de Datos
$conexion = mysqli_connect("qvm602.aprendiendoarduino.com","qvm602","password","qvm602");

if (!$conexion) {
    echo "Error: No se pudo conectar a MySQL." . PHP_EOL;
    echo "errno de depuraci�n: " . mysqli_connect_errno() . PHP_EOL;
    echo "error de depuraci�n: " . mysqli_connect_error() . PHP_EOL;
    exit;
}

$hoy = date ("Y-n-d H:i:s");
$ayer = strtotime($hoy)-86400;
$ayer = date("Y-n-d H:i:s",$ayer);
$query = "SELECT date,arduino,dato FROM  Datos WHERE date > '$ayer' ORDER BY date DESC LIMIT 30";
	
if (!$result = $conexion->query($query)) {
    // �Oh, no! La consulta fall�. 
    echo "Lo sentimos, este sitio web est� experimentando problemas.";

    // De nuevo, no hacer esto en un sitio p�blico, aunque nosotros mostraremos
    // c�mo obtener informaci�n del error
    echo "Error: La ejecuci�n de la consulta fall� debido a: \n";
    echo "Query: " . $sql . "\n";
    echo "Errno: " . $mysqli->errno . "\n";
    echo "Error: " . $mysqli->error . "\n";
    exit;
}

// Pinto los campos de la consulta
echo "<table border='2'>";
echo "<tr>";
while ($campo = mysqli_fetch_field($result)){
	echo ("<td> <b> $campo->name </b> </td>");
}
echo "</tr>";
// recorro todas las filas y saco el NI y el comentario
while ($row = mysqli_fetch_array($result,MYSQLI_ASSOC)) {
	echo "<tr>";
	foreach ($row as $item){
		echo ("<td>$item</td>");
	}
	echo "</tr>";
}
echo "</table>";
$conexion ->close();	
?>