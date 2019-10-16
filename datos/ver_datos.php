<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css" href="./css/style.css">
<link rel="stylesheet" type="text/css" href="./css/table.css">
</head>
<body>

<?php
function get_val ( $val )
{

	return $_GET[$val];

}

$sonda = get_val ("sensor");

$hoy = date ("Y-n-d H:i:s");
$ayer = strtotime($hoy)-86400;
$ayer = date("Y-n-d H:i:s",$ayer);
$query = "SELECT * FROM Datos WHERE arduino='$sonda' AND date BETWEEN '$ayer' AND '$hoy' ORDER BY date DESC";


imprime($query);

function imprime($query)
{
	
	// conexion a la BdD
	$conexion = mysqli_connect("qvm602.aprendiendoarduino.com","qvm602","password","qvm602");

	if (!$conexion) {
    	  echo "Error: No se pudo conectar a MySQL." . PHP_EOL;
    	  echo "errno de depuración: " . mysqli_connect_errno() . PHP_EOL;
    	  echo "error de depuración: " . mysqli_connect_error() . PHP_EOL;
    	  exit;
	}

	// lanzo la consulta
	if (!$result = $conexion->query($query)) {
    	// ¡Oh, no! La consulta falló. 
	    echo "Lo sentimos, este sitio web está experimentando problemas.";

    	// De nuevo, no hacer esto en un sitio público, aunque nosotros mostraremos
    	// cómo obtener información del error
    	  echo "Error: La ejecución de la consulta falló debido a: \n";
    	  echo "Query: " . $sql . "\n";
    	  echo "Errno: " . $mysqli->errno . "\n";
    	  echo "Error: " . $mysqli->error . "\n";
    	 exit;
	}
	
	// funcion para imprimir consultas 
	
	echo "<table border='2'>";
	echo "<tr>";
	// nÂº de campos y filas de la consulta
	echo ("<td> Numero Campos Consulta </td>");
	echo ("<td> Numero Filas Consulta </td>");
	echo "</tr>";
	
	echo "<tr>";
	$num = mysqli_num_fields($result);
	$num_row = mysqli_num_rows ($result);
	echo ("<td> $num </td>");
	echo ("<td> $num_row </td>");
	echo "</tr>";
	
	echo "</table> <br>";
	
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
			if (!$item){
				$item="-";
			}
			
			echo ("<td>$item</td>");
		}
		echo "</tr>";
	}
	echo "</table>";
	
	$conexion ->close();	
}

?>
</body>
</html>