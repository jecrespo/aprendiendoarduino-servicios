<?php
//recojo variables
if(isset($_GET["arduino"]) && isset($_GET["dato"])){
	$arduino = $_GET["arduino"];
	$temperatura = $_GET["dato"];
}
else{
	echo("Faltan Datos");
	die();
}
//Crear conexión a la Base de Datos
$conexion = mysqli_connect("qvm602.aprendiendoarduino.com","qvm602","password","qvm602");

if (!$conexion) {
    echo "Error: No se pudo conectar a MySQL." . PHP_EOL;
    echo "errno de depuración: " . mysqli_connect_errno() . PHP_EOL;
    echo "error de depuración: " . mysqli_connect_error() . PHP_EOL;
    exit;
}

$query = "INSERT INTO Datos (date, arduino, dato) VALUES (CURRENT_TIMESTAMP, {$arduino}, {$temperatura})";
	
if (!$resultado = $conexion->query($query)) {
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
	
$conexion ->close();

echo ("GRABADOS");
?>